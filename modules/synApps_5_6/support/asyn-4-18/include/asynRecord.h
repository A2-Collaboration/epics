/* asynRecord.h generated from asynRecord.dbd */

#ifndef INC_asynRecord_H
#define INC_asynRecord_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "epicsTime.h"

typedef enum {
    serialPRTY_unknown              /* Unknown */,
    serialPRTY_None                 /* None */,
    serialPRTY_Even                 /* Even */,
    serialPRTY_Odd                  /* Odd */,
    serialPRTY_NUM_CHOICES
} serialPRTY;

typedef enum {
    asynAUTOCONNECT_noAutoConnect   /* noAutoConnect */,
    asynAUTOCONNECT_autoConnect     /* autoConnect */,
    asynAUTOCONNECT_NUM_CHOICES
} asynAUTOCONNECT;

typedef enum {
    asynFMT_ASCII                   /* ASCII */,
    asynFMT_Hybrid                  /* Hybrid */,
    asynFMT_Binary                  /* Binary */,
    asynFMT_NUM_CHOICES
} asynFMT;

typedef enum {
    serialSBIT_unknown              /* Unknown */,
    serialSBIT_1                    /* 1 */,
    serialSBIT_2                    /* 2 */,
    serialSBIT_NUM_CHOICES
} serialSBIT;

typedef enum {
    asynCONNECT_Disconnect          /* Disconnect */,
    asynCONNECT_Connect             /* Connect */,
    asynCONNECT_NUM_CHOICES
} asynCONNECT;

typedef enum {
    gpibUCMD_None                   /* None */,
    gpibUCMD_Device_Clear__DCL_     /* Device Clear (DCL) */,
    gpibUCMD_Local_Lockout__LL0_    /* Local Lockout (LL0) */,
    gpibUCMD_Serial_Poll_Disable__SPD_ /* Serial Poll Disable (SPD) */,
    gpibUCMD_Serial_Poll_Enable__SPE_ /* Serial Poll Enable (SPE) */,
    gpibUCMD_Unlisten__UNL_         /* Unlisten (UNL) */,
    gpibUCMD_Untalk__UNT_           /* Untalk (UNT) */,
    gpibUCMD_NUM_CHOICES
} gpibUCMD;

typedef enum {
    serialBAUD_unknown              /* Unknown */,
    serialBAUD_300                  /* 300 */,
    serialBAUD_600                  /* 600 */,
    serialBAUD_1200                 /* 1200 */,
    serialBAUD_2400                 /* 2400 */,
    serialBAUD_4800                 /* 4800 */,
    serialBAUD_9600                 /* 9600 */,
    serialBAUD_19200                /* 19200 */,
    serialBAUD_38400                /* 38400 */,
    serialBAUD_57600                /* 57600 */,
    serialBAUD_115200               /* 115200 */,
    serialBAUD_230400               /* 230400 */,
    serialBAUD_NUM_CHOICES
} serialBAUD;

typedef enum {
    asynTRACE_Off                   /* Off */,
    asynTRACE_On                    /* On */,
    asynTRACE_NUM_CHOICES
} asynTRACE;

typedef enum {
    asynEOMREASONNone               /* None */,
    asynEOMREASONCNT                /* Count */,
    asynEOMREASONEOS                /* Eos */,
    asynEOMREASONCNTEOS             /* Count Eos */,
    asynEOMREASONEND                /* End */,
    asynEOMREASONCNTEND             /* Count End */,
    asynEOMREASONEOSEND             /* Eos End */,
    asynEOMREASONCNTEOSEND          /* Count Eos End */,
    asynEOMREASON_NUM_CHOICES
} asynEOMREASON;

typedef enum {
    gpibACMD_None                   /* None */,
    gpibACMD_Group_Execute_Trig___GET_ /* Group Execute Trig. (GET) */,
    gpibACMD_Go_To_Local__GTL_      /* Go To Local (GTL) */,
    gpibACMD_Selected_Dev__Clear__SDC_ /* Selected Dev. Clear (SDC) */,
    gpibACMD_Take_Control__TCT_     /* Take Control (TCT) */,
    gpibACMD_Serial_Poll            /* Serial Poll */,
    gpibACMD_NUM_CHOICES
} gpibACMD;

typedef enum {
    serialMCTL_unknown              /* Unknown */,
    serialMCTL_CLOCAL               /* CLOCAL */,
    serialMCTL_Yes                  /* YES */,
    serialMCTL_NUM_CHOICES
} serialMCTL;

