/* ab1771NRecord.h generated from ab1771NRecord.dbd */

#ifndef INC_ab1771NRecord_H
#define INC_ab1771NRecord_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "epicsTime.h"

typedef enum {
    ab1771N_NIS                     /* 1771-NIS */,
    ab1771N_NIV                     /* 1771-NIV */,
    ab1771N_NIV1                    /* 1771-NIV1 */,
    ab1771N_NIVR                    /* 1771-NIVR */,
    ab1771N_NIVT                    /* 1771-NIVT */,
    ab1771N_NR                      /* 1771-NR */,
    ab1771N_NT1                     /* 1771-NT1 */,
    ab1771N_NT2                     /* 1771-NT2 */,
    ab1771N_NOC                     /* 1771-NOC */,
    ab1771N_NOV                     /* 1771-NOV */,
    ab1771N_NB4T                    /* 1771-NB4T */,
    ab1771N_NB4S                    /* 1771-NB4S */,
    ab1771N_NBSC                    /* 1771-NBSC */,
    ab1771N_NBRC                    /* 1771-NBRC */,
    ab1771N_NBTC                    /* 1771-NBTC */,
    ab1771N_NBV1                    /* 1771-NBV1 */,
    ab1771N_NBVC                    /* 1771-NBVC */,
    ab1771N_NX1                     /* 1771-NX1 */,
    ab1771N_NX2                     /* 1771-NX2 */,
    ab1771N_NX3                     /* 1771-NX3 */,
    ab1771N_NX4                     /* 1771-NX4 */,
    ab1771N_MTYP_NUM_CHOICES
} ab1771N_MTYP;

typedef enum {
    ab1771N_CJS_Ok                  /* Cold Junction Ok */,
    ab1771N_CJS_UnderRange          /* Cold Junction  Under Range */,
    ab1771N_CJS_OverRange           /* Cold Junction  Over Range */,
    ab1771N_CJS_Bad                 /* Cold Junction  bad Value */,
    ab1771N_CJS_NUM_CHOICES
} ab1771N_CJS;

typedef enum {
    ab1771N_UnitsF                  /* degF */,
    ab1771N_UnitsC                  /* degC */,
    ab1771N_UnitsOhms               /* Ohm */,
    ab1771N_Units_NUM_CHOICES
} ab1771N_Units;

typedef enum {
    ab1771N_CMD_None                /* None */,
    ab1771N_Init                    /* Initialize */,
    ab1771N_CMD_NUM_CHOICES
} ab1771N_CMD;

typedef enum {
    ab1771N_TYPE_VA                 /* Volts or Amps */,
    ab1771N_TYPE_tcB                /* tc B */,
    ab1771N_TYPE_tcE                /* tc E */,
    ab1771N_TYPE_tcJ                /* tc J */,
    ab1771N_TYPE_tcK                /* tc K */,
    ab1771N_TYPE_tcR                /* tc R */,
    ab1771N_TYPE_tcS                /* tc S */,
    ab1771N_TYPE_tcT                /* tc T */,
    ab1771N_TYPE_tcC                /* tc C */,
    ab1771N_TYPE_tcN                /* tc N */,
    ab1771N_TYPE_RTDPtEurope        /* RTD 100 ohm Pt, European Standard */,
    ab1771N_TYPE_RTDPtUSA           /* RTD 100 ohm Pt, USA Standard */,
    ab1771N_TYPE_RTDCopper          /* RTD 10 ohm copper */,
    ab1771N_TYPE_RTDNickel          /* RTD 120 ohm nickel */,
    ab1771N_TYPE_NUM_CHOICES
} ab1771N_TYPE;

