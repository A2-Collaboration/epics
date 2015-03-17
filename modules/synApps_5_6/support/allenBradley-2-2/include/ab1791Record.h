/* ab1791Record.h generated from ab1791Record.dbd */

#ifndef INC_ab1791Record_H
#define INC_ab1791Record_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "epicsTime.h"

typedef enum {
    ab1791RANG__10_to_10            /* -10 to 10 */,
    ab1791RANG__5_to_5              /* -5 to 5 */,
    ab1791RANG_0_to_10              /* 0 to 10 */,
    ab1791RANG_0_to_5               /* 0 to 5 */,
    ab1791RANG_NUM_CHOICES
} ab1791RANG;

typedef enum {
    ab1791TYPE_Voltage              /* Voltage */,
    ab1791TYPE_Current              /* Current */,
    ab1791TYPE_NUM_CHOICES
} ab1791TYPE;

typedef enum {
    ab1791FILT_None                 /* None */,
    ab1791FILT_200ms                /* 200ms */,
    ab1791FILT_300ms                /* 300ms */,
    ab1791FILT_400ms                /* 400ms */,
    ab1791FILT_500ms                /* 500ms */,
    ab1791FILT_600ms                /* 600ms */,
    ab1791FILT_700ms                /* 700ms */,
    ab1791FILT_800ms                /* 800ms */,
    ab1791FILT_900ms                /* 900ms */,
    ab1791FILT_1000ms               /* 1000ms */,
    ab1791FILT_1100ms               /* 1100ms */,
    ab1791FILT_1200ms               /* 1200ms */,
    ab1791FILT_1300ms               /* 1300ms */,
    ab1791FILT_1400ms               /* 1400ms */,
    ab1791FILT_1500ms               /* 1500ms */,
    ab1791FILT_NUM_CHOICES
} ab1791FILT;

typedef struct ab1791Record {
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
    epicsInt16          val;        /* Value - Not Used */
    epicsEnum16         type;       /* Type */
    epicsEnum16         rang;       /* Range */
    epicsEnum16         filt;       /* Filter */
    char                lkst[40];   /* Link Status */
    epicsEnum16         loca;       /* scanIoRequest comm err */
    epicsUInt16         link;       /* Scanner Number */
    epicsUInt16         rack;       /* Rack */
    epicsUInt16         slot;       /* Slot */
    epicsInt16          nfai;       /* Number Failures */
    epicsInt16          inp0;       /* Input Channel 0 */
    epicsInt16          inp1;       /* Input Channel 1 */
    epicsInt16          inp2;       /* Input Channel 2 */
    epicsInt16          inp3;       /* Input Channel 3 */
    epicsInt16          out0;       /* Output Channel 0 */
    epicsInt16          out1;       /* Output Channel 1 */
} ab1791Record;

typedef enum {
	ab1791RecordNAME = 0,
	ab1791RecordDESC = 1,
	ab1791RecordASG = 2,
	ab1791RecordSCAN = 3,
	ab1791RecordPINI = 4,
	ab1791RecordPHAS = 5,
	ab1791RecordEVNT = 6,
	ab1791RecordTSE = 7,
	ab1791RecordTSEL = 8,
	ab1791RecordDTYP = 9,
	ab1791RecordDISV = 10,
	ab1791RecordDISA = 11,
	ab1791RecordSDIS = 12,
	ab1791RecordMLOK = 13,
	ab1791RecordMLIS = 14,
	ab1791RecordDISP = 15,
	ab1791RecordPROC = 16,
	ab1791RecordSTAT = 17,
	ab1791RecordSEVR = 18,
	ab1791RecordNSTA = 19,
	ab1791RecordNSEV = 20,
	ab1791RecordACKS = 21,
	ab1791RecordACKT = 22,
	ab1791RecordDISS = 23,
	ab1791RecordLCNT = 24,
	ab1791RecordPACT = 25,
	ab1791RecordPUTF = 26,
	ab1791RecordRPRO = 27,
	ab1791RecordASP = 28,
	ab1791RecordPPN = 29,
	ab1791RecordPPNR = 30,
	ab1791RecordSPVT = 31,
	ab1791RecordRSET = 32,
	ab1791RecordDSET = 33,
	ab1791RecordDPVT = 34,
	ab1791RecordRDES = 35,
	ab1791RecordLSET = 36,
	ab1791RecordPRIO = 37,
	ab1791RecordTPRO = 38,
	ab1791RecordBKPT = 39,
	ab1791RecordUDF = 40,
	ab1791RecordUDFS = 41,
	ab1791RecordTIME = 42,
	ab1791RecordFLNK = 43,
	ab1791RecordVAL = 44,
	ab1791RecordTYPE = 45,
	ab1791RecordRANG = 46,
	ab1791RecordFILT = 47,
	ab1791RecordLKST = 48,
	ab1791RecordLOCA = 49,
	ab1791RecordLINK = 50,
	ab1791RecordRACK = 51,
	ab1791RecordSLOT = 52,
	ab1791RecordNFAI = 53,
	ab1791RecordINP0 = 54,
	ab1791RecordINP1 = 55,
	ab1791RecordINP2 = 56,
	ab1791RecordINP3 = 57,
	ab1791RecordOUT0 = 58,
	ab1791RecordOUT1 = 59
} ab1791FieldIndex;

