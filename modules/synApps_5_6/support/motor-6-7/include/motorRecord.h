/* motorRecord.h generated from motorRecord.dbd */

#ifndef INC_motorRecord_H
#define INC_motorRecord_H

#include "epicsTypes.h"
#include "link.h"
#include "epicsMutex.h"
#include "ellLib.h"
#include "epicsTime.h"

typedef enum {
    motorRMOD_D                     /* Default */,
    motorRMOD_A                     /* Arthmetic */,
    motorRMOD_G                     /* Geometric */,
    motorRMOD_NUM_CHOICES
} motorRMOD;

typedef enum {
    motorDIR_Pos                    /* Pos */,
    motorDIR_Neg                    /* Neg */,
    motorDIR_NUM_CHOICES
} motorDIR;

typedef enum {
    motorSTUP_OFF                   /* OFF */,
    motorSTUP_ON                    /* ON */,
    motorSTUP_BUSY                  /* BUSY */,
    motorSTUP_NUM_CHOICES
} motorSTUP;

typedef enum {
    motorSPMG_Stop                  /* Stop */,
    motorSPMG_Pause                 /* Pause */,
    motorSPMG_Move                  /* Move */,
    motorSPMG_Go                    /* Go */,
    motorSPMG_NUM_CHOICES
} motorSPMG;

typedef enum {
    menuOmslsupervisory             /* supervisory */,
    menuOmslclosed_loop             /* closed_loop */,
    menuOmsl_NUM_CHOICES
} menuOmsl;

typedef enum {
    motorMODE_Position              /* Position */,
    motorMODE_Velocity              /* Velocity */,
    motorMODE_NUM_CHOICES
} motorMODE;

typedef enum {
    motorFOFF_Variable              /* Variable */,
    motorFOFF_Frozen                /* Frozen */,
    motorFOFF_NUM_CHOICES
} motorFOFF;

typedef enum {
    motorSET_Use                    /* Use */,
    motorSET_Set                    /* Set */,
    motorSET_NUM_CHOICES
} motorSET;

typedef enum {
    motorTORQ_Disable               /* Disable */,
    motorTORQ_Enable                /* Enable */,
    motorTORQ_NUM_CHOICES
} motorTORQ;

typedef enum {
    menuYesNoNO                     /* NO */,
    menuYesNoYES                    /* YES */,
    menuYesNo_NUM_CHOICES
} menuYesNo;

typedef enum {
    motorUEIP_No                    /* No */,
    motorUEIP_Yes                   /* Yes */,
    motorUEIP_NUM_CHOICES
} motorUEIP;

