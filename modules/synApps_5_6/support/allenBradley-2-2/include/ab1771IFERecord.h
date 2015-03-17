/* ab1771IFERecord.h generated from ab1771IFERecord.dbd */

#ifndef INC_ab1771IFERecord_H
#define INC_ab1771IFERecord_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "epicsTime.h"

typedef enum {
    ab1771IFE_CMD_None              /* None */,
    ab1771IFE_Init                  /* Initialize */,
    ab1771IFE_CMD_NUM_CHOICES
} ab1771IFE_CMD;

typedef enum {
    ab1771IFE_RANGE_0               /* 1to5V,4to20mA */,
    ab1771IFE_RANGE_1               /* 0to5V,0to20mA */,
    ab1771IFE_RANGE_2               /* -5to5V,-20to20mA */,
    ab1771IFE_RANGE_3               /* -10to10V,0to10V */,
    ab1771IFE_RANGE_NUM_CHOICES
} ab1771IFE_RANGE;

typedef enum {
    ab1771IFE_SE                    /* SingleEndedInput */,
    ab1771IFE_DI                    /* DifferentialInput */,
    ab1771IFE_SEDI_NUM_CHOICES
} ab1771IFE_SEDI;

typedef struct ab1771IFERecord {
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
    epicsEnum16         sedi;       /* Single/Double Ended */
    epicsInt16          filt;       /* Filter 00to99 */
    epicsInt16          stim;       /* Sample Time Period */
    epicsEnum16         r0;         /* Range signal 0 */
    epicsEnum16         r1;         /* Range signal 1 */
    epicsEnum16         r2;         /* Range signal 2 */
    epicsEnum16         r3;         /* Range signal 3 */
    epicsEnum16         r4;         /* Range signal 4 */
    epicsEnum16         r5;         /* Range signal 5 */
    epicsEnum16         r6;         /* Range signal 6 */
    epicsEnum16         r7;         /* Range signal 7 */
    epicsEnum16         r8;         /* Range signal 8 */
    epicsEnum16         r9;         /* Range signal 9 */
    epicsEnum16         r10;        /* Range signal 10 */
    epicsEnum16         r11;        /* Range signal 11 */
    epicsEnum16         r12;        /* Range signal 12 */
    epicsEnum16         r13;        /* Range signal 13 */
    epicsEnum16         r14;        /* Range signal 14 */
    epicsEnum16         r15;        /* Range signal 15 */
} ab1771IFERecord;

typedef enum {
	ab1771IFERecordNAME = 0,
	ab1771IFERecordDESC = 1,
	ab1771IFERecordASG = 2,
	ab1771IFERecordSCAN = 3,
	ab1771IFERecordPINI = 4,
	ab1771IFERecordPHAS = 5,
	ab1771IFERecordEVNT = 6,
	ab1771IFERecordTSE = 7,
	ab1771IFERecordTSEL = 8,
	ab1771IFERecordDTYP = 9,
	ab1771IFERecordDISV = 10,
	ab1771IFERecordDISA = 11,
	ab1771IFERecordSDIS = 12,
	ab1771IFERecordMLOK = 13,
	ab1771IFERecordMLIS = 14,
	ab1771IFERecordDISP = 15,
	ab1771IFERecordPROC = 16,
	ab1771IFERecordSTAT = 17,
	ab1771IFERecordSEVR = 18,
	ab1771IFERecordNSTA = 19,
	ab1771IFERecordNSEV = 20,
	ab1771IFERecordACKS = 21,
	ab1771IFERecordACKT = 22,
	ab1771IFERecordDISS = 23,
	ab1771IFERecordLCNT = 24,
	ab1771IFERecordPACT = 25,
	ab1771IFERecordPUTF = 26,
	ab1771IFERecordRPRO = 27,
	ab1771IFERecordASP = 28,
	ab1771IFERecordPPN = 29,
	ab1771IFERecordPPNR = 30,
	ab1771IFERecordSPVT = 31,
	ab1771IFERecordRSET = 32,
	ab1771IFERecordDSET = 33,
	ab1771IFERecordDPVT = 34,
	ab1771IFERecordRDES = 35,
	ab1771IFERecordLSET = 36,
	ab1771IFERecordPRIO = 37,
	ab1771IFERecordTPRO = 38,
	ab1771IFERecordBKPT = 39,
	ab1771IFERecordUDF = 40,
	ab1771IFERecordUDFS = 41,
	ab1771IFERecordTIME = 42,
	ab1771IFERecordFLNK = 43,
	ab1771IFERecordVAL = 44,
	ab1771IFERecordCMD = 45,
	ab1771IFERecordLOCA = 46,
	ab1771IFERecordLINK = 47,
	ab1771IFERecordRACK = 48,
	ab1771IFERecordSLOT = 49,
	ab1771IFERecordOUTM = 50,
	ab1771IFERecordINPM = 51,
	ab1771IFERecordIAI1 = 52,
	ab1771IFERecordSEDI = 53,
	ab1771IFERecordFILT = 54,
	ab1771IFERecordSTIM = 55,
	ab1771IFERecordR0 = 56,
	ab1771IFERecordR1 = 57,
	ab1771IFERecordR2 = 58,
	ab1771IFERecordR3 = 59,
	ab1771IFERecordR4 = 60,
	ab1771IFERecordR5 = 61,
	ab1771IFERecordR6 = 62,
	ab1771IFERecordR7 = 63,
	ab1771IFERecordR8 = 64,
	ab1771IFERecordR9 = 65,
	ab1771IFERecordR10 = 66,
	ab1771IFERecordR11 = 67,
	ab1771IFERecordR12 = 68,
	ab1771IFERecordR13 = 69,
	ab1771IFERecordR14 = 70,
	ab1771IFERecordR15 = 71
} ab1771IFEFieldIndex;

