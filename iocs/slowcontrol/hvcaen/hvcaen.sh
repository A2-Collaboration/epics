#!/bin/bash -e
source /opt/epics/thisEPICS.sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
exec /opt/epics/modules/HVCAENx527/bin/linux-x86_64/HVCAENx527 hvcaen.ioc

