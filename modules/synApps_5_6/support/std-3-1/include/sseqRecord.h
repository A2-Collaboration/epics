
#ifndef INCsseqWAITH
#define INCsseqWAITH
typedef enum {
	sseqWAIT_NoWait,
	sseqWAIT_Wait,
	sseqWAIT_Wait1,
	sseqWAIT_Wait2,
	sseqWAIT_Wait3,
	sseqWAIT_Wait4,
	sseqWAIT_Wait5,
	sseqWAIT_Wait6,
	sseqWAIT_Wait7,
	sseqWAIT_Wait8,
	sseqWAIT_Wait9,
	sseqWAIT_Wait10
}sseqWAIT;
#endif /*INCsseqWAITH*/

#ifndef INCsseqSELMH
#define INCsseqSELMH
typedef enum {
	sseqSELM_All,
	sseqSELM_Specified,
	sseqSELM_Mask
}sseqSELM;
#endif /*INCsseqSELMH*/

#ifndef INCsseqLNKVH
#define INCsseqLNKVH
typedef enum {
	sseqLNKV_EXT_NC,
	sseqLNKV_EXT,
	sseqLNKV_LOC,
	sseqLNKV_CON
}sseqLNKV;
#endif /*INCsseqLNKVH*/
#ifndef INCsseqH
#define INCsseqH
#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "epicsTime.h"
typedef struct sseqRecord {
	char		name[61];	/* Record Name */
	char		desc[41];	/* Descriptor */
	char		asg[29];	/* Access Security Group */
	epicsEnum16	scan;	/* Scan Mechanism */
	epicsEnum16	pini;	/* Process at iocInit */
	epicsInt16	phas;	/* Scan Phase */
	epicsInt16	evnt;	/* Event Number */
	epicsInt16	tse;	/* Time Stamp Event */
	DBLINK		tsel;	/* Time Stamp Link */
	epicsEnum16	dtyp;	/* Device Type */
	epicsInt16	disv;	/* Disable Value */
	epicsInt16	disa;	/* Disable */
	DBLINK		sdis;	/* Scanning Disable */
	epicsMutexId	mlok;	/* Monitor lock */
	ELLLIST		mlis;	/* Monitor List */
	epicsUInt8	disp;	/* Disable putField */
	epicsUInt8	proc;	/* Force Processing */
	epicsEnum16	stat;	/* Alarm Status */
	epicsEnum16	sevr;	/* Alarm Severity */
	epicsEnum16	nsta;	/* New Alarm Status */
	epicsEnum16	nsev;	/* New Alarm Severity */
	epicsEnum16	acks;	/* Alarm Ack Severity */
	epicsEnum16	ackt;	/* Alarm Ack Transient */
	epicsEnum16	diss;	/* Disable Alarm Sevrty */
	epicsUInt8	lcnt;	/* Lock Count */
	epicsUInt8	pact;	/* Record active */
	epicsUInt8	putf;	/* dbPutField process */
	epicsUInt8	rpro;	/* Reprocess  */
	struct asgMember *asp;	/* Access Security Pvt */
	struct putNotify *ppn;	/* addr of PUTNOTIFY */
	struct putNotifyRecord *ppnr;	/* pputNotifyRecord */
	struct scan_element *spvt;	/* Scan Private */
	struct rset	*rset;	/* Address of RSET */
	struct dset	*dset;	/* DSET address */
	void		*dpvt;	/* Device Private */
	struct dbRecordType *rdes;	/* Address of dbRecordType */
	struct lockRecord *lset;	/* Lock Set */
	epicsEnum16	prio;	/* Scheduling Priority */
	epicsUInt8	tpro;	/* Trace Processing */
	char bkpt;	/* Break Point */
	epicsUInt8	udf;	/* Undefined */
	epicsTimeStamp	time;	/* Time */
	DBLINK		flnk;	/* Forward Process Link */
	epicsInt32	val;	/* Used to trigger */
	epicsEnum16	selm;	/* Select Mechanism */
	epicsUInt16	seln;	/* Link Selection */
	DBLINK		sell;	/* Link Selection Loc */
	epicsInt16	prec;	/* Display Precision */
	epicsFloat64	dly1;	/* Delay 1 */
	DBLINK		dol1;	/* Input link1 */
	epicsFloat64	do1;	/* Constant input 1 */
	DBLINK		lnk1;	/* Output Link 1 */
	char		str1[40];	/* String value 1 */
	epicsInt16	dt1;	/* DOL link type */
	epicsInt16	lt1;	/* LNK link type */
	epicsEnum16	wait1;	/* Wait for completion? */
	epicsInt16	wtg1;	/*  */
	epicsInt16	ix1;	/*  */
	epicsEnum16	dol1v;	/* DOL LINK Status */
	epicsEnum16	lnk1v;	/* LNK LINK Status */
	epicsFloat64	dly2;	/* Delay 2 */
	DBLINK		dol2;	/* Input link 2 */
	epicsFloat64	do2;	/* Constant input 2 */
	DBLINK		lnk2;	/* Output Link 2 */
	char		str2[40];	/* String value 2 */
	epicsInt16	dt2;	/* DOL link type */
	epicsInt16	lt2;	/* LNK link type */
	epicsEnum16	wait2;	/* Wait for completion? */
	epicsInt16	wtg2;	/*  */
	epicsInt16	ix2;	/*  */
	epicsEnum16	dol2v;	/* DOL LINK Status */
	epicsEnum16	lnk2v;	/* LNK LINK Status */
	epicsFloat64	dly3;	/* Delay 3 */
	DBLINK		dol3;	/* Input link 3 */
	epicsFloat64	do3;	/* Constant input 3 */
	DBLINK		lnk3;	/* Output Link 3 */
	char		str3[40];	/* String value 3 */
	epicsInt16	dt3;	/* DOL link type */
	epicsInt16	lt3;	/* LNK link type */
	epicsEnum16	wait3;	/* Wait for completion? */
	epicsInt16	wtg3;	/*  */
	epicsInt16	ix3;	/*  */
	epicsEnum16	dol3v;	/* DOL LINK Status */
	epicsEnum16	lnk3v;	/* LNK LINK Status */
	epicsFloat64	dly4;	/* Delay 4 */
	DBLINK		dol4;	/* Input link 4 */
	epicsFloat64	do4;	/* Constant input 4 */
	DBLINK		lnk4;	/* Output Link 4 */
	char		str4[40];	/* String value 4 */
	epicsInt16	dt4;	/* DOL link type */
	epicsInt16	lt4;	/* LNK link type */
	epicsEnum16	wait4;	/* Wait for completion? */
	epicsInt16	wtg4;	/*  */
	epicsInt16	ix4;	/*  */
	epicsEnum16	dol4v;	/* DOL LINK Status */
	epicsEnum16	lnk4v;	/* LNK LINK Status */
	epicsFloat64	dly5;	/* Delay 5 */
	DBLINK		dol5;	/* Input link 5 */
	epicsFloat64	do5;	/* Constant input 5 */
	DBLINK		lnk5;	/* Output Link 5 */
	char		str5[40];	/* String value 5 */
	epicsInt16	dt5;	/* DOL link type */
	epicsInt16	lt5;	/* LNK link type */
	epicsEnum16	wait5;	/* Wait for completion? */
	epicsInt16	wtg5;	/*  */
	epicsInt16	ix5;	/*  */
	epicsEnum16	dol5v;	/* DOL LINK Status */
	epicsEnum16	lnk5v;	/* LNK LINK Status */
	epicsFloat64	dly6;	/* Delay 6 */
	DBLINK		dol6;	/* Input link 6 */
	epicsFloat64	do6;	/* Constant input 6 */
	DBLINK		lnk6;	/* Output Link 6 */
	char		str6[40];	/* String value 6 */
	epicsInt16	dt6;	/* DOL link type */
	epicsInt16	lt6;	/* LNK link type */
	epicsEnum16	wait6;	/* Wait for completion? */
	epicsInt16	wtg6;	/*  */
	epicsInt16	ix6;	/*  */
	epicsEnum16	dol6v;	/* DOL LINK Status */
	epicsEnum16	lnk6v;	/* LNK LINK Status */
	epicsFloat64	dly7;	/* Delay 7 */
	DBLINK		dol7;	/* Input link 7 */
	epicsFloat64	do7;	/* Constant input 7 */
	DBLINK		lnk7;	/* Output Link 7 */
	char		str7[40];	/* String value 7 */
	epicsInt16	dt7;	/* DOL link type */
	epicsInt16	lt7;	/* LNK link type */
	epicsEnum16	wait7;	/* Wait for completion? */
	epicsInt16	wtg7;	/*  */
	epicsInt16	ix7;	/*  */
	epicsEnum16	dol7v;	/* DOL LINK Status */
	epicsEnum16	lnk7v;	/* LNK LINK Status */
	epicsFloat64	dly8;	/* Delay 8 */
	DBLINK		dol8;	/* Input link 8 */
	epicsFloat64	do8;	/* Constant input 8 */
	DBLINK		lnk8;	/* Output Link 8 */
	char		str8[40];	/* String value 8 */
	epicsInt16	dt8;	/* DOL link type */
	epicsInt16	lt8;	/* LNK link type */
	epicsEnum16	wait8;	/* Wait for completion? */
	epicsInt16	wtg8;	/*  */
	epicsInt16	ix8;	/*  */
	epicsEnum16	dol8v;	/* DOL LINK Status */
	epicsEnum16	lnk8v;	/* LNK LINK Status */
	epicsFloat64	dly9;	/* Delay 9 */
	DBLINK		dol9;	/* Input link 9 */
	epicsFloat64	do9;	/* Constant input 9 */
	DBLINK		lnk9;	/* Output Link 9 */
	char		str9[40];	/* String value 9 */
	epicsInt16	dt9;	/* DOL link type */
	epicsInt16	lt9;	/* LNK link type */
	epicsEnum16	wait9;	/* Wait for completion? */
	epicsInt16	wtg9;	/*  */
	epicsInt16	ix9;	/*  */
	epicsEnum16	dol9v;	/* DOL LINK Status */
	epicsEnum16	lnk9v;	/* LNK LINK Status */
	epicsFloat64	dlya;	/* Delay 10 */
	DBLINK		dola;	/* Input link 10 */
	epicsFloat64	doa;	/* Constant input 10 */
	DBLINK		lnka;	/* Output Link 10 */
	char		stra[40];	/* String value A */
	epicsInt16	dta;	/* DOL link type */
	epicsInt16	lta;	/* LNK link type */
	epicsEnum16	waita;	/* Wait for completion? */
	epicsInt16	wtga;	/*  */
	epicsInt16	ixa;	/*  */
	epicsEnum16	dolav;	/* DOL LINK Status */
	epicsEnum16	lnkav;	/* LNK LINK Status */
	epicsInt16	abort;	/* Abort sequence */
	epicsInt16	aborting;	/* Aborting */
	epicsInt16	busy;	/* Sequence active */
} sseqRecord;
#define sseqRecordNAME	0
#define sseqRecordDESC	1
#define sseqRecordASG	2
#define sseqRecordSCAN	3
#define sseqRecordPINI	4
#define sseqRecordPHAS	5
#define sseqRecordEVNT	6
#define sseqRecordTSE	7
#define sseqRecordTSEL	8
#define sseqRecordDTYP	9
#define sseqRecordDISV	10
#define sseqRecordDISA	11
#define sseqRecordSDIS	12
#define sseqRecordMLOK	13
#define sseqRecordMLIS	14
#define sseqRecordDISP	15
#define sseqRecordPROC	16
#define sseqRecordSTAT	17
#define sseqRecordSEVR	18
#define sseqRecordNSTA	19
#define sseqRecordNSEV	20
#define sseqRecordACKS	21
#define sseqRecordACKT	22
#define sseqRecordDISS	23
#define sseqRecordLCNT	24
#define sseqRecordPACT	25
#define sseqRecordPUTF	26
#define sseqRecordRPRO	27
#define sseqRecordASP	28
#define sseqRecordPPN	29
#define sseqRecordPPNR	30
#define sseqRecordSPVT	31
#define sseqRecordRSET	32
#define sseqRecordDSET	33
#define sseqRecordDPVT	34
#define sseqRecordRDES	35
#define sseqRecordLSET	36
#define sseqRecordPRIO	37
#define sseqRecordTPRO	38
#define sseqRecordBKPT	39
#define sseqRecordUDF	40
#define sseqRecordTIME	41
#define sseqRecordFLNK	42
#define sseqRecordVAL	43
#define sseqRecordSELM	44
#define sseqRecordSELN	45
#define sseqRecordSELL	46
#define sseqRecordPREC	47
#define sseqRecordDLY1	48
#define sseqRecordDOL1	49
#define sseqRecordDO1	50
#define sseqRecordLNK1	51
#define sseqRecordSTR1	52
#define sseqRecordDT1	53
#define sseqRecordLT1	54
#define sseqRecordWAIT1	55
#define sseqRecordWTG1	56
#define sseqRecordIX1	57
#define sseqRecordDOL1V	58
#define sseqRecordLNK1V	59
#define sseqRecordDLY2	60
#define sseqRecordDOL2	61
#define sseqRecordDO2	62
#define sseqRecordLNK2	63
#define sseqRecordSTR2	64
#define sseqRecordDT2	65
#define sseqRecordLT2	66
#define sseqRecordWAIT2	67
#define sseqRecordWTG2	68
#define sseqRecordIX2	69
#define sseqRecordDOL2V	70
#define sseqRecordLNK2V	71
#define sseqRecordDLY3	72
#define sseqRecordDOL3	73
#define sseqRecordDO3	74
#define sseqRecordLNK3	75
#define sseqRecordSTR3	76
#define sseqRecordDT3	77
#define sseqRecordLT3	78
#define sseqRecordWAIT3	79
#define sseqRecordWTG3	80
#define sseqRecordIX3	81
#define sseqRecordDOL3V	82
#define sseqRecordLNK3V	83
#define sseqRecordDLY4	84
#define sseqRecordDOL4	85
#define sseqRecordDO4	86
#define sseqRecordLNK4	87
#define sseqRecordSTR4	88
#define sseqRecordDT4	89
#define sseqRecordLT4	90
#define sseqRecordWAIT4	91
#define sseqRecordWTG4	92
#define sseqRecordIX4	93
#define sseqRecordDOL4V	94
#define sseqRecordLNK4V	95
#define sseqRecordDLY5	96
#define sseqRecordDOL5	97
#define sseqRecordDO5	98
#define sseqRecordLNK5	99
#define sseqRecordSTR5	100
#define sseqRecordDT5	101
#define sseqRecordLT5	102
#define sseqRecordWAIT5	103
#define sseqRecordWTG5	104
#define sseqRecordIX5	105
#define sseqRecordDOL5V	106
#define sseqRecordLNK5V	107
#define sseqRecordDLY6	108
#define sseqRecordDOL6	109
#define sseqRecordDO6	110
#define sseqRecordLNK6	111
#define sseqRecordSTR6	112
#define sseqRecordDT6	113
#define sseqRecordLT6	114
#define sseqRecordWAIT6	115
#define sseqRecordWTG6	116
#define sseqRecordIX6	117
#define sseqRecordDOL6V	118
#define sseqRecordLNK6V	119
#define sseqRecordDLY7	120
#define sseqRecordDOL7	121
#define sseqRecordDO7	122
#define sseqRecordLNK7	123
#define sseqRecordSTR7	124
#define sseqRecordDT7	125
#define sseqRecordLT7	126
#define sseqRecordWAIT7	127
#define sseqRecordWTG7	128
#define sseqRecordIX7	129
#define sseqRecordDOL7V	130
#define sseqRecordLNK7V	131
#define sseqRecordDLY8	132
#define sseqRecordDOL8	133
#define sseqRecordDO8	134
#define sseqRecordLNK8	135
#define sseqRecordSTR8	136
#define sseqRecordDT8	137
#define sseqRecordLT8	138
#define sseqRecordWAIT8	139
#define sseqRecordWTG8	140
#define sseqRecordIX8	141
#define sseqRecordDOL8V	142
#define sseqRecordLNK8V	143
#define sseqRecordDLY9	144
#define sseqRecordDOL9	145
#define sseqRecordDO9	146
#define sseqRecordLNK9	147
#define sseqRecordSTR9	148
#define sseqRecordDT9	149
#define sseqRecordLT9	150
#define sseqRecordWAIT9	151
#define sseqRecordWTG9	152
#define sseqRecordIX9	153
#define sseqRecordDOL9V	154
#define sseqRecordLNK9V	155
#define sseqRecordDLYA	156
#define sseqRecordDOLA	157
#define sseqRecordDOA	158
#define sseqRecordLNKA	159
#define sseqRecordSTRA	160
#define sseqRecordDTA	161
#define sseqRecordLTA	162
#define sseqRecordWAITA	163
#define sseqRecordWTGA	164
#define sseqRecordIXA	165
#define sseqRecordDOLAV	166
#define sseqRecordLNKAV	167
#define sseqRecordABORT	168
#define sseqRecordABORTING	169
#define sseqRecordBUSY	170
#endif /*INCsseqH*/
#ifdef GEN_SIZE_OFFSET
#ifdef __cplusplus
extern "C" {
#endif
#include <epicsExport.h>
static int sseqRecordSizeOffset(dbRecordType *pdbRecordType)
{
    sseqRecord *prec = 0;
  pdbRecordType->papFldDes[0]->size=sizeof(prec->name);
  pdbRecordType->papFldDes[0]->offset=(short)((char *)&prec->name - (char *)prec);
  pdbRecordType->papFldDes[1]->size=sizeof(prec->desc);
  pdbRecordType->papFldDes[1]->offset=(short)((char *)&prec->desc - (char *)prec);
  pdbRecordType->papFldDes[2]->size=sizeof(prec->asg);
  pdbRecordType->papFldDes[2]->offset=(short)((char *)&prec->asg - (char *)prec);
  pdbRecordType->papFldDes[3]->size=sizeof(prec->scan);
  pdbRecordType->papFldDes[3]->offset=(short)((char *)&prec->scan - (char *)prec);
  pdbRecordType->papFldDes[4]->size=sizeof(prec->pini);
  pdbRecordType->papFldDes[4]->offset=(short)((char *)&prec->pini - (char *)prec);
  pdbRecordType->papFldDes[5]->size=sizeof(prec->phas);
  pdbRecordType->papFldDes[5]->offset=(short)((char *)&prec->phas - (char *)prec);
  pdbRecordType->papFldDes[6]->size=sizeof(prec->evnt);
  pdbRecordType->papFldDes[6]->offset=(short)((char *)&prec->evnt - (char *)prec);
  pdbRecordType->papFldDes[7]->size=sizeof(prec->tse);
  pdbRecordType->papFldDes[7]->offset=(short)((char *)&prec->tse - (char *)prec);
  pdbRecordType->papFldDes[8]->size=sizeof(prec->tsel);
  pdbRecordType->papFldDes[8]->offset=(short)((char *)&prec->tsel - (char *)prec);
  pdbRecordType->papFldDes[9]->size=sizeof(prec->dtyp);
  pdbRecordType->papFldDes[9]->offset=(short)((char *)&prec->dtyp - (char *)prec);
  pdbRecordType->papFldDes[10]->size=sizeof(prec->disv);
  pdbRecordType->papFldDes[10]->offset=(short)((char *)&prec->disv - (char *)prec);
  pdbRecordType->papFldDes[11]->size=sizeof(prec->disa);
  pdbRecordType->papFldDes[11]->offset=(short)((char *)&prec->disa - (char *)prec);
  pdbRecordType->papFldDes[12]->size=sizeof(prec->sdis);
  pdbRecordType->papFldDes[12]->offset=(short)((char *)&prec->sdis - (char *)prec);
  pdbRecordType->papFldDes[13]->size=sizeof(prec->mlok);
  pdbRecordType->papFldDes[13]->offset=(short)((char *)&prec->mlok - (char *)prec);
  pdbRecordType->papFldDes[14]->size=sizeof(prec->mlis);
  pdbRecordType->papFldDes[14]->offset=(short)((char *)&prec->mlis - (char *)prec);
  pdbRecordType->papFldDes[15]->size=sizeof(prec->disp);
  pdbRecordType->papFldDes[15]->offset=(short)((char *)&prec->disp - (char *)prec);
  pdbRecordType->papFldDes[16]->size=sizeof(prec->proc);
  pdbRecordType->papFldDes[16]->offset=(short)((char *)&prec->proc - (char *)prec);
  pdbRecordType->papFldDes[17]->size=sizeof(prec->stat);
  pdbRecordType->papFldDes[17]->offset=(short)((char *)&prec->stat - (char *)prec);
  pdbRecordType->papFldDes[18]->size=sizeof(prec->sevr);
  pdbRecordType->papFldDes[18]->offset=(short)((char *)&prec->sevr - (char *)prec);
  pdbRecordType->papFldDes[19]->size=sizeof(prec->nsta);
  pdbRecordType->papFldDes[19]->offset=(short)((char *)&prec->nsta - (char *)prec);
  pdbRecordType->papFldDes[20]->size=sizeof(prec->nsev);
  pdbRecordType->papFldDes[20]->offset=(short)((char *)&prec->nsev - (char *)prec);
  pdbRecordType->papFldDes[21]->size=sizeof(prec->acks);
  pdbRecordType->papFldDes[21]->offset=(short)((char *)&prec->acks - (char *)prec);
  pdbRecordType->papFldDes[22]->size=sizeof(prec->ackt);
  pdbRecordType->papFldDes[22]->offset=(short)((char *)&prec->ackt - (char *)prec);
  pdbRecordType->papFldDes[23]->size=sizeof(prec->diss);
  pdbRecordType->papFldDes[23]->offset=(short)((char *)&prec->diss - (char *)prec);
  pdbRecordType->papFldDes[24]->size=sizeof(prec->lcnt);
  pdbRecordType->papFldDes[24]->offset=(short)((char *)&prec->lcnt - (char *)prec);
  pdbRecordType->papFldDes[25]->size=sizeof(prec->pact);
  pdbRecordType->papFldDes[25]->offset=(short)((char *)&prec->pact - (char *)prec);
  pdbRecordType->papFldDes[26]->size=sizeof(prec->putf);
  pdbRecordType->papFldDes[26]->offset=(short)((char *)&prec->putf - (char *)prec);
  pdbRecordType->papFldDes[27]->size=sizeof(prec->rpro);
  pdbRecordType->papFldDes[27]->offset=(short)((char *)&prec->rpro - (char *)prec);
  pdbRecordType->papFldDes[28]->size=sizeof(prec->asp);
  pdbRecordType->papFldDes[28]->offset=(short)((char *)&prec->asp - (char *)prec);
  pdbRecordType->papFldDes[29]->size=sizeof(prec->ppn);
  pdbRecordType->papFldDes[29]->offset=(short)((char *)&prec->ppn - (char *)prec);
  pdbRecordType->papFldDes[30]->size=sizeof(prec->ppnr);
  pdbRecordType->papFldDes[30]->offset=(short)((char *)&prec->ppnr - (char *)prec);
  pdbRecordType->papFldDes[31]->size=sizeof(prec->spvt);
  pdbRecordType->papFldDes[31]->offset=(short)((char *)&prec->spvt - (char *)prec);
  pdbRecordType->papFldDes[32]->size=sizeof(prec->rset);
  pdbRecordType->papFldDes[32]->offset=(short)((char *)&prec->rset - (char *)prec);
  pdbRecordType->papFldDes[33]->size=sizeof(prec->dset);
  pdbRecordType->papFldDes[33]->offset=(short)((char *)&prec->dset - (char *)prec);
  pdbRecordType->papFldDes[34]->size=sizeof(prec->dpvt);
  pdbRecordType->papFldDes[34]->offset=(short)((char *)&prec->dpvt - (char *)prec);
  pdbRecordType->papFldDes[35]->size=sizeof(prec->rdes);
  pdbRecordType->papFldDes[35]->offset=(short)((char *)&prec->rdes - (char *)prec);
  pdbRecordType->papFldDes[36]->size=sizeof(prec->lset);
  pdbRecordType->papFldDes[36]->offset=(short)((char *)&prec->lset - (char *)prec);
  pdbRecordType->papFldDes[37]->size=sizeof(prec->prio);
  pdbRecordType->papFldDes[37]->offset=(short)((char *)&prec->prio - (char *)prec);
  pdbRecordType->papFldDes[38]->size=sizeof(prec->tpro);
  pdbRecordType->papFldDes[38]->offset=(short)((char *)&prec->tpro - (char *)prec);
  pdbRecordType->papFldDes[39]->size=sizeof(prec->bkpt);
  pdbRecordType->papFldDes[39]->offset=(short)((char *)&prec->bkpt - (char *)prec);
  pdbRecordType->papFldDes[40]->size=sizeof(prec->udf);
  pdbRecordType->papFldDes[40]->offset=(short)((char *)&prec->udf - (char *)prec);
  pdbRecordType->papFldDes[41]->size=sizeof(prec->time);
  pdbRecordType->papFldDes[41]->offset=(short)((char *)&prec->time - (char *)prec);
  pdbRecordType->papFldDes[42]->size=sizeof(prec->flnk);
  pdbRecordType->papFldDes[42]->offset=(short)((char *)&prec->flnk - (char *)prec);
  pdbRecordType->papFldDes[43]->size=sizeof(prec->val);
  pdbRecordType->papFldDes[43]->offset=(short)((char *)&prec->val - (char *)prec);
  pdbRecordType->papFldDes[44]->size=sizeof(prec->selm);
  pdbRecordType->papFldDes[44]->offset=(short)((char *)&prec->selm - (char *)prec);
  pdbRecordType->papFldDes[45]->size=sizeof(prec->seln);
  pdbRecordType->papFldDes[45]->offset=(short)((char *)&prec->seln - (char *)prec);
  pdbRecordType->papFldDes[46]->size=sizeof(prec->sell);
  pdbRecordType->papFldDes[46]->offset=(short)((char *)&prec->sell - (char *)prec);
  pdbRecordType->papFldDes[47]->size=sizeof(prec->prec);
  pdbRecordType->papFldDes[47]->offset=(short)((char *)&prec->prec - (char *)prec);
  pdbRecordType->papFldDes[48]->size=sizeof(prec->dly1);
  pdbRecordType->papFldDes[48]->offset=(short)((char *)&prec->dly1 - (char *)prec);
  pdbRecordType->papFldDes[49]->size=sizeof(prec->dol1);
  pdbRecordType->papFldDes[49]->offset=(short)((char *)&prec->dol1 - (char *)prec);
  pdbRecordType->papFldDes[50]->size=sizeof(prec->do1);
  pdbRecordType->papFldDes[50]->offset=(short)((char *)&prec->do1 - (char *)prec);
  pdbRecordType->papFldDes[51]->size=sizeof(prec->lnk1);
  pdbRecordType->papFldDes[51]->offset=(short)((char *)&prec->lnk1 - (char *)prec);
  pdbRecordType->papFldDes[52]->size=sizeof(prec->str1);
  pdbRecordType->papFldDes[52]->offset=(short)((char *)&prec->str1 - (char *)prec);
  pdbRecordType->papFldDes[53]->size=sizeof(prec->dt1);
  pdbRecordType->papFldDes[53]->offset=(short)((char *)&prec->dt1 - (char *)prec);
  pdbRecordType->papFldDes[54]->size=sizeof(prec->lt1);
  pdbRecordType->papFldDes[54]->offset=(short)((char *)&prec->lt1 - (char *)prec);
  pdbRecordType->papFldDes[55]->size=sizeof(prec->wait1);
  pdbRecordType->papFldDes[55]->offset=(short)((char *)&prec->wait1 - (char *)prec);
  pdbRecordType->papFldDes[56]->size=sizeof(prec->wtg1);
  pdbRecordType->papFldDes[56]->offset=(short)((char *)&prec->wtg1 - (char *)prec);
  pdbRecordType->papFldDes[57]->size=sizeof(prec->ix1);
  pdbRecordType->papFldDes[57]->offset=(short)((char *)&prec->ix1 - (char *)prec);
  pdbRecordType->papFldDes[58]->size=sizeof(prec->dol1v);
  pdbRecordType->papFldDes[58]->offset=(short)((char *)&prec->dol1v - (char *)prec);
  pdbRecordType->papFldDes[59]->size=sizeof(prec->lnk1v);
  pdbRecordType->papFldDes[59]->offset=(short)((char *)&prec->lnk1v - (char *)prec);
  pdbRecordType->papFldDes[60]->size=sizeof(prec->dly2);
  pdbRecordType->papFldDes[60]->offset=(short)((char *)&prec->dly2 - (char *)prec);
  pdbRecordType->papFldDes[61]->size=sizeof(prec->dol2);
  pdbRecordType->papFldDes[61]->offset=(short)((char *)&prec->dol2 - (char *)prec);
  pdbRecordType->papFldDes[62]->size=sizeof(prec->do2);
  pdbRecordType->papFldDes[62]->offset=(short)((char *)&prec->do2 - (char *)prec);
  pdbRecordType->papFldDes[63]->size=sizeof(prec->lnk2);
  pdbRecordType->papFldDes[63]->offset=(short)((char *)&prec->lnk2 - (char *)prec);
  pdbRecordType->papFldDes[64]->size=sizeof(prec->str2);
  pdbRecordType->papFldDes[64]->offset=(short)((char *)&prec->str2 - (char *)prec);
  pdbRecordType->papFldDes[65]->size=sizeof(prec->dt2);
  pdbRecordType->papFldDes[65]->offset=(short)((char *)&prec->dt2 - (char *)prec);
  pdbRecordType->papFldDes[66]->size=sizeof(prec->lt2);
  pdbRecordType->papFldDes[66]->offset=(short)((char *)&prec->lt2 - (char *)prec);
  pdbRecordType->papFldDes[67]->size=sizeof(prec->wait2);
  pdbRecordType->papFldDes[67]->offset=(short)((char *)&prec->wait2 - (char *)prec);
  pdbRecordType->papFldDes[68]->size=sizeof(prec->wtg2);
  pdbRecordType->papFldDes[68]->offset=(short)((char *)&prec->wtg2 - (char *)prec);
  pdbRecordType->papFldDes[69]->size=sizeof(prec->ix2);
  pdbRecordType->papFldDes[69]->offset=(short)((char *)&prec->ix2 - (char *)prec);
  pdbRecordType->papFldDes[70]->size=sizeof(prec->dol2v);
  pdbRecordType->papFldDes[70]->offset=(short)((char *)&prec->dol2v - (char *)prec);
  pdbRecordType->papFldDes[71]->size=sizeof(prec->lnk2v);
  pdbRecordType->papFldDes[71]->offset=(short)((char *)&prec->lnk2v - (char *)prec);
  pdbRecordType->papFldDes[72]->size=sizeof(prec->dly3);
  pdbRecordType->papFldDes[72]->offset=(short)((char *)&prec->dly3 - (char *)prec);
  pdbRecordType->papFldDes[73]->size=sizeof(prec->dol3);
  pdbRecordType->papFldDes[73]->offset=(short)((char *)&prec->dol3 - (char *)prec);
  pdbRecordType->papFldDes[74]->size=sizeof(prec->do3);
  pdbRecordType->papFldDes[74]->offset=(short)((char *)&prec->do3 - (char *)prec);
  pdbRecordType->papFldDes[75]->size=sizeof(prec->lnk3);
  pdbRecordType->papFldDes[75]->offset=(short)((char *)&prec->lnk3 - (char *)prec);
  pdbRecordType->papFldDes[76]->size=sizeof(prec->str3);
  pdbRecordType->papFldDes[76]->offset=(short)((char *)&prec->str3 - (char *)prec);
  pdbRecordType->papFldDes[77]->size=sizeof(prec->dt3);
  pdbRecordType->papFldDes[77]->offset=(short)((char *)&prec->dt3 - (char *)prec);
  pdbRecordType->papFldDes[78]->size=sizeof(prec->lt3);
  pdbRecordType->papFldDes[78]->offset=(short)((char *)&prec->lt3 - (char *)prec);
  pdbRecordType->papFldDes[79]->size=sizeof(prec->wait3);
  pdbRecordType->papFldDes[79]->offset=(short)((char *)&prec->wait3 - (char *)prec);
  pdbRecordType->papFldDes[80]->size=sizeof(prec->wtg3);
  pdbRecordType->papFldDes[80]->offset=(short)((char *)&prec->wtg3 - (char *)prec);
  pdbRecordType->papFldDes[81]->size=sizeof(prec->ix3);
  pdbRecordType->papFldDes[81]->offset=(short)((char *)&prec->ix3 - (char *)prec);
  pdbRecordType->papFldDes[82]->size=sizeof(prec->dol3v);
  pdbRecordType->papFldDes[82]->offset=(short)((char *)&prec->dol3v - (char *)prec);
  pdbRecordType->papFldDes[83]->size=sizeof(prec->lnk3v);
  pdbRecordType->papFldDes[83]->offset=(short)((char *)&prec->lnk3v - (char *)prec);
  pdbRecordType->papFldDes[84]->size=sizeof(prec->dly4);
  pdbRecordType->papFldDes[84]->offset=(short)((char *)&prec->dly4 - (char *)prec);
  pdbRecordType->papFldDes[85]->size=sizeof(prec->dol4);
  pdbRecordType->papFldDes[85]->offset=(short)((char *)&prec->dol4 - (char *)prec);
  pdbRecordType->papFldDes[86]->size=sizeof(prec->do4);
  pdbRecordType->papFldDes[86]->offset=(short)((char *)&prec->do4 - (char *)prec);
  pdbRecordType->papFldDes[87]->size=sizeof(prec->lnk4);
  pdbRecordType->papFldDes[87]->offset=(short)((char *)&prec->lnk4 - (char *)prec);
  pdbRecordType->papFldDes[88]->size=sizeof(prec->str4);
  pdbRecordType->papFldDes[88]->offset=(short)((char *)&prec->str4 - (char *)prec);
  pdbRecordType->papFldDes[89]->size=sizeof(prec->dt4);
  pdbRecordType->papFldDes[89]->offset=(short)((char *)&prec->dt4 - (char *)prec);
  pdbRecordType->papFldDes[90]->size=sizeof(prec->lt4);
  pdbRecordType->papFldDes[90]->offset=(short)((char *)&prec->lt4 - (char *)prec);
  pdbRecordType->papFldDes[91]->size=sizeof(prec->wait4);
  pdbRecordType->papFldDes[91]->offset=(short)((char *)&prec->wait4 - (char *)prec);
  pdbRecordType->papFldDes[92]->size=sizeof(prec->wtg4);
  pdbRecordType->papFldDes[92]->offset=(short)((char *)&prec->wtg4 - (char *)prec);
  pdbRecordType->papFldDes[93]->size=sizeof(prec->ix4);
  pdbRecordType->papFldDes[93]->offset=(short)((char *)&prec->ix4 - (char *)prec);
  pdbRecordType->papFldDes[94]->size=sizeof(prec->dol4v);
  pdbRecordType->papFldDes[94]->offset=(short)((char *)&prec->dol4v - (char *)prec);
  pdbRecordType->papFldDes[95]->size=sizeof(prec->lnk4v);
  pdbRecordType->papFldDes[95]->offset=(short)((char *)&prec->lnk4v - (char *)prec);
  pdbRecordType->papFldDes[96]->size=sizeof(prec->dly5);
  pdbRecordType->papFldDes[96]->offset=(short)((char *)&prec->dly5 - (char *)prec);
  pdbRecordType->papFldDes[97]->size=sizeof(prec->dol5);
  pdbRecordType->papFldDes[97]->offset=(short)((char *)&prec->dol5 - (char *)prec);
  pdbRecordType->papFldDes[98]->size=sizeof(prec->do5);
  pdbRecordType->papFldDes[98]->offset=(short)((char *)&prec->do5 - (char *)prec);
  pdbRecordType->papFldDes[99]->size=sizeof(prec->lnk5);
  pdbRecordType->papFldDes[99]->offset=(short)((char *)&prec->lnk5 - (char *)prec);
  pdbRecordType->papFldDes[100]->size=sizeof(prec->str5);
  pdbRecordType->papFldDes[100]->offset=(short)((char *)&prec->str5 - (char *)prec);
  pdbRecordType->papFldDes[101]->size=sizeof(prec->dt5);
  pdbRecordType->papFldDes[101]->offset=(short)((char *)&prec->dt5 - (char *)prec);
  pdbRecordType->papFldDes[102]->size=sizeof(prec->lt5);
  pdbRecordType->papFldDes[102]->offset=(short)((char *)&prec->lt5 - (char *)prec);
  pdbRecordType->papFldDes[103]->size=sizeof(prec->wait5);
  pdbRecordType->papFldDes[103]->offset=(short)((char *)&prec->wait5 - (char *)prec);
  pdbRecordType->papFldDes[104]->size=sizeof(prec->wtg5);
  pdbRecordType->papFldDes[104]->offset=(short)((char *)&prec->wtg5 - (char *)prec);
  pdbRecordType->papFldDes[105]->size=sizeof(prec->ix5);
  pdbRecordType->papFldDes[105]->offset=(short)((char *)&prec->ix5 - (char *)prec);
  pdbRecordType->papFldDes[106]->size=sizeof(prec->dol5v);
  pdbRecordType->papFldDes[106]->offset=(short)((char *)&prec->dol5v - (char *)prec);
  pdbRecordType->papFldDes[107]->size=sizeof(prec->lnk5v);
  pdbRecordType->papFldDes[107]->offset=(short)((char *)&prec->lnk5v - (char *)prec);
  pdbRecordType->papFldDes[108]->size=sizeof(prec->dly6);
  pdbRecordType->papFldDes[108]->offset=(short)((char *)&prec->dly6 - (char *)prec);
  pdbRecordType->papFldDes[109]->size=sizeof(prec->dol6);
  pdbRecordType->papFldDes[109]->offset=(short)((char *)&prec->dol6 - (char *)prec);
  pdbRecordType->papFldDes[110]->size=sizeof(prec->do6);
  pdbRecordType->papFldDes[110]->offset=(short)((char *)&prec->do6 - (char *)prec);
  pdbRecordType->papFldDes[111]->size=sizeof(prec->lnk6);
  pdbRecordType->papFldDes[111]->offset=(short)((char *)&prec->lnk6 - (char *)prec);
  pdbRecordType->papFldDes[112]->size=sizeof(prec->str6);
  pdbRecordType->papFldDes[112]->offset=(short)((char *)&prec->str6 - (char *)prec);
  pdbRecordType->papFldDes[113]->size=sizeof(prec->dt6);
  pdbRecordType->papFldDes[113]->offset=(short)((char *)&prec->dt6 - (char *)prec);
  pdbRecordType->papFldDes[114]->size=sizeof(prec->lt6);
  pdbRecordType->papFldDes[114]->offset=(short)((char *)&prec->lt6 - (char *)prec);
  pdbRecordType->papFldDes[115]->size=sizeof(prec->wait6);
  pdbRecordType->papFldDes[115]->offset=(short)((char *)&prec->wait6 - (char *)prec);
  pdbRecordType->papFldDes[116]->size=sizeof(prec->wtg6);
  pdbRecordType->papFldDes[116]->offset=(short)((char *)&prec->wtg6 - (char *)prec);
  pdbRecordType->papFldDes[117]->size=sizeof(prec->ix6);
  pdbRecordType->papFldDes[117]->offset=(short)((char *)&prec->ix6 - (char *)prec);
  pdbRecordType->papFldDes[118]->size=sizeof(prec->dol6v);
  pdbRecordType->papFldDes[118]->offset=(short)((char *)&prec->dol6v - (char *)prec);
  pdbRecordType->papFldDes[119]->size=sizeof(prec->lnk6v);
  pdbRecordType->papFldDes[119]->offset=(short)((char *)&prec->lnk6v - (char *)prec);
  pdbRecordType->papFldDes[120]->size=sizeof(prec->dly7);
  pdbRecordType->papFldDes[120]->offset=(short)((char *)&prec->dly7 - (char *)prec);
  pdbRecordType->papFldDes[121]->size=sizeof(prec->dol7);
  pdbRecordType->papFldDes[121]->offset=(short)((char *)&prec->dol7 - (char *)prec);
  pdbRecordType->papFldDes[122]->size=sizeof(prec->do7);
  pdbRecordType->papFldDes[122]->offset=(short)((char *)&prec->do7 - (char *)prec);
  pdbRecordType->papFldDes[123]->size=sizeof(prec->lnk7);
  pdbRecordType->papFldDes[123]->offset=(short)((char *)&prec->lnk7 - (char *)prec);
  pdbRecordType->papFldDes[124]->size=sizeof(prec->str7);
  pdbRecordType->papFldDes[124]->offset=(short)((char *)&prec->str7 - (char *)prec);
  pdbRecordType->papFldDes[125]->size=sizeof(prec->dt7);
  pdbRecordType->papFldDes[125]->offset=(short)((char *)&prec->dt7 - (char *)prec);
  pdbRecordType->papFldDes[126]->size=sizeof(prec->lt7);
  pdbRecordType->papFldDes[126]->offset=(short)((char *)&prec->lt7 - (char *)prec);
  pdbRecordType->papFldDes[127]->size=sizeof(prec->wait7);
  pdbRecordType->papFldDes[127]->offset=(short)((char *)&prec->wait7 - (char *)prec);
  pdbRecordType->papFldDes[128]->size=sizeof(prec->wtg7);
  pdbRecordType->papFldDes[128]->offset=(short)((char *)&prec->wtg7 - (char *)prec);
  pdbRecordType->papFldDes[129]->size=sizeof(prec->ix7);
  pdbRecordType->papFldDes[129]->offset=(short)((char *)&prec->ix7 - (char *)prec);
  pdbRecordType->papFldDes[130]->size=sizeof(prec->dol7v);
  pdbRecordType->papFldDes[130]->offset=(short)((char *)&prec->dol7v - (char *)prec);
  pdbRecordType->papFldDes[131]->size=sizeof(prec->lnk7v);
  pdbRecordType->papFldDes[131]->offset=(short)((char *)&prec->lnk7v - (char *)prec);
  pdbRecordType->papFldDes[132]->size=sizeof(prec->dly8);
  pdbRecordType->papFldDes[132]->offset=(short)((char *)&prec->dly8 - (char *)prec);
  pdbRecordType->papFldDes[133]->size=sizeof(prec->dol8);
  pdbRecordType->papFldDes[133]->offset=(short)((char *)&prec->dol8 - (char *)prec);
  pdbRecordType->papFldDes[134]->size=sizeof(prec->do8);
  pdbRecordType->papFldDes[134]->offset=(short)((char *)&prec->do8 - (char *)prec);
  pdbRecordType->papFldDes[135]->size=sizeof(prec->lnk8);
  pdbRecordType->papFldDes[135]->offset=(short)((char *)&prec->lnk8 - (char *)prec);
  pdbRecordType->papFldDes[136]->size=sizeof(prec->str8);
  pdbRecordType->papFldDes[136]->offset=(short)((char *)&prec->str8 - (char *)prec);
  pdbRecordType->papFldDes[137]->size=sizeof(prec->dt8);
  pdbRecordType->papFldDes[137]->offset=(short)((char *)&prec->dt8 - (char *)prec);
  pdbRecordType->papFldDes[138]->size=sizeof(prec->lt8);
  pdbRecordType->papFldDes[138]->offset=(short)((char *)&prec->lt8 - (char *)prec);
  pdbRecordType->papFldDes[139]->size=sizeof(prec->wait8);
  pdbRecordType->papFldDes[139]->offset=(short)((char *)&prec->wait8 - (char *)prec);
  pdbRecordType->papFldDes[140]->size=sizeof(prec->wtg8);
  pdbRecordType->papFldDes[140]->offset=(short)((char *)&prec->wtg8 - (char *)prec);
  pdbRecordType->papFldDes[141]->size=sizeof(prec->ix8);
  pdbRecordType->papFldDes[141]->offset=(short)((char *)&prec->ix8 - (char *)prec);
  pdbRecordType->papFldDes[142]->size=sizeof(prec->dol8v);
  pdbRecordType->papFldDes[142]->offset=(short)((char *)&prec->dol8v - (char *)prec);
  pdbRecordType->papFldDes[143]->size=sizeof(prec->lnk8v);
  pdbRecordType->papFldDes[143]->offset=(short)((char *)&prec->lnk8v - (char *)prec);
  pdbRecordType->papFldDes[144]->size=sizeof(prec->dly9);
  pdbRecordType->papFldDes[144]->offset=(short)((char *)&prec->dly9 - (char *)prec);
  pdbRecordType->papFldDes[145]->size=sizeof(prec->dol9);
  pdbRecordType->papFldDes[145]->offset=(short)((char *)&prec->dol9 - (char *)prec);
  pdbRecordType->papFldDes[146]->size=sizeof(prec->do9);
  pdbRecordType->papFldDes[146]->offset=(short)((char *)&prec->do9 - (char *)prec);
  pdbRecordType->papFldDes[147]->size=sizeof(prec->lnk9);
  pdbRecordType->papFldDes[147]->offset=(short)((char *)&prec->lnk9 - (char *)prec);
  pdbRecordType->papFldDes[148]->size=sizeof(prec->str9);
  pdbRecordType->papFldDes[148]->offset=(short)((char *)&prec->str9 - (char *)prec);
  pdbRecordType->papFldDes[149]->size=sizeof(prec->dt9);
  pdbRecordType->papFldDes[149]->offset=(short)((char *)&prec->dt9 - (char *)prec);
  pdbRecordType->papFldDes[150]->size=sizeof(prec->lt9);
  pdbRecordType->papFldDes[150]->offset=(short)((char *)&prec->lt9 - (char *)prec);
  pdbRecordType->papFldDes[151]->size=sizeof(prec->wait9);
  pdbRecordType->papFldDes[151]->offset=(short)((char *)&prec->wait9 - (char *)prec);
  pdbRecordType->papFldDes[152]->size=sizeof(prec->wtg9);
  pdbRecordType->papFldDes[152]->offset=(short)((char *)&prec->wtg9 - (char *)prec);
  pdbRecordType->papFldDes[153]->size=sizeof(prec->ix9);
  pdbRecordType->papFldDes[153]->offset=(short)((char *)&prec->ix9 - (char *)prec);
  pdbRecordType->papFldDes[154]->size=sizeof(prec->dol9v);
  pdbRecordType->papFldDes[154]->offset=(short)((char *)&prec->dol9v - (char *)prec);
  pdbRecordType->papFldDes[155]->size=sizeof(prec->lnk9v);
  pdbRecordType->papFldDes[155]->offset=(short)((char *)&prec->lnk9v - (char *)prec);
  pdbRecordType->papFldDes[156]->size=sizeof(prec->dlya);
  pdbRecordType->papFldDes[156]->offset=(short)((char *)&prec->dlya - (char *)prec);
  pdbRecordType->papFldDes[157]->size=sizeof(prec->dola);
  pdbRecordType->papFldDes[157]->offset=(short)((char *)&prec->dola - (char *)prec);
  pdbRecordType->papFldDes[158]->size=sizeof(prec->doa);
  pdbRecordType->papFldDes[158]->offset=(short)((char *)&prec->doa - (char *)prec);
  pdbRecordType->papFldDes[159]->size=sizeof(prec->lnka);
  pdbRecordType->papFldDes[159]->offset=(short)((char *)&prec->lnka - (char *)prec);
  pdbRecordType->papFldDes[160]->size=sizeof(prec->stra);
  pdbRecordType->papFldDes[160]->offset=(short)((char *)&prec->stra - (char *)prec);
  pdbRecordType->papFldDes[161]->size=sizeof(prec->dta);
  pdbRecordType->papFldDes[161]->offset=(short)((char *)&prec->dta - (char *)prec);
  pdbRecordType->papFldDes[162]->size=sizeof(prec->lta);
  pdbRecordType->papFldDes[162]->offset=(short)((char *)&prec->lta - (char *)prec);
  pdbRecordType->papFldDes[163]->size=sizeof(prec->waita);
  pdbRecordType->papFldDes[163]->offset=(short)((char *)&prec->waita - (char *)prec);
  pdbRecordType->papFldDes[164]->size=sizeof(prec->wtga);
  pdbRecordType->papFldDes[164]->offset=(short)((char *)&prec->wtga - (char *)prec);
  pdbRecordType->papFldDes[165]->size=sizeof(prec->ixa);
  pdbRecordType->papFldDes[165]->offset=(short)((char *)&prec->ixa - (char *)prec);
  pdbRecordType->papFldDes[166]->size=sizeof(prec->dolav);
  pdbRecordType->papFldDes[166]->offset=(short)((char *)&prec->dolav - (char *)prec);
  pdbRecordType->papFldDes[167]->size=sizeof(prec->lnkav);
  pdbRecordType->papFldDes[167]->offset=(short)((char *)&prec->lnkav - (char *)prec);
  pdbRecordType->papFldDes[168]->size=sizeof(prec->abort);
  pdbRecordType->papFldDes[168]->offset=(short)((char *)&prec->abort - (char *)prec);
  pdbRecordType->papFldDes[169]->size=sizeof(prec->aborting);
  pdbRecordType->papFldDes[169]->offset=(short)((char *)&prec->aborting - (char *)prec);
  pdbRecordType->papFldDes[170]->size=sizeof(prec->busy);
  pdbRecordType->papFldDes[170]->offset=(short)((char *)&prec->busy - (char *)prec);
    pdbRecordType->rec_size = sizeof(*prec);
    return(0);
}
epicsExportRegistrar(sseqRecordSizeOffset);
#ifdef __cplusplus
}
#endif
#endif /*GEN_SIZE_OFFSET*/
