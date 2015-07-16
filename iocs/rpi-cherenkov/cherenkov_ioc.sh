#!/bin/bash -e

. /opt/epics/thisEPICS.sh

cd /opt/epics/iocs/rpi-cherenkov/

screen -dm -S cherenkov-ioc -c screenrc

echo "Screen session with name cherenkov-ioc started."