#ifdef GEN_SIZE_OFFSET

#ifdef __cplusplus
extern "C" {
#endif
#include <epicsExport.h>
static int ab1791RecordSizeOffset(dbRecordType *prt)
{
    ab1791Record *prec = 0;
    prt->papFldDes[ab1791RecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[ab1791RecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[ab1791RecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[ab1791RecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[ab1791RecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[ab1791RecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[ab1791RecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[ab1791RecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[ab1791RecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[ab1791RecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[ab1791RecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[ab1791RecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[ab1791RecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[ab1791RecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[ab1791RecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[ab1791RecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[ab1791RecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[ab1791RecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[ab1791RecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[ab1791RecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[ab1791RecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[ab1791RecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[ab1791RecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[ab1791RecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[ab1791RecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[ab1791RecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[ab1791RecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[ab1791RecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[ab1791RecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[ab1791RecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[ab1791RecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[ab1791RecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[ab1791RecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[ab1791RecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[ab1791RecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[ab1791RecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[ab1791RecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[ab1791RecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[ab1791RecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[ab1791RecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[ab1791RecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[ab1791RecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[ab1791RecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[ab1791RecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[ab1791RecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[ab1791RecordTYPE]->size = sizeof(prec->type);
    prt->papFldDes[ab1791RecordRANG]->size = sizeof(prec->rang);
    prt->papFldDes[ab1791RecordFILT]->size = sizeof(prec->filt);
    prt->papFldDes[ab1791RecordLKST]->size = sizeof(prec->lkst);
    prt->papFldDes[ab1791RecordLOCA]->size = sizeof(prec->loca);
    prt->papFldDes[ab1791RecordLINK]->size = sizeof(prec->link);
    prt->papFldDes[ab1791RecordRACK]->size = sizeof(prec->rack);
    prt->papFldDes[ab1791RecordSLOT]->size = sizeof(prec->slot);
    prt->papFldDes[ab1791RecordNFAI]->size = sizeof(prec->nfai);
    prt->papFldDes[ab1791RecordINP0]->size = sizeof(prec->inp0);
    prt->papFldDes[ab1791RecordINP1]->size = sizeof(prec->inp1);
    prt->papFldDes[ab1791RecordINP2]->size = sizeof(prec->inp2);
    prt->papFldDes[ab1791RecordINP3]->size = sizeof(prec->inp3);
    prt->papFldDes[ab1791RecordOUT0]->size = sizeof(prec->out0);
    prt->papFldDes[ab1791RecordOUT1]->size = sizeof(prec->out1);
    prt->papFldDes[ab1791RecordNAME]->offset = (char *)&prec->name - (char *)prec;
    prt->papFldDes[ab1791RecordDESC]->offset = (char *)&prec->desc - (char *)prec;
    prt->papFldDes[ab1791RecordASG]->offset = (char *)&prec->asg - (char *)prec;
    prt->papFldDes[ab1791RecordSCAN]->offset = (char *)&prec->scan - (char *)prec;
    prt->papFldDes[ab1791RecordPINI]->offset = (char *)&prec->pini - (char *)prec;
    prt->papFldDes[ab1791RecordPHAS]->offset = (char *)&prec->phas - (char *)prec;
    prt->papFldDes[ab1791RecordEVNT]->offset = (char *)&prec->evnt - (char *)prec;
    prt->papFldDes[ab1791RecordTSE]->offset = (char *)&prec->tse - (char *)prec;
    prt->papFldDes[ab1791RecordTSEL]->offset = (char *)&prec->tsel - (char *)prec;
    prt->papFldDes[ab1791RecordDTYP]->offset = (char *)&prec->dtyp - (char *)prec;
    prt->papFldDes[ab1791RecordDISV]->offset = (char *)&prec->disv - (char *)prec;
    prt->papFldDes[ab1791RecordDISA]->offset = (char *)&prec->disa - (char *)prec;
    prt->papFldDes[ab1791RecordSDIS]->offset = (char *)&prec->sdis - (char *)prec;
    prt->papFldDes[ab1791RecordMLOK]->offset = (char *)&prec->mlok - (char *)prec;
    prt->papFldDes[ab1791RecordMLIS]->offset = (char *)&prec->mlis - (char *)prec;
    prt->papFldDes[ab1791RecordDISP]->offset = (char *)&prec->disp - (char *)prec;
    prt->papFldDes[ab1791RecordPROC]->offset = (char *)&prec->proc - (char *)prec;
    prt->papFldDes[ab1791RecordSTAT]->offset = (char *)&prec->stat - (char *)prec;
    prt->papFldDes[ab1791RecordSEVR]->offset = (char *)&prec->sevr - (char *)prec;
    prt->papFldDes[ab1791RecordNSTA]->offset = (char *)&prec->nsta - (char *)prec;
    prt->papFldDes[ab1791RecordNSEV]->offset = (char *)&prec->nsev - (char *)prec;
    prt->papFldDes[ab1791RecordACKS]->offset = (char *)&prec->acks - (char *)prec;
    prt->papFldDes[ab1791RecordACKT]->offset = (char *)&prec->ackt - (char *)prec;
    prt->papFldDes[ab1791RecordDISS]->offset = (char *)&prec->diss - (char *)prec;
    prt->papFldDes[ab1791RecordLCNT]->offset = (char *)&prec->lcnt - (char *)prec;
    prt->papFldDes[ab1791RecordPACT]->offset = (char *)&prec->pact - (char *)prec;
    prt->papFldDes[ab1791RecordPUTF]->offset = (char *)&prec->putf - (char *)prec;
    prt->papFldDes[ab1791RecordRPRO]->offset = (char *)&prec->rpro - (char *)prec;
    prt->papFldDes[ab1791RecordASP]->offset = (char *)&prec->asp - (char *)prec;
    prt->papFldDes[ab1791RecordPPN]->offset = (char *)&prec->ppn - (char *)prec;
    prt->papFldDes[ab1791RecordPPNR]->offset = (char *)&prec->ppnr - (char *)prec;
    prt->papFldDes[ab1791RecordSPVT]->offset = (char *)&prec->spvt - (char *)prec;
    prt->papFldDes[ab1791RecordRSET]->offset = (char *)&prec->rset - (char *)prec;
    prt->papFldDes[ab1791RecordDSET]->offset = (char *)&prec->dset - (char *)prec;
    prt->papFldDes[ab1791RecordDPVT]->offset = (char *)&prec->dpvt - (char *)prec;
    prt->papFldDes[ab1791RecordRDES]->offset = (char *)&prec->rdes - (char *)prec;
    prt->papFldDes[ab1791RecordLSET]->offset = (char *)&prec->lset - (char *)prec;
    prt->papFldDes[ab1791RecordPRIO]->offset = (char *)&prec->prio - (char *)prec;
    prt->papFldDes[ab1791RecordTPRO]->offset = (char *)&prec->tpro - (char *)prec;
    prt->papFldDes[ab1791RecordBKPT]->offset = (char *)&prec->bkpt - (char *)prec;
    prt->papFldDes[ab1791RecordUDF]->offset = (char *)&prec->udf - (char *)prec;
    prt->papFldDes[ab1791RecordUDFS]->offset = (char *)&prec->udfs - (char *)prec;
    prt->papFldDes[ab1791RecordTIME]->offset = (char *)&prec->time - (char *)prec;
    prt->papFldDes[ab1791RecordFLNK]->offset = (char *)&prec->flnk - (char *)prec;
    prt->papFldDes[ab1791RecordVAL]->offset = (char *)&prec->val - (char *)prec;
    prt->papFldDes[ab1791RecordTYPE]->offset = (char *)&prec->type - (char *)prec;
    prt->papFldDes[ab1791RecordRANG]->offset = (char *)&prec->rang - (char *)prec;
    prt->papFldDes[ab1791RecordFILT]->offset = (char *)&prec->filt - (char *)prec;
    prt->papFldDes[ab1791RecordLKST]->offset = (char *)&prec->lkst - (char *)prec;
    prt->papFldDes[ab1791RecordLOCA]->offset = (char *)&prec->loca - (char *)prec;
    prt->papFldDes[ab1791RecordLINK]->offset = (char *)&prec->link - (char *)prec;
    prt->papFldDes[ab1791RecordRACK]->offset = (char *)&prec->rack - (char *)prec;
    prt->papFldDes[ab1791RecordSLOT]->offset = (char *)&prec->slot - (char *)prec;
    prt->papFldDes[ab1791RecordNFAI]->offset = (char *)&prec->nfai - (char *)prec;
    prt->papFldDes[ab1791RecordINP0]->offset = (char *)&prec->inp0 - (char *)prec;
    prt->papFldDes[ab1791RecordINP1]->offset = (char *)&prec->inp1 - (char *)prec;
    prt->papFldDes[ab1791RecordINP2]->offset = (char *)&prec->inp2 - (char *)prec;
    prt->papFldDes[ab1791RecordINP3]->offset = (char *)&prec->inp3 - (char *)prec;
    prt->papFldDes[ab1791RecordOUT0]->offset = (char *)&prec->out0 - (char *)prec;
    prt->papFldDes[ab1791RecordOUT1]->offset = (char *)&prec->out1 - (char *)prec;
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(ab1791RecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_ab1791Record_H */
