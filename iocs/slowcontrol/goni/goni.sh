#!/bin/bash -e
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
exec /opt/epics/modules/synApps_5_6/support/motor-6-7/bin/linux-x86_64/WithAsyn goni.ioc
