/*************************************************************************\
Copyright (c) 2010-2011 Helmholtz-Zentrum Berlin f. Materialien
                        und Energie GmbH, Germany (HZB)
This file is distributed subject to a Software License Agreement found
in the file LICENSE that is included with this distribution.
\*************************************************************************/
#ifndef INCtestSupport_h
#define INCtestSupport_h

#include "epicsThread.h"
#include "epicsMutex.h"
#include "epicsUnitTest.h"

void run_seq_test(seqProgram *seqProg);
void seq_test_done(void);

#endif /* INCtestSupport_h */
