#!/bin/bash
#
#  This sets EPICS variables
#
EPICS_TOP=/opt/epics

export EPICS_BASE=$EPICS_TOP/base
export EPICS_HOST_ARCH=$($EPICS_TOP/base/startup/EpicsHostArch)
export EPICS_EXTENSIONS=$EPICS_TOP/extensions
export EPICS_CA_MAX_ARRAY_BYTES=60000

export PATH=$PATH:$EPICS_BASE/bin/$EPICS_HOST_ARCH:$EPICS_EXTENSIONS/bin/$EPICS_HOST_ARCH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$EPICS_BASE/lib/$EPICS_HOST_ARCH:$EPICS_EXTENSIONS/lib/$EPICS_HOST_ARCH

if [[ $HOSTNAME = "slowcontrol" ]]; then
    export EPICS_CA_AUTO_ADDR_LIST=NO;
    export EPICS_CA_ADDR_LIST="10.32.168.67";
fi
