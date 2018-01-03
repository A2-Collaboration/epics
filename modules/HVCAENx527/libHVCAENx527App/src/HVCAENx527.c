/* $Header: HVCAENx527/libHVCAENx527App/src/HVCAENx527.c 1.21.1.4 2014/04/30 16:10:08CST Ru Igarashi (igarasr) Exp  $
 *
 * Copyright Canadian Light Source, Inc.  All rights reserved.
 *    - see licence.txt and licence_CAEN.txt for limitations on use.
 */
/*
 * HVCAENx527.c:
 * "private" routines for network interface to CAEN x527 HV power
 * supply crates.  These are essentially the interface routines for
 * EPICS driver and device support routines to the CAEN-supplied
 * library.
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <epicsThread.h>
#include <dbDefs.h>
#include <dbAccess.h>
#include <dbScan.h>
#include <recSup.h>
#include <recGbl.h>
#include <devSup.h>
#include <menuScan.h>
#include <callback.h>
#include <sys/time.h>
#include <netdb.h>

#include <CAENHVWrapper.h>

#include "HVCAENx527.h"
extern char *strndup( const char *s, size_t n);

short DEBUG;
short Busy[MAX_CRATES];
epicsThreadId scanThread;

HVCRATE Crate[MAX_CRATES];

static char *ParUnitStr[] = {
	"",
	"A",
	"V",
	"W",
	"C",
	"Hz",
	"Bar",
	"V/s",
	"s",
	"rpm",
	"counts"
};

static struct timeval Timer1, Timer2, Timer3, TimerLong;
float Period1, Period2, Period3, PeriodLong;

/* Device args in the db records have format:
   "<devaddr> <par>"
   where <par> is the name of any HV channel parameter that has an 
   associated record.
   Device support address for the CAEN x527 HV crates are formatted:
   R.SS.CCC
   where R = crate number, SS = slot number, CCC = channel number,
   left padded with zeros.
   Return value type depends on whether operation is a crate, slot, 
   or channel operation.
*/
/* Why on Earth didn't I use the same kind of syntax as the other
   drivers, i.e. "Ca Sb Nc @parm"???  Consider changing this before
   the software propagates.
   Too late?
*/
void *
CAENx527ParseDevArgs( char *saddr)
{
	int i;
	short cr, sl, ch;
	char pnm[32];
	short narg;
	HVCHAN *hvch;
	void *retp;

	if( saddr == NULL || strlen( saddr) < 8)
		return( NULL);

	narg = sscanf( saddr, "%hd.%hd.%hd %s", &cr, &sl, &ch, pnm);
PDEBUG(4) printf( "DEBUG: parsed dev args: %s -> %hd %hd %hd %s\n", saddr, cr, sl, ch, pnm);
	if( narg != 4)
	{
		printf( "ParseDevArgs: Not enough args.\n");
		return( NULL);
	}

	/* search the crate list for crate cr */
	for( i = 0; i < MAX_CRATES && Crate[i].hvchan != NULL && Crate[i].crate != cr; i++);
	if( i >= MAX_CRATES || Crate[i].hvchan == NULL)
	{
		printf( "ParseDevArgs: No crate found\n");
		return( NULL);
	}
	if( Crate[i].hvchmap == NULL)
	{
		printf( "ParseDevArgs: Crate %d empty.\n", i);
		return( NULL);
	}
	if( Crate[i].hvchmap[sl].hvchan == NULL)
	{
		printf( "ParseDevArgs: Crate %d, Slot %hd empty.\n", i, sl);
		return( NULL);
	}
	if( Crate[i].hvchmap[sl].hvchan[ch] == NULL)
	{
		printf( "ParseDevArgs: Crate %d, Slot %hd, Channel %hd empty.\n", i, sl, ch);
		return( NULL);
	}

	hvch = Crate[i].hvchmap[sl].hvchan[ch];
	if( hvch == NULL)
		return( NULL);

	if( strcmp( pnm, "ChName") == 0)
	{
		retp = hvch;
	}
	else
	{
		/* Note: if parameter names need to be remapped, this loop will
		   be needed, so don't delete it, ru. */
		for( i = 0; i < hvch->npar && strcmp(hvch->pplist[i].pname, pnm) != 0; i++);
		if( i >= hvch->npar)
			return( NULL);
		retp = &(hvch->pplist[i]);
	}


	return( retp);
}

#if CAENHVWrapperVERSION / 100 == 2
static void
ReadChParProp( char *name, unsigned short slot, unsigned short chan, char *pname, PARPROP *pp)
#else
static void
ReadChParProp( int handle, unsigned short slot, unsigned short chan, char *pname, PARPROP *pp)
#endif	/* CAENHVWrapperVERSION */
{
	CAENHVRESULT retval;

	/* get type parameter's type */
#if CAENHVWrapperVERSION / 100 == 2
	retval = CAENHVGetChParamProp(name, slot, chan, pname, "Type", &(pp->Type));
#else
	retval = CAENHV_GetChParamProp(handle, slot, chan, pname, "Type", &(pp->Type));
#endif	/* CAENHVWrapperVERSION */
	if( retval != CAENHV_OK)
	{
#if CAENHVWrapperVERSION / 100 == 2
		printf( "CAENHVGetCHParamProp(): %s (%d)\n", CAENHVGetError( name), retval);
#else
		printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
	}

#if CAENHVWrapperVERSION / 100 == 2
	retval = CAENHVGetChParamProp(name, slot, chan, pname, "Mode", &(pp->Mode));
#else
	retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "Mode", &(pp->Mode));
#endif	/* CAENHVWrapperVERSION */
	if( retval != CAENHV_OK)
	{
#if CAENHVWrapperVERSION / 100 == 2
		printf( "CAENHVGetCHParamProp(): %s (%d)\n", CAENHVGetError( name), retval);
#else
		printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
	}

	if( pp->Type == PARAM_TYPE_NUMERIC)
	{
#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChParamProp(name, slot, chan, pname, "Minval", &(pp->Minval));
#else
		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "Minval", &(pp->Minval));
#endif	/* CAENHVWrapperVERSION */
		if( retval != CAENHV_OK)
		{
#if CAENHVWrapperVERSION / 100 == 2
			printf( "CAENHVGetCHParamProp(): %s (%d)\n", CAENHVGetError( name), retval);
#else
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
		}

#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChParamProp(name, slot, chan, pname, "Maxval", &(pp->Maxval));
#else
		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "Maxval", &(pp->Maxval));
#endif	/* CAENHVWrapperVERSION */
		if( retval != CAENHV_OK)
		{
#if CAENHVWrapperVERSION / 100 == 2
			printf( "CAENHVGetCHParamProp(): %s (%d)\n", CAENHVGetError( name), retval);
#else
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
		}

#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChParamProp(name, slot, chan, pname, "Unit", &(pp->Unit));
#else
		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "Unit", &(pp->Unit));
#endif	/* CAENHVWrapperVERSION */
		if( retval != CAENHV_OK)
		{
#if CAENHVWrapperVERSION / 100 == 2
			printf( "CAENHVGetCHParamProp(): %s (%d)\n", CAENHVGetError( name), retval);
#else
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
		}

#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChParamProp(name, slot, chan, pname, "Exp", &(pp->Exp));
#else
		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "Exp", &(pp->Exp));
#endif	/* CAENHVWrapperVERSION */
		if( retval != CAENHV_OK)
		{
#if CAENHVWrapperVERSION / 100 == 2
			printf( "CAENHVGetCHParamProp(): %s (%d)\n", CAENHVGetError( name), retval);
#else
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
		}

	}
	else if( pp->Type == PARAM_TYPE_ONOFF)
	{
#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChParamProp(name, slot, chan, pname, "Onstate", pp->Onstate);
#else
		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "Onstate", pp->Onstate);
#endif	/* CAENHVWrapperVERSION */
		if( retval != CAENHV_OK)
		{
#if CAENHVWrapperVERSION / 100 == 2
			printf( "CAENHVGetCHParamProp(): %s (%d)\n", CAENHVGetError( name), retval);
#else
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
		}

