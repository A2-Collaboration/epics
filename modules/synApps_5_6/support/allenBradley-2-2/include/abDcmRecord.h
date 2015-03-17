/* abDcmRecord.h generated from abDcmRecord.dbd */

#ifndef INC_abDcmRecord_H
#define INC_abDcmRecord_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "epicsTime.h"

typedef enum {
    abDcm_1771DCM                   /* 1771-DCM */,
    abDcm_1771PLCadapter            /* PLC adapter port */,
    abDcm_1771MultiSlot             /* PLCMultiSlot */,
    abDcm_DCMT_NUM_CHOICES
} abDcm_DCMT;

typedef struct abDcmRecord {
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
    char                val[40];    /* Link Status */
    char                oval[40];   /* Link Status */
    epicsEnum16         dcmt;       /* DCM Type */
    epicsUInt16         nt;         /* Number of Tables */
    epicsUInt16         toff;       /* Offset in message of Table Number */
    epicsFloat32        dly;        /* block transfer delay  */
    epicsEnum16         loca;       /* scanIoRequest comm err */
    epicsUInt16         link;       /* Scanner Number */
    epicsUInt16         rack;       /* Rack */
    epicsUInt16         slot;       /* Slot */
    epicsUInt16         mcw;        /* Max Consecutive Writes */
    void *		t0;                     /* Table Array 0 */
    void *		t1;                     /* Table Array 1 */
    void *		t2;                     /* Table Array 2 */
    void *		t3;                     /* Table Array 3 */
    void *		t4;                     /* Table Array 4 */
    void *		t5;                     /* Table Array 5 */
    void *		t6;                     /* Table Array 6 */
    void *		t7;                     /* Table Array 7 */
    void *		t8;                     /* Table Array 8 */
    void *		t9;                     /* Table Array 9 */
} abDcmRecord;

typedef enum {
	abDcmRecordNAME = 0,
	abDcmRecordDESC = 1,
	abDcmRecordASG = 2,
	abDcmRecordSCAN = 3,
	abDcmRecordPINI = 4,
	abDcmRecordPHAS = 5,
	abDcmRecordEVNT = 6,
	abDcmRecordTSE = 7,
	abDcmRecordTSEL = 8,
	abDcmRecordDTYP = 9,
	abDcmRecordDISV = 10,
	abDcmRecordDISA = 11,
	abDcmRecordSDIS = 12,
	abDcmRecordMLOK = 13,
	abDcmRecordMLIS = 14,
	abDcmRecordDISP = 15,
	abDcmRecordPROC = 16,
	abDcmRecordSTAT = 17,
	abDcmRecordSEVR = 18,
	abDcmRecordNSTA = 19,
	abDcmRecordNSEV = 20,
	abDcmRecordACKS = 21,
	abDcmRecordACKT = 22,
	abDcmRecordDISS = 23,
	abDcmRecordLCNT = 24,
	abDcmRecordPACT = 25,
	abDcmRecordPUTF = 26,
	abDcmRecordRPRO = 27,
	abDcmRecordASP = 28,
	abDcmRecordPPN = 29,
	abDcmRecordPPNR = 30,
	abDcmRecordSPVT = 31,
	abDcmRecordRSET = 32,
	abDcmRecordDSET = 33,
	abDcmRecordDPVT = 34,
	abDcmRecordRDES = 35,
	abDcmRecordLSET = 36,
	abDcmRecordPRIO = 37,
	abDcmRecordTPRO = 38,
	abDcmRecordBKPT = 39,
	abDcmRecordUDF = 40,
	abDcmRecordUDFS = 41,
	abDcmRecordTIME = 42,
	abDcmRecordFLNK = 43,
	abDcmRecordVAL = 44,
	abDcmRecordOVAL = 45,
	abDcmRecordDCMT = 46,
	abDcmRecordNT = 47,
	abDcmRecordTOFF = 48,
	abDcmRecordDLY = 49,
	abDcmRecordLOCA = 50,
	abDcmRecordLINK = 51,
	abDcmRecordRACK = 52,
	abDcmRecordSLOT = 53,
	abDcmRecordMCW = 54,
	abDcmRecordT0 = 55,
	abDcmRecordT1 = 56,
	abDcmRecordT2 = 57,
	abDcmRecordT3 = 58,
	abDcmRecordT4 = 59,
	abDcmRecordT5 = 60,
	abDcmRecordT6 = 61,
	abDcmRecordT7 = 62,
	abDcmRecordT8 = 63,
	abDcmRecordT9 = 64
} abDcmFieldIndex;

#ifdef GEN_SIZE_OFFSET

