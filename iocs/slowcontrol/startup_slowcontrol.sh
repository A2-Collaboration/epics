#/bin/bash

set -e # fail on error
. /opt/epics/thisEPICS.sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
screen -dm -S EPICS -c screenrc || echo "Error launching screen"