typedef struct motorRecord {
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
    epicsFloat32        vers;       /* Code Version */
    epicsFloat64        off;        /* User Offset (EGU) */
    epicsEnum16         foff;       /* Offset-Freeze Switch */
    epicsInt16          fof;        /* Freeze Offset */
    epicsInt16          vof;        /* Variable Offset */
    epicsEnum16         dir;        /* User Direction */
    epicsEnum16         set;        /* Set/Use Switch */
    epicsInt16          sset;       /* Set SET Mode */
    epicsInt16          suse;       /* Set USE Mode */
    epicsFloat64        velo;       /* Velocity (EGU/s) */
    epicsFloat64        vbas;       /* Base Velocity (EGU/s) */
    epicsFloat64        vmax;       /* Max. Velocity (EGU/s) */
    epicsFloat64        s;          /* Speed (revolutions/sec) */
    epicsFloat64        sbas;       /* Base Speed (RPS) */
    epicsFloat64        smax;       /* Max. Speed (RPS) */
    epicsFloat64        accl;       /* Seconds to Velocity */
    epicsFloat64        bdst;       /* BL Distance (EGU) */
    epicsFloat64        bvel;       /* BL Velocity (EGU/s) */
    epicsFloat64        sbak;       /* BL Speed (RPS) */
    epicsFloat64        bacc;       /* BL Seconds to Velocity */
    epicsFloat32        frac;       /* Move Fraction */
    DBLINK              out;        /* Output Specification */
    epicsInt16          card;       /* Card Number */
    DBLINK              rdbl;       /* Readback Location */
    DBLINK              dol;        /* Desired Output Loc */
    epicsEnum16         omsl;       /* Output Mode Select */
    DBLINK              rlnk;       /* Readback OutLink */
    epicsInt32          srev;       /* Steps per Revolution */
    epicsFloat64        urev;       /* EGU's per Revolution */
    epicsFloat64        mres;       /* Motor Step Size (EGU) */
    epicsFloat64        eres;       /* Encoder Step Size (EGU) */
    epicsFloat64        rres;       /* Readback Step Size (EGU */
    epicsEnum16         ueip;       /* Use Encoder If Present */
    epicsEnum16         urip;       /* Use RDBL Link If Presen */
    epicsInt16          prec;       /* Display Precision */
    char                egu[16];    /* Engineering Units */
    epicsFloat64        hlm;        /* User High Limit */
    epicsFloat64        llm;        /* User Low Limit */
    epicsFloat64        dhlm;       /* Dial High Limit */
    epicsFloat64        dllm;       /* Dial Low Limit */
    epicsFloat64        hopr;       /* High Operating Range */
    epicsFloat64        lopr;       /* Low Operating Range */
    epicsInt16          hls;        /* User High Limit Switch */
    epicsInt16          lls;        /* User Low Limit Switch */
    epicsInt16          rhls;       /* Raw High Limit Switch */
    epicsInt16          rlls;       /* Raw Low Limit Switch */
    epicsFloat64        hihi;       /* Hihi Alarm Limit (EGU) */
    epicsFloat64        lolo;       /* Lolo Alarm Limit (EGU) */
    epicsFloat64        high;       /* High Alarm Limit (EGU) */
    epicsFloat64        low;        /* Low Alarm Limit (EGU) */
    epicsEnum16         hhsv;       /* Hihi Severity */
    epicsEnum16         llsv;       /* Lolo Severity */
    epicsEnum16         hsv;        /* High Severity */
    epicsEnum16         lsv;        /* Low Severity */
    epicsEnum16         hlsv;       /* HW Limit Violation Svr */
    epicsFloat64        rdbd;       /* Retry Deadband (EGU) */
    epicsInt16          rcnt;       /* Retry count */
    epicsInt16          rtry;       /* Max retry count */
    epicsInt16          miss;       /* Ran out of retries */
    epicsEnum16         spmg;       /* Stop/Pause/Move/Go */
    epicsEnum16         lspg;       /* Last SPMG */
    epicsInt16          stop;       /* Stop */
    epicsInt16          homf;       /* Home Forward */
    epicsInt16          homr;       /* Home Reverse */
    epicsInt16          jogf;       /* Jog motor Forward */
    epicsInt16          jogr;       /* Jog motor Reverse */
    epicsInt16          twf;        /* Tweak motor Forward */
    epicsInt16          twr;        /* Tweak motor Reverse */
    epicsFloat64        twv;        /* Tweak Step Size (EGU) */
    epicsFloat64        val;        /* User Desired Value (EGU */
    epicsFloat64        lval;       /* Last User Des Val (EGU) */
    epicsFloat64        dval;       /* Dial Desired Value (EGU */
    epicsFloat64        ldvl;       /* Last Dial Des Val (EGU) */
    epicsInt32          rval;       /* Raw Desired Value (step */
    epicsInt32          lrvl;       /* Last Raw Des Val (steps */
    epicsFloat64        rlv;        /* Relative Value (EGU) */
    epicsFloat64        lrlv;       /* Last Rel Value (EGU) */
    epicsFloat64        rbv;        /* User Readback Value */
    epicsFloat64        drbv;       /* Dial Readback Value */
    epicsFloat64        diff;       /* Difference dval-drbv */
    epicsInt32          rdif;       /* Difference rval-rrbv */
    epicsInt16          cdir;       /* Raw cmnd direction */
    epicsInt32          rrbv;       /* Raw Readback Value */
    epicsInt32          rmp;        /* Raw Motor Position */
    epicsInt32          rep;        /* Raw Encoder Position */
    epicsInt32          rvel;       /* Raw Velocity */
    epicsInt16          dmov;       /* Done moving to value */
    epicsInt16          movn;       /* Motor is moving */
    epicsUInt32         msta;       /* Motor Status */
    epicsInt16          lvio;       /* Limit violation */
    epicsInt16          tdir;       /* Direction of Travel */
    epicsInt16          athm;       /* At HOME */
    epicsInt16          pp;         /* Post process command */
    epicsUInt16         mip;        /* Motion In Progress */
    epicsUInt32         mmap;       /* Monitor Mask */
    epicsUInt32         nmap;       /* Monitor Mask (more) */
    epicsFloat64        dly;        /* Readback settle time (s) */
    void             *cbak;         /* Callback structure */
    epicsFloat64        pcof;       /* Proportional Gain */
    epicsFloat64        icof;       /* Integral Gain */
    epicsFloat64        dcof;       /* Derivative Gain */
    epicsEnum16         cnen;       /* Enable control */
    char                init[40];   /* Startup commands */
    char                prem[40];   /* Pre-move commands */
    char                post[40];   /* Post-move commands */
    DBLINK              stoo;       /* STOP OutLink */
    DBLINK              dinp;       /* DMOV Input Link */
    DBLINK              rinp;       /* RMP Input Link */
    epicsFloat64        jvel;       /* Jog Velocity (EGU/s) */
    epicsFloat64        jar;        /* Jog Accel. (EGU/s^2) */
    epicsEnum16         lock;       /* Soft Channel Position Lock */
    epicsEnum16         ntm;        /* New Target Monitor */
    epicsUInt16         ntmf;       /* NTM Deadband Factor */
    epicsFloat64        hvel;       /* Home Velocity (EGU/s) */
    epicsEnum16         stup;       /* Status Update */
    epicsEnum16         rmod;       /* Retry Mode */
    epicsFloat64        adel;       /* Archive Deadband */
    epicsFloat64        mdel;       /* Monitor Deadband */
    epicsFloat64        alst;       /* Last Value Archived */
    epicsFloat64        mlst;       /* Last Val Monitored */
    epicsInt16          sync;       /* Sync position */
} motorRecord;

