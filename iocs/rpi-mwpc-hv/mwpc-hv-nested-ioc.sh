#!/bin/bash -e

. /opt/epics/thisEPICS.sh

cd $EPICS_BASE/../iocs/rpi-mwpc-hv/

screen -dm -S MWPC -c screenrc
