#/bin/bash -e
. /opt/epics/thisEPICS.sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
screen -dm -S EPTHallProbe -c screenrc
echo "Screen session with name EPTHallProbe started."
