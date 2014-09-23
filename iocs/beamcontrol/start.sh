#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
/opt/epics/base/bin/linux-x86_64/softIoc -d beamcontrol.db