typedef enum {
    asynTMOD_Write_Read             /* Write/Read */,
    asynTMOD_Write                  /* Write */,
    asynTMOD_Read                   /* Read */,
    asynTMOD_Flush                  /* Flush */,
    asynTMOD_NoIO                   /* NoI/O */,
    asynTMOD_NUM_CHOICES
} asynTMOD;

typedef enum {
    serialFCTL_unknown              /* Unknown */,
    serialFCTL_None                 /* None */,
    serialFCTL_Hardware             /* Hardware */,
    serialFCTL_NUM_CHOICES
} serialFCTL;

typedef enum {
    asynENABLE_Disable              /* Disable */,
    asynENABLE_Enable               /* Enable */,
    asynENABLE_NUM_CHOICES
} asynENABLE;

typedef enum {
    serialIX_unknown                /* Unknown */,
    serialIX_No                     /* No */,
    serialIX_Yes                    /* Yes */,
    serialIX_NUM_CHOICES
} serialIX;

typedef enum {
    asynINTERFACE_OCTET             /* asynOctet */,
    asynINTERFACE_INT32             /* asynInt32 */,
    asynINTERFACE_UINT32            /* asynUInt32Digital */,
    asynINTERFACE_FLOAT64           /* asynFloat64 */,
    asynINTERFACE_NUM_CHOICES
} asynINTERFACE;

typedef enum {
    serialDBIT_unknown              /* Unknown */,
    serialDBIT_5                    /* 5 */,
    serialDBIT_6                    /* 6 */,
    serialDBIT_7                    /* 7 */,
    serialDBIT_8                    /* 8 */,
    serialDBIT_NUM_CHOICES
} serialDBIT;

