/*************************************************************************\
Copyright (c) 2010-2011 Helmholtz-Zentrum Berlin f. Materialien
                        und Energie GmbH, Germany (HZB)
This file is distributed subject to a Software License Agreement found
in the file LICENSE that is included with this distribution.
\*************************************************************************/
program p

int x;
evflag f;
sync x to f; /* error: not assigned */

#include "simple.st"
