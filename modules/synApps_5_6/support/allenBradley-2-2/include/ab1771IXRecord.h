/* ab1771IXRecord.h generated from ab1771IXRecord.dbd */

#ifndef INC_ab1771IXRecord_H
#define INC_ab1771IXRecord_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "epicsTime.h"

typedef enum {
    ab1771IX_HR                     /* 1771-IXHR */,
    ab1771IX_E                      /* 1771-IXE */,
    ab1771IX_MTYP_NUM_CHOICES
} ab1771IX_MTYP;

typedef enum {
    ab1771IX_UnitsC                 /* degC */,
    ab1771IX_UnitsF                 /* degF */,
    ab1771IX_Units_NUM_CHOICES
} ab1771IX_Units;

typedef enum {
    ab1771IX_CMD_None               /* None */,
    ab1771IX_Init                   /* Initialize */,
    ab1771IX_CMD_NUM_CHOICES
} ab1771IX_CMD;

typedef enum {
    ab1771IX_STA_Ok                 /* Ok */,
    ab1771IX_STA_Under              /* Underrange */,
    ab1771IX_STA_Over               /* Overrange */,
    ab1771IX_STA_NUM_CHOICES
} ab1771IX_STA;

typedef enum {
    ab1771IX_TYPE_MV                /* Millivolt */,
    ab1771IX_TYPE_tcB               /* tc B */,
    ab1771IX_TYPE_tcE               /* tc E */,
    ab1771IX_TYPE_tcJ               /* tc J */,
    ab1771IX_TYPE_tcK               /* tc K */,
    ab1771IX_TYPE_tcR               /* tc R */,
    ab1771IX_TYPE_tcS               /* tc S */,
    ab1771IX_TYPE_tcT               /* tc T */,
    ab1771IX_TYPE_NUM_CHOICES
} ab1771IX_TYPE;

typedef struct ab1771IXRecord {
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
    epicsEnum16         mtyp;       /* Module Type */
    epicsEnum16         typa;       /* Chan 1-4 type */
    epicsEnum16         typb;       /* Chan 5-8 type */
    epicsEnum16         scal;       /* Temperature Scale */
    epicsInt16          stim;       /* Sample Time Period */
    epicsEnum16         zoom;       /* Enable zoom for millivolt */
    epicsInt16          zca;        /* Zoom center channels 1-4 */
    epicsInt16          zcb;        /* Zoom center channels 5-8 */
    epicsInt16          fila;       /* Filter value channels 1-4 */
    epicsInt16          filb;       /* Filter value channels 5-8 */
    epicsFloat32        cjt;        /* Cold Junction Temperature  */
    epicsEnum16         sta1;       /* Chan 1 status */
    epicsInt16          raw1;       /* Chan 1 raw value */
    epicsEnum16         sta2;       /* Chan 2 status */
    epicsInt16          raw2;       /* Chan 2 raw value */
    epicsEnum16         sta3;       /* Chan 3 status */
    epicsInt16          raw3;       /* Chan 3 raw value */
    epicsEnum16         sta4;       /* Chan 4 status */
    epicsInt16          raw4;       /* Chan 4 raw value */
    epicsEnum16         sta5;       /* Chan 5 status */
    epicsInt16          raw5;       /* Chan 5 raw value */
    epicsEnum16         sta6;       /* Chan 6 status */
    epicsInt16          raw6;       /* Chan 6 raw value */
    epicsEnum16         sta7;       /* Chan 7 status */
    epicsInt16          raw7;       /* Chan 7 raw value */
    epicsEnum16         sta8;       /* Chan 8 status */
    epicsInt16          raw8;       /* Chan 8 raw value */
} ab1771IXRecord;

