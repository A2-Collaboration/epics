#!/bin/bash
source ~/root-build/bin/thisroot.sh
source /opt/epics/thisEPICS.sh

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
