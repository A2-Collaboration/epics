#!/bin/sh
#prepend the 64 bit versions of the epics library for root 
export LD_LIBRARY_PATH="${EPICS_BASE}/lib/linux-x86_64:${EPICS_EXTENSIONS}/lib/linux-x86_64:${LD_LIBRARY_PATH}"
xterm -e "root -l  makeEnh.C" & 