typedef struct asynRecord {
    char                name[61];   /* Record Name */
    char                desc[41];   /* Descriptor */
    char                asg[29];    /* Access Security Group */
    epicsEnum16         scan;       /* Scan Mechanism */
    epicsEnum16         pini;       /* Process at iocInit */
    epicsInt16          phas;       /* Scan Phase */
    char                evnt[40];   /* Event Name */
    epicsInt16          tse;        /* Time Stamp Event */
    DBLINK              tsel;       /* Time Stamp Link */
    epicsEnum16         dtyp;       /* Device Type */
    epicsInt16          disv;       /* Disable Value */
    epicsInt16          disa;       /* Disable */
    DBLINK              sdis;       /* Scanning Disable */
    epicsMutexId        mlok;       /* Monitor lock */
    ELLLIST             mlis;       /* Monitor List */
    epicsUInt8          disp;       /* Disable putField */
    epicsUInt8          proc;       /* Force Processing */
    epicsEnum16         stat;       /* Alarm Status */
    epicsEnum16         sevr;       /* Alarm Severity */
    epicsEnum16         nsta;       /* New Alarm Status */
    epicsEnum16         nsev;       /* New Alarm Severity */
    epicsEnum16         acks;       /* Alarm Ack Severity */
    epicsEnum16         ackt;       /* Alarm Ack Transient */
    epicsEnum16         diss;       /* Disable Alarm Sevrty */
    epicsUInt8          lcnt;       /* Lock Count */
    epicsUInt8          pact;       /* Record active */
    epicsUInt8          putf;       /* dbPutField process */
    epicsUInt8          rpro;       /* Reprocess  */
    struct asgMember    *asp;       /* Access Security Pvt */
    struct processNotify *ppn;      /* pprocessNotify */
    struct processNotifyRecord *ppnr; /* pprocessNotifyRecord */
    struct scan_element *spvt;      /* Scan Private */
    struct rset         *rset;      /* Address of RSET */
    struct dset         *dset;      /* DSET address */
    void                *dpvt;      /* Device Private */
    struct dbRecordType *rdes;      /* Address of dbRecordType */
    struct lockRecord   *lset;      /* Lock Set */
    epicsEnum16         prio;       /* Scheduling Priority */
    epicsUInt8          tpro;       /* Trace Processing */
    char                bkpt;       /* Break Point */
    epicsUInt8          udf;        /* Undefined */
    epicsEnum16         udfs;       /* Undefined Alarm Sevrty */
    epicsTimeStamp      time;       /* Time */
    DBLINK              flnk;       /* Forward Process Link */
    epicsInt32          val;        /* Value field (unused) */
    char                port[40];   /* asyn port */
    epicsInt32          addr;       /* asyn address */
    epicsEnum16         pcnct;      /* Port Connect/Disconnect */
    char                drvinfo[40];/* Driver info string */
    epicsInt32          reason;     /* asynUser->reason */
    epicsEnum16         tmod;       /* Transaction mode */
    epicsFloat64        tmot;       /* Timeout (sec) */
    epicsEnum16         iface;      /* Interface */
    epicsInt32          octetiv;    /* asynOctet is valid */
    epicsInt32          optioniv;   /* asynOption is valid */
    epicsInt32          gpibiv;     /* asynGPIB is valid */
    epicsInt32          i32iv;      /* asynInt32 is valid */
    epicsInt32          ui32iv;     /* asynUInt32Digital is valid */
    epicsInt32          f64iv;      /* asynFloat64 is valid */
    char                aout[40];   /* Output (command) string */
    char                oeos[40];   /* Output delimiter */
    epicsInt8           bout;       /* Output binary data */
    void *optr;                     /* Output buffer pointer */
    epicsInt32          omax;       /* Max. size of output array */
    epicsInt32          nowt;       /* Number of bytes to write */
    epicsInt32          nawt;       /* Number of bytes actually written */
    epicsEnum16         ofmt;       /* Output format */
    char                ainp[40];   /* Input (response) string */
    char                tinp[40];   /* Translated input string */
    char                ieos[40];   /* Input Delimiter */
    epicsInt8           binp;       /* Input binary data */
    void *iptr;                     /* Input buffer pointer */
    epicsInt32          imax;       /* Max. size of input array */
    epicsInt32          nrrd;       /* Number of bytes to read */
    epicsInt32          nord;       /* Number of bytes read */
    epicsEnum16         ifmt;       /* Input format */
    epicsEnum16         eomr;       /* EOM reason */
    epicsInt32          i32inp;     /* asynInt32 input */
    epicsInt32          i32out;     /* asynInt32 output */
    epicsUInt32         ui32inp;    /* asynUInt32Digital input */
    epicsUInt32         ui32out;    /* asynUInt32Digital output */
    epicsUInt32         ui32mask;   /* asynUInt32Digital mask */
    epicsFloat64        f64inp;     /* asynFloat64 input */
    epicsFloat64        f64out;     /* asynFloat64 output */
    epicsEnum16         baud;       /* Baud rate */
    epicsEnum16         prty;       /* Parity */
    epicsEnum16         dbit;       /* Data bits */
    epicsEnum16         sbit;       /* Stop bits */
    epicsEnum16         mctl;       /* Modem control */
    epicsEnum16         fctl;       /* Flow control */
    epicsEnum16         ixon;       /* Output XON/XOFF */
    epicsEnum16         ixoff;      /* Input XON/XOFF */
    epicsEnum16         ixany;      /* XON=any character */
    epicsEnum16         ucmd;       /* Universal command */
    epicsEnum16         acmd;       /* Addressed command */
    epicsUInt8          spr;        /* Serial poll response */
    epicsInt32          tmsk;       /* Trace mask */
    epicsEnum16         tb0;        /* Trace error */
    epicsEnum16         tb1;        /* Trace IO device */
    epicsEnum16         tb2;        /* Trace IO filter */
    epicsEnum16         tb3;        /* Trace IO driver */
    epicsEnum16         tb4;        /* Trace flow */
    epicsInt32          tiom;       /* Trace I/O mask */
    epicsEnum16         tib0;       /* Trace IO ASCII */
    epicsEnum16         tib1;       /* Trace IO escape */
    epicsEnum16         tib2;       /* Trace IO hex */
    epicsInt32          tsiz;       /* Trace IO truncate size */
    char                tfil[40];   /* Trace IO file */
    epicsEnum16         auct;       /* Autoconnect */
    epicsEnum16         cnct;       /* Connect/Disconnect */
    epicsEnum16         enbl;       /* Enable/Disable */
    char *errs;                     /* Error string */
    epicsUInt8          aqr;        /* Abort queueRequest */
} asynRecord;