typedef enum {
	motorRecordNAME = 0,
	motorRecordDESC = 1,
	motorRecordASG = 2,
	motorRecordSCAN = 3,
	motorRecordPINI = 4,
	motorRecordPHAS = 5,
	motorRecordEVNT = 6,
	motorRecordTSE = 7,
	motorRecordTSEL = 8,
	motorRecordDTYP = 9,
	motorRecordDISV = 10,
	motorRecordDISA = 11,
	motorRecordSDIS = 12,
	motorRecordMLOK = 13,
	motorRecordMLIS = 14,
	motorRecordDISP = 15,
	motorRecordPROC = 16,
	motorRecordSTAT = 17,
	motorRecordSEVR = 18,
	motorRecordNSTA = 19,
	motorRecordNSEV = 20,
	motorRecordACKS = 21,
	motorRecordACKT = 22,
	motorRecordDISS = 23,
	motorRecordLCNT = 24,
	motorRecordPACT = 25,
	motorRecordPUTF = 26,
	motorRecordRPRO = 27,
	motorRecordASP = 28,
	motorRecordPPN = 29,
	motorRecordPPNR = 30,
	motorRecordSPVT = 31,
	motorRecordRSET = 32,
	motorRecordDSET = 33,
	motorRecordDPVT = 34,
	motorRecordRDES = 35,
	motorRecordLSET = 36,
	motorRecordPRIO = 37,
	motorRecordTPRO = 38,
	motorRecordBKPT = 39,
	motorRecordUDF = 40,
	motorRecordUDFS = 41,
	motorRecordTIME = 42,
	motorRecordFLNK = 43,
	motorRecordVERS = 44,
	motorRecordOFF = 45,
	motorRecordFOFF = 46,
	motorRecordFOF = 47,
	motorRecordVOF = 48,
	motorRecordDIR = 49,
	motorRecordSET = 50,
	motorRecordSSET = 51,
	motorRecordSUSE = 52,
	motorRecordVELO = 53,
	motorRecordVBAS = 54,
	motorRecordVMAX = 55,
	motorRecordS = 56,
	motorRecordSBAS = 57,
	motorRecordSMAX = 58,
	motorRecordACCL = 59,
	motorRecordBDST = 60,
	motorRecordBVEL = 61,
	motorRecordSBAK = 62,
	motorRecordBACC = 63,
	motorRecordFRAC = 64,
	motorRecordOUT = 65,
	motorRecordCARD = 66,
	motorRecordRDBL = 67,
	motorRecordDOL = 68,
	motorRecordOMSL = 69,
	motorRecordRLNK = 70,
	motorRecordSREV = 71,
	motorRecordUREV = 72,
	motorRecordMRES = 73,
	motorRecordERES = 74,
	motorRecordRRES = 75,
	motorRecordUEIP = 76,
	motorRecordURIP = 77,
	motorRecordPREC = 78,
	motorRecordEGU = 79,
	motorRecordHLM = 80,
	motorRecordLLM = 81,
	motorRecordDHLM = 82,
	motorRecordDLLM = 83,
	motorRecordHOPR = 84,
	motorRecordLOPR = 85,
	motorRecordHLS = 86,
	motorRecordLLS = 87,
	motorRecordRHLS = 88,
	motorRecordRLLS = 89,
	motorRecordHIHI = 90,
	motorRecordLOLO = 91,
	motorRecordHIGH = 92,
	motorRecordLOW = 93,
	motorRecordHHSV = 94,
	motorRecordLLSV = 95,
	motorRecordHSV = 96,
	motorRecordLSV = 97,
	motorRecordHLSV = 98,
	motorRecordRDBD = 99,
	motorRecordRCNT = 100,
	motorRecordRTRY = 101,
	motorRecordMISS = 102,
	motorRecordSPMG = 103,
	motorRecordLSPG = 104,
	motorRecordSTOP = 105,
	motorRecordHOMF = 106,
	motorRecordHOMR = 107,
	motorRecordJOGF = 108,
	motorRecordJOGR = 109,
	motorRecordTWF = 110,
	motorRecordTWR = 111,
	motorRecordTWV = 112,
	motorRecordVAL = 113,
	motorRecordLVAL = 114,
	motorRecordDVAL = 115,
	motorRecordLDVL = 116,
	motorRecordRVAL = 117,
	motorRecordLRVL = 118,
	motorRecordRLV = 119,
	motorRecordLRLV = 120,
	motorRecordRBV = 121,
	motorRecordDRBV = 122,
	motorRecordDIFF = 123,
	motorRecordRDIF = 124,
	motorRecordCDIR = 125,
	motorRecordRRBV = 126,
	motorRecordRMP = 127,
	motorRecordREP = 128,
	motorRecordRVEL = 129,
	motorRecordDMOV = 130,
	motorRecordMOVN = 131,
	motorRecordMSTA = 132,
	motorRecordLVIO = 133,
	motorRecordTDIR = 134,
	motorRecordATHM = 135,
	motorRecordPP = 136,
	motorRecordMIP = 137,
	motorRecordMMAP = 138,
	motorRecordNMAP = 139,
	motorRecordDLY = 140,
	motorRecordCBAK = 141,
	motorRecordPCOF = 142,
	motorRecordICOF = 143,
	motorRecordDCOF = 144,
	motorRecordCNEN = 145,
	motorRecordINIT = 146,
	motorRecordPREM = 147,
	motorRecordPOST = 148,
	motorRecordSTOO = 149,
	motorRecordDINP = 150,
	motorRecordRINP = 151,
	motorRecordJVEL = 152,
	motorRecordJAR = 153,
	motorRecordLOCK = 154,
	motorRecordNTM = 155,
	motorRecordNTMF = 156,
	motorRecordHVEL = 157,
	motorRecordSTUP = 158,
	motorRecordRMOD = 159,
	motorRecordADEL = 160,
	motorRecordMDEL = 161,
	motorRecordALST = 162,
	motorRecordMLST = 163,
	motorRecordSYNC = 164
} motorFieldIndex;

#ifdef GEN_SIZE_OFFSET