#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChParamProp(name, slot, chan, pname, "Offstate", pp->Onstate);
#else
		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "Offstate", pp->Onstate);
#endif	/* CAENHVWrapperVERSION */
		if( retval != CAENHV_OK)
		{
#if CAENHVWrapperVERSION / 100 == 2
			printf( "CAENHVGetCHParamProp(): %s (%d)\n", CAENHVGetError( name), retval);
#else
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
		}
	}
	else if( pp->Type == PARAM_TYPE_CHSTATUS)
	{
	}
	else if( pp->Type == PARAM_TYPE_BDSTATUS)
	{
	}
#if CAENHVWrapperVERSION / 100 == 2
/* Documented but not in header
	else if( pp->Type == PARAM_TYPE_ENUM)
	{
		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "MinVal", &(pp->Minval));
		if( retval != CAENHV_OK)
		{
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
		}

		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "MaxVal", &(pp->Maxval));
		if( retval != CAENHV_OK)
		{
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
		}

		retval = CAENHV_GetChParamProp( handle, slot, chan, pname, "Enum", &(pp->Enum));
		if( retval != CAENHV_OK)
		{
			printf( "CAENHV_GetCHParamProp(): %s (%d)\n", CAENHV_GetError( handle), retval);
		}
	}
*/
#endif	/* CAENHVWrapperVERSION */
}

/* There is support for scanning all channels in a crate sequentially,
   on a slot by slot basis, and by parameter name. 
   cr->hvchan is the sequential list,
   cr->hvchmap is a slot X channel matrix (with variable channel numbers),
   cr->csl is the  list by parameter name.
 */
static void
InitCrate( HVCRATE *cr)
{
	int i, j, k, l;
	unsigned short nsl, *nch;
	char *model, *desc;
	unsigned short *sn;
	unsigned char *fmwrmin, *fmwrmax;
	char *str;
	char *par, (*parnamelist)[MAX_PARAM_NAME];
	int npar;
	HVCHAN *hvch;
	CAENHVRESULT retval;

#if CAENHVWrapperVERSION / 100 == 2
	retval = CAENHVGetCrateMap( cr->name, &nsl, &nch, &model, &desc, &sn, &fmwrmin, &fmwrmax );
#else
	retval = CAENHV_GetCrateMap( cr->handle, &nsl, &nch, &model, &desc, &sn, &fmwrmin, &fmwrmax );
#endif	/* CAENHVWrapperVERSION */
	if( retval != CAENHV_OK)
	{
#if CAENHVWrapperVERSION / 100 == 2
		printf( "CAENHVGetCrateMap(): %s (%d)\n", CAENHVGetError( cr->name), retval);
#else
		printf( "CAENHV_GetCrateMap(): %s (%d)\n", CAENHV_GetError( cr->handle), retval);
#endif	/* CAENHVWrapperVERSION */
		return;
	}
	else
	{
		cr->connected = 1;
		/* Set up cratemap */
		cr->hvchmap = (HVSLOT *)calloc( sizeof( HVSLOT), nsl + 1);
		if( cr->hvchmap)
		{
			cr->nsl = nsl;
			cr->nchan = 0;
			str = model;
			for( i = 0; i < nsl; i++)
			{
				if( str[0] != '\0')
				{
					snprintf( cr->hvchmap[i].slname, MAX_BOARD_NAME, "%s", str);
PDEBUG(1) printf( "DEBUG: model %s in slot %d\n", str, i);
					cr->hvchmap[i].nchan = nch[i];
					cr->hvchmap[i].hvchan = (HVCHAN **)calloc( sizeof( HVCHAN *), nch[i] + 1);
					if( cr->hvchmap[i].hvchan == NULL)
					{
						printf( "DEBUG: failed to allocate mem for channel list for slot %hd\n", i);
						return;
					}
					for( j = 0; j <= nch[i]; j++)
					{
						cr->hvchmap[i].hvchan[j] = NULL;
					}
					cr->nchan += nch[i];
				}
				else
				{
					cr->hvchmap[i].hvchan = NULL;
				}
				str += strlen( str) + 1;
			}
		}
		else
		{
			printf( "DEBUG: failed to allocate mem for cratemap for crate %hd\n", cr->crate);
			return;
		}
PDEBUG(1) printf( "DEBUG: InitCrate(): found %d slots, with total of %d channels\n", cr->nsl, cr->nchan);
		/* Build sequential channel list and fill cratemap */
		cr->hvchan = (HVCHAN *)calloc( sizeof(HVCHAN), cr->nchan);
		if( cr->hvchan == NULL)
		{
			printf( "InitCrate: Failed to calloc channel list\n");
			return;
		}

		k = 0;
		str = model;
		for( i = 0; i < nsl; i++)
		{
			if( str[0] != '\0')
			{
				/* get parameters for each channel
				   and put into respective PV fields */
#if CAENHVWrapperVERSION / 100 == 2
				retval = CAENHVGetChParamInfo(cr->name, i, 0, &par);
#else
				retval = CAENHV_GetChParamInfo(cr->handle, i, 0, &par, &npar);
#endif	/* CAENHVWrapperVERSION */
				if( retval != CAENHV_OK)
				{
					return;
				}
				parnamelist = (char (*)[MAX_PARAM_NAME])par;

				for( j = 0; parnamelist[j][0]; j++);
				npar = j;
PDEBUG(3) printf( "DEBUG: number of parameters for each channel: %d\n", npar);

				for( j = 0; j < nch[i]; j++)
				{
					hvch = &(cr->hvchan[k]);
					hvch->crate = &(cr->crate);
					hvch->slot = i;
					hvch->chan = j;
					hvch->epicsenabled = 0;
					hvch->npar = npar;
					snprintf( hvch->chaddr, 10, "%1d%02d%03d", cr->crate, hvch->slot, hvch->chan);

					hvch->pplist = (PARPROP *)calloc( sizeof(PARPROP), hvch->npar);
					if( hvch->pplist == NULL)
					{
						printf( "InitCrate: Failed to calloc parameter property list.\n");
						return;
					}
					cr->hvchmap[i].hvchan[j] = hvch;
					hvch->hvcrate = cr;

					for( l = 0; l < hvch->npar; l++)
					{
						strncpy( hvch->pplist[l].pname, parnamelist[l], MAX_PARAM_NAME);
PDEBUG(4) printf( "DEBUG: paramname %s\n", parnamelist[l]);
#if CAENHVWrapperVERSION / 100 == 2
						ReadChParProp( cr->name, hvch->slot, hvch->chan, hvch->pplist[l].pname, &(hvch->pplist[l]));
#else
						ReadChParProp( cr->handle, hvch->slot, hvch->chan, hvch->pplist[l].pname, &(hvch->pplist[l]));
#endif	/* CAENHVWrapperVERSION */
						hvch->pplist[l].hvchan = hvch;
					}
					k++;
				}
				free( parnamelist);
			}
			str += strlen( str) + 1;
		}
	}
	free( nch);
	free( model);
	free( desc);
	free( sn);
	free( fmwrmin);
	free( fmwrmax);
}

