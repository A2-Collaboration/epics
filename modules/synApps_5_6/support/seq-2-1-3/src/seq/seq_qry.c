/*************************************************************************\
Copyright (c) 1990-1994 The Regents of the University of California
                        and the University of Chicago.
                        Los Alamos National Laboratory
Copyright (c) 2010-2011 Helmholtz-Zentrum Berlin f. Materialien
                        und Energie GmbH, Germany (HZB)
This file is distributed subject to a Software License Agreement found
in the file LICENSE that is included with this distribution.
\*************************************************************************/
/*************************************************************************\
        Task query & debug routines for run-time sequencer
\*************************************************************************/
#include "seq.h"

static int userInput(void);
static void printValue(pr_fun *pr, void *val, unsigned count, int type);
static SSCB *seqQryFind(epicsThreadId tid);
static void seqShowAll(void);

void print_channel_value(pr_fun *pr, CHAN *ch, void *val)
{
	printValue(pr, val, ch->count, ch->type->putType);
}

/*
 * seqShow() - Query the sequencer for state information.
 * If a non-zero thread id is specified then print the information about
 * the state program, otherwise print a brief summary of all state programs
 */
epicsShareFunc void epicsShareAPI seqShow(epicsThreadId tid)
{
	SSCB	*ss = seqQryFind(tid);
	SPROG	*sp;
	STATE	*st;
	unsigned nss;
	double	timeNow, timeElapsed;

	if (ss == NULL) return;
	sp = ss->sprog;

	/* Print info about state program */
	printf("State Program: \"%s\"\n", sp->progName);
	printf("  thread priority = %d\n", sp->threadPriority);
	printf("  number of state sets = %d\n", sp->numSS);
	printf("  number of syncQ queues = %d\n", sp->numQueues);
	if (sp->numQueues > 0)
		printf("  queue array address = %p\n",sp->queues);
	printf("  number of channels = %d\n", sp->numChans);
	/* Note: need not take programLock since read-ony */
	printf("  number of channels assigned = %d\n", sp->assignCount);
	printf("  number of channels connected = %d\n", sp->connectCount);
	printf("  number of channels monitored = %d\n", sp->monitorCount);
	printf("  options: async=%d, debug=%d, newef=%d, reent=%d, conn=%d, "
		"main=%d\n",
		(sp->options & OPT_ASYNC) != 0, (sp->options & OPT_DEBUG) != 0,
		(sp->options & OPT_NEWEF) != 0, (sp->options & OPT_REENT) != 0,
		(sp->options & OPT_CONN)  != 0, (sp->options & OPT_MAIN)  != 0);
	if (sp->options & OPT_REENT)
		printf("  user variables: address = %p, length = %u\n",
			sp->var, (unsigned)sp->varSize);
	printf("\n");

	/* Print state set info */
	for (nss = 0; nss < sp->numSS; nss++)
	{
		unsigned n;
		SSCB	*ss = sp->ss + nss;

		printf("  State Set: \"%s\"\n", ss->ssName);

		if (ss->threadId != (epicsThreadId)0)
		{
			char threadName[THREAD_NAME_SIZE];
			epicsThreadGetName(ss->threadId, threadName,sizeof(threadName));
			printf("  thread name = %s;", threadName);
		}

		printf("  Thread id = %p\n", ss->threadId);

		st = ss->states;
		printf("  First state = \"%s\"\n", st->stateName);

		st = ss->states + ss->currentState;
		printf("  Current state = \"%s\"\n", st->stateName);

		st = ss->states + ss->prevState;
		printf("  Previous state = \"%s\"\n", ss->prevState >= 0 ?
			st->stateName : "");

		pvTimeGetCurrentDouble(&timeNow);
		timeElapsed = timeNow - ss->timeEntered;
		printf("  Elapsed time since state was entered = %.1f "
			"seconds\n", timeElapsed);

		printf("  Get in progress = [");
		for (n = 0; n < sp->numChans; n++)
			if ((sp->options & OPT_SAFE) || seq_pvAssigned(ss, n))
				printf("%d",!seq_pvGetComplete(ss, n));
		printf("]\n");

		printf("  Put in progress = [");
		for (n = 0; n < sp->numChans; n++)
			if ((sp->options & OPT_SAFE) || seq_pvAssigned(ss, n))
				printf("%d",!seq_pvPutComplete(ss, n, 0, 0, 0));
		printf("]\n");

		printf("  Queued time delays:\n");
		for (n = 0; n < ss->numDelays; n++)
		{
			printf("\tdelay[%d]=%f", n, ss->delay[n]);
			if (ss->delayExpired[n])
				printf(" - expired");
			printf("\n");
		}

		if (sp->options & OPT_SAFE)
			printf("  User variables: address = %p, length = %u\n",
				sp->var, (unsigned)sp->varSize);
		printf("\n");
	}
}