typedef enum {
	asynRecordNAME = 0,
	asynRecordDESC = 1,
	asynRecordASG = 2,
	asynRecordSCAN = 3,
	asynRecordPINI = 4,
	asynRecordPHAS = 5,
	asynRecordEVNT = 6,
	asynRecordTSE = 7,
	asynRecordTSEL = 8,
	asynRecordDTYP = 9,
	asynRecordDISV = 10,
	asynRecordDISA = 11,
	asynRecordSDIS = 12,
	asynRecordMLOK = 13,
	asynRecordMLIS = 14,
	asynRecordDISP = 15,
	asynRecordPROC = 16,
	asynRecordSTAT = 17,
	asynRecordSEVR = 18,
	asynRecordNSTA = 19,
	asynRecordNSEV = 20,
	asynRecordACKS = 21,
	asynRecordACKT = 22,
	asynRecordDISS = 23,
	asynRecordLCNT = 24,
	asynRecordPACT = 25,
	asynRecordPUTF = 26,
	asynRecordRPRO = 27,
	asynRecordASP = 28,
	asynRecordPPN = 29,
	asynRecordPPNR = 30,
	asynRecordSPVT = 31,
	asynRecordRSET = 32,
	asynRecordDSET = 33,
	asynRecordDPVT = 34,
	asynRecordRDES = 35,
	asynRecordLSET = 36,
	asynRecordPRIO = 37,
	asynRecordTPRO = 38,
	asynRecordBKPT = 39,
	asynRecordUDF = 40,
	asynRecordUDFS = 41,
	asynRecordTIME = 42,
	asynRecordFLNK = 43,
	asynRecordVAL = 44,
	asynRecordPORT = 45,
	asynRecordADDR = 46,
	asynRecordPCNCT = 47,
	asynRecordDRVINFO = 48,
	asynRecordREASON = 49,
	asynRecordTMOD = 50,
	asynRecordTMOT = 51,
	asynRecordIFACE = 52,
	asynRecordOCTETIV = 53,
	asynRecordOPTIONIV = 54,
	asynRecordGPIBIV = 55,
	asynRecordI32IV = 56,
	asynRecordUI32IV = 57,
	asynRecordF64IV = 58,
	asynRecordAOUT = 59,
	asynRecordOEOS = 60,
	asynRecordBOUT = 61,
	asynRecordOPTR = 62,
	asynRecordOMAX = 63,
	asynRecordNOWT = 64,
	asynRecordNAWT = 65,
	asynRecordOFMT = 66,
	asynRecordAINP = 67,
	asynRecordTINP = 68,
	asynRecordIEOS = 69,
	asynRecordBINP = 70,
	asynRecordIPTR = 71,
	asynRecordIMAX = 72,
	asynRecordNRRD = 73,
	asynRecordNORD = 74,
	asynRecordIFMT = 75,
	asynRecordEOMR = 76,
	asynRecordI32INP = 77,
	asynRecordI32OUT = 78,
	asynRecordUI32INP = 79,
	asynRecordUI32OUT = 80,
	asynRecordUI32MASK = 81,
	asynRecordF64INP = 82,
	asynRecordF64OUT = 83,
	asynRecordBAUD = 84,
	asynRecordPRTY = 85,
	asynRecordDBIT = 86,
	asynRecordSBIT = 87,
	asynRecordMCTL = 88,
	asynRecordFCTL = 89,
	asynRecordIXON = 90,
	asynRecordIXOFF = 91,
	asynRecordIXANY = 92,
	asynRecordUCMD = 93,
	asynRecordACMD = 94,
	asynRecordSPR = 95,
	asynRecordTMSK = 96,
	asynRecordTB0 = 97,
	asynRecordTB1 = 98,
	asynRecordTB2 = 99,
	asynRecordTB3 = 100,
	asynRecordTB4 = 101,
	asynRecordTIOM = 102,
	asynRecordTIB0 = 103,
	asynRecordTIB1 = 104,
	asynRecordTIB2 = 105,
	asynRecordTSIZ = 106,
	asynRecordTFIL = 107,
	asynRecordAUCT = 108,
	asynRecordCNCT = 109,
	asynRecordENBL = 110,
	asynRecordERRS = 111,
	asynRecordAQR = 112
} asynFieldIndex;

#ifdef GEN_SIZE_OFFSET