#if CAENHVWrapperVERSION / 100 == 2
int
ConnectCrate( char *name, char *linkaddr, char *user, char *pw)
#else
int
ConnectCrate( char *name, char *linkaddr, CAENHV_SYSTEM_TYPE_t type, char *user, char *pw)
#endif	/* CAENHVWrapperVERSION */
{
	int i;
	CAENHVRESULT retval;
#if CAENHVWrapperVERSION >= 2
	int handle;
#endif	/* CAENHVWrapperVERSION */

#if CAENHVWrapperVERSION / 100 == 2
	if( name == NULL || name[0] == '\0' || linkaddr[0] == '\0')
	{
		printf( "ConnectCrate(): lacking crate name or address\n");
		return -1;
	}
#else
	if( ( linkaddr == NULL) || ( linkaddr[0] == '\0'))
	{
		printf( "ConnectCrate(): lacking crate's address\n");
		return -1;
	}
#endif	/* CAENHVWrapperVERSION */


	/* TCP/IP connection to crates */
#if CAENHVWrapperVERSION / 100 == 2
	/*        retval = CAENHVInitSystem( name, LINKTYPE_TCPIP, (void *)linkaddr, "admin", "admin");*/
	retval = CAENHVInitSystem( name, LINKTYPE_TCPIP, (void *)linkaddr, user,pw);
#else
	/*        retval = CAENHV_InitSystem( type, LINKTYPE_TCPIP, (void *)linkaddr, "admin", "admin", &handle);*/
	retval = CAENHV_InitSystem( type, LINKTYPE_TCPIP, (void *)linkaddr, user,pw, &handle);
#endif	/* CAENHVWrapperVERSION */
	printf( "Connected to crate %s@%s\n", name, linkaddr);
	if( retval == CAENHV_OK)
	{
		i = 0;
		while( i < MAX_CRATES && Crate[i].hvchan != NULL) i++;
		if( i < MAX_CRATES)
		{
			Crate[i].crate = i;
			snprintf( Crate[i].name, 63, "%s", name);
			snprintf( Crate[i].IPaddr, 63, "%s", linkaddr);
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
			Crate[i].handle = handle;
			Crate[i].type = type;
#endif	/* CAENHVWrapperVERSION */
			/* get list of boards */
			InitCrate( &(Crate[i]));
			return( 0);
		}
	}
	else
	{
#if CAENHVWrapperVERSION / 100 == 2
		printf( "CAENHVInitSystem(): %s (%d)\n", CAENHVGetError( name), retval);
#else
		printf( "CAENHV_InitSystem(): %s (%d)\n", CAENHV_GetError( handle), retval);
#endif	/* CAENHVWrapperVERSION */
	}
	return( -1);
}

void
ParseCrateAddr( char (*straddr)[255], short naddr)
{
	int i, j;
	int crnlen;
	char *str;
	char crname[32], craddr[32], crip[32];
	char user[32],pw[32],*ptru,*ptrpw; /*kl mod to allow %user%pw tagger on end of ip address */
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
	int type;
#endif	/* CAENHVWrapperVERSION */
	struct hostent *hostip;

	if( straddr)
	{
	        for( i = 0; i < naddr; i++)
		{
			str = straddr[i];

                        /*kl mod to allow %user%pw tagger on end of ip address */
			sprintf(user,"admin");  /*default to admin,admin */
			sprintf(pw,"admin");
			ptru=strstr(str,"%");
			if(ptru){
			  ptrpw=strstr(ptru+1,"%");
			}
			if(ptru&&ptrpw){
			  sprintf(pw,ptrpw+1);
			  sprintf(ptrpw,"");
			  sprintf(user,ptru+1);
			  sprintf(ptru,"");
			}
                        /*fprintf(stderr,"str= %s, user= %s, pw= %s\n",str,user,pw);*/
                        /*kl mod end */

			crnlen = strlen( str);
			for( j = 0; j < crnlen && str[j] != '@'; j++);
			snprintf( crname, ++j, "%s", str);
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
			type = ParseSystemType( crname);
			if( type < 0)
				exit( -2);
#endif	/* CAENHVWrapperVERSION */
			if( j < crnlen)
			{
				str += j;
				crnlen -= j;
				for( j = 0; j < crnlen && straddr[i][j] != ':'; j++);
				snprintf( craddr, ++j, "%s", str);
				hostip = gethostbyname( craddr);
				if( hostip->h_addrtype == AF_INET)
				{
			/* RU! There has to be a more elegant way of
			converting the IP to string... inet_*()? */
					snprintf( crip, 32, "%hd.%hd.%hd.%hd", (unsigned char)(hostip->h_addr[0]), (unsigned char)(hostip->h_addr[1]), (unsigned char)(hostip->h_addr[2]), (unsigned char)(hostip->h_addr[3]));
				}
				else
				{
					printf( "IPv6 addresses are not supported");
					exit( -1);
				}
PDEBUG(1) printf( "DEBUG: resolve %s -> %s (%s,%s,%d)\n", craddr, crip, hostip->h_name, hostip->h_addr, hostip->h_length);
			}
			if( j < crnlen)
			{
				str += j;
				crnlen -= j;
					printf( "slot option currently not supported: %s\n", str);
			}
#if CAENHVWrapperVERSION / 100 == 2
			/*                        if( ConnectCrate( crname, crip) == 0)*/
			if( ConnectCrate( crname, crip, user, pw) == 0)
#else
			  /*			  if( ConnectCrate( crname, crip, type) == 0)*/
			  if( ConnectCrate( crname, crip, type, user, pw) == 0)
#endif	/* CAENHVWrapperVERSION / 100 */
			{
				printf( "Successfully connected to %s @ %s\n", crname, craddr);
			}
		}
	}
}

#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
int
ParseSystemType( char *strtype)
{
	if( strncasecmp( strtype, "SY1527", 6) == 0)
		return SY1527;
	else if( strncasecmp( strtype, "SY2527", 6) == 0)
		return SY2527;
	else if( strncasecmp( strtype, "SY4527", 6) == 0)
		return SY4527;
	else if( strncasecmp( strtype, "SY5527", 6) == 0)
		return SY5527;
	else if( strncasecmp( strtype, "N568", 4) == 0)
		return N568;
	else if( strncasecmp( strtype, "V65XX", 5) == 0)
		return V65XX;
	else if( strncasecmp( strtype, "N1470", 5) == 0)
		return N1470;
	else if( strncasecmp( strtype, "V8100", 5) == 0)
		return V8100;
	else
	{
		printf( "ParseSystemType: %s is not a recognized system type.  Trying SY1527.", strtype);
		return -1;
	}
}
#endif	/* CAENHVWrapperVERSION */

short
CAENx527GetConnectionStatus( short cr)
{
	short retval;

	if( ( cr < MAX_CRATES) && ( Crate[cr].hvchan))
		retval = Crate[cr].connected;
	else
		retval = 0;

	return( retval);
}

/* This function should be used sparingly, if at all. */
void *
CAENx527GetChParVal( PARPROP *pp)
{
	union
	{
		float f;
		int l;
		double d;
		short s;
		char *c;
	} value;
	HVCHAN *hvch;
	CAENHVRESULT retval;

	if( pp == NULL || pp->hvchan->epicsenabled == 0)
		return( NULL);

	hvch = pp->hvchan;

	while( Busy[*(hvch->crate)])
		epicsThreadSleep(0.01);

	/* get value of one parameter */
	Busy[*(hvch->crate)] = 1;


	if( pp->Type == PARAM_TYPE_NUMERIC)
	{
#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChParam( hvch->hvcrate->name, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(value.f));
		
#else
		retval = CAENHV_GetChParam( hvch->hvcrate->handle, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(value.f));

#endif	/* CAENHVWrapperVERSION */
		if( retval != CAENHV_OK)
			return NULL;
		pp->pval.f = value.f;
	}
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
/* Documented but not in header
	else if( pp->Type == PARAM_TYPE_ENUM)
	{
		retval = CAENHV_GetChParam( hvch->hvcrate->handle, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(value.s));
		if( retval != CAENHV_OK)
			return NULL;
		pp->pval.s = value.s;
	}
*/
	else if( pp->Type == PARAM_TYPE_STRING)
	{
		retval = CAENHV_GetChParam( hvch->hvcrate->handle, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(value.c));
		if( retval != CAENHV_OK)
			return NULL;
		pp->pval.c = strndup( value.c, MAX_VAL_STRING);
	}
#endif	/* CAENHVWrapperVERSION */
	else
	{
#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChParam( hvch->hvcrate->name, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(value.l));
#else
		retval = CAENHV_GetChParam( hvch->hvcrate->handle, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(value.l));
#endif	/* CAENHVWrapperVERSION */
		if( retval != CAENHV_OK)
			return NULL;
		pp->pval.l = value.l;
	}
	Busy[*(hvch->crate)] = 0;

	/* We also pass the value to the calling routine because the final 
	   type and value often depends on the EPICS PV definition */
	return( &(pp->pval));
}

