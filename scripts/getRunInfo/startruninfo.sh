#/bin/bash

. /opt/epics/thisEPICS.sh
export PYEPICS_LIBCA=$EPICS_BASE/lib/$EPICS_HOST_ARCH/libca.so
cd $EPICS_TOP/scripts/getRunInfo/
exec /usr/bin/python getRunInfo.py