/*
 * seqChanShow() - Show channel information for a state program.
 */
epicsShareFunc void epicsShareAPI seqChanShow(epicsThreadId tid, const char *str)
{
	SSCB	*ss = seqQryFind(tid);
	SPROG	*sp;
	int	nch = 0;
	int	dn = 1;
	char	connQual;
	int	match, showAll;

	if (ss == NULL) return;
	sp = ss->sprog;

	printf("State Program: \"%s\"\n", sp->progName);
	printf("Number of channels=%d\n", sp->numChans);
	printf("View: State set %s\n", ss->ssName);

	if (str != NULL)
	{
		connQual = str[0];
		/* Check for channel connect qualifier */
		if ((connQual == '+') || (connQual == '-'))
		{
			str += 1;
		}
	}
	else
		connQual = 0;

	while (dn && (unsigned)nch < sp->numChans)
	{
		CHAN *ch = sp->chan + nch;
		DBCHAN *dbch = ch->dbch;

		if (str != NULL)
		{
			/* Check for channel connect qualifier */
			if (connQual == '+')
				showAll = dbch && dbch->connected;
			else if (connQual == '-')
				showAll = dbch && (!dbch->connected);
			else
				showAll = TRUE;

			/* Check for pattern match if specified */
			match = (str[0] == 0) ||
					(dbch && strstr(dbch->dbName, str) != NULL);
			if (!(match && showAll))
			{
				ch += 1;
				nch += 1;
				continue; /* skip this channel */
			}
		}
		printf("\n#%d of %d:\n", nch+1, sp->numChans);
		printf("  Variable name: \"%s\"\n", ch->varName);
		printf("    type = %s\n", ch->type->typeStr);
		printf("    count = %u\n", ch->count);
		printf("  Value =");
		printValue(printf, valPtr(ch,ss), ch->count, ch->type->putType);

		if (dbch)
			printf("  Assigned to \"%s\"\n", dbch->dbName);
		else
			printf("  Anonymous\n");

		if(dbch && dbch->connected)
			printf("  Connected\n");
		else
			printf("  Not connected\n");

		if (ch->monitored)
			printf("  Monitored\n");
		else
			printf("  Not monitored\n");

		if (ch->efId)
			printf("  Sync'ed to event flag %u\n", ch->efId);
		else
			printf("  Not sync'ed\n");

		if (dbch)
		{
			PVMETA	*meta = metaPtr(ch,ss);
			char	timeFormatStr[30] = "%Y-%m-%d %H:%M:%S.%06f";
			char	tsBfr[28];

			printf("  Status = %d\n", meta->status);
			printf("  Severity = %d\n", meta->severity);
			printf("  Message = %s\n", meta->message != NULL ?
				meta->message : "");

			/* Print time stamp in text format: "yyyy/mm/dd hh:mm:ss.sss" */
			epicsTimeToStrftime(tsBfr, sizeof(tsBfr),
				timeFormatStr, &meta->timeStamp);
			printf("  Time stamp = %s\n", tsBfr);
		}

		dn = userInput();
		nch = max(0, nch + dn);
		assert(nch >= 0);
	}
}
/*
 * seqcar() - Sequencer Channel Access Report
 */

struct seqStats
{
	int	level;
	int	nProgs;
	int	nChans;
	int	nConn;
};

static int seqcarCollect(SPROG *sp, void *param)
{
	struct seqStats	*pstats = (struct seqStats *) param;
	unsigned	nch;
	int		level = pstats->level;
	int 		printedProgName = 0;

	pstats->nProgs++;
	for (nch = 0; nch < sp->numChans; nch++)
	{
		CHAN *ch = sp->chan + nch;
		DBCHAN *dbch = ch->dbch;

		if (dbch) pstats->nChans++;
		if (dbch && dbch->connected) pstats->nConn++;
		if (level > 1 ||
			(level == 1 && dbch && !dbch->connected))
		{
			if (!printedProgName)
			{
				printf("  Program \"%s\"\n", sp->progName);
				printedProgName = 1;
			}
			if (dbch)
				printf("    Variable \"%s\" %sconnected to PV \"%s\"\n",
					ch->varName,
					dbch->connected ? "" : "not ",
					dbch->dbName);
			else
				printf("    Variable \"%s\" not assigned to PV\n",
					ch->varName);
		}
	}
	return FALSE;	/* continue traversal */
}