int
CAENx527SetChParVal( PARPROP *pp)
{
	HVCHAN *hvch;
	CAENHVRESULT retval;

	if( pp == NULL || pp->hvchan->epicsenabled == 0)
		return( 3);

	hvch = pp->hvchan;

	while( Busy[*(hvch->crate)])
		epicsThreadSleep( 0.01);

	/* set value of one parameter */
	Busy[*(hvch->crate)] = 1;
#if CAENHVWrapperVERSION / 100 == 2
	if( pp->Type == PARAM_TYPE_NUMERIC)
	{
		retval = CAENHVSetChParam( hvch->hvcrate->name, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(pp->pvalset.f));
	}
	else
	{
		retval = CAENHVSetChParam( hvch->hvcrate->name, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(pp->pvalset.l));
	}
#else	/* CAENHVWrapperVERSION */
	if( pp->Type == PARAM_TYPE_NUMERIC)
	{
		retval = CAENHV_SetChParam( hvch->hvcrate->handle, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(pp->pvalset.f));
	}
/* Documented but not in header
	else if( pp->Type == PARAM_TYPE_ENUM)
	{
		retval = CAENHV_SetChParam( hvch->hvcrate->handle, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(pp->pvalset.s));
	}
*/
	else if( pp->Type == PARAM_TYPE_STRING)
	{
		retval = CAENHV_SetChParam( hvch->hvcrate->handle, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(pp->pvalset.c));
	}
	else
	{
		retval = CAENHV_SetChParam( hvch->hvcrate->handle, hvch->slot, pp->pname, 1, (unsigned short *)&(hvch->chan), &(pp->pvalset.l));
	}
#endif	/* CAENHVWrapperVERSION */
	Busy[*(hvch->crate)] = 0;

	if( retval != CAENHV_OK)
		return( 3);
	
	/* get feedback about setting in crate, so user can verify
	   setpoint was successfully set.
	   Note: this is prone to occasional lag at the crate. */
	if( CAENx527GetChParVal( pp) == NULL)
		return( 4);

	return( 0);
}

/* in the given crate, for all channels that have the given parameter, 
   and which have a PV, get their values in one call */
int
CAENx527GetAllChParVal( HVCRATE *cr, char *pname)
{
	int i, j;
	int nset;
	int pnum;
	unsigned long type;
	short *chlist;
	/* 4-byte data */
	union pval
	{
		float f;
		int l;
	} *pval;
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
	/* 2-byte data */
	union pval2
	{
		short s;
	} *pval2;
	/* 8-byte data */
	union pval8
	{
		double f;
	} *pval8;
	/* arch-dependent-sized data */
	union pvala
	{
		long l;
		char *c;
	} *pvala;
#endif	/* CAENHVWrapperVERSION */
	HVCHAN *hvch;
	CAENHVRESULT retval;
	int rval;

	if( cr == NULL || cr->hvchan == NULL || cr->connected == 0)
		return( 3);

	rval = 0;
	/* We have to do this one slot at a time since modules may vary */
	for( i = 0; i < cr->nsl; i++)
	{
		while( Busy[cr->crate])
			epicsThreadSleep( 0.01);

		Busy[cr->crate] = 1;
		/* Build the list of channels to change in this slot */
		nset = 0;
		pnum = 9999;
		type = PARAM_TYPE_NUMERIC;
/* RU!  This degree of nested blocks is ridiculous! */
		if( cr->hvchmap[i].nchan)
		{
			hvch = cr->hvchmap[i].hvchan[0];

			chlist = (short *)calloc( sizeof(short), cr->nchan);
			if( chlist == NULL)
			{
				printf( "GetAllChParVal: Failed to calloc channel list.\n");
				return( 3);
			}
			for( j = 0; j < hvch->npar && strcmp( hvch->pplist[j].pname, pname) != 0; j++);
			pnum = j;
			type = hvch->pplist[j].Type;
			for( j = 0; j < cr->hvchmap[i].nchan; j++)
			{
				hvch = cr->hvchmap[i].hvchan[j];
				if( hvch->epicsenabled)
				{
					if( pnum < hvch->npar)
					{
						chlist[nset] = j;
						nset++;
					}
				}
				else
				{
					pnum = hvch->npar;
				}
			}
			if( nset)
			{
/* Note: allocating and building these lists repeatedly is not efficient.
   This should really be done once at init_record. */
				pval = NULL;
#if CAENHVWrapperVERSION / 100 == 2
				pval = (union pval *)calloc( sizeof(union pval), cr->nchan);
				if( pval == NULL)
				{
					printf( "GetAllChParVal: Failed to calloc value list.\n");
					return( 3);
				}
				retval = CAENHVGetChParam( cr->name, i, pname, nset, chlist, pval);
#else /* CAENHVWrapperVERSION */
				pval8 = NULL;
				pval2 = NULL;
				pvala = NULL;
				if( type == PARAM_TYPE_STRING)
				{
					pvala = (union pvala *)calloc( sizeof(union pvala), cr->nchan);
					if( pvala == NULL)
					{
						printf( "GetAllChParVal: Failed to calloc value list.\n");
						return( 3);
					}
					retval = CAENHV_GetChParam( cr->handle, (ushort)i, pname, (ushort)nset, (ushort*)chlist, pvala);
				}
/* Documented but not in header
				else if( type == PARAM_TYPE_ENUM)
				{
					pval2 = (union pval2 *)calloc( sizeof(union pval2), cr->nchan);
					if( pval2 == NULL)
					{
						printf( "GetAllChParVal: Failed to calloc value list.\n");
						return( 3);
					}
					retval = CAENHV_GetChParam( cr->handle, (ushort)i, pname, (ushort)nset, (ushort*)chlist, pval2);
				}
*/
				else
				{
					pval = (union pval *)calloc( sizeof(union pval), cr->nchan);
					if( pval == NULL)
					{
						printf( "GetAllChParVal: Failed to calloc value list.\n");
						return( 3);
					}
					retval = CAENHV_GetChParam( cr->handle, (ushort)i, pname, (ushort)nset, (ushort*)chlist, pval);
				}
#endif	/* CAENHVWrapperVERSION */
				/* Now parse the return using the channel list for indeces */
				if( retval == CAENHV_OK)
				{
					for( j = 0; j < nset; j++)
					{
						hvch = cr->hvchmap[i].hvchan[chlist[j]];
						if( pnum < hvch->npar)
						{
							if( type == PARAM_TYPE_NUMERIC)
								hvch->pplist[pnum].pval.f = pval[chlist[j]].f;
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
/* Documented but not in header
							else if( type == PARAM_TYPE_ENUM)
								hvch->pplist[pnum].pval.s = pval2[chlist[j]].s;
*/
							else if( type == PARAM_TYPE_STRING)
								hvch->pplist[pnum].pval.c = strndup( pvala[chlist[j]].c, MAX_VAL_STRING);
#endif	/* CAENHVWrapperVERSION */
							else
								hvch->pplist[pnum].pval.l = pval[chlist[j]].l;
						/* RU!  Do we push the value to the PV or
						   let it scan for it? */
#if 0
							/* push value to PV VAL field */
							if( hvch->pplist[pnum].PVaddr.precord == NULL)
								dbNameToAddr( hvch->pplist[pnum].PVname, &(hvch->pplist[pnum].PVaddr));
							if( hvch->pplist[pnum].PVaddr.precord != NULL)
							{
								union
								{
									float f;
									long l;
									double d;
									short s;
								} pval;
								if( type == PARAM_TYPE_NUMERIC)
								{
									pval.d = hvch->pplist[pnum].pval.f;
									dbPutField( &(hvch->pplist[pnum].PVaddr), DBR_DOUBLE, &(pval.d), 1);
								}
								else
								{
								}
							}
#endif
						}
					}
				}
				else if( retval == CAENHV_TIMEERR)
				{
					cr->connected = 0;
					printf( "Lost connection to %s@%s\n", Crate[i].name, Crate[i].IPaddr);
#if CAENHVWrapperVERSION / 100 == 2
					CAENHVDeinitSystem( cr->name);
#else
					CAENHV_DeinitSystem( cr->handle);
#endif	/* CAENHVWrapperVERSION */
					rval = 4;
				}
				else
				{
					rval = 3;
				}
#if CAENHVWrapperVERSION / 100 == 2
				free( pval);
#else
				if( type == PARAM_TYPE_STRING)
					free( pvala);
				else
					free( pval);
#endif	/* CAENHVWrapperVERSION */
			}
			free( chlist);
		}
		else
		{
			rval = 3;
		}
		Busy[cr->crate] = 0;
	}
	return( rval);
}