typedef enum {
	ab1771IXRecordNAME = 0,
	ab1771IXRecordDESC = 1,
	ab1771IXRecordASG = 2,
	ab1771IXRecordSCAN = 3,
	ab1771IXRecordPINI = 4,
	ab1771IXRecordPHAS = 5,
	ab1771IXRecordEVNT = 6,
	ab1771IXRecordTSE = 7,
	ab1771IXRecordTSEL = 8,
	ab1771IXRecordDTYP = 9,
	ab1771IXRecordDISV = 10,
	ab1771IXRecordDISA = 11,
	ab1771IXRecordSDIS = 12,
	ab1771IXRecordMLOK = 13,
	ab1771IXRecordMLIS = 14,
	ab1771IXRecordDISP = 15,
	ab1771IXRecordPROC = 16,
	ab1771IXRecordSTAT = 17,
	ab1771IXRecordSEVR = 18,
	ab1771IXRecordNSTA = 19,
	ab1771IXRecordNSEV = 20,
	ab1771IXRecordACKS = 21,
	ab1771IXRecordACKT = 22,
	ab1771IXRecordDISS = 23,
	ab1771IXRecordLCNT = 24,
	ab1771IXRecordPACT = 25,
	ab1771IXRecordPUTF = 26,
	ab1771IXRecordRPRO = 27,
	ab1771IXRecordASP = 28,
	ab1771IXRecordPPN = 29,
	ab1771IXRecordPPNR = 30,
	ab1771IXRecordSPVT = 31,
	ab1771IXRecordRSET = 32,
	ab1771IXRecordDSET = 33,
	ab1771IXRecordDPVT = 34,
	ab1771IXRecordRDES = 35,
	ab1771IXRecordLSET = 36,
	ab1771IXRecordPRIO = 37,
	ab1771IXRecordTPRO = 38,
	ab1771IXRecordBKPT = 39,
	ab1771IXRecordUDF = 40,
	ab1771IXRecordUDFS = 41,
	ab1771IXRecordTIME = 42,
	ab1771IXRecordFLNK = 43,
	ab1771IXRecordVAL = 44,
	ab1771IXRecordCMD = 45,
	ab1771IXRecordLOCA = 46,
	ab1771IXRecordLINK = 47,
	ab1771IXRecordRACK = 48,
	ab1771IXRecordSLOT = 49,
	ab1771IXRecordOUTM = 50,
	ab1771IXRecordINPM = 51,
	ab1771IXRecordIAI1 = 52,
	ab1771IXRecordMTYP = 53,
	ab1771IXRecordTYPA = 54,
	ab1771IXRecordTYPB = 55,
	ab1771IXRecordSCAL = 56,
	ab1771IXRecordSTIM = 57,
	ab1771IXRecordZOOM = 58,
	ab1771IXRecordZCA = 59,
	ab1771IXRecordZCB = 60,
	ab1771IXRecordFILA = 61,
	ab1771IXRecordFILB = 62,
	ab1771IXRecordCJT = 63,
	ab1771IXRecordSTA1 = 64,
	ab1771IXRecordRAW1 = 65,
	ab1771IXRecordSTA2 = 66,
	ab1771IXRecordRAW2 = 67,
	ab1771IXRecordSTA3 = 68,
	ab1771IXRecordRAW3 = 69,
	ab1771IXRecordSTA4 = 70,
	ab1771IXRecordRAW4 = 71,
	ab1771IXRecordSTA5 = 72,
	ab1771IXRecordRAW5 = 73,
	ab1771IXRecordSTA6 = 74,
	ab1771IXRecordRAW6 = 75,
	ab1771IXRecordSTA7 = 76,
	ab1771IXRecordRAW7 = 77,
	ab1771IXRecordSTA8 = 78,
	ab1771IXRecordRAW8 = 79
} ab1771IXFieldIndex;

#ifdef GEN_SIZE_OFFSET