typedef struct ab1771NRecord {
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
    char                val[40];    /* Status */
    epicsEnum16         cmd;        /* Command */
    epicsEnum16         loca;       /* scanIoRequest comm err */
    epicsUInt16         link;       /* Scanner Number */
    epicsUInt16         rack;       /* Rack */
    epicsUInt16         slot;       /* Slot */
    short	*outm;                    /* Output Message */
    short	*inpm;                    /* Input Message */
    void	*iai1;                     /* Interface for ai */
    void	*iao1;                     /* Interface for ao */
    epicsEnum16         mtyp;       /* Module Type */
    epicsEnum16         scal;       /* Temperature Scale */
    epicsEnum16         cjae;       /* Cold Junction alarm enable */
    epicsEnum16         cjs;        /* Cold Junction status */
    epicsFloat32        cjt;        /* Cold Junction Temperature  */
    epicsEnum16         typ1;       /* Chan 1 type */
    epicsFloat32        fil1;       /* Chan 1 Filter Time Constant (.1 - 10.0)secs */
    epicsFloat32        ral1;       /* Chan 1 Rate Alarm  */
    epicsFloat32        ohm1;       /* Chan 1 10 ohm offset (RTD Copper only) */
    epicsInt16          sta1;       /* Chan 1 status */
    epicsInt16          raw1;       /* Chan 1 raw value */
    epicsEnum16         typ2;       /* Chan 2 type */
    epicsFloat32        fil2;       /* Chan 2 Filter Time Constant (.1 - 10.0)secs */
    epicsFloat32        ral2;       /* Chan 2 Rate Alarm  */
    epicsFloat32        ohm2;       /* Chan 2 10 ohm offset (RTD Copper only) */
    epicsInt16          sta2;       /* Chan 2 status */
    epicsInt16          raw2;       /* Chan 2 raw value */
    epicsEnum16         typ3;       /* Chan 3 type */
    epicsFloat32        fil3;       /* Chan 3 Filter Time Constant (.1 - 10.0)secs */
    epicsFloat32        ral3;       /* Chan 3 Rate Alarm  */
    epicsFloat32        ohm3;       /* Chan 3 10 ohm offset (RTD Copper only) */
    epicsInt16          sta3;       /* Chan 3 status */
    epicsInt16          raw3;       /* Chan 3 raw value */
    epicsEnum16         typ4;       /* Chan 4 type */
    epicsFloat32        fil4;       /* Chan 4 Filter Time Constant (.1 - 10.0)secs */
    epicsFloat32        ral4;       /* Chan 4 Rate Alarm  */
    epicsFloat32        ohm4;       /* Chan 4 10 ohm offset (RTD Copper only) */
    epicsInt16          sta4;       /* Chan 4 status */
    epicsInt16          raw4;       /* Chan 4 raw value */
    epicsEnum16         typ5;       /* Chan 5 type */
    epicsFloat32        fil5;       /* Chan 5 Filter Time Constant (.1 - 10.0)secs */
    epicsFloat32        ral5;       /* Chan 5 Rate Alarm  */
    epicsFloat32        ohm5;       /* Chan 5 10 ohm offset (RTD Copper only) */
    epicsInt16          sta5;       /* Chan 5 status */
    epicsInt16          raw5;       /* Chan 5 raw value */
    epicsEnum16         typ6;       /* Chan 6 type */
    epicsFloat32        fil6;       /* Chan 6 Filter Time Constant (.1 - 10.0)secs */
    epicsFloat32        ral6;       /* Chan 6 Rate Alarm  */
    epicsFloat32        ohm6;       /* Chan 6 10 ohm offset (RTD Copper only) */
    epicsInt16          sta6;       /* Chan 6 status */
    epicsInt16          raw6;       /* Chan 6 raw value */
    epicsEnum16         typ7;       /* Chan 7 type */
    epicsFloat32        fil7;       /* Chan 7 Filter Time Constant (.1 - 10.0)secs */
    epicsFloat32        ral7;       /* Chan 7 Rate Alarm  */
    epicsFloat32        ohm7;       /* Chan 7 10 ohm offset (RTD Copper only) */
    epicsInt16          sta7;       /* Chan 7 status */
    epicsInt16          raw7;       /* Chan 7 raw value */
    epicsEnum16         typ8;       /* Chan 8 type */
    epicsFloat32        fil8;       /* Chan 8 Filter Time Constant (.1 - 10.0)secs */
    epicsFloat32        ral8;       /* Chan 8 Rate Alarm  */
    epicsFloat32        ohm8;       /* Chan 8 10 ohm offset (RTD Copper only) */
    epicsInt16          sta8;       /* Chan 8 status */
    epicsInt16          raw8;       /* Chan 8 raw value */
} ab1771NRecord;