/* in the given crate, for all channels that have the given parameter, 
   and which have a PV, set them in one call, with the given value */
int
CAENx527SetAllChParVal( HVCRATE *cr, char *pname, void *val)
{
	int i, j;
	int nset;
	int pnum;
	unsigned long type;
	short *chlist;
	union pval
	{
		float f;
		int l;
	} *pval;
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
	/* 2-byte data */
	union pval2
	{
		short s;
	} *pval2;
	/* 8-byte data */
	union pval8
	{
		double f;
	} *pval8;
	/* arch-dependent-sized data */
	union pvala
	{
		long l;
		char *c;
	} *pvala;
#endif	/* CAENHVWrapperVERSION */
	HVCHAN *hvch;
	CAENHVRESULT retval;

	if( cr == NULL || cr->hvchan == NULL || cr->connected == 0)
		return( 3);

	/* We have to do this one slot at a time since modules may vary */
	for( i = 0; i < cr->nsl; i++)
	{
		while( Busy[cr->crate])
			epicsThreadSleep( 0.01);

		Busy[cr->crate] = 1;

/* Note: allocating and building these lists repeatedly is not efficient.
   This should really be done once at init_record. */
		pval = NULL;
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
		pval8 = NULL;
		pval2 = NULL;
		pvala = NULL;
#endif	/* CAENHVWrapperVERSION */
		chlist = (short *)calloc( sizeof(short), cr->nchan);
		if( chlist == NULL)
		{
			printf( "SetAllChParVal: Failed to calloc channel list.\n");
			return( 3);
		}
#if CAENHVWrapperVERSION / 100 == 2
		pval = (union pval *)calloc( sizeof(union pval), cr->nchan);
		if( pval == NULL)
		{
			printf( "SetAllChParVal: Failed to calloc value list.\n");
			return( 3);
		}
#else	/* CAENHVWrapperVERSION */
		hvch = cr->hvchmap[i].hvchan[0];
		for( j = 0; j < hvch->npar && strcmp( hvch->pplist[j].pname, pname) != 0; j++);
		pnum = j;
		type = hvch->pplist[pnum].Type;
		if( type == PARAM_TYPE_STRING)
		{
			pvala = (union pvala *)calloc( sizeof(union pvala), cr->nchan);
			if( pvala == NULL)
			{
				printf( "SetAllChParVal: Failed to calloc value list.\n");
				return( 3);
			}
		}
/* Documented but not in header
		if( type == PARAM_TYPE_ENUM)
		{
			pval2 = (union pval2 *)calloc( sizeof(union pval2), cr->nchan);
			if( pval2 == NULL)
			{
				printf( "SetAllChParVal: Failed to calloc value list.\n");
				return( 3);
			}
		}
*/
		else
		{
			pval = (union pval *)calloc( sizeof(union pval), cr->nchan);
			if( pval == NULL)
			{
				printf( "SetAllChParVal: Failed to calloc value list.\n");
				return( 3);
			}
		}
#endif	/* CAENHVWrapperVERSION */
		/* Build the list of channels to change in this slot,
		   and store the value to send */
		nset = 0;
		for( j = 0; j < cr->hvchmap[i].nchan; j++)
		{
			hvch = cr->hvchmap[i].hvchan[j];
			if( hvch->epicsenabled)
			{
				if( pnum < hvch->npar)
				{
					chlist[nset] = j;
					if( type == PARAM_TYPE_NUMERIC)
						pval[nset].f = hvch->pplist[pnum].pval.f;
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
/* Documented but not in header
					else if( type == PARAM_TYPE_ENUM)
						pval2[nset].s = hvch->pplist[pnum].pval.s;
*/
					else if( type == PARAM_TYPE_STRING)
						pvala[nset].c = strndup( hvch->pplist[pnum].pval.c, MAX_VAL_STRING);
#endif	/* CAENHVWrapperVERSION */
					else
						pval[nset].l = hvch->pplist[pnum].pval.l;
					nset++;
				}
			}
		}
#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVSetChParam( cr->name, i, pname, nset, chlist, pval);
		free( pval);
#else
		if( type == PARAM_TYPE_STRING)
		{
			retval = CAENHV_SetChParam( cr->handle, (ushort)i, pname, (ushort)nset, (ushort*)chlist, pvala);
			free( pvala);
		}
/* Documented but not in header
		else if( type == PARAM_TYPE_ENUM)
		{
			retval = CAENHV_SetChParam( cr->handle, (ushort)i, pname, (ushort)nset, (ushort*)chlist, pval2);
			free( pval2);
		}
*/
		else
		{
			retval = CAENHV_SetChParam( cr->handle, (ushort)i, pname, (ushort)nset, (ushort*)chlist, pval);
			free( pval);
		}
#endif	/* CAENHVWrapperVERSION */
		Busy[cr->crate] = 0;
		free( chlist);
		if( retval != CAENHV_OK)
		{
			cr->connected = 0;
			return( 3);
		}
	}
	return( 0);
}

/* in the given crate, for all channels which have a PV, get their 
   channel name in one call */
/* RU!  Why didn't you make channel name another channel parameter? 
   Complications from chname list? */
int
CAENx527GetAllChName( HVCRATE *cr)
{
	int i, j;
	int nset;
	short *chlist;
	char (*chname)[MAX_CH_NAME];
	HVCHAN *hvch;
	CAENHVRESULT retval;

	if( cr == NULL || cr->hvchan == NULL)
		return( 3);

	/* We have to do this one slot at a time since modules may vary */
	for( i = 0; i < cr->nsl; i++)
	{
		while( Busy[cr->crate])
			epicsThreadSleep( 0.01);

		Busy[cr->crate] = 1;

/* Note: allocating and building these lists repeatedly is not efficient.
   This should really be done once at init_record. */
		chlist = (short *)calloc( sizeof(short), cr->nchan);
		if( chlist == NULL)
		{
			printf( "GetAllChName: Failed to calloc channel list.\n");
			return( 3);
		}
		chname = calloc( sizeof(char)*MAX_CH_NAME, cr->nchan);
		if( chname == NULL)
		{
			printf( "GetAllChName: Failed to calloc channel name.\n");
			return( 3);
		}
		/* Build the list of channels to change in this slot */
		nset = 0;
		for( j = 0; j < cr->hvchmap[i].nchan; j++)
		{
			hvch = cr->hvchmap[i].hvchan[j];
			if( hvch->epicsenabled)
			{
				chlist[nset] = j;
				nset++;
			}
		}
#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVGetChName( cr->name, i, nset, chlist, chname);
#else
		retval = CAENHV_GetChName( cr->handle, (ushort)i, (ushort)nset, (ushort*)chlist, chname);
#endif
		if( retval == CAENHV_OK)
		{
			for( j = 0; j < nset; j++)
			{
				hvch = cr->hvchmap[i].hvchan[chlist[j]];
				snprintf( hvch->chname, MAX_CH_NAME, "%s", chname[chlist[j]]);
				/* RU!  Do we push the value to the PV or
				   let it scan for it? */
#if 0
				/* push value to PV VAL field */
				if( hvch->PVaddr.precord == NULL)
					dbNameToAddr( hvch->pplist[pnum].PVname, &(hvch->PVaddr));
				if( hvch->PVaddr.precord != NULL)
				{
					dbPutField( &(hvch->PVaddr), DBR_DOUBLE, hvch->chname, 1);
				}
#endif
			}
		}
		Busy[cr->crate] = 0;
		free( chlist);
		free( chname);
		if( retval != CAENHV_OK)
			return( 3);
	}
	return( 0);
}