#ifdef __cplusplus
extern "C" {
#endif
#include <epicsExport.h>
static int ab1771IXRecordSizeOffset(dbRecordType *prt)
{
    ab1771IXRecord *prec = 0;
    prt->papFldDes[ab1771IXRecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[ab1771IXRecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[ab1771IXRecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[ab1771IXRecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[ab1771IXRecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[ab1771IXRecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[ab1771IXRecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[ab1771IXRecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[ab1771IXRecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[ab1771IXRecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[ab1771IXRecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[ab1771IXRecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[ab1771IXRecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[ab1771IXRecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[ab1771IXRecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[ab1771IXRecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[ab1771IXRecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[ab1771IXRecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[ab1771IXRecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[ab1771IXRecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[ab1771IXRecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[ab1771IXRecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[ab1771IXRecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[ab1771IXRecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[ab1771IXRecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[ab1771IXRecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[ab1771IXRecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[ab1771IXRecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[ab1771IXRecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[ab1771IXRecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[ab1771IXRecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[ab1771IXRecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[ab1771IXRecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[ab1771IXRecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[ab1771IXRecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[ab1771IXRecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[ab1771IXRecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[ab1771IXRecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[ab1771IXRecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[ab1771IXRecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[ab1771IXRecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[ab1771IXRecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[ab1771IXRecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[ab1771IXRecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[ab1771IXRecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[ab1771IXRecordCMD]->size = sizeof(prec->cmd);
    prt->papFldDes[ab1771IXRecordLOCA]->size = sizeof(prec->loca);
    prt->papFldDes[ab1771IXRecordLINK]->size = sizeof(prec->link);
    prt->papFldDes[ab1771IXRecordRACK]->size = sizeof(prec->rack);
    prt->papFldDes[ab1771IXRecordSLOT]->size = sizeof(prec->slot);
    prt->papFldDes[ab1771IXRecordOUTM]->size = sizeof(prec->outm);
    prt->papFldDes[ab1771IXRecordINPM]->size = sizeof(prec->inpm);
    prt->papFldDes[ab1771IXRecordIAI1]->size = sizeof(prec->iai1);
    prt->papFldDes[ab1771IXRecordMTYP]->size = sizeof(prec->mtyp);
    prt->papFldDes[ab1771IXRecordTYPA]->size = sizeof(prec->typa);
    prt->papFldDes[ab1771IXRecordTYPB]->size = sizeof(prec->typb);
    prt->papFldDes[ab1771IXRecordSCAL]->size = sizeof(prec->scal);
    prt->papFldDes[ab1771IXRecordSTIM]->size = sizeof(prec->stim);
    prt->papFldDes[ab1771IXRecordZOOM]->size = sizeof(prec->zoom);
    prt->papFldDes[ab1771IXRecordZCA]->size = sizeof(prec->zca);
    prt->papFldDes[ab1771IXRecordZCB]->size = sizeof(prec->zcb);
    prt->papFldDes[ab1771IXRecordFILA]->size = sizeof(prec->fila);
    prt->papFldDes[ab1771IXRecordFILB]->size = sizeof(prec->filb);
    prt->papFldDes[ab1771IXRecordCJT]->size = sizeof(prec->cjt);
    prt->papFldDes[ab1771IXRecordSTA1]->size = sizeof(prec->sta1);
    prt->papFldDes[ab1771IXRecordRAW1]->size = sizeof(prec->raw1);
    prt->papFldDes[ab1771IXRecordSTA2]->size = sizeof(prec->sta2);
    prt->papFldDes[ab1771IXRecordRAW2]->size = sizeof(prec->raw2);
    prt->papFldDes[ab1771IXRecordSTA3]->size = sizeof(prec->sta3);
    prt->papFldDes[ab1771IXRecordRAW3]->size = sizeof(prec->raw3);
    prt->papFldDes[ab1771IXRecordSTA4]->size = sizeof(prec->sta4);
    prt->papFldDes[ab1771IXRecordRAW4]->size = sizeof(prec->raw4);
    prt->papFldDes[ab1771IXRecordSTA5]->size = sizeof(prec->sta5);
    prt->papFldDes[ab1771IXRecordRAW5]->size = sizeof(prec->raw5);
    prt->papFldDes[ab1771IXRecordSTA6]->size = sizeof(prec->sta6);
    prt->papFldDes[ab1771IXRecordRAW6]->size = sizeof(prec->raw6);
    prt->papFldDes[ab1771IXRecordSTA7]->size = sizeof(prec->sta7);
    prt->papFldDes[ab1771IXRecordRAW7]->size = sizeof(prec->raw7);
    prt->papFldDes[ab1771IXRecordSTA8]->size = sizeof(prec->sta8);
    prt->papFldDes[ab1771IXRecordRAW8]->size = sizeof(prec->raw8);
    prt->papFldDes[ab1771IXRecordNAME]->offset = (char *)&prec->name - (char *)prec;
    prt->papFldDes[ab1771IXRecordDESC]->offset = (char *)&prec->desc - (char *)prec;
    prt->papFldDes[ab1771IXRecordASG]->offset = (char *)&prec->asg - (char *)prec;
    prt->papFldDes[ab1771IXRecordSCAN]->offset = (char *)&prec->scan - (char *)prec;
    prt->papFldDes[ab1771IXRecordPINI]->offset = (char *)&prec->pini - (char *)prec;
    prt->papFldDes[ab1771IXRecordPHAS]->offset = (char *)&prec->phas - (char *)prec;
    prt->papFldDes[ab1771IXRecordEVNT]->offset = (char *)&prec->evnt - (char *)prec;
    prt->papFldDes[ab1771IXRecordTSE]->offset = (char *)&prec->tse - (char *)prec;
    prt->papFldDes[ab1771IXRecordTSEL]->offset = (char *)&prec->tsel - (char *)prec;
    prt->papFldDes[ab1771IXRecordDTYP]->offset = (char *)&prec->dtyp - (char *)prec;
    prt->papFldDes[ab1771IXRecordDISV]->offset = (char *)&prec->disv - (char *)prec;
    prt->papFldDes[ab1771IXRecordDISA]->offset = (char *)&prec->disa - (char *)prec;
    prt->papFldDes[ab1771IXRecordSDIS]->offset = (char *)&prec->sdis - (char *)prec;
    prt->papFldDes[ab1771IXRecordMLOK]->offset = (char *)&prec->mlok - (char *)prec;
    prt->papFldDes[ab1771IXRecordMLIS]->offset = (char *)&prec->mlis - (char *)prec;
    prt->papFldDes[ab1771IXRecordDISP]->offset = (char *)&prec->disp - (char *)prec;
    prt->papFldDes[ab1771IXRecordPROC]->offset = (char *)&prec->proc - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTAT]->offset = (char *)&prec->stat - (char *)prec;
    prt->papFldDes[ab1771IXRecordSEVR]->offset = (char *)&prec->sevr - (char *)prec;
    prt->papFldDes[ab1771IXRecordNSTA]->offset = (char *)&prec->nsta - (char *)prec;
    prt->papFldDes[ab1771IXRecordNSEV]->offset = (char *)&prec->nsev - (char *)prec;
    prt->papFldDes[ab1771IXRecordACKS]->offset = (char *)&prec->acks - (char *)prec;
    prt->papFldDes[ab1771IXRecordACKT]->offset = (char *)&prec->ackt - (char *)prec;
    prt->papFldDes[ab1771IXRecordDISS]->offset = (char *)&prec->diss - (char *)prec;
    prt->papFldDes[ab1771IXRecordLCNT]->offset = (char *)&prec->lcnt - (char *)prec;
    prt->papFldDes[ab1771IXRecordPACT]->offset = (char *)&prec->pact - (char *)prec;
    prt->papFldDes[ab1771IXRecordPUTF]->offset = (char *)&prec->putf - (char *)prec;
    prt->papFldDes[ab1771IXRecordRPRO]->offset = (char *)&prec->rpro - (char *)prec;
    prt->papFldDes[ab1771IXRecordASP]->offset = (char *)&prec->asp - (char *)prec;
    prt->papFldDes[ab1771IXRecordPPN]->offset = (char *)&prec->ppn - (char *)prec;
    prt->papFldDes[ab1771IXRecordPPNR]->offset = (char *)&prec->ppnr - (char *)prec;
    prt->papFldDes[ab1771IXRecordSPVT]->offset = (char *)&prec->spvt - (char *)prec;
    prt->papFldDes[ab1771IXRecordRSET]->offset = (char *)&prec->rset - (char *)prec;
    prt->papFldDes[ab1771IXRecordDSET]->offset = (char *)&prec->dset - (char *)prec;
    prt->papFldDes[ab1771IXRecordDPVT]->offset = (char *)&prec->dpvt - (char *)prec;
    prt->papFldDes[ab1771IXRecordRDES]->offset = (char *)&prec->rdes - (char *)prec;
    prt->papFldDes[ab1771IXRecordLSET]->offset = (char *)&prec->lset - (char *)prec;
    prt->papFldDes[ab1771IXRecordPRIO]->offset = (char *)&prec->prio - (char *)prec;
    prt->papFldDes[ab1771IXRecordTPRO]->offset = (char *)&prec->tpro - (char *)prec;
    prt->papFldDes[ab1771IXRecordBKPT]->offset = (char *)&prec->bkpt - (char *)prec;
    prt->papFldDes[ab1771IXRecordUDF]->offset = (char *)&prec->udf - (char *)prec;
    prt->papFldDes[ab1771IXRecordUDFS]->offset = (char *)&prec->udfs - (char *)prec;
    prt->papFldDes[ab1771IXRecordTIME]->offset = (char *)&prec->time - (char *)prec;
    prt->papFldDes[ab1771IXRecordFLNK]->offset = (char *)&prec->flnk - (char *)prec;
    prt->papFldDes[ab1771IXRecordVAL]->offset = (char *)&prec->val - (char *)prec;
    prt->papFldDes[ab1771IXRecordCMD]->offset = (char *)&prec->cmd - (char *)prec;
    prt->papFldDes[ab1771IXRecordLOCA]->offset = (char *)&prec->loca - (char *)prec;
    prt->papFldDes[ab1771IXRecordLINK]->offset = (char *)&prec->link - (char *)prec;
    prt->papFldDes[ab1771IXRecordRACK]->offset = (char *)&prec->rack - (char *)prec;
    prt->papFldDes[ab1771IXRecordSLOT]->offset = (char *)&prec->slot - (char *)prec;
    prt->papFldDes[ab1771IXRecordOUTM]->offset = (char *)&prec->outm - (char *)prec;
    prt->papFldDes[ab1771IXRecordINPM]->offset = (char *)&prec->inpm - (char *)prec;
    prt->papFldDes[ab1771IXRecordIAI1]->offset = (char *)&prec->iai1 - (char *)prec;
    prt->papFldDes[ab1771IXRecordMTYP]->offset = (char *)&prec->mtyp - (char *)prec;
    prt->papFldDes[ab1771IXRecordTYPA]->offset = (char *)&prec->typa - (char *)prec;
    prt->papFldDes[ab1771IXRecordTYPB]->offset = (char *)&prec->typb - (char *)prec;
    prt->papFldDes[ab1771IXRecordSCAL]->offset = (char *)&prec->scal - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTIM]->offset = (char *)&prec->stim - (char *)prec;
    prt->papFldDes[ab1771IXRecordZOOM]->offset = (char *)&prec->zoom - (char *)prec;
    prt->papFldDes[ab1771IXRecordZCA]->offset = (char *)&prec->zca - (char *)prec;
    prt->papFldDes[ab1771IXRecordZCB]->offset = (char *)&prec->zcb - (char *)prec;
    prt->papFldDes[ab1771IXRecordFILA]->offset = (char *)&prec->fila - (char *)prec;
    prt->papFldDes[ab1771IXRecordFILB]->offset = (char *)&prec->filb - (char *)prec;
    prt->papFldDes[ab1771IXRecordCJT]->offset = (char *)&prec->cjt - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTA1]->offset = (char *)&prec->sta1 - (char *)prec;
    prt->papFldDes[ab1771IXRecordRAW1]->offset = (char *)&prec->raw1 - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTA2]->offset = (char *)&prec->sta2 - (char *)prec;
    prt->papFldDes[ab1771IXRecordRAW2]->offset = (char *)&prec->raw2 - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTA3]->offset = (char *)&prec->sta3 - (char *)prec;
    prt->papFldDes[ab1771IXRecordRAW3]->offset = (char *)&prec->raw3 - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTA4]->offset = (char *)&prec->sta4 - (char *)prec;
    prt->papFldDes[ab1771IXRecordRAW4]->offset = (char *)&prec->raw4 - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTA5]->offset = (char *)&prec->sta5 - (char *)prec;
    prt->papFldDes[ab1771IXRecordRAW5]->offset = (char *)&prec->raw5 - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTA6]->offset = (char *)&prec->sta6 - (char *)prec;
    prt->papFldDes[ab1771IXRecordRAW6]->offset = (char *)&prec->raw6 - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTA7]->offset = (char *)&prec->sta7 - (char *)prec;
    prt->papFldDes[ab1771IXRecordRAW7]->offset = (char *)&prec->raw7 - (char *)prec;
    prt->papFldDes[ab1771IXRecordSTA8]->offset = (char *)&prec->sta8 - (char *)prec;
    prt->papFldDes[ab1771IXRecordRAW8]->offset = (char *)&prec->raw8 - (char *)prec;
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(ab1771IXRecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_ab1771IXRecord_H */