#ifdef __cplusplus
extern "C" {
#endif
#include <epicsExport.h>
static int abDcmRecordSizeOffset(dbRecordType *prt)
{
    abDcmRecord *prec = 0;
    prt->papFldDes[abDcmRecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[abDcmRecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[abDcmRecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[abDcmRecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[abDcmRecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[abDcmRecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[abDcmRecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[abDcmRecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[abDcmRecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[abDcmRecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[abDcmRecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[abDcmRecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[abDcmRecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[abDcmRecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[abDcmRecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[abDcmRecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[abDcmRecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[abDcmRecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[abDcmRecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[abDcmRecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[abDcmRecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[abDcmRecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[abDcmRecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[abDcmRecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[abDcmRecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[abDcmRecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[abDcmRecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[abDcmRecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[abDcmRecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[abDcmRecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[abDcmRecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[abDcmRecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[abDcmRecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[abDcmRecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[abDcmRecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[abDcmRecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[abDcmRecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[abDcmRecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[abDcmRecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[abDcmRecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[abDcmRecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[abDcmRecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[abDcmRecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[abDcmRecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[abDcmRecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[abDcmRecordOVAL]->size = sizeof(prec->oval);
    prt->papFldDes[abDcmRecordDCMT]->size = sizeof(prec->dcmt);
    prt->papFldDes[abDcmRecordNT]->size = sizeof(prec->nt);
    prt->papFldDes[abDcmRecordTOFF]->size = sizeof(prec->toff);
    prt->papFldDes[abDcmRecordDLY]->size = sizeof(prec->dly);
    prt->papFldDes[abDcmRecordLOCA]->size = sizeof(prec->loca);
    prt->papFldDes[abDcmRecordLINK]->size = sizeof(prec->link);
    prt->papFldDes[abDcmRecordRACK]->size = sizeof(prec->rack);
    prt->papFldDes[abDcmRecordSLOT]->size = sizeof(prec->slot);
    prt->papFldDes[abDcmRecordMCW]->size = sizeof(prec->mcw);
    prt->papFldDes[abDcmRecordT0]->size = sizeof(prec->t0);
    prt->papFldDes[abDcmRecordT1]->size = sizeof(prec->t1);
    prt->papFldDes[abDcmRecordT2]->size = sizeof(prec->t2);
    prt->papFldDes[abDcmRecordT3]->size = sizeof(prec->t3);
    prt->papFldDes[abDcmRecordT4]->size = sizeof(prec->t4);
    prt->papFldDes[abDcmRecordT5]->size = sizeof(prec->t5);
    prt->papFldDes[abDcmRecordT6]->size = sizeof(prec->t6);
    prt->papFldDes[abDcmRecordT7]->size = sizeof(prec->t7);
    prt->papFldDes[abDcmRecordT8]->size = sizeof(prec->t8);
    prt->papFldDes[abDcmRecordT9]->size = sizeof(prec->t9);
    prt->papFldDes[abDcmRecordNAME]->offset = (char *)&prec->name - (char *)prec;
    prt->papFldDes[abDcmRecordDESC]->offset = (char *)&prec->desc - (char *)prec;
    prt->papFldDes[abDcmRecordASG]->offset = (char *)&prec->asg - (char *)prec;
    prt->papFldDes[abDcmRecordSCAN]->offset = (char *)&prec->scan - (char *)prec;
    prt->papFldDes[abDcmRecordPINI]->offset = (char *)&prec->pini - (char *)prec;
    prt->papFldDes[abDcmRecordPHAS]->offset = (char *)&prec->phas - (char *)prec;
    prt->papFldDes[abDcmRecordEVNT]->offset = (char *)&prec->evnt - (char *)prec;
    prt->papFldDes[abDcmRecordTSE]->offset = (char *)&prec->tse - (char *)prec;
    prt->papFldDes[abDcmRecordTSEL]->offset = (char *)&prec->tsel - (char *)prec;
    prt->papFldDes[abDcmRecordDTYP]->offset = (char *)&prec->dtyp - (char *)prec;
    prt->papFldDes[abDcmRecordDISV]->offset = (char *)&prec->disv - (char *)prec;
    prt->papFldDes[abDcmRecordDISA]->offset = (char *)&prec->disa - (char *)prec;
    prt->papFldDes[abDcmRecordSDIS]->offset = (char *)&prec->sdis - (char *)prec;
    prt->papFldDes[abDcmRecordMLOK]->offset = (char *)&prec->mlok - (char *)prec;
    prt->papFldDes[abDcmRecordMLIS]->offset = (char *)&prec->mlis - (char *)prec;
    prt->papFldDes[abDcmRecordDISP]->offset = (char *)&prec->disp - (char *)prec;
    prt->papFldDes[abDcmRecordPROC]->offset = (char *)&prec->proc - (char *)prec;
    prt->papFldDes[abDcmRecordSTAT]->offset = (char *)&prec->stat - (char *)prec;
    prt->papFldDes[abDcmRecordSEVR]->offset = (char *)&prec->sevr - (char *)prec;
    prt->papFldDes[abDcmRecordNSTA]->offset = (char *)&prec->nsta - (char *)prec;
    prt->papFldDes[abDcmRecordNSEV]->offset = (char *)&prec->nsev - (char *)prec;
    prt->papFldDes[abDcmRecordACKS]->offset = (char *)&prec->acks - (char *)prec;
    prt->papFldDes[abDcmRecordACKT]->offset = (char *)&prec->ackt - (char *)prec;
    prt->papFldDes[abDcmRecordDISS]->offset = (char *)&prec->diss - (char *)prec;
    prt->papFldDes[abDcmRecordLCNT]->offset = (char *)&prec->lcnt - (char *)prec;
    prt->papFldDes[abDcmRecordPACT]->offset = (char *)&prec->pact - (char *)prec;
    prt->papFldDes[abDcmRecordPUTF]->offset = (char *)&prec->putf - (char *)prec;
    prt->papFldDes[abDcmRecordRPRO]->offset = (char *)&prec->rpro - (char *)prec;
    prt->papFldDes[abDcmRecordASP]->offset = (char *)&prec->asp - (char *)prec;
    prt->papFldDes[abDcmRecordPPN]->offset = (char *)&prec->ppn - (char *)prec;
    prt->papFldDes[abDcmRecordPPNR]->offset = (char *)&prec->ppnr - (char *)prec;
    prt->papFldDes[abDcmRecordSPVT]->offset = (char *)&prec->spvt - (char *)prec;
    prt->papFldDes[abDcmRecordRSET]->offset = (char *)&prec->rset - (char *)prec;
    prt->papFldDes[abDcmRecordDSET]->offset = (char *)&prec->dset - (char *)prec;
    prt->papFldDes[abDcmRecordDPVT]->offset = (char *)&prec->dpvt - (char *)prec;
    prt->papFldDes[abDcmRecordRDES]->offset = (char *)&prec->rdes - (char *)prec;
    prt->papFldDes[abDcmRecordLSET]->offset = (char *)&prec->lset - (char *)prec;
    prt->papFldDes[abDcmRecordPRIO]->offset = (char *)&prec->prio - (char *)prec;
    prt->papFldDes[abDcmRecordTPRO]->offset = (char *)&prec->tpro - (char *)prec;
    prt->papFldDes[abDcmRecordBKPT]->offset = (char *)&prec->bkpt - (char *)prec;
    prt->papFldDes[abDcmRecordUDF]->offset = (char *)&prec->udf - (char *)prec;
    prt->papFldDes[abDcmRecordUDFS]->offset = (char *)&prec->udfs - (char *)prec;
    prt->papFldDes[abDcmRecordTIME]->offset = (char *)&prec->time - (char *)prec;
    prt->papFldDes[abDcmRecordFLNK]->offset = (char *)&prec->flnk - (char *)prec;
    prt->papFldDes[abDcmRecordVAL]->offset = (char *)&prec->val - (char *)prec;
    prt->papFldDes[abDcmRecordOVAL]->offset = (char *)&prec->oval - (char *)prec;
    prt->papFldDes[abDcmRecordDCMT]->offset = (char *)&prec->dcmt - (char *)prec;
    prt->papFldDes[abDcmRecordNT]->offset = (char *)&prec->nt - (char *)prec;
    prt->papFldDes[abDcmRecordTOFF]->offset = (char *)&prec->toff - (char *)prec;
    prt->papFldDes[abDcmRecordDLY]->offset = (char *)&prec->dly - (char *)prec;
    prt->papFldDes[abDcmRecordLOCA]->offset = (char *)&prec->loca - (char *)prec;
    prt->papFldDes[abDcmRecordLINK]->offset = (char *)&prec->link - (char *)prec;
    prt->papFldDes[abDcmRecordRACK]->offset = (char *)&prec->rack - (char *)prec;
    prt->papFldDes[abDcmRecordSLOT]->offset = (char *)&prec->slot - (char *)prec;
    prt->papFldDes[abDcmRecordMCW]->offset = (char *)&prec->mcw - (char *)prec;
    prt->papFldDes[abDcmRecordT0]->offset = (char *)&prec->t0 - (char *)prec;
    prt->papFldDes[abDcmRecordT1]->offset = (char *)&prec->t1 - (char *)prec;
    prt->papFldDes[abDcmRecordT2]->offset = (char *)&prec->t2 - (char *)prec;
    prt->papFldDes[abDcmRecordT3]->offset = (char *)&prec->t3 - (char *)prec;
    prt->papFldDes[abDcmRecordT4]->offset = (char *)&prec->t4 - (char *)prec;
    prt->papFldDes[abDcmRecordT5]->offset = (char *)&prec->t5 - (char *)prec;
    prt->papFldDes[abDcmRecordT6]->offset = (char *)&prec->t6 - (char *)prec;
    prt->papFldDes[abDcmRecordT7]->offset = (char *)&prec->t7 - (char *)prec;
    prt->papFldDes[abDcmRecordT8]->offset = (char *)&prec->t8 - (char *)prec;
    prt->papFldDes[abDcmRecordT9]->offset = (char *)&prec->t9 - (char *)prec;
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(abDcmRecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_abDcmRecord_H */