/* Convert a multibit binary word to a state value.  Selects the
   highest order bit if it is a recognized type, otherwise just
   passes the raw value.  This does not extract the bit pattern.
 */
short
CAENx527mbbi2state( PARPROP *pp)
{
	int i;
	short oval;

	if( pp->Type == PARAM_TYPE_CHSTATUS || pp->Type == PARAM_TYPE_BDSTATUS)
	{
		oval = 0;
		for( i = 0; i < 16; i++)
		{
			if( ( pp->pval.l >> i) & 0x1)
				oval = i + 1;
		}
	}
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
/* Documented but not in header
	else if( pp->Type == PARAM_TYPE_ENUM)
	{
		oval = pp->pval.s;
	}
*/
#endif	/* CAENHVWrapperVERSION */
	else
	{
		oval = (short)(pp->pval.l);
	}

	return( oval);
}

/* Convert a multibit binary word to an array of single bit variables,
   each array element holding a 0 or 1 for each bit of the word.
 */
void
CAENx527mbbi2bits( PARPROP *pp, char *bits, short nbits)
{
	int i;

#if CAENHVWrapperVERSION / 100 == 2
	if( pp->Type == PARAM_TYPE_CHSTATUS || pp->Type == PARAM_TYPE_BDSTATUS)
#else
	if( pp->Type == PARAM_TYPE_CHSTATUS || pp->Type == PARAM_TYPE_BDSTATUS || pp->Type == PARAM_TYPE_BINARY)
#endif /* CAENHVWrapperVERSION */
	{
		for( i = 0; i < nbits; i++)
		{
			bits[i] = ( pp->pval.l >> i) & 0x1;
		}
	}
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
/* Documented but not in header
	else if( pp->Type == PARAM_TYPE_ENUM)
	{
		for( i = 0; i < nbits; i++)
			bits[i] = 0;
		if( pp->pval.s < nbits)
			bits[pp->pval.s] = 1;
	}
*/
#endif /* CAENHVWrapperVERSION */
	else
	{
		for( i = 0; i < nbits; i++)
			bits[i] = 0;
	}

	return;
}

char *
CAENx527GetChName( HVCHAN *hvch)
{
	char chname[MAX_CH_NAME];
	CAENHVRESULT retval;

	if( hvch == NULL || hvch->hvcrate == NULL || hvch->epicsenabled == 0)
		return( NULL);

	while( Busy[*(hvch->crate)])
		epicsThreadSleep( 0.01);

	Busy[*(hvch->crate)] = 1;
#if CAENHVWrapperVERSION / 100 == 2
	retval = CAENHVGetChName( hvch->hvcrate->name, hvch->slot, 1, &(hvch->chan), &chname);
#else
	retval = CAENHV_GetChName( hvch->hvcrate->handle, hvch->slot, 1, &(hvch->chan), &chname);
#endif /* CAENHVWrapperVERSION */
	Busy[*(hvch->crate)] = 0;

	if( retval != CAENHV_OK)
		return( NULL);

	snprintf( hvch->chname, MAX_CH_NAME, "%s", chname);

	return( hvch->chname);
}

int
CAENx527SetChName( HVCHAN *hvch, char *chname)
{
	CAENHVRESULT retval;

	if( hvch == NULL || hvch->hvcrate == NULL || hvch->epicsenabled == 0)
		return( 3);

	while( Busy[*(hvch->crate)])
		epicsThreadSleep( 0.01);

	Busy[*(hvch->crate)] = 1;
	snprintf( hvch->chname, MAX_CH_NAME, "%s", chname);
#if CAENHVWrapperVERSION / 100 == 2
	retval = CAENHVSetChName( hvch->hvcrate->name, hvch->slot, 1, &(hvch->chan), hvch->chname);
#else
	retval = CAENHV_SetChName( hvch->hvcrate->handle, hvch->slot, 1, &(hvch->chan), hvch->chname);
#endif	/* CAENHVWrapperVERSION */
	Busy[*(hvch->crate)] = 0;

	if( retval != CAENHV_OK)
		return( 3);

	return( 0);
}

/* Get the engineering units the crate is using for this parameter
   and fill a user-defined char string with it */
char *
CAENx527GetParUnit( PARPROP *pp, char *fieldval)
{
	char exp[8];

	strcpy( exp, "");
	if( pp->Exp)
	{
		if( pp->Exp == 6)
			strcpy( exp, "M\0");
		else if( pp->Exp == 3)
			strcpy( exp, "k\0");
		else if( pp->Exp == -3)
			strcpy( exp, "m\0");
		else if( pp->Exp == -6)
			strcpy( exp, "u\0");
PDEBUG(4) printf( "DEBUG: EGU scale %d -> %s\n", pp->Exp, exp);
	}
			
	snprintf( fieldval, 64, "%s%s", exp, ParUnitStr[pp->Unit]);

	return( fieldval);
}

void
Shutdown()
{
	int i, j;
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
	int k;
#endif
	CAENHVRESULT retval;

	i = 0;
	while( i < MAX_CRATES && Crate[i].hvchan != NULL)
	{
		printf( "DEBUG: shutting down crate %d\n", i);
#if CAENHVWrapperVERSION / 100 == 2
		retval = CAENHVDeinitSystem( Crate[i].name);
#else
		retval = CAENHV_DeinitSystem( Crate[i].handle);
#endif
		if( retval != CAENHV_OK)
		{
			printf( "Shutdown: could not disconnect from crate %s@%s\n", Crate[i].name, Crate[i].IPaddr);
		}
		else
		{
			for( j = 0; j < Crate[i].nsl; j++)
			{
				free( Crate[i].hvchmap[j].hvchan);
			}
			free( Crate[i].hvchmap);
			for( j = 0; j < Crate[i].nchan; j++)
			{
#if CAENHVWrapperVERSION / 100 > 2 || ! defined( CAENHVWrapperVERSION)
				for( k = 0; k < Crate[i].hvchan[j].npar; k++)
				{
					if( Crate[i].hvchan[j].pplist[k].Type == PARAM_TYPE_STRING)
					{
						free( Crate[i].hvchan[j].pplist[k].pval.c);
						free( Crate[i].hvchan[j].pplist[k].pvalset.c);
					}
/* Documented but not in header
					else if( Crate[i].hvchmap[k].hvchan[k].Type == PARAM_TYPE_ENUM)
					{
						free( Crate[i].hvchmap[k].hvchan[k].Enum)
					}
*/
				}
#endif	/* CAENHVWrapperVERSION */
				free( Crate[i].hvchan[j].pplist);
			}
			free( Crate[i].hvchan);
			printf( "Shutdown: successfully disconnected from crate %s@%s\n", Crate[i].name, Crate[i].IPaddr);
		}
		i++;
	}
}

#include <signal.h>

void
SigShutdownHandler( int signal)
{
	if( signal < sizeof( sys_siglist))
		printf( "DEBUG: Caught a termination signal (%s).\n", sys_siglist[signal]);
	else
		return;

	Shutdown();
	exit(0);
}

void
SetSigShutdownHandler(void)
{
	struct sigaction action;

	action.sa_handler = SigShutdownHandler;
	action.sa_flags = SA_ONESHOT | SA_NOCLDSTOP;
	(void)sigaction( SIGHUP, &action, NULL);
	(void)sigaction( SIGINT, &action, NULL);
	(void)sigaction( SIGQUIT, &action, NULL);
	(void)sigaction( SIGTERM, &action, NULL);
}

#if 0
void
iCallback( CALLBACK *pcallback)
{
	dbCommon *pior;
	struct rset *prset;

	callbackGetUser( pior, pcallback);
	prset = (struct rset *)pior->rset;
	dbScanLock( pior);
	(*prset->process)(pior);
	dbScanUnlock( pior);
}

void
oCallback( CALLBACK *pcallback)
{
	dbCommon *pior;
	struct rset *prset;

	callbackGetUser( pior, pcallback);
	prset = (struct rset *)pior->rset;
	dbScanLock( pior);
	(*prset->process)(pior);
	dbScanUnlock( pior);
}
#endif

