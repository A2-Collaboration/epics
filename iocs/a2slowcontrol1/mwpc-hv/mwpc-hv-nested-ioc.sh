#!/bin/bash -e

. /opt/epics/thisEPICS.sh

cd $EPICS_BASE/../iocs/a2slowcontrol1/mwpc-hv/

screen -dm -S MWPC -c screenrc
