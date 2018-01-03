#!/bin/bash -e
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
exec /opt/epics/modules/streamdevice/bin/$EPICS_HOST_ARCH/streamApp cb-hv12.ioc