#include <registryFunction.h>
#include <epicsExport.h>
#include <subRecord.h>
#include <drvSup.h>

/* RU!  I think the code below will be or already is deprecated */
#if 0
/* Read all values associated with the given channel */
static void
ReadChannel( char *name, HVCHAN *hvch)
{
	int i;
	CAENHVRESULT retval;

	for( i = 0; i < hvch->npar; i++)
	{
		/* get value of one parameter */
/*printf( "DEBUG: %d %d scan par %d\n", hvch->slot, hvch->chan, i);*/
		if( hvch->pplist[i].Type == PARAM_TYPE_NUMERIC)
		{
#if CAENHVWrapperVERSION / 100 == 2
			retval = CAENHVGetChParam( name, hvch->slot, hvch->pplist[i].pname, 1, &(hvch->chan), &(hvch->pplist[i].pval.f));
#else
			retval = CAENHV_GetChParam( handle, hvch->slot, hvch->pplist[i].pname, 1, &(hvch->chan), &(hvch->pplist[i].pval.f));
#endif	/* CAENHVWrapperVERSION */
		}
		else
		{
#if CAENHVWrapperVERSION / 100 == 2
			retval = CAENHVGetChParam( name, hvch->slot, hvch->pplist[i].pname, 1, &(hvch->chan), &(hvch->pplist[i].pval.l));
#else
			retval = CAENHV_GetChParam( handle, hvch->slot, hvch->pplist[i].pname, 1, &(hvch->chan), &(hvch->pplist[i].pval.l));
#endif	/* CAENHVWrapperVERSION */
		}

		/* put value into respective PV VAL field */
		if( retval != CAENHV_OK)
		{
		}
		else
		{
			if( strcasecmp( hvch->pplist[i].pname, "Vmon") == 0)
			{
				hvch->pplist[i].pval.d = (double)hvch->pplist[i].pval.f;
				if( hvch->pplist[i].PVaddr.precord == NULL)
					dbNameToAddr( hvch->pplist[i].PVname, &(hvch->pplist[i].PVaddr));
/*printf( "DEBUG: PV info: %s (%x)\n", hvch->pplist[i].PVname, &(hvch->pplist[i].PVaddr));*/
				if( hvch->pplist[i].PVaddr.precord != NULL)
					dbPutField( &(hvch->pplist[i].PVaddr), DBR_DOUBLE, &(hvch->pplist[i].pval.d), 1);
/*printf( "DEBUG: measured voltage (%d) = %f\n", hvch->chan, hvch->pplist[i].pval.f);*/
			}
		}
	}
}
#endif

void
ScanChannels()
{
	int i;
	CRATESCANLIST *csl;
	struct timeval tnow;
	float telapsed;
	short lapsed1, lapsed2, lapsed3, lapsedLong;
	char HvPwSM[64];
	CAENHVRESULT retval;

	lapsed1 = 0;
	lapsed2 = 0;
	lapsed3 = 0;
	lapsedLong = 0;
	gettimeofday( &tnow, NULL);
	telapsed = ( tnow.tv_sec - Timer1.tv_sec) + ( tnow.tv_usec - Timer1.tv_usec) / 1.0e6;
	if( telapsed > Period1)
	{
PDEBUG(9) printf( "DEBUG: lapsed 1 %f\n", telapsed);
		lapsed1 = 1;
		Timer1.tv_sec = tnow.tv_sec;
		Timer1.tv_usec = tnow.tv_usec;
	}
	telapsed = ( tnow.tv_sec - Timer2.tv_sec) + ( tnow.tv_usec - Timer2.tv_usec) / 1.0e6;
	if( telapsed > Period2)
	{
PDEBUG(9) printf( "DEBUG: lapsed 2 %f\n", telapsed);
		lapsed2 = 1;
		Timer2.tv_sec = tnow.tv_sec;
		Timer2.tv_usec = tnow.tv_usec;
	}
	telapsed = ( tnow.tv_sec - Timer3.tv_sec) + ( tnow.tv_usec - Timer3.tv_usec) / 1.0e6;
	if( telapsed > Period3)
	{
PDEBUG(9) printf( "DEBUG: lapsed 3 %f\n", telapsed);
		lapsed3 = 1;
		Timer3.tv_sec = tnow.tv_sec;
		Timer3.tv_usec = tnow.tv_usec;
	}
	telapsed = ( tnow.tv_sec - TimerLong.tv_sec) + ( tnow.tv_usec - TimerLong.tv_usec) / 1.0e6;
	if( telapsed > PeriodLong)
	{
PDEBUG(9) printf( "DEBUG: lapsed Long %f\n", telapsed);
		lapsedLong = 1;
		TimerLong.tv_sec = tnow.tv_sec;
		TimerLong.tv_usec = tnow.tv_usec;
	}

	for( i = 0; i < MAX_CRATES && Crate[i].hvchan != NULL; i++)
	{
PDEBUG(10) printf( "DEBUG: scanning crate %d\n", i);
		
		/* crate connection check */
		if( Crate[i].connected == 1)
		{
			if( lapsed1)
			{
				while( Busy[Crate[i].crate])
					epicsThreadSleep( 0.01);

				Busy[Crate[i].crate] = 1;
#if CAENHVWrapperVERSION / 100 == 2
				retval = CAENHVGetSysProp( Crate[i].name, "HvPwSM", HvPwSM);
#else
				retval = CAENHV_GetSysProp( Crate[i].handle, "HvPwSM", HvPwSM);
#endif /* CAENHVWrapperVERSION */
				Busy[Crate[i].crate] = 0;
				/* If we lose the connection, the crate will
				   log us out, but if we misinterpreted we
				   have to force a logout. */
				if( retval == CAENHV_TIMEERR)
				{
					Crate[i].connected = 0;
					printf( "Lost connection to %s@%s\n", Crate[i].name, Crate[i].IPaddr);
#if CAENHVWrapperVERSION / 100 == 2
					CAENHVDeinitSystem( Crate[i].name);
#else
					CAENHV_DeinitSystem( Crate[i].handle);
#endif	/* CAENHVWrapperVERSION */
				}
			}
		}
		else
		{
			if( lapsedLong)
			{
				/* If we lose the connection, we have to log
				   back in. */
#if 1
#if CAENHVWrapperVERSION / 100 == 2
				retval = CAENHVInitSystem( Crate[i].name, LINKTYPE_TCPIP, (void *)(Crate[i].IPaddr), "admin", "admin");
#else
				retval = CAENHV_InitSystem( Crate[i].type, LINKTYPE_TCPIP, (void *)(Crate[i].IPaddr), "admin", "admin", &(Crate[i].handle));
#endif	/* CAENHVWrapperVERSION */
				if( retval == CAENHV_OK)
				{
					Crate[i].connected = 1;
					printf( "Regained connection to %s@%s\n", Crate[i].name, Crate[i].IPaddr);
				}
#else
/* Eventually, you should actually rebuild the raw data tables,
   unless you find the device support is gibbled in the process.
   Don't forget to free() pointers, i.e. need to do some sort of
   clear().*/
#if CAENHVWrapperVERSION / 100 == 2
				if( ConnectCrate( Crate[i].name, Crate[i].IPaddr) == 0)
#else
				if( ConnectCrate( Crate[i].name, Crate[i].IPaddr, Crate[i].type) == 0)
#endif	/* CAENHVWrapperVERSION */
				{
					Crate[i].connected = 1;
					printf( "Regained connection to %s@%s\n", Crate[i].name, Crate[i].IPaddr);
				}
#endif
			}
		}
		if( Crate[i].connected == 1)
		{
			for( csl = Crate[i].csl; csl->next != NULL; csl = csl->next)
			{
				/* check timer */
				if( csl->period >= Period3) 
				{
					if ( lapsed3)
					{
						CAENx527GetAllChParVal( &(Crate[i]), csl->pname);
PDEBUG(6) printf( "DEBUG: scanning crate %d for %s\n", i, csl->pname);
					}
				}
				else if( csl->period >= Period2)
				{
					if( lapsed2)
					{
						CAENx527GetAllChParVal( &(Crate[i]), csl->pname);
PDEBUG(6) printf( "DEBUG: scanning crate %d for %s\n", i, csl->pname);
					}
				}
				else
				{
					if( lapsed1)
					{
						CAENx527GetAllChParVal( &(Crate[i]), csl->pname);
PDEBUG(6) printf( "DEBUG: scanning crate %d for %s\n", i, csl->pname);
					}
				}
			}
			/* ChName needs to be handled separately */
#if 1
			if( Crate[i].hvchan[0].chname_period >= Period3) 
			{
				if( lapsed3)
					CAENx527GetAllChName( &(Crate[i]));
			}
			else if( Crate[i].hvchan[0].chname_period >= Period2)
			{
				if( lapsed2)
					CAENx527GetAllChName( &(Crate[i]));
			}
			else
			{
				if( lapsed1)
					CAENx527GetAllChName( &(Crate[i]));
			}
#else
			if( lapsed3)
				CAENx527GetAllChName( &(Crate[i]));
#endif
		}
	}

	if( lapsed1)
		post_event( EVNTNO_T1);
	if( lapsed2)
		post_event( EVNTNO_T2);
	if( lapsed3)
		post_event( EVNTNO_T3);
}

