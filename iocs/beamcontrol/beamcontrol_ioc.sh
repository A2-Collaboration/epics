#/bin/bash -e


. /opt/epics/thisEPICS.sh

cd /opt/epics/iocs/beamcontrol/
screen -dm -S beam-data -c screenrc

echo "Screen session with name beam-data started."