typedef enum {
	ab1771NRecordNAME = 0,
	ab1771NRecordDESC = 1,
	ab1771NRecordASG = 2,
	ab1771NRecordSCAN = 3,
	ab1771NRecordPINI = 4,
	ab1771NRecordPHAS = 5,
	ab1771NRecordEVNT = 6,
	ab1771NRecordTSE = 7,
	ab1771NRecordTSEL = 8,
	ab1771NRecordDTYP = 9,
	ab1771NRecordDISV = 10,
	ab1771NRecordDISA = 11,
	ab1771NRecordSDIS = 12,
	ab1771NRecordMLOK = 13,
	ab1771NRecordMLIS = 14,
	ab1771NRecordDISP = 15,
	ab1771NRecordPROC = 16,
	ab1771NRecordSTAT = 17,
	ab1771NRecordSEVR = 18,
	ab1771NRecordNSTA = 19,
	ab1771NRecordNSEV = 20,
	ab1771NRecordACKS = 21,
	ab1771NRecordACKT = 22,
	ab1771NRecordDISS = 23,
	ab1771NRecordLCNT = 24,
	ab1771NRecordPACT = 25,
	ab1771NRecordPUTF = 26,
	ab1771NRecordRPRO = 27,
	ab1771NRecordASP = 28,
	ab1771NRecordPPN = 29,
	ab1771NRecordPPNR = 30,
	ab1771NRecordSPVT = 31,
	ab1771NRecordRSET = 32,
	ab1771NRecordDSET = 33,
	ab1771NRecordDPVT = 34,
	ab1771NRecordRDES = 35,
	ab1771NRecordLSET = 36,
	ab1771NRecordPRIO = 37,
	ab1771NRecordTPRO = 38,
	ab1771NRecordBKPT = 39,
	ab1771NRecordUDF = 40,
	ab1771NRecordUDFS = 41,
	ab1771NRecordTIME = 42,
	ab1771NRecordFLNK = 43,
	ab1771NRecordVAL = 44,
	ab1771NRecordCMD = 45,
	ab1771NRecordLOCA = 46,
	ab1771NRecordLINK = 47,
	ab1771NRecordRACK = 48,
	ab1771NRecordSLOT = 49,
	ab1771NRecordOUTM = 50,
	ab1771NRecordINPM = 51,
	ab1771NRecordIAI1 = 52,
	ab1771NRecordIAO1 = 53,
	ab1771NRecordMTYP = 54,
	ab1771NRecordSCAL = 55,
	ab1771NRecordCJAE = 56,
	ab1771NRecordCJS = 57,
	ab1771NRecordCJT = 58,
	ab1771NRecordTYP1 = 59,
	ab1771NRecordFIL1 = 60,
	ab1771NRecordRAL1 = 61,
	ab1771NRecordOHM1 = 62,
	ab1771NRecordSTA1 = 63,
	ab1771NRecordRAW1 = 64,
	ab1771NRecordTYP2 = 65,
	ab1771NRecordFIL2 = 66,
	ab1771NRecordRAL2 = 67,
	ab1771NRecordOHM2 = 68,
	ab1771NRecordSTA2 = 69,
	ab1771NRecordRAW2 = 70,
	ab1771NRecordTYP3 = 71,
	ab1771NRecordFIL3 = 72,
	ab1771NRecordRAL3 = 73,
	ab1771NRecordOHM3 = 74,
	ab1771NRecordSTA3 = 75,
	ab1771NRecordRAW3 = 76,
	ab1771NRecordTYP4 = 77,
	ab1771NRecordFIL4 = 78,
	ab1771NRecordRAL4 = 79,
	ab1771NRecordOHM4 = 80,
	ab1771NRecordSTA4 = 81,
	ab1771NRecordRAW4 = 82,
	ab1771NRecordTYP5 = 83,
	ab1771NRecordFIL5 = 84,
	ab1771NRecordRAL5 = 85,
	ab1771NRecordOHM5 = 86,
	ab1771NRecordSTA5 = 87,
	ab1771NRecordRAW5 = 88,
	ab1771NRecordTYP6 = 89,
	ab1771NRecordFIL6 = 90,
	ab1771NRecordRAL6 = 91,
	ab1771NRecordOHM6 = 92,
	ab1771NRecordSTA6 = 93,
	ab1771NRecordRAW6 = 94,
	ab1771NRecordTYP7 = 95,
	ab1771NRecordFIL7 = 96,
	ab1771NRecordRAL7 = 97,
	ab1771NRecordOHM7 = 98,
	ab1771NRecordSTA7 = 99,
	ab1771NRecordRAW7 = 100,
	ab1771NRecordTYP8 = 101,
	ab1771NRecordFIL8 = 102,
	ab1771NRecordRAL8 = 103,
	ab1771NRecordOHM8 = 104,
	ab1771NRecordSTA8 = 105,
	ab1771NRecordRAW8 = 106
} ab1771NFieldIndex;

