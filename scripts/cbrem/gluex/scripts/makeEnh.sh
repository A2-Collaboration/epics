#!/bin/sh

#prepend the 64 bit versions of the epics library for root
export LD_LIBRARY_PATH="${EPICS_BASE}/lib/linux-x86_64:${EPICS_EXTENSIONS}/lib/linux-x86_64:${LD_LIBRARY_PATH}"

#kill if there's already one running
process=`ps x | grep makeEnh | grep xterm | awk '{print $1}'`
if [ -n "$process" ]; then
    echo $process;
    kill -9 $process;
fi

if [ $1 != "stop" ]; then
   xterm -e "root -l ~/cbrem/scripts/makeEnh.C"
fi

exit 0;