void
InitScanChannels()
{
	int i, j, k, m;
	CRATESCANLIST *csl;
	HVCHAN *hvch;

	/* set up scan lists by parameter name, for each crate */
	for( i = 0;  i < MAX_CRATES && Crate[i].hvchan != NULL; i++)
	{
		Crate[i].csl = (CRATESCANLIST *)calloc( sizeof(CRATESCANLIST), 1);
		if( Crate[i].csl == NULL)
			printf( "InitScanChannels: Failed to calloc crate scanlist\n");
		for( j = 0; j < Crate[i].nsl; j++)
		{
PDEBUG(5) printf( "DEBUG: slot name (%d out of %d): %s\n", j, Crate[i].nsl, Crate[i].hvchmap[j].slname);
			if( Crate[i].hvchmap[j].slname[0] != '\0')
			{
				hvch = Crate[i].hvchmap[j].hvchan[0];
				for( k = 0; k < hvch->npar; k++)
				{
					for( csl = Crate[i].csl; csl->next != NULL && strcmp( csl->pname, hvch->pplist[k].pname) != 0; csl = csl->next);
PDEBUG(6) printf( "DEBUG: csl->next = %p ?= NULL, '%s' ?= '%s'\n", csl->next, csl->pname, hvch->pplist[k].pname);
					if( csl->next == NULL)
					{
						csl->next = (CRATESCANLIST *)calloc( sizeof(CRATESCANLIST), 1);
						if( csl->next == NULL)
							printf( "InitScanChannels: Failed to calloc next crate scanlist\n");
						strcpy( csl->pname, hvch->pplist[k].pname);
						/* RU!  This should really
						default to the longest period
						and be explicit with shorter
						period parameters */
						csl->period = 30.0;
						csl->evntno = EVNTNO_T3;

						/* Default scan period setup */
						if( ( strcmp( csl->pname, "Status") == 0) ||
							( strcmp( csl->pname, "Pw") == 0) ||
							( strcmp( csl->pname, "VMon") == 0) ||
							( strcmp( csl->pname, "IMon") == 0)
						)
						{
				/* This is very short because the values
				   are dynamic */
						  csl->period = 0.5;
						  csl->evntno = EVNTNO_T1;
						  /*csl->period = 5.0;
						    csl->evntno = EVNTNO_T2;*/
						}
						else if(
							( strcmp( csl->pname, "V0Set") == 0) ||
							( strcmp( csl->pname, "I0Set") == 0) ||
							( strcmp( csl->pname, "V1Set") == 0) ||
							( strcmp( csl->pname, "I1Set") == 0)
						)
						{
				/* This is short because we want to be
				   sure the associated variable gets set */
							csl->period = 5.0;
							csl->evntno = EVNTNO_T2;
						}
					}
					if( ( csl->next == NULL) || ( strcmp( csl->pname, hvch->pplist[k].pname) == 0))
					{
						for( m = 0; m < Crate[i].hvchmap[j].nchan; m++)
						{
							hvch[m].pplist[k].period = csl->period;
							hvch[m].pplist[k].evntno = csl->evntno;
PDEBUG( 7) printf( "DEBUG: %s: event #: %d\n", csl->pname, hvch[m].pplist[k].evntno);
						}
					}
				}
				/* channel name must be handled separately */
				for( m = 0; m < Crate[i].hvchmap[j].nchan; m++)
				{
					hvch[m].chname_period = 10.0;
					hvch[m].chname_evntno = EVNTNO_T3;
				}
			}
		}
	}

	/* Set up timers */
	Period1 = 0.5;
	Period2 = 5.0;
	Period3 = 10.0;
	PeriodLong = 30.0;
	gettimeofday( &Timer1, NULL);
	Timer2.tv_sec = Timer1.tv_sec;
	Timer2.tv_usec = Timer1.tv_usec;
	Timer3.tv_sec = Timer1.tv_sec;
	Timer3.tv_usec = Timer1.tv_usec;
	TimerLong.tv_sec = Timer1.tv_sec;
	TimerLong.tv_usec = Timer1.tv_usec;
}

#if 1

void
ScanChannels_Thread( void *param)
{
	while( 1)
	{
		ScanChannels();
		epicsThreadSleep( ScanChannelsPeriod);
	}
}

static long
init()
{
	errlogPrintf("Starting CAEN x527 driver\n");

	ScanChannelsPeriod = 0.2;
	InitScanChannels();
	scanThread = epicsThreadCreate( "HVCAENx527Thread", epicsThreadPriorityMedium + 5, epicsThreadGetStackSize(epicsThreadStackBig), ScanChannels_Thread, NULL);

	return( 0);
}

static long
report( int level)
{
	return( 0);
}

struct
{
	long number;
	DRVSUPFUN	report;
	DRVSUPFUN	init;
} drvCAENx527 =
	{
		2,
		report,
		init
	};
epicsExportAddress( drvet, drvCAENx527);
#endif

#if 0
epicsRegisterFunction( InitScanChannels);
epicsRegisterFunction( ScanChannels);
#endif

/*
 * $Log: HVCAENx527/libHVCAENx527App/src/HVCAENx527.c  $
 * Revision 1.21.1.4 2014/04/30 16:10:08CST Ru Igarashi (igarasr) 
 * eliminated redundant search loop that was scanning for param num of channel with
 * param number that was previously extracted for entire card
 * Revision 1.21.1.3 2014/04/30 15:58:17CST Ru Igarashi (igarasr) 
 * - fixed potential bug in GetAllChPar that could have bypassed epicsenabled setting
 * - refined pre-processor condition for blocks that only contained code for V5.x wrapper
 * - replaced check of type from each channel with one for the entire card
 * Revision 1.21.1.2 2014/04/29 23:04:40CST Ru Igarashi (igarasr) 
 * Member moved from HVCAENx527/HVCAENx527App/src/HVCAENx527.c in project e:/MKS_Home/archive/cs/epics_local/drivers/CAENx527HV/project.pj to HVCAENx527/libHVCAENx527App/src/HVCAENx527.c in project e:/MKS_Home/archive/cs/epics_local/drivers/CAENx527HV/project.pj.
 * Revision 1.21.1.1 2014/04/29 19:24:23CST Ru Igarashi (igarasr) 
 * implemented support of new CAEN wrapper API
 * Revision 1.21 2014/04/21 19:51:44CST Ru Igarashi (igarasr) 
 * reduced priority of debug statements in scan loop to reduce noise at middle debug levels
 * Revision 1.20 2007/06/01 13:32:57CST Ru Igarashi (igarasr) 
 * Member moved from EPICS/HVCAENx527App/src/HVCAENx527.c in project e:/MKS_Home/archive/cs/epics_local/drivers/CAENx527HV/project.pj to HVCAENx527/HVCAENx527App/src/HVCAENx527.c in project e:/MKS_Home/archive/cs/epics_local/drivers/CAENx527HV/project.pj.
 */