#ifdef GEN_SIZE_OFFSET

#ifdef __cplusplus
extern "C" {
#endif
#include <epicsExport.h>
static int ab1771NRecordSizeOffset(dbRecordType *prt)
{
    ab1771NRecord *prec = 0;
    prt->papFldDes[ab1771NRecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[ab1771NRecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[ab1771NRecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[ab1771NRecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[ab1771NRecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[ab1771NRecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[ab1771NRecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[ab1771NRecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[ab1771NRecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[ab1771NRecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[ab1771NRecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[ab1771NRecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[ab1771NRecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[ab1771NRecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[ab1771NRecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[ab1771NRecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[ab1771NRecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[ab1771NRecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[ab1771NRecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[ab1771NRecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[ab1771NRecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[ab1771NRecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[ab1771NRecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[ab1771NRecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[ab1771NRecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[ab1771NRecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[ab1771NRecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[ab1771NRecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[ab1771NRecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[ab1771NRecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[ab1771NRecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[ab1771NRecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[ab1771NRecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[ab1771NRecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[ab1771NRecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[ab1771NRecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[ab1771NRecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[ab1771NRecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[ab1771NRecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[ab1771NRecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[ab1771NRecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[ab1771NRecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[ab1771NRecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[ab1771NRecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[ab1771NRecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[ab1771NRecordCMD]->size = sizeof(prec->cmd);
    prt->papFldDes[ab1771NRecordLOCA]->size = sizeof(prec->loca);
    prt->papFldDes[ab1771NRecordLINK]->size = sizeof(prec->link);
    prt->papFldDes[ab1771NRecordRACK]->size = sizeof(prec->rack);
    prt->papFldDes[ab1771NRecordSLOT]->size = sizeof(prec->slot);
    prt->papFldDes[ab1771NRecordOUTM]->size = sizeof(prec->outm);
    prt->papFldDes[ab1771NRecordINPM]->size = sizeof(prec->inpm);
    prt->papFldDes[ab1771NRecordIAI1]->size = sizeof(prec->iai1);
    prt->papFldDes[ab1771NRecordIAO1]->size = sizeof(prec->iao1);
    prt->papFldDes[ab1771NRecordMTYP]->size = sizeof(prec->mtyp);
    prt->papFldDes[ab1771NRecordSCAL]->size = sizeof(prec->scal);
    prt->papFldDes[ab1771NRecordCJAE]->size = sizeof(prec->cjae);
    prt->papFldDes[ab1771NRecordCJS]->size = sizeof(prec->cjs);
    prt->papFldDes[ab1771NRecordCJT]->size = sizeof(prec->cjt);
    prt->papFldDes[ab1771NRecordTYP1]->size = sizeof(prec->typ1);
    prt->papFldDes[ab1771NRecordFIL1]->size = sizeof(prec->fil1);
    prt->papFldDes[ab1771NRecordRAL1]->size = sizeof(prec->ral1);
    prt->papFldDes[ab1771NRecordOHM1]->size = sizeof(prec->ohm1);
    prt->papFldDes[ab1771NRecordSTA1]->size = sizeof(prec->sta1);
    prt->papFldDes[ab1771NRecordRAW1]->size = sizeof(prec->raw1);
    prt->papFldDes[ab1771NRecordTYP2]->size = sizeof(prec->typ2);
    prt->papFldDes[ab1771NRecordFIL2]->size = sizeof(prec->fil2);
    prt->papFldDes[ab1771NRecordRAL2]->size = sizeof(prec->ral2);
    prt->papFldDes[ab1771NRecordOHM2]->size = sizeof(prec->ohm2);
    prt->papFldDes[ab1771NRecordSTA2]->size = sizeof(prec->sta2);
    prt->papFldDes[ab1771NRecordRAW2]->size = sizeof(prec->raw2);
    prt->papFldDes[ab1771NRecordTYP3]->size = sizeof(prec->typ3);
    prt->papFldDes[ab1771NRecordFIL3]->size = sizeof(prec->fil3);
    prt->papFldDes[ab1771NRecordRAL3]->size = sizeof(prec->ral3);
    prt->papFldDes[ab1771NRecordOHM3]->size = sizeof(prec->ohm3);
    prt->papFldDes[ab1771NRecordSTA3]->size = sizeof(prec->sta3);
    prt->papFldDes[ab1771NRecordRAW3]->size = sizeof(prec->raw3);
    prt->papFldDes[ab1771NRecordTYP4]->size = sizeof(prec->typ4);
    prt->papFldDes[ab1771NRecordFIL4]->size = sizeof(prec->fil4);
    prt->papFldDes[ab1771NRecordRAL4]->size = sizeof(prec->ral4);
    prt->papFldDes[ab1771NRecordOHM4]->size = sizeof(prec->ohm4);
    prt->papFldDes[ab1771NRecordSTA4]->size = sizeof(prec->sta4);
    prt->papFldDes[ab1771NRecordRAW4]->size = sizeof(prec->raw4);
    prt->papFldDes[ab1771NRecordTYP5]->size = sizeof(prec->typ5);
    prt->papFldDes[ab1771NRecordFIL5]->size = sizeof(prec->fil5);
    prt->papFldDes[ab1771NRecordRAL5]->size = sizeof(prec->ral5);
    prt->papFldDes[ab1771NRecordOHM5]->size = sizeof(prec->ohm5);
    prt->papFldDes[ab1771NRecordSTA5]->size = sizeof(prec->sta5);
    prt->papFldDes[ab1771NRecordRAW5]->size = sizeof(prec->raw5);
    prt->papFldDes[ab1771NRecordTYP6]->size = sizeof(prec->typ6);
    prt->papFldDes[ab1771NRecordFIL6]->size = sizeof(prec->fil6);
    prt->papFldDes[ab1771NRecordRAL6]->size = sizeof(prec->ral6);
    prt->papFldDes[ab1771NRecordOHM6]->size = sizeof(prec->ohm6);
    prt->papFldDes[ab1771NRecordSTA6]->size = sizeof(prec->sta6);
    prt->papFldDes[ab1771NRecordRAW6]->size = sizeof(prec->raw6);
    prt->papFldDes[ab1771NRecordTYP7]->size = sizeof(prec->typ7);
    prt->papFldDes[ab1771NRecordFIL7]->size = sizeof(prec->fil7);
    prt->papFldDes[ab1771NRecordRAL7]->size = sizeof(prec->ral7);
    prt->papFldDes[ab1771NRecordOHM7]->size = sizeof(prec->ohm7);
    prt->papFldDes[ab1771NRecordSTA7]->size = sizeof(prec->sta7);
    prt->papFldDes[ab1771NRecordRAW7]->size = sizeof(prec->raw7);
    prt->papFldDes[ab1771NRecordTYP8]->size = sizeof(prec->typ8);
    prt->papFldDes[ab1771NRecordFIL8]->size = sizeof(prec->fil8);
    prt->papFldDes[ab1771NRecordRAL8]->size = sizeof(prec->ral8);
    prt->papFldDes[ab1771NRecordOHM8]->size = sizeof(prec->ohm8);
    prt->papFldDes[ab1771NRecordSTA8]->size = sizeof(prec->sta8);
    prt->papFldDes[ab1771NRecordRAW8]->size = sizeof(prec->raw8);
    prt->papFldDes[ab1771NRecordNAME]->offset = (char *)&prec->name - (char *)prec;
    prt->papFldDes[ab1771NRecordDESC]->offset = (char *)&prec->desc - (char *)prec;
    prt->papFldDes[ab1771NRecordASG]->offset = (char *)&prec->asg - (char *)prec;
    prt->papFldDes[ab1771NRecordSCAN]->offset = (char *)&prec->scan - (char *)prec;
    prt->papFldDes[ab1771NRecordPINI]->offset = (char *)&prec->pini - (char *)prec;
    prt->papFldDes[ab1771NRecordPHAS]->offset = (char *)&prec->phas - (char *)prec;
    prt->papFldDes[ab1771NRecordEVNT]->offset = (char *)&prec->evnt - (char *)prec;
    prt->papFldDes[ab1771NRecordTSE]->offset = (char *)&prec->tse - (char *)prec;
    prt->papFldDes[ab1771NRecordTSEL]->offset = (char *)&prec->tsel - (char *)prec;
    prt->papFldDes[ab1771NRecordDTYP]->offset = (char *)&prec->dtyp - (char *)prec;
    prt->papFldDes[ab1771NRecordDISV]->offset = (char *)&prec->disv - (char *)prec;
    prt->papFldDes[ab1771NRecordDISA]->offset = (char *)&prec->disa - (char *)prec;
    prt->papFldDes[ab1771NRecordSDIS]->offset = (char *)&prec->sdis - (char *)prec;
    prt->papFldDes[ab1771NRecordMLOK]->offset = (char *)&prec->mlok - (char *)prec;
    prt->papFldDes[ab1771NRecordMLIS]->offset = (char *)&prec->mlis - (char *)prec;
    prt->papFldDes[ab1771NRecordDISP]->offset = (char *)&prec->disp - (char *)prec;
    prt->papFldDes[ab1771NRecordPROC]->offset = (char *)&prec->proc - (char *)prec;
    prt->papFldDes[ab1771NRecordSTAT]->offset = (char *)&prec->stat - (char *)prec;
    prt->papFldDes[ab1771NRecordSEVR]->offset = (char *)&prec->sevr - (char *)prec;
    prt->papFldDes[ab1771NRecordNSTA]->offset = (char *)&prec->nsta - (char *)prec;
    prt->papFldDes[ab1771NRecordNSEV]->offset = (char *)&prec->nsev - (char *)prec;
    prt->papFldDes[ab1771NRecordACKS]->offset = (char *)&prec->acks - (char *)prec;
    prt->papFldDes[ab1771NRecordACKT]->offset = (char *)&prec->ackt - (char *)prec;
    prt->papFldDes[ab1771NRecordDISS]->offset = (char *)&prec->diss - (char *)prec;
    prt->papFldDes[ab1771NRecordLCNT]->offset = (char *)&prec->lcnt - (char *)prec;
    prt->papFldDes[ab1771NRecordPACT]->offset = (char *)&prec->pact - (char *)prec;
    prt->papFldDes[ab1771NRecordPUTF]->offset = (char *)&prec->putf - (char *)prec;
    prt->papFldDes[ab1771NRecordRPRO]->offset = (char *)&prec->rpro - (char *)prec;
    prt->papFldDes[ab1771NRecordASP]->offset = (char *)&prec->asp - (char *)prec;
    prt->papFldDes[ab1771NRecordPPN]->offset = (char *)&prec->ppn - (char *)prec;
    prt->papFldDes[ab1771NRecordPPNR]->offset = (char *)&prec->ppnr - (char *)prec;
    prt->papFldDes[ab1771NRecordSPVT]->offset = (char *)&prec->spvt - (char *)prec;
    prt->papFldDes[ab1771NRecordRSET]->offset = (char *)&prec->rset - (char *)prec;
    prt->papFldDes[ab1771NRecordDSET]->offset = (char *)&prec->dset - (char *)prec;
    prt->papFldDes[ab1771NRecordDPVT]->offset = (char *)&prec->dpvt - (char *)prec;
    prt->papFldDes[ab1771NRecordRDES]->offset = (char *)&prec->rdes - (char *)prec;
    prt->papFldDes[ab1771NRecordLSET]->offset = (char *)&prec->lset - (char *)prec;
    prt->papFldDes[ab1771NRecordPRIO]->offset = (char *)&prec->prio - (char *)prec;
    prt->papFldDes[ab1771NRecordTPRO]->offset = (char *)&prec->tpro - (char *)prec;
    prt->papFldDes[ab1771NRecordBKPT]->offset = (char *)&prec->bkpt - (char *)prec;
    prt->papFldDes[ab1771NRecordUDF]->offset = (char *)&prec->udf - (char *)prec;
    prt->papFldDes[ab1771NRecordUDFS]->offset = (char *)&prec->udfs - (char *)prec;
    prt->papFldDes[ab1771NRecordTIME]->offset = (char *)&prec->time - (char *)prec;
    prt->papFldDes[ab1771NRecordFLNK]->offset = (char *)&prec->flnk - (char *)prec;
    prt->papFldDes[ab1771NRecordVAL]->offset = (char *)&prec->val - (char *)prec;
    prt->papFldDes[ab1771NRecordCMD]->offset = (char *)&prec->cmd - (char *)prec;
    prt->papFldDes[ab1771NRecordLOCA]->offset = (char *)&prec->loca - (char *)prec;
    prt->papFldDes[ab1771NRecordLINK]->offset = (char *)&prec->link - (char *)prec;
    prt->papFldDes[ab1771NRecordRACK]->offset = (char *)&prec->rack - (char *)prec;
    prt->papFldDes[ab1771NRecordSLOT]->offset = (char *)&prec->slot - (char *)prec;
    prt->papFldDes[ab1771NRecordOUTM]->offset = (char *)&prec->outm - (char *)prec;
    prt->papFldDes[ab1771NRecordINPM]->offset = (char *)&prec->inpm - (char *)prec;
    prt->papFldDes[ab1771NRecordIAI1]->offset = (char *)&prec->iai1 - (char *)prec;
    prt->papFldDes[ab1771NRecordIAO1]->offset = (char *)&prec->iao1 - (char *)prec;
    prt->papFldDes[ab1771NRecordMTYP]->offset = (char *)&prec->mtyp - (char *)prec;
    prt->papFldDes[ab1771NRecordSCAL]->offset = (char *)&prec->scal - (char *)prec;
    prt->papFldDes[ab1771NRecordCJAE]->offset = (char *)&prec->cjae - (char *)prec;
    prt->papFldDes[ab1771NRecordCJS]->offset = (char *)&prec->cjs - (char *)prec;
    prt->papFldDes[ab1771NRecordCJT]->offset = (char *)&prec->cjt - (char *)prec;
    prt->papFldDes[ab1771NRecordTYP1]->offset = (char *)&prec->typ1 - (char *)prec;
    prt->papFldDes[ab1771NRecordFIL1]->offset = (char *)&prec->fil1 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAL1]->offset = (char *)&prec->ral1 - (char *)prec;
    prt->papFldDes[ab1771NRecordOHM1]->offset = (char *)&prec->ohm1 - (char *)prec;
    prt->papFldDes[ab1771NRecordSTA1]->offset = (char *)&prec->sta1 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAW1]->offset = (char *)&prec->raw1 - (char *)prec;
    prt->papFldDes[ab1771NRecordTYP2]->offset = (char *)&prec->typ2 - (char *)prec;
    prt->papFldDes[ab1771NRecordFIL2]->offset = (char *)&prec->fil2 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAL2]->offset = (char *)&prec->ral2 - (char *)prec;
    prt->papFldDes[ab1771NRecordOHM2]->offset = (char *)&prec->ohm2 - (char *)prec;
    prt->papFldDes[ab1771NRecordSTA2]->offset = (char *)&prec->sta2 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAW2]->offset = (char *)&prec->raw2 - (char *)prec;
    prt->papFldDes[ab1771NRecordTYP3]->offset = (char *)&prec->typ3 - (char *)prec;
    prt->papFldDes[ab1771NRecordFIL3]->offset = (char *)&prec->fil3 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAL3]->offset = (char *)&prec->ral3 - (char *)prec;
    prt->papFldDes[ab1771NRecordOHM3]->offset = (char *)&prec->ohm3 - (char *)prec;
    prt->papFldDes[ab1771NRecordSTA3]->offset = (char *)&prec->sta3 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAW3]->offset = (char *)&prec->raw3 - (char *)prec;
    prt->papFldDes[ab1771NRecordTYP4]->offset = (char *)&prec->typ4 - (char *)prec;
    prt->papFldDes[ab1771NRecordFIL4]->offset = (char *)&prec->fil4 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAL4]->offset = (char *)&prec->ral4 - (char *)prec;
    prt->papFldDes[ab1771NRecordOHM4]->offset = (char *)&prec->ohm4 - (char *)prec;
    prt->papFldDes[ab1771NRecordSTA4]->offset = (char *)&prec->sta4 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAW4]->offset = (char *)&prec->raw4 - (char *)prec;
    prt->papFldDes[ab1771NRecordTYP5]->offset = (char *)&prec->typ5 - (char *)prec;
    prt->papFldDes[ab1771NRecordFIL5]->offset = (char *)&prec->fil5 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAL5]->offset = (char *)&prec->ral5 - (char *)prec;
    prt->papFldDes[ab1771NRecordOHM5]->offset = (char *)&prec->ohm5 - (char *)prec;
    prt->papFldDes[ab1771NRecordSTA5]->offset = (char *)&prec->sta5 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAW5]->offset = (char *)&prec->raw5 - (char *)prec;
    prt->papFldDes[ab1771NRecordTYP6]->offset = (char *)&prec->typ6 - (char *)prec;
    prt->papFldDes[ab1771NRecordFIL6]->offset = (char *)&prec->fil6 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAL6]->offset = (char *)&prec->ral6 - (char *)prec;
    prt->papFldDes[ab1771NRecordOHM6]->offset = (char *)&prec->ohm6 - (char *)prec;
    prt->papFldDes[ab1771NRecordSTA6]->offset = (char *)&prec->sta6 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAW6]->offset = (char *)&prec->raw6 - (char *)prec;
    prt->papFldDes[ab1771NRecordTYP7]->offset = (char *)&prec->typ7 - (char *)prec;
    prt->papFldDes[ab1771NRecordFIL7]->offset = (char *)&prec->fil7 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAL7]->offset = (char *)&prec->ral7 - (char *)prec;
    prt->papFldDes[ab1771NRecordOHM7]->offset = (char *)&prec->ohm7 - (char *)prec;
    prt->papFldDes[ab1771NRecordSTA7]->offset = (char *)&prec->sta7 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAW7]->offset = (char *)&prec->raw7 - (char *)prec;
    prt->papFldDes[ab1771NRecordTYP8]->offset = (char *)&prec->typ8 - (char *)prec;
    prt->papFldDes[ab1771NRecordFIL8]->offset = (char *)&prec->fil8 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAL8]->offset = (char *)&prec->ral8 - (char *)prec;
    prt->papFldDes[ab1771NRecordOHM8]->offset = (char *)&prec->ohm8 - (char *)prec;
    prt->papFldDes[ab1771NRecordSTA8]->offset = (char *)&prec->sta8 - (char *)prec;
    prt->papFldDes[ab1771NRecordRAW8]->offset = (char *)&prec->raw8 - (char *)prec;
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(ab1771NRecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_ab1771NRecord_H */