#ifdef GEN_SIZE_OFFSET

#ifdef __cplusplus
extern "C" {
#endif
#include <epicsExport.h>
static int ab1771IFERecordSizeOffset(dbRecordType *prt)
{
    ab1771IFERecord *prec = 0;
    prt->papFldDes[ab1771IFERecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[ab1771IFERecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[ab1771IFERecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[ab1771IFERecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[ab1771IFERecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[ab1771IFERecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[ab1771IFERecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[ab1771IFERecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[ab1771IFERecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[ab1771IFERecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[ab1771IFERecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[ab1771IFERecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[ab1771IFERecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[ab1771IFERecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[ab1771IFERecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[ab1771IFERecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[ab1771IFERecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[ab1771IFERecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[ab1771IFERecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[ab1771IFERecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[ab1771IFERecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[ab1771IFERecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[ab1771IFERecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[ab1771IFERecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[ab1771IFERecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[ab1771IFERecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[ab1771IFERecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[ab1771IFERecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[ab1771IFERecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[ab1771IFERecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[ab1771IFERecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[ab1771IFERecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[ab1771IFERecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[ab1771IFERecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[ab1771IFERecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[ab1771IFERecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[ab1771IFERecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[ab1771IFERecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[ab1771IFERecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[ab1771IFERecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[ab1771IFERecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[ab1771IFERecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[ab1771IFERecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[ab1771IFERecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[ab1771IFERecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[ab1771IFERecordCMD]->size = sizeof(prec->cmd);
    prt->papFldDes[ab1771IFERecordLOCA]->size = sizeof(prec->loca);
    prt->papFldDes[ab1771IFERecordLINK]->size = sizeof(prec->link);
    prt->papFldDes[ab1771IFERecordRACK]->size = sizeof(prec->rack);
    prt->papFldDes[ab1771IFERecordSLOT]->size = sizeof(prec->slot);
    prt->papFldDes[ab1771IFERecordOUTM]->size = sizeof(prec->outm);
    prt->papFldDes[ab1771IFERecordINPM]->size = sizeof(prec->inpm);
    prt->papFldDes[ab1771IFERecordIAI1]->size = sizeof(prec->iai1);
    prt->papFldDes[ab1771IFERecordSEDI]->size = sizeof(prec->sedi);
    prt->papFldDes[ab1771IFERecordFILT]->size = sizeof(prec->filt);
    prt->papFldDes[ab1771IFERecordSTIM]->size = sizeof(prec->stim);
    prt->papFldDes[ab1771IFERecordR0]->size = sizeof(prec->r0);
    prt->papFldDes[ab1771IFERecordR1]->size = sizeof(prec->r1);
    prt->papFldDes[ab1771IFERecordR2]->size = sizeof(prec->r2);
    prt->papFldDes[ab1771IFERecordR3]->size = sizeof(prec->r3);
    prt->papFldDes[ab1771IFERecordR4]->size = sizeof(prec->r4);
    prt->papFldDes[ab1771IFERecordR5]->size = sizeof(prec->r5);
    prt->papFldDes[ab1771IFERecordR6]->size = sizeof(prec->r6);
    prt->papFldDes[ab1771IFERecordR7]->size = sizeof(prec->r7);
    prt->papFldDes[ab1771IFERecordR8]->size = sizeof(prec->r8);
    prt->papFldDes[ab1771IFERecordR9]->size = sizeof(prec->r9);
    prt->papFldDes[ab1771IFERecordR10]->size = sizeof(prec->r10);
    prt->papFldDes[ab1771IFERecordR11]->size = sizeof(prec->r11);
    prt->papFldDes[ab1771IFERecordR12]->size = sizeof(prec->r12);
    prt->papFldDes[ab1771IFERecordR13]->size = sizeof(prec->r13);
    prt->papFldDes[ab1771IFERecordR14]->size = sizeof(prec->r14);
    prt->papFldDes[ab1771IFERecordR15]->size = sizeof(prec->r15);
    prt->papFldDes[ab1771IFERecordNAME]->offset = (char *)&prec->name - (char *)prec;
    prt->papFldDes[ab1771IFERecordDESC]->offset = (char *)&prec->desc - (char *)prec;
    prt->papFldDes[ab1771IFERecordASG]->offset = (char *)&prec->asg - (char *)prec;
    prt->papFldDes[ab1771IFERecordSCAN]->offset = (char *)&prec->scan - (char *)prec;
    prt->papFldDes[ab1771IFERecordPINI]->offset = (char *)&prec->pini - (char *)prec;
    prt->papFldDes[ab1771IFERecordPHAS]->offset = (char *)&prec->phas - (char *)prec;
    prt->papFldDes[ab1771IFERecordEVNT]->offset = (char *)&prec->evnt - (char *)prec;
    prt->papFldDes[ab1771IFERecordTSE]->offset = (char *)&prec->tse - (char *)prec;
    prt->papFldDes[ab1771IFERecordTSEL]->offset = (char *)&prec->tsel - (char *)prec;
    prt->papFldDes[ab1771IFERecordDTYP]->offset = (char *)&prec->dtyp - (char *)prec;
    prt->papFldDes[ab1771IFERecordDISV]->offset = (char *)&prec->disv - (char *)prec;
    prt->papFldDes[ab1771IFERecordDISA]->offset = (char *)&prec->disa - (char *)prec;
    prt->papFldDes[ab1771IFERecordSDIS]->offset = (char *)&prec->sdis - (char *)prec;
    prt->papFldDes[ab1771IFERecordMLOK]->offset = (char *)&prec->mlok - (char *)prec;
    prt->papFldDes[ab1771IFERecordMLIS]->offset = (char *)&prec->mlis - (char *)prec;
    prt->papFldDes[ab1771IFERecordDISP]->offset = (char *)&prec->disp - (char *)prec;
    prt->papFldDes[ab1771IFERecordPROC]->offset = (char *)&prec->proc - (char *)prec;
    prt->papFldDes[ab1771IFERecordSTAT]->offset = (char *)&prec->stat - (char *)prec;
    prt->papFldDes[ab1771IFERecordSEVR]->offset = (char *)&prec->sevr - (char *)prec;
    prt->papFldDes[ab1771IFERecordNSTA]->offset = (char *)&prec->nsta - (char *)prec;
    prt->papFldDes[ab1771IFERecordNSEV]->offset = (char *)&prec->nsev - (char *)prec;
    prt->papFldDes[ab1771IFERecordACKS]->offset = (char *)&prec->acks - (char *)prec;
    prt->papFldDes[ab1771IFERecordACKT]->offset = (char *)&prec->ackt - (char *)prec;
    prt->papFldDes[ab1771IFERecordDISS]->offset = (char *)&prec->diss - (char *)prec;
    prt->papFldDes[ab1771IFERecordLCNT]->offset = (char *)&prec->lcnt - (char *)prec;
    prt->papFldDes[ab1771IFERecordPACT]->offset = (char *)&prec->pact - (char *)prec;
    prt->papFldDes[ab1771IFERecordPUTF]->offset = (char *)&prec->putf - (char *)prec;
    prt->papFldDes[ab1771IFERecordRPRO]->offset = (char *)&prec->rpro - (char *)prec;
    prt->papFldDes[ab1771IFERecordASP]->offset = (char *)&prec->asp - (char *)prec;
    prt->papFldDes[ab1771IFERecordPPN]->offset = (char *)&prec->ppn - (char *)prec;
    prt->papFldDes[ab1771IFERecordPPNR]->offset = (char *)&prec->ppnr - (char *)prec;
    prt->papFldDes[ab1771IFERecordSPVT]->offset = (char *)&prec->spvt - (char *)prec;
    prt->papFldDes[ab1771IFERecordRSET]->offset = (char *)&prec->rset - (char *)prec;
    prt->papFldDes[ab1771IFERecordDSET]->offset = (char *)&prec->dset - (char *)prec;
    prt->papFldDes[ab1771IFERecordDPVT]->offset = (char *)&prec->dpvt - (char *)prec;
    prt->papFldDes[ab1771IFERecordRDES]->offset = (char *)&prec->rdes - (char *)prec;
    prt->papFldDes[ab1771IFERecordLSET]->offset = (char *)&prec->lset - (char *)prec;
    prt->papFldDes[ab1771IFERecordPRIO]->offset = (char *)&prec->prio - (char *)prec;
    prt->papFldDes[ab1771IFERecordTPRO]->offset = (char *)&prec->tpro - (char *)prec;
    prt->papFldDes[ab1771IFERecordBKPT]->offset = (char *)&prec->bkpt - (char *)prec;
    prt->papFldDes[ab1771IFERecordUDF]->offset = (char *)&prec->udf - (char *)prec;
    prt->papFldDes[ab1771IFERecordUDFS]->offset = (char *)&prec->udfs - (char *)prec;
    prt->papFldDes[ab1771IFERecordTIME]->offset = (char *)&prec->time - (char *)prec;
    prt->papFldDes[ab1771IFERecordFLNK]->offset = (char *)&prec->flnk - (char *)prec;
    prt->papFldDes[ab1771IFERecordVAL]->offset = (char *)&prec->val - (char *)prec;
    prt->papFldDes[ab1771IFERecordCMD]->offset = (char *)&prec->cmd - (char *)prec;
    prt->papFldDes[ab1771IFERecordLOCA]->offset = (char *)&prec->loca - (char *)prec;
    prt->papFldDes[ab1771IFERecordLINK]->offset = (char *)&prec->link - (char *)prec;
    prt->papFldDes[ab1771IFERecordRACK]->offset = (char *)&prec->rack - (char *)prec;
    prt->papFldDes[ab1771IFERecordSLOT]->offset = (char *)&prec->slot - (char *)prec;
    prt->papFldDes[ab1771IFERecordOUTM]->offset = (char *)&prec->outm - (char *)prec;
    prt->papFldDes[ab1771IFERecordINPM]->offset = (char *)&prec->inpm - (char *)prec;
    prt->papFldDes[ab1771IFERecordIAI1]->offset = (char *)&prec->iai1 - (char *)prec;
    prt->papFldDes[ab1771IFERecordSEDI]->offset = (char *)&prec->sedi - (char *)prec;
    prt->papFldDes[ab1771IFERecordFILT]->offset = (char *)&prec->filt - (char *)prec;
    prt->papFldDes[ab1771IFERecordSTIM]->offset = (char *)&prec->stim - (char *)prec;
    prt->papFldDes[ab1771IFERecordR0]->offset = (char *)&prec->r0 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR1]->offset = (char *)&prec->r1 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR2]->offset = (char *)&prec->r2 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR3]->offset = (char *)&prec->r3 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR4]->offset = (char *)&prec->r4 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR5]->offset = (char *)&prec->r5 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR6]->offset = (char *)&prec->r6 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR7]->offset = (char *)&prec->r7 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR8]->offset = (char *)&prec->r8 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR9]->offset = (char *)&prec->r9 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR10]->offset = (char *)&prec->r10 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR11]->offset = (char *)&prec->r11 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR12]->offset = (char *)&prec->r12 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR13]->offset = (char *)&prec->r13 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR14]->offset = (char *)&prec->r14 - (char *)prec;
    prt->papFldDes[ab1771IFERecordR15]->offset = (char *)&prec->r15 - (char *)prec;
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(ab1771IFERecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_ab1771IFERecord_H */