#ifdef __cplusplus
extern "C" {
#endif
#include <epicsExport.h>
static int motorRecordSizeOffset(dbRecordType *prt)
{
    motorRecord *prec = 0;
    prt->papFldDes[motorRecordNAME]->size = sizeof(prec->name);
    prt->papFldDes[motorRecordDESC]->size = sizeof(prec->desc);
    prt->papFldDes[motorRecordASG]->size = sizeof(prec->asg);
    prt->papFldDes[motorRecordSCAN]->size = sizeof(prec->scan);
    prt->papFldDes[motorRecordPINI]->size = sizeof(prec->pini);
    prt->papFldDes[motorRecordPHAS]->size = sizeof(prec->phas);
    prt->papFldDes[motorRecordEVNT]->size = sizeof(prec->evnt);
    prt->papFldDes[motorRecordTSE]->size = sizeof(prec->tse);
    prt->papFldDes[motorRecordTSEL]->size = sizeof(prec->tsel);
    prt->papFldDes[motorRecordDTYP]->size = sizeof(prec->dtyp);
    prt->papFldDes[motorRecordDISV]->size = sizeof(prec->disv);
    prt->papFldDes[motorRecordDISA]->size = sizeof(prec->disa);
    prt->papFldDes[motorRecordSDIS]->size = sizeof(prec->sdis);
    prt->papFldDes[motorRecordMLOK]->size = sizeof(prec->mlok);
    prt->papFldDes[motorRecordMLIS]->size = sizeof(prec->mlis);
    prt->papFldDes[motorRecordDISP]->size = sizeof(prec->disp);
    prt->papFldDes[motorRecordPROC]->size = sizeof(prec->proc);
    prt->papFldDes[motorRecordSTAT]->size = sizeof(prec->stat);
    prt->papFldDes[motorRecordSEVR]->size = sizeof(prec->sevr);
    prt->papFldDes[motorRecordNSTA]->size = sizeof(prec->nsta);
    prt->papFldDes[motorRecordNSEV]->size = sizeof(prec->nsev);
    prt->papFldDes[motorRecordACKS]->size = sizeof(prec->acks);
    prt->papFldDes[motorRecordACKT]->size = sizeof(prec->ackt);
    prt->papFldDes[motorRecordDISS]->size = sizeof(prec->diss);
    prt->papFldDes[motorRecordLCNT]->size = sizeof(prec->lcnt);
    prt->papFldDes[motorRecordPACT]->size = sizeof(prec->pact);
    prt->papFldDes[motorRecordPUTF]->size = sizeof(prec->putf);
    prt->papFldDes[motorRecordRPRO]->size = sizeof(prec->rpro);
    prt->papFldDes[motorRecordASP]->size = sizeof(prec->asp);
    prt->papFldDes[motorRecordPPN]->size = sizeof(prec->ppn);
    prt->papFldDes[motorRecordPPNR]->size = sizeof(prec->ppnr);
    prt->papFldDes[motorRecordSPVT]->size = sizeof(prec->spvt);
    prt->papFldDes[motorRecordRSET]->size = sizeof(prec->rset);
    prt->papFldDes[motorRecordDSET]->size = sizeof(prec->dset);
    prt->papFldDes[motorRecordDPVT]->size = sizeof(prec->dpvt);
    prt->papFldDes[motorRecordRDES]->size = sizeof(prec->rdes);
    prt->papFldDes[motorRecordLSET]->size = sizeof(prec->lset);
    prt->papFldDes[motorRecordPRIO]->size = sizeof(prec->prio);
    prt->papFldDes[motorRecordTPRO]->size = sizeof(prec->tpro);
    prt->papFldDes[motorRecordBKPT]->size = sizeof(prec->bkpt);
    prt->papFldDes[motorRecordUDF]->size = sizeof(prec->udf);
    prt->papFldDes[motorRecordUDFS]->size = sizeof(prec->udfs);
    prt->papFldDes[motorRecordTIME]->size = sizeof(prec->time);
    prt->papFldDes[motorRecordFLNK]->size = sizeof(prec->flnk);
    prt->papFldDes[motorRecordVERS]->size = sizeof(prec->vers);
    prt->papFldDes[motorRecordOFF]->size = sizeof(prec->off);
    prt->papFldDes[motorRecordFOFF]->size = sizeof(prec->foff);
    prt->papFldDes[motorRecordFOF]->size = sizeof(prec->fof);
    prt->papFldDes[motorRecordVOF]->size = sizeof(prec->vof);
    prt->papFldDes[motorRecordDIR]->size = sizeof(prec->dir);
    prt->papFldDes[motorRecordSET]->size = sizeof(prec->set);
    prt->papFldDes[motorRecordSSET]->size = sizeof(prec->sset);
    prt->papFldDes[motorRecordSUSE]->size = sizeof(prec->suse);
    prt->papFldDes[motorRecordVELO]->size = sizeof(prec->velo);
    prt->papFldDes[motorRecordVBAS]->size = sizeof(prec->vbas);
    prt->papFldDes[motorRecordVMAX]->size = sizeof(prec->vmax);
    prt->papFldDes[motorRecordS]->size = sizeof(prec->s);
    prt->papFldDes[motorRecordSBAS]->size = sizeof(prec->sbas);
    prt->papFldDes[motorRecordSMAX]->size = sizeof(prec->smax);
    prt->papFldDes[motorRecordACCL]->size = sizeof(prec->accl);
    prt->papFldDes[motorRecordBDST]->size = sizeof(prec->bdst);
    prt->papFldDes[motorRecordBVEL]->size = sizeof(prec->bvel);
    prt->papFldDes[motorRecordSBAK]->size = sizeof(prec->sbak);
    prt->papFldDes[motorRecordBACC]->size = sizeof(prec->bacc);
    prt->papFldDes[motorRecordFRAC]->size = sizeof(prec->frac);
    prt->papFldDes[motorRecordOUT]->size = sizeof(prec->out);
    prt->papFldDes[motorRecordCARD]->size = sizeof(prec->card);
    prt->papFldDes[motorRecordRDBL]->size = sizeof(prec->rdbl);
    prt->papFldDes[motorRecordDOL]->size = sizeof(prec->dol);
    prt->papFldDes[motorRecordOMSL]->size = sizeof(prec->omsl);
    prt->papFldDes[motorRecordRLNK]->size = sizeof(prec->rlnk);
    prt->papFldDes[motorRecordSREV]->size = sizeof(prec->srev);
    prt->papFldDes[motorRecordUREV]->size = sizeof(prec->urev);
    prt->papFldDes[motorRecordMRES]->size = sizeof(prec->mres);
    prt->papFldDes[motorRecordERES]->size = sizeof(prec->eres);
    prt->papFldDes[motorRecordRRES]->size = sizeof(prec->rres);
    prt->papFldDes[motorRecordUEIP]->size = sizeof(prec->ueip);
    prt->papFldDes[motorRecordURIP]->size = sizeof(prec->urip);
    prt->papFldDes[motorRecordPREC]->size = sizeof(prec->prec);
    prt->papFldDes[motorRecordEGU]->size = sizeof(prec->egu);
    prt->papFldDes[motorRecordHLM]->size = sizeof(prec->hlm);
    prt->papFldDes[motorRecordLLM]->size = sizeof(prec->llm);
    prt->papFldDes[motorRecordDHLM]->size = sizeof(prec->dhlm);
    prt->papFldDes[motorRecordDLLM]->size = sizeof(prec->dllm);
    prt->papFldDes[motorRecordHOPR]->size = sizeof(prec->hopr);
    prt->papFldDes[motorRecordLOPR]->size = sizeof(prec->lopr);
    prt->papFldDes[motorRecordHLS]->size = sizeof(prec->hls);
    prt->papFldDes[motorRecordLLS]->size = sizeof(prec->lls);
    prt->papFldDes[motorRecordRHLS]->size = sizeof(prec->rhls);
    prt->papFldDes[motorRecordRLLS]->size = sizeof(prec->rlls);
    prt->papFldDes[motorRecordHIHI]->size = sizeof(prec->hihi);
    prt->papFldDes[motorRecordLOLO]->size = sizeof(prec->lolo);
    prt->papFldDes[motorRecordHIGH]->size = sizeof(prec->high);
    prt->papFldDes[motorRecordLOW]->size = sizeof(prec->low);
    prt->papFldDes[motorRecordHHSV]->size = sizeof(prec->hhsv);
    prt->papFldDes[motorRecordLLSV]->size = sizeof(prec->llsv);
    prt->papFldDes[motorRecordHSV]->size = sizeof(prec->hsv);
    prt->papFldDes[motorRecordLSV]->size = sizeof(prec->lsv);
    prt->papFldDes[motorRecordHLSV]->size = sizeof(prec->hlsv);
    prt->papFldDes[motorRecordRDBD]->size = sizeof(prec->rdbd);
    prt->papFldDes[motorRecordRCNT]->size = sizeof(prec->rcnt);
    prt->papFldDes[motorRecordRTRY]->size = sizeof(prec->rtry);
    prt->papFldDes[motorRecordMISS]->size = sizeof(prec->miss);
    prt->papFldDes[motorRecordSPMG]->size = sizeof(prec->spmg);
    prt->papFldDes[motorRecordLSPG]->size = sizeof(prec->lspg);
    prt->papFldDes[motorRecordSTOP]->size = sizeof(prec->stop);
    prt->papFldDes[motorRecordHOMF]->size = sizeof(prec->homf);
    prt->papFldDes[motorRecordHOMR]->size = sizeof(prec->homr);
    prt->papFldDes[motorRecordJOGF]->size = sizeof(prec->jogf);
    prt->papFldDes[motorRecordJOGR]->size = sizeof(prec->jogr);
    prt->papFldDes[motorRecordTWF]->size = sizeof(prec->twf);
    prt->papFldDes[motorRecordTWR]->size = sizeof(prec->twr);
    prt->papFldDes[motorRecordTWV]->size = sizeof(prec->twv);
    prt->papFldDes[motorRecordVAL]->size = sizeof(prec->val);
    prt->papFldDes[motorRecordLVAL]->size = sizeof(prec->lval);
    prt->papFldDes[motorRecordDVAL]->size = sizeof(prec->dval);
    prt->papFldDes[motorRecordLDVL]->size = sizeof(prec->ldvl);
    prt->papFldDes[motorRecordRVAL]->size = sizeof(prec->rval);
    prt->papFldDes[motorRecordLRVL]->size = sizeof(prec->lrvl);
    prt->papFldDes[motorRecordRLV]->size = sizeof(prec->rlv);
    prt->papFldDes[motorRecordLRLV]->size = sizeof(prec->lrlv);
    prt->papFldDes[motorRecordRBV]->size = sizeof(prec->rbv);
    prt->papFldDes[motorRecordDRBV]->size = sizeof(prec->drbv);
    prt->papFldDes[motorRecordDIFF]->size = sizeof(prec->diff);
    prt->papFldDes[motorRecordRDIF]->size = sizeof(prec->rdif);
    prt->papFldDes[motorRecordCDIR]->size = sizeof(prec->cdir);
    prt->papFldDes[motorRecordRRBV]->size = sizeof(prec->rrbv);
    prt->papFldDes[motorRecordRMP]->size = sizeof(prec->rmp);
    prt->papFldDes[motorRecordREP]->size = sizeof(prec->rep);
    prt->papFldDes[motorRecordRVEL]->size = sizeof(prec->rvel);
    prt->papFldDes[motorRecordDMOV]->size = sizeof(prec->dmov);
    prt->papFldDes[motorRecordMOVN]->size = sizeof(prec->movn);
    prt->papFldDes[motorRecordMSTA]->size = sizeof(prec->msta);
    prt->papFldDes[motorRecordLVIO]->size = sizeof(prec->lvio);
    prt->papFldDes[motorRecordTDIR]->size = sizeof(prec->tdir);
    prt->papFldDes[motorRecordATHM]->size = sizeof(prec->athm);
    prt->papFldDes[motorRecordPP]->size = sizeof(prec->pp);
    prt->papFldDes[motorRecordMIP]->size = sizeof(prec->mip);
    prt->papFldDes[motorRecordMMAP]->size = sizeof(prec->mmap);
    prt->papFldDes[motorRecordNMAP]->size = sizeof(prec->nmap);
    prt->papFldDes[motorRecordDLY]->size = sizeof(prec->dly);
    prt->papFldDes[motorRecordCBAK]->size = sizeof(prec->cbak);
    prt->papFldDes[motorRecordPCOF]->size = sizeof(prec->pcof);
    prt->papFldDes[motorRecordICOF]->size = sizeof(prec->icof);
    prt->papFldDes[motorRecordDCOF]->size = sizeof(prec->dcof);
    prt->papFldDes[motorRecordCNEN]->size = sizeof(prec->cnen);
    prt->papFldDes[motorRecordINIT]->size = sizeof(prec->init);
    prt->papFldDes[motorRecordPREM]->size = sizeof(prec->prem);
    prt->papFldDes[motorRecordPOST]->size = sizeof(prec->post);
    prt->papFldDes[motorRecordSTOO]->size = sizeof(prec->stoo);
    prt->papFldDes[motorRecordDINP]->size = sizeof(prec->dinp);
    prt->papFldDes[motorRecordRINP]->size = sizeof(prec->rinp);
    prt->papFldDes[motorRecordJVEL]->size = sizeof(prec->jvel);
    prt->papFldDes[motorRecordJAR]->size = sizeof(prec->jar);
    prt->papFldDes[motorRecordLOCK]->size = sizeof(prec->lock);
    prt->papFldDes[motorRecordNTM]->size = sizeof(prec->ntm);
    prt->papFldDes[motorRecordNTMF]->size = sizeof(prec->ntmf);
    prt->papFldDes[motorRecordHVEL]->size = sizeof(prec->hvel);
    prt->papFldDes[motorRecordSTUP]->size = sizeof(prec->stup);
    prt->papFldDes[motorRecordRMOD]->size = sizeof(prec->rmod);
    prt->papFldDes[motorRecordADEL]->size = sizeof(prec->adel);
    prt->papFldDes[motorRecordMDEL]->size = sizeof(prec->mdel);
    prt->papFldDes[motorRecordALST]->size = sizeof(prec->alst);
    prt->papFldDes[motorRecordMLST]->size = sizeof(prec->mlst);
    prt->papFldDes[motorRecordSYNC]->size = sizeof(prec->sync);
    prt->papFldDes[motorRecordNAME]->offset = (char *)&prec->name - (char *)prec;
    prt->papFldDes[motorRecordDESC]->offset = (char *)&prec->desc - (char *)prec;
    prt->papFldDes[motorRecordASG]->offset = (char *)&prec->asg - (char *)prec;
    prt->papFldDes[motorRecordSCAN]->offset = (char *)&prec->scan - (char *)prec;
    prt->papFldDes[motorRecordPINI]->offset = (char *)&prec->pini - (char *)prec;
    prt->papFldDes[motorRecordPHAS]->offset = (char *)&prec->phas - (char *)prec;
    prt->papFldDes[motorRecordEVNT]->offset = (char *)&prec->evnt - (char *)prec;
    prt->papFldDes[motorRecordTSE]->offset = (char *)&prec->tse - (char *)prec;
    prt->papFldDes[motorRecordTSEL]->offset = (char *)&prec->tsel - (char *)prec;
    prt->papFldDes[motorRecordDTYP]->offset = (char *)&prec->dtyp - (char *)prec;
    prt->papFldDes[motorRecordDISV]->offset = (char *)&prec->disv - (char *)prec;
    prt->papFldDes[motorRecordDISA]->offset = (char *)&prec->disa - (char *)prec;
    prt->papFldDes[motorRecordSDIS]->offset = (char *)&prec->sdis - (char *)prec;
    prt->papFldDes[motorRecordMLOK]->offset = (char *)&prec->mlok - (char *)prec;
    prt->papFldDes[motorRecordMLIS]->offset = (char *)&prec->mlis - (char *)prec;
    prt->papFldDes[motorRecordDISP]->offset = (char *)&prec->disp - (char *)prec;
    prt->papFldDes[motorRecordPROC]->offset = (char *)&prec->proc - (char *)prec;
    prt->papFldDes[motorRecordSTAT]->offset = (char *)&prec->stat - (char *)prec;
    prt->papFldDes[motorRecordSEVR]->offset = (char *)&prec->sevr - (char *)prec;
    prt->papFldDes[motorRecordNSTA]->offset = (char *)&prec->nsta - (char *)prec;
    prt->papFldDes[motorRecordNSEV]->offset = (char *)&prec->nsev - (char *)prec;
    prt->papFldDes[motorRecordACKS]->offset = (char *)&prec->acks - (char *)prec;
    prt->papFldDes[motorRecordACKT]->offset = (char *)&prec->ackt - (char *)prec;
    prt->papFldDes[motorRecordDISS]->offset = (char *)&prec->diss - (char *)prec;
    prt->papFldDes[motorRecordLCNT]->offset = (char *)&prec->lcnt - (char *)prec;
    prt->papFldDes[motorRecordPACT]->offset = (char *)&prec->pact - (char *)prec;
    prt->papFldDes[motorRecordPUTF]->offset = (char *)&prec->putf - (char *)prec;
    prt->papFldDes[motorRecordRPRO]->offset = (char *)&prec->rpro - (char *)prec;
    prt->papFldDes[motorRecordASP]->offset = (char *)&prec->asp - (char *)prec;
    prt->papFldDes[motorRecordPPN]->offset = (char *)&prec->ppn - (char *)prec;
    prt->papFldDes[motorRecordPPNR]->offset = (char *)&prec->ppnr - (char *)prec;
    prt->papFldDes[motorRecordSPVT]->offset = (char *)&prec->spvt - (char *)prec;
    prt->papFldDes[motorRecordRSET]->offset = (char *)&prec->rset - (char *)prec;
    prt->papFldDes[motorRecordDSET]->offset = (char *)&prec->dset - (char *)prec;
    prt->papFldDes[motorRecordDPVT]->offset = (char *)&prec->dpvt - (char *)prec;
    prt->papFldDes[motorRecordRDES]->offset = (char *)&prec->rdes - (char *)prec;
    prt->papFldDes[motorRecordLSET]->offset = (char *)&prec->lset - (char *)prec;
    prt->papFldDes[motorRecordPRIO]->offset = (char *)&prec->prio - (char *)prec;
    prt->papFldDes[motorRecordTPRO]->offset = (char *)&prec->tpro - (char *)prec;
    prt->papFldDes[motorRecordBKPT]->offset = (char *)&prec->bkpt - (char *)prec;
    prt->papFldDes[motorRecordUDF]->offset = (char *)&prec->udf - (char *)prec;
    prt->papFldDes[motorRecordUDFS]->offset = (char *)&prec->udfs - (char *)prec;
    prt->papFldDes[motorRecordTIME]->offset = (char *)&prec->time - (char *)prec;
    prt->papFldDes[motorRecordFLNK]->offset = (char *)&prec->flnk - (char *)prec;
    prt->papFldDes[motorRecordVERS]->offset = (char *)&prec->vers - (char *)prec;
    prt->papFldDes[motorRecordOFF]->offset = (char *)&prec->off - (char *)prec;
    prt->papFldDes[motorRecordFOFF]->offset = (char *)&prec->foff - (char *)prec;
    prt->papFldDes[motorRecordFOF]->offset = (char *)&prec->fof - (char *)prec;
    prt->papFldDes[motorRecordVOF]->offset = (char *)&prec->vof - (char *)prec;
    prt->papFldDes[motorRecordDIR]->offset = (char *)&prec->dir - (char *)prec;
    prt->papFldDes[motorRecordSET]->offset = (char *)&prec->set - (char *)prec;
    prt->papFldDes[motorRecordSSET]->offset = (char *)&prec->sset - (char *)prec;
    prt->papFldDes[motorRecordSUSE]->offset = (char *)&prec->suse - (char *)prec;
    prt->papFldDes[motorRecordVELO]->offset = (char *)&prec->velo - (char *)prec;
    prt->papFldDes[motorRecordVBAS]->offset = (char *)&prec->vbas - (char *)prec;
    prt->papFldDes[motorRecordVMAX]->offset = (char *)&prec->vmax - (char *)prec;
    prt->papFldDes[motorRecordS]->offset = (char *)&prec->s - (char *)prec;
    prt->papFldDes[motorRecordSBAS]->offset = (char *)&prec->sbas - (char *)prec;
    prt->papFldDes[motorRecordSMAX]->offset = (char *)&prec->smax - (char *)prec;
    prt->papFldDes[motorRecordACCL]->offset = (char *)&prec->accl - (char *)prec;
    prt->papFldDes[motorRecordBDST]->offset = (char *)&prec->bdst - (char *)prec;
    prt->papFldDes[motorRecordBVEL]->offset = (char *)&prec->bvel - (char *)prec;
    prt->papFldDes[motorRecordSBAK]->offset = (char *)&prec->sbak - (char *)prec;
    prt->papFldDes[motorRecordBACC]->offset = (char *)&prec->bacc - (char *)prec;
    prt->papFldDes[motorRecordFRAC]->offset = (char *)&prec->frac - (char *)prec;
    prt->papFldDes[motorRecordOUT]->offset = (char *)&prec->out - (char *)prec;
    prt->papFldDes[motorRecordCARD]->offset = (char *)&prec->card - (char *)prec;
    prt->papFldDes[motorRecordRDBL]->offset = (char *)&prec->rdbl - (char *)prec;
    prt->papFldDes[motorRecordDOL]->offset = (char *)&prec->dol - (char *)prec;
    prt->papFldDes[motorRecordOMSL]->offset = (char *)&prec->omsl - (char *)prec;
    prt->papFldDes[motorRecordRLNK]->offset = (char *)&prec->rlnk - (char *)prec;
    prt->papFldDes[motorRecordSREV]->offset = (char *)&prec->srev - (char *)prec;
    prt->papFldDes[motorRecordUREV]->offset = (char *)&prec->urev - (char *)prec;
    prt->papFldDes[motorRecordMRES]->offset = (char *)&prec->mres - (char *)prec;
    prt->papFldDes[motorRecordERES]->offset = (char *)&prec->eres - (char *)prec;
    prt->papFldDes[motorRecordRRES]->offset = (char *)&prec->rres - (char *)prec;
    prt->papFldDes[motorRecordUEIP]->offset = (char *)&prec->ueip - (char *)prec;
    prt->papFldDes[motorRecordURIP]->offset = (char *)&prec->urip - (char *)prec;
    prt->papFldDes[motorRecordPREC]->offset = (char *)&prec->prec - (char *)prec;
    prt->papFldDes[motorRecordEGU]->offset = (char *)&prec->egu - (char *)prec;
    prt->papFldDes[motorRecordHLM]->offset = (char *)&prec->hlm - (char *)prec;
    prt->papFldDes[motorRecordLLM]->offset = (char *)&prec->llm - (char *)prec;
    prt->papFldDes[motorRecordDHLM]->offset = (char *)&prec->dhlm - (char *)prec;
    prt->papFldDes[motorRecordDLLM]->offset = (char *)&prec->dllm - (char *)prec;
    prt->papFldDes[motorRecordHOPR]->offset = (char *)&prec->hopr - (char *)prec;
    prt->papFldDes[motorRecordLOPR]->offset = (char *)&prec->lopr - (char *)prec;
    prt->papFldDes[motorRecordHLS]->offset = (char *)&prec->hls - (char *)prec;
    prt->papFldDes[motorRecordLLS]->offset = (char *)&prec->lls - (char *)prec;
    prt->papFldDes[motorRecordRHLS]->offset = (char *)&prec->rhls - (char *)prec;
    prt->papFldDes[motorRecordRLLS]->offset = (char *)&prec->rlls - (char *)prec;
    prt->papFldDes[motorRecordHIHI]->offset = (char *)&prec->hihi - (char *)prec;
    prt->papFldDes[motorRecordLOLO]->offset = (char *)&prec->lolo - (char *)prec;
    prt->papFldDes[motorRecordHIGH]->offset = (char *)&prec->high - (char *)prec;
    prt->papFldDes[motorRecordLOW]->offset = (char *)&prec->low - (char *)prec;
    prt->papFldDes[motorRecordHHSV]->offset = (char *)&prec->hhsv - (char *)prec;
    prt->papFldDes[motorRecordLLSV]->offset = (char *)&prec->llsv - (char *)prec;
    prt->papFldDes[motorRecordHSV]->offset = (char *)&prec->hsv - (char *)prec;
    prt->papFldDes[motorRecordLSV]->offset = (char *)&prec->lsv - (char *)prec;
    prt->papFldDes[motorRecordHLSV]->offset = (char *)&prec->hlsv - (char *)prec;
    prt->papFldDes[motorRecordRDBD]->offset = (char *)&prec->rdbd - (char *)prec;
    prt->papFldDes[motorRecordRCNT]->offset = (char *)&prec->rcnt - (char *)prec;
    prt->papFldDes[motorRecordRTRY]->offset = (char *)&prec->rtry - (char *)prec;
    prt->papFldDes[motorRecordMISS]->offset = (char *)&prec->miss - (char *)prec;
    prt->papFldDes[motorRecordSPMG]->offset = (char *)&prec->spmg - (char *)prec;
    prt->papFldDes[motorRecordLSPG]->offset = (char *)&prec->lspg - (char *)prec;
    prt->papFldDes[motorRecordSTOP]->offset = (char *)&prec->stop - (char *)prec;
    prt->papFldDes[motorRecordHOMF]->offset = (char *)&prec->homf - (char *)prec;
    prt->papFldDes[motorRecordHOMR]->offset = (char *)&prec->homr - (char *)prec;
    prt->papFldDes[motorRecordJOGF]->offset = (char *)&prec->jogf - (char *)prec;
    prt->papFldDes[motorRecordJOGR]->offset = (char *)&prec->jogr - (char *)prec;
    prt->papFldDes[motorRecordTWF]->offset = (char *)&prec->twf - (char *)prec;
    prt->papFldDes[motorRecordTWR]->offset = (char *)&prec->twr - (char *)prec;
    prt->papFldDes[motorRecordTWV]->offset = (char *)&prec->twv - (char *)prec;
    prt->papFldDes[motorRecordVAL]->offset = (char *)&prec->val - (char *)prec;
    prt->papFldDes[motorRecordLVAL]->offset = (char *)&prec->lval - (char *)prec;
    prt->papFldDes[motorRecordDVAL]->offset = (char *)&prec->dval - (char *)prec;
    prt->papFldDes[motorRecordLDVL]->offset = (char *)&prec->ldvl - (char *)prec;
    prt->papFldDes[motorRecordRVAL]->offset = (char *)&prec->rval - (char *)prec;
    prt->papFldDes[motorRecordLRVL]->offset = (char *)&prec->lrvl - (char *)prec;
    prt->papFldDes[motorRecordRLV]->offset = (char *)&prec->rlv - (char *)prec;
    prt->papFldDes[motorRecordLRLV]->offset = (char *)&prec->lrlv - (char *)prec;
    prt->papFldDes[motorRecordRBV]->offset = (char *)&prec->rbv - (char *)prec;
    prt->papFldDes[motorRecordDRBV]->offset = (char *)&prec->drbv - (char *)prec;
    prt->papFldDes[motorRecordDIFF]->offset = (char *)&prec->diff - (char *)prec;
    prt->papFldDes[motorRecordRDIF]->offset = (char *)&prec->rdif - (char *)prec;
    prt->papFldDes[motorRecordCDIR]->offset = (char *)&prec->cdir - (char *)prec;
    prt->papFldDes[motorRecordRRBV]->offset = (char *)&prec->rrbv - (char *)prec;
    prt->papFldDes[motorRecordRMP]->offset = (char *)&prec->rmp - (char *)prec;
    prt->papFldDes[motorRecordREP]->offset = (char *)&prec->rep - (char *)prec;
    prt->papFldDes[motorRecordRVEL]->offset = (char *)&prec->rvel - (char *)prec;
    prt->papFldDes[motorRecordDMOV]->offset = (char *)&prec->dmov - (char *)prec;
    prt->papFldDes[motorRecordMOVN]->offset = (char *)&prec->movn - (char *)prec;
    prt->papFldDes[motorRecordMSTA]->offset = (char *)&prec->msta - (char *)prec;
    prt->papFldDes[motorRecordLVIO]->offset = (char *)&prec->lvio - (char *)prec;
    prt->papFldDes[motorRecordTDIR]->offset = (char *)&prec->tdir - (char *)prec;
    prt->papFldDes[motorRecordATHM]->offset = (char *)&prec->athm - (char *)prec;
    prt->papFldDes[motorRecordPP]->offset = (char *)&prec->pp - (char *)prec;
    prt->papFldDes[motorRecordMIP]->offset = (char *)&prec->mip - (char *)prec;
    prt->papFldDes[motorRecordMMAP]->offset = (char *)&prec->mmap - (char *)prec;
    prt->papFldDes[motorRecordNMAP]->offset = (char *)&prec->nmap - (char *)prec;
    prt->papFldDes[motorRecordDLY]->offset = (char *)&prec->dly - (char *)prec;
    prt->papFldDes[motorRecordCBAK]->offset = (char *)&prec->cbak - (char *)prec;
    prt->papFldDes[motorRecordPCOF]->offset = (char *)&prec->pcof - (char *)prec;
    prt->papFldDes[motorRecordICOF]->offset = (char *)&prec->icof - (char *)prec;
    prt->papFldDes[motorRecordDCOF]->offset = (char *)&prec->dcof - (char *)prec;
    prt->papFldDes[motorRecordCNEN]->offset = (char *)&prec->cnen - (char *)prec;
    prt->papFldDes[motorRecordINIT]->offset = (char *)&prec->init - (char *)prec;
    prt->papFldDes[motorRecordPREM]->offset = (char *)&prec->prem - (char *)prec;
    prt->papFldDes[motorRecordPOST]->offset = (char *)&prec->post - (char *)prec;
    prt->papFldDes[motorRecordSTOO]->offset = (char *)&prec->stoo - (char *)prec;
    prt->papFldDes[motorRecordDINP]->offset = (char *)&prec->dinp - (char *)prec;
    prt->papFldDes[motorRecordRINP]->offset = (char *)&prec->rinp - (char *)prec;
    prt->papFldDes[motorRecordJVEL]->offset = (char *)&prec->jvel - (char *)prec;
    prt->papFldDes[motorRecordJAR]->offset = (char *)&prec->jar - (char *)prec;
    prt->papFldDes[motorRecordLOCK]->offset = (char *)&prec->lock - (char *)prec;
    prt->papFldDes[motorRecordNTM]->offset = (char *)&prec->ntm - (char *)prec;
    prt->papFldDes[motorRecordNTMF]->offset = (char *)&prec->ntmf - (char *)prec;
    prt->papFldDes[motorRecordHVEL]->offset = (char *)&prec->hvel - (char *)prec;
    prt->papFldDes[motorRecordSTUP]->offset = (char *)&prec->stup - (char *)prec;
    prt->papFldDes[motorRecordRMOD]->offset = (char *)&prec->rmod - (char *)prec;
    prt->papFldDes[motorRecordADEL]->offset = (char *)&prec->adel - (char *)prec;
    prt->papFldDes[motorRecordMDEL]->offset = (char *)&prec->mdel - (char *)prec;
    prt->papFldDes[motorRecordALST]->offset = (char *)&prec->alst - (char *)prec;
    prt->papFldDes[motorRecordMLST]->offset = (char *)&prec->mlst - (char *)prec;
    prt->papFldDes[motorRecordSYNC]->offset = (char *)&prec->sync - (char *)prec;
    prt->rec_size = sizeof(*prec);
    return 0;
}
epicsExportRegistrar(motorRecordSizeOffset);

#ifdef __cplusplus
}
#endif
#endif /* GEN_SIZE_OFFSET */

#endif /* INC_motorRecord_H */
