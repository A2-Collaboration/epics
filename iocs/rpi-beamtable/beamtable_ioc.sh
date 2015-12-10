#!/bin/bash -e

. /opt/epics/thisEPICS.sh

cd /opt/epics/iocs/rpi-beamtable

screen -dm -S beamtable-ioc -c screenrc

echo "Screen session with name beamtable-ioc started."