#ifdef __cplusplus
extern "C" {
#endif
#include <epicsExport.h>
static int asynRecordSizeOffset(dbRecordType *prt)
{
    asynRecord *prec = 0;
    prt->papFldDes[asynRecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[asynRecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[asynRecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[asynRecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[asynRecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[asynRecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[asynRecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[asynRecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[asynRecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[asynRecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[asynRecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[asynRecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[asynRecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[asynRecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[asynRecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[asynRecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[asynRecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[asynRecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[asynRecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[asynRecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[asynRecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[asynRecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[asynRecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[asynRecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[asynRecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[asynRecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[asynRecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[asynRecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[asynRecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[asynRecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[asynRecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[asynRecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[asynRecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[asynRecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[asynRecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[asynRecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[asynRecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[asynRecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[asynRecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[asynRecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[asynRecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[asynRecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[asynRecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[asynRecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[asynRecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[asynRecordPORT]->size = sizeof(prec->port);
    prt->papFldDes[asynRecordADDR]->size = sizeof(prec->addr);
    prt->papFldDes[asynRecordPCNCT]->size = sizeof(prec->pcnct);
    prt->papFldDes[asynRecordDRVINFO]->size = sizeof(prec->drvinfo);
    prt->papFldDes[asynRecordREASON]->size = sizeof(prec->reason);
    prt->papFldDes[asynRecordTMOD]->size = sizeof(prec->tmod);
    prt->papFldDes[asynRecordTMOT]->size = sizeof(prec->tmot);
    prt->papFldDes[asynRecordIFACE]->size = sizeof(prec->iface);
    prt->papFldDes[asynRecordOCTETIV]->size = sizeof(prec->octetiv);
    prt->papFldDes[asynRecordOPTIONIV]->size = sizeof(prec->optioniv);
    prt->papFldDes[asynRecordGPIBIV]->size = sizeof(prec->gpibiv);
    prt->papFldDes[asynRecordI32IV]->size = sizeof(prec->i32iv);
    prt->papFldDes[asynRecordUI32IV]->size = sizeof(prec->ui32iv);
    prt->papFldDes[asynRecordF64IV]->size = sizeof(prec->f64iv);
    prt->papFldDes[asynRecordAOUT]->size = sizeof(prec->aout);
    prt->papFldDes[asynRecordOEOS]->size = sizeof(prec->oeos);
    prt->papFldDes[asynRecordBOUT]->size = sizeof(prec->bout);
    prt->papFldDes[asynRecordOPTR]->size = sizeof(prec->optr);
    prt->papFldDes[asynRecordOMAX]->size = sizeof(prec->omax);
    prt->papFldDes[asynRecordNOWT]->size = sizeof(prec->nowt);
    prt->papFldDes[asynRecordNAWT]->size = sizeof(prec->nawt);
    prt->papFldDes[asynRecordOFMT]->size = sizeof(prec->ofmt);
    prt->papFldDes[asynRecordAINP]->size = sizeof(prec->ainp);
    prt->papFldDes[asynRecordTINP]->size = sizeof(prec->tinp);
    prt->papFldDes[asynRecordIEOS]->size = sizeof(prec->ieos);
    prt->papFldDes[asynRecordBINP]->size = sizeof(prec->binp);
    prt->papFldDes[asynRecordIPTR]->size = sizeof(prec->iptr);
    prt->papFldDes[asynRecordIMAX]->size = sizeof(prec->imax);
    prt->papFldDes[asynRecordNRRD]->size = sizeof(prec->nrrd);
    prt->papFldDes[asynRecordNORD]->size = sizeof(prec->nord);
    prt->papFldDes[asynRecordIFMT]->size = sizeof(prec->ifmt);
    prt->papFldDes[asynRecordEOMR]->size = sizeof(prec->eomr);
    prt->papFldDes[asynRecordI32INP]->size = sizeof(prec->i32inp);
    prt->papFldDes[asynRecordI32OUT]->size = sizeof(prec->i32out);
    prt->papFldDes[asynRecordUI32INP]->size = sizeof(prec->ui32inp);
    prt->papFldDes[asynRecordUI32OUT]->size = sizeof(prec->ui32out);
    prt->papFldDes[asynRecordUI32MASK]->size = sizeof(prec->ui32mask);
    prt->papFldDes[asynRecordF64INP]->size = sizeof(prec->f64inp);
    prt->papFldDes[asynRecordF64OUT]->size = sizeof(prec->f64out);
    prt->papFldDes[asynRecordBAUD]->size = sizeof(prec->baud);
    prt->papFldDes[asynRecordPRTY]->size = sizeof(prec->prty);
    prt->papFldDes[asynRecordDBIT]->size = sizeof(prec->dbit);
    prt->papFldDes[asynRecordSBIT]->size = sizeof(prec->sbit);
    prt->papFldDes[asynRecordMCTL]->size = sizeof(prec->mctl);
    prt->papFldDes[asynRecordFCTL]->size = sizeof(prec->fctl);
    prt->papFldDes[asynRecordIXON]->size = sizeof(prec->ixon);
    prt->papFldDes[asynRecordIXOFF]->size = sizeof(prec->ixoff);
    prt->papFldDes[asynRecordIXANY]->size = sizeof(prec->ixany);
    prt->papFldDes[asynRecordUCMD]->size = sizeof(prec->ucmd);
    prt->papFldDes[asynRecordACMD]->size = sizeof(prec->acmd);
    prt->papFldDes[asynRecordSPR]->size = sizeof(prec->spr);
    prt->papFldDes[asynRecordTMSK]->size = sizeof(prec->tmsk);
    prt->papFldDes[asynRecordTB0]->size = sizeof(prec->tb0);
    prt->papFldDes[asynRecordTB1]->size = sizeof(prec->tb1);
    prt->papFldDes[asynRecordTB2]->size = sizeof(prec->tb2);
    prt->papFldDes[asynRecordTB3]->size = sizeof(prec->tb3);
    prt->papFldDes[asynRecordTB4]->size = sizeof(prec->tb4);
    prt->papFldDes[asynRecordTIOM]->size = sizeof(prec->tiom);
    prt->papFldDes[asynRecordTIB0]->size = sizeof(prec->tib0);
    prt->papFldDes[asynRecordTIB1]->size = sizeof(prec->tib1);
    prt->papFldDes[asynRecordTIB2]->size = sizeof(prec->tib2);
    prt->papFldDes[asynRecordTSIZ]->size = sizeof(prec->tsiz);
    prt->papFldDes[asynRecordTFIL]->size = sizeof(prec->tfil);
    prt->papFldDes[asynRecordAUCT]->size = sizeof(prec->auct);
    prt->papFldDes[asynRecordCNCT]->size = sizeof(prec->cnct);
    prt->papFldDes[asynRecordENBL]->size = sizeof(prec->enbl);
    prt->papFldDes[asynRecordERRS]->size = sizeof(prec->errs);
    prt->papFldDes[asynRecordAQR]->size = sizeof(prec->aqr);
    prt->papFldDes[asynRecordNAME]->offset = (char *)&prec->name - (char *)prec;
    prt->papFldDes[asynRecordDESC]->offset = (char *)&prec->desc - (char *)prec;
    prt->papFldDes[asynRecordASG]->offset = (char *)&prec->asg - (char *)prec;
    prt->papFldDes[asynRecordSCAN]->offset = (char *)&prec->scan - (char *)prec;
    prt->papFldDes[asynRecordPINI]->offset = (char *)&prec->pini - (char *)prec;
    prt->papFldDes[asynRecordPHAS]->offset = (char *)&prec->phas - (char *)prec;
    prt->papFldDes[asynRecordEVNT]->offset = (char *)&prec->evnt - (char *)prec;
    prt->papFldDes[asynRecordTSE]->offset = (char *)&prec->tse - (char *)prec;
    prt->papFldDes[asynRecordTSEL]->offset = (char *)&prec->tsel - (char *)prec;
    prt->papFldDes[asynRecordDTYP]->offset = (char *)&prec->dtyp - (char *)prec;
    prt->papFldDes[asynRecordDISV]->offset = (char *)&prec->disv - (char *)prec;
    prt->papFldDes[asynRecordDISA]->offset = (char *)&prec->disa - (char *)prec;
    prt->papFldDes[asynRecordSDIS]->offset = (char *)&prec->sdis - (char *)prec;
    prt->papFldDes[asynRecordMLOK]->offset = (char *)&prec->mlok - (char *)prec;
    prt->papFldDes[asynRecordMLIS]->offset = (char *)&prec->mlis - (char *)prec;
    prt->papFldDes[asynRecordDISP]->offset = (char *)&prec->disp - (char *)prec;
    prt->papFldDes[asynRecordPROC]->offset = (char *)&prec->proc - (char *)prec;
    prt->papFldDes[asynRecordSTAT]->offset = (char *)&prec->stat - (char *)prec;
    prt->papFldDes[asynRecordSEVR]->offset = (char *)&prec->sevr - (char *)prec;
    prt->papFldDes[asynRecordNSTA]->offset = (char *)&prec->nsta - (char *)prec;
    prt->papFldDes[asynRecordNSEV]->offset = (char *)&prec->nsev - (char *)prec;
    prt->papFldDes[asynRecordACKS]->offset = (char *)&prec->acks - (char *)prec;
    prt->papFldDes[asynRecordACKT]->offset = (char *)&prec->ackt - (char *)prec;
    prt->papFldDes[asynRecordDISS]->offset = (char *)&prec->diss - (char *)prec;
    prt->papFldDes[asynRecordLCNT]->offset = (char *)&prec->lcnt - (char *)prec;
    prt->papFldDes[asynRecordPACT]->offset = (char *)&prec->pact - (char *)prec;
    prt->papFldDes[asynRecordPUTF]->offset = (char *)&prec->putf - (char *)prec;
    prt->papFldDes[asynRecordRPRO]->offset = (char *)&prec->rpro - (char *)prec;
    prt->papFldDes[asynRecordASP]->offset = (char *)&prec->asp - (char *)prec;
    prt->papFldDes[asynRecordPPN]->offset = (char *)&prec->ppn - (char *)prec;
    prt->papFldDes[asynRecordPPNR]->offset = (char *)&prec->ppnr - (char *)prec;
    prt->papFldDes[asynRecordSPVT]->offset = (char *)&prec->spvt - (char *)prec;
    prt->papFldDes[asynRecordRSET]->offset = (char *)&prec->rset - (char *)prec;
    prt->papFldDes[asynRecordDSET]->offset = (char *)&prec->dset - (char *)prec;
    prt->papFldDes[asynRecordDPVT]->offset = (char *)&prec->dpvt - (char *)prec;
    prt->papFldDes[asynRecordRDES]->offset = (char *)&prec->rdes - (char *)prec;
    prt->papFldDes[asynRecordLSET]->offset = (char *)&prec->lset - (char *)prec;
    prt->papFldDes[asynRecordPRIO]->offset = (char *)&prec->prio - (char *)prec;
    prt->papFldDes[asynRecordTPRO]->offset = (char *)&prec->tpro - (char *)prec;
    prt->papFldDes[asynRecordBKPT]->offset = (char *)&prec->bkpt - (char *)prec;
    prt->papFldDes[asynRecordUDF]->offset = (char *)&prec->udf - (char *)prec;
    prt->papFldDes[asynRecordUDFS]->offset = (char *)&prec->udfs - (char *)prec;
    prt->papFldDes[asynRecordTIME]->offset = (char *)&prec->time - (char *)prec;
    prt->papFldDes[asynRecordFLNK]->offset = (char *)&prec->flnk - (char *)prec;
    prt->papFldDes[asynRecordVAL]->offset = (char *)&prec->val - (char *)prec;
    prt->papFldDes[asynRecordPORT]->offset = (char *)&prec->port - (char *)prec;
    prt->papFldDes[asynRecordADDR]->offset = (char *)&prec->addr - (char *)prec;
    prt->papFldDes[asynRecordPCNCT]->offset = (char *)&prec->pcnct - (char *)prec;
    prt->papFldDes[asynRecordDRVINFO]->offset = (char *)&prec->drvinfo - (char *)prec;
    prt->papFldDes[asynRecordREASON]->offset = (char *)&prec->reason - (char *)prec;
    prt->papFldDes[asynRecordTMOD]->offset = (char *)&prec->tmod - (char *)prec;
    prt->papFldDes[asynRecordTMOT]->offset = (char *)&prec->tmot - (char *)prec;
    prt->papFldDes[asynRecordIFACE]->offset = (char *)&prec->iface - (char *)prec;
    prt->papFldDes[asynRecordOCTETIV]->offset = (char *)&prec->octetiv - (char *)prec;
    prt->papFldDes[asynRecordOPTIONIV]->offset = (char *)&prec->optioniv - (char *)prec;
    prt->papFldDes[asynRecordGPIBIV]->offset = (char *)&prec->gpibiv - (char *)prec;
    prt->papFldDes[asynRecordI32IV]->offset = (char *)&prec->i32iv - (char *)prec;
    prt->papFldDes[asynRecordUI32IV]->offset = (char *)&prec->ui32iv - (char *)prec;
    prt->papFldDes[asynRecordF64IV]->offset = (char *)&prec->f64iv - (char *)prec;
    prt->papFldDes[asynRecordAOUT]->offset = (char *)&prec->aout - (char *)prec;
    prt->papFldDes[asynRecordOEOS]->offset = (char *)&prec->oeos - (char *)prec;
    prt->papFldDes[asynRecordBOUT]->offset = (char *)&prec->bout - (char *)prec;
    prt->papFldDes[asynRecordOPTR]->offset = (char *)&prec->optr - (char *)prec;
    prt->papFldDes[asynRecordOMAX]->offset = (char *)&prec->omax - (char *)prec;
    prt->papFldDes[asynRecordNOWT]->offset = (char *)&prec->nowt - (char *)prec;
    prt->papFldDes[asynRecordNAWT]->offset = (char *)&prec->nawt - (char *)prec;
    prt->papFldDes[asynRecordOFMT]->offset = (char *)&prec->ofmt - (char *)prec;
    prt->papFldDes[asynRecordAINP]->offset = (char *)&prec->ainp - (char *)prec;
    prt->papFldDes[asynRecordTINP]->offset = (char *)&prec->tinp - (char *)prec;
    prt->papFldDes[asynRecordIEOS]->offset = (char *)&prec->ieos - (char *)prec;
    prt->papFldDes[asynRecordBINP]->offset = (char *)&prec->binp - (char *)prec;
    prt->papFldDes[asynRecordIPTR]->offset = (char *)&prec->iptr - (char *)prec;
    prt->papFldDes[asynRecordIMAX]->offset = (char *)&prec->imax - (char *)prec;
    prt->papFldDes[asynRecordNRRD]->offset = (char *)&prec->nrrd - (char *)prec;
    prt->papFldDes[asynRecordNORD]->offset = (char *)&prec->nord - (char *)prec;
    prt->papFldDes[asynRecordIFMT]->offset = (char *)&prec->ifmt - (char *)prec;
    prt->papFldDes[asynRecordEOMR]->offset = (char *)&prec->eomr - (char *)prec;
    prt->papFldDes[asynRecordI32INP]->offset = (char *)&prec->i32inp - (char *)prec;
    prt->papFldDes[asynRecordI32OUT]->offset = (char *)&prec->i32out - (char *)prec;
    prt->papFldDes[asynRecordUI32INP]->offset = (char *)&prec->ui32inp - (char *)prec;
    prt->papFldDes[asynRecordUI32OUT]->offset = (char *)&prec->ui32out - (char *)prec;
    prt->papFldDes[asynRecordUI32MASK]->offset = (char *)&prec->ui32mask - (char *)prec;
    prt->papFldDes[asynRecordF64INP]->offset = (char *)&prec->f64inp - (char *)prec;
    prt->papFldDes[asynRecordF64OUT]->offset = (char *)&prec->f64out - (char *)prec;
    prt->papFldDes[asynRecordBAUD]->offset = (char *)&prec->baud - (char *)prec;
    prt->papFldDes[asynRecordPRTY]->offset = (char *)&prec->prty - (char *)prec;
    prt->papFldDes[asynRecordDBIT]->offset = (char *)&prec->dbit - (char *)prec;
    prt->papFldDes[asynRecordSBIT]->offset = (char *)&prec->sbit - (char *)prec;
    prt->papFldDes[asynRecordMCTL]->offset = (char *)&prec->mctl - (char *)prec;
    prt->papFldDes[asynRecordFCTL]->offset = (char *)&prec->fctl - (char *)prec;
    prt->papFldDes[asynRecordIXON]->offset = (char *)&prec->ixon - (char *)prec;
    prt->papFldDes[asynRecordIXOFF]->offset = (char *)&prec->ixoff - (char *)prec;
    prt->papFldDes[asynRecordIXANY]->offset = (char *)&prec->ixany - (char *)prec;
    prt->papFldDes[asynRecordUCMD]->offset = (char *)&prec->ucmd - (char *)prec;
    prt->papFldDes[asynRecordACMD]->offset = (char *)&prec->acmd - (char *)prec;
    prt->papFldDes[asynRecordSPR]->offset = (char *)&prec->spr - (char *)prec;
    prt->papFldDes[asynRecordTMSK]->offset = (char *)&prec->tmsk - (char *)prec;
    prt->papFldDes[asynRecordTB0]->offset = (char *)&prec->tb0 - (char *)prec;
    prt->papFldDes[asynRecordTB1]->offset = (char *)&prec->tb1 - (char *)prec;
    prt->papFldDes[asynRecordTB2]->offset = (char *)&prec->tb2 - (char *)prec;
    prt->papFldDes[asynRecordTB3]->offset = (char *)&prec->tb3 - (char *)prec;
    prt->papFldDes[asynRecordTB4]->offset = (char *)&prec->tb4 - (char *)prec;
    prt->papFldDes[asynRecordTIOM]->offset = (char *)&prec->tiom - (char *)prec;
    prt->papFldDes[asynRecordTIB0]->offset = (char *)&prec->tib0 - (char *)prec;
    prt->papFldDes[asynRecordTIB1]->offset = (char *)&prec->tib1 - (char *)prec;
    prt->papFldDes[asynRecordTIB2]->offset = (char *)&prec->tib2 - (char *)prec;
    prt->papFldDes[asynRecordTSIZ]->offset = (char *)&prec->tsiz - (char *)prec;
    prt->papFldDes[asynRecordTFIL]->offset = (char *)&prec->tfil - (char *)prec;
    prt->papFldDes[asynRecordAUCT]->offset = (char *)&prec->auct - (char *)prec;
    prt->papFldDes[asynRecordCNCT]->offset = (char *)&prec->cnct - (char *)prec;
    prt->papFldDes[asynRecordENBL]->offset = (char *)&prec->enbl - (char *)prec;
    prt->papFldDes[asynRecordERRS]->offset = (char *)&prec->errs - (char *)prec;
    prt->papFldDes[asynRecordAQR]->offset = (char *)&prec->aqr - (char *)prec;
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(asynRecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_asynRecord_H */