epicsShareFunc void epicsShareAPI seqcar(int level)
{
	struct seqStats	stats = {0, 0, 0, 0};

	stats.level = level;
	seqTraverseProg(seqcarCollect, (void *) &stats);
	printf("Total programs=%d, channels=%d, connected=%d, disconnected=%d\n",
		stats.nProgs, stats.nChans, stats.nConn,
		stats.nChans - stats.nConn);
}

#if 0
epicsShareFunc void epicsShareAPI seqcaStats(int *pchans, int *pdiscon)
{
	struct seqStats stats = {0, 0, 0, 0};
	seqTraverseProg(seqcarCollect, (void *) &stats);
	if (pchans)  *pchans  = stats.nChans;
	if (pdiscon) *pdiscon = stats.nChans - stats.nConn;
}
#endif

/*
 * seqQueueShow() - Show syncQ queue information for a state program.
 */
epicsShareFunc void epicsShareAPI seqQueueShow(epicsThreadId tid)
{
	SSCB	*ss = seqQryFind(tid);
	SPROG	*sp;
	int	n = 0;
	int	dn = 1;

	if (ss == NULL) return;
	sp = ss->sprog;
	printf("State Program: \"%s\"\n", sp->progName);
	printf("Number of queues = %d\n", sp->numQueues);
	while (dn && (unsigned)n < sp->numQueues)
	{
		QUEUE	queue = sp->queues[n];

		printf("  Queue #%d: numElems=%u, used=%u, elemSize=%u\n", n,
			(unsigned)seqQueueNumElems(queue),
			(unsigned)seqQueueUsed(queue),
			(unsigned)seqQueueElemSize(queue));
		dn = userInput();
		n = max(0, n + dn);
		assert(n >= 0);
	}
}

/* Read from console until a RETURN is detected.
   The return value <n> value means:
   n == 0: quit
   n > 0 : move forward n items
   n < 0 : move backward n items
*/
static int userInput(void)
{
	char	buffer[10];
	int	n;

	printf("Next? (+/- skip count)\n");
	if (fgets(buffer, 10, stdin) == NULL)
		return 0;
	if (buffer[0] == 'q')
		return 0; /* quit */

	n = atoi(buffer);
	if (n == 0)
		n = 1;
	return n;
}

/* Print the current internal value of a database channel */
static void printValue(pr_fun *pr, void *val, unsigned count, int type)
{
	char	*c = (char *)val;
	short	*s = (short *)val;
	long	*l = (long *)val;
	float	*f = (float *)val;
	double	*d = (double *)val;
	typedef char string[MAX_STRING_SIZE];
	string	*t = (string *)val;

	while (count--)
	{
		switch (type)
		{
		case pvTypeSTRING:
			pr(" \"%.*s\"", MAX_STRING_SIZE, *t++);
			break;
		case pvTypeCHAR:
			pr(" %d", *c++);
			break;
		case pvTypeSHORT:
			pr(" %d", *s++);
			break;
		case pvTypeLONG:
			pr(" %ld", *l++);
			break;
		case pvTypeFLOAT:
			pr(" %g", *f++);
			break;
		case pvTypeDOUBLE:
			pr(" %g", *d++);
			break;
		}
	}
	pr("\n");
}

/* Find a state program associated with a given thread id */
static SSCB *seqQryFind(epicsThreadId tid)
{
	SSCB *ss;

	ss = seqFindStateSet(tid);
	if (ss == NULL)
	{
		if (tid)
			printf("No program instance is running thread %p.\n", tid);
		seqShowAll();
	}
	return ss;
}

/* This routine is called by seqTraverseProg() for seqShowAll() */
static int seqShowSP(SPROG *sp, void *parg)
{
	unsigned	nss;
	const char	*progName;
	char		threadName[THREAD_NAME_SIZE];
	int		*pprogCount = (int *)parg;

	if ((*pprogCount)++ == 0)
		printf("Program Name     Thread ID  Thread Name      SS Name\n");
		printf("------------     ---------  -----------      -------\n");
	progName = sp->progName;
	for (nss = 0; nss < sp->numSS; nss++)
	{
		SSCB *ss = sp->ss + nss;

		if (ss->threadId == 0)
			strcpy(threadName,"(no thread)");
		else
			epicsThreadGetName(ss->threadId, threadName,
				      sizeof(threadName));
		printf("%-16s %-8p  %-16s %-16s\n", progName,
			ss->threadId, threadName, ss->ssName );
		progName = "";
	}
	return FALSE;	/* continue traversal */
}

/* Print a brief summary of all state programs */
static void seqShowAll(void)
{
	int progCount = 0;

	seqTraverseProg(seqShowSP, &progCount);
	if (progCount == 0)
		printf("No active state programs\n");
}
