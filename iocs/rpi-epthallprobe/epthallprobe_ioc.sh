#/bin/bash -e

. /opt/epics/thisEPICS.sh

cd $EPICS_TOP/iocs/epthallprobe/
screen -dm -S EPTHallProbe -c screenrc

echo "Screen session with name EPTHallProbe started."
