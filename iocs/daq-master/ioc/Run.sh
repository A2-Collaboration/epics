#!/bin/bash
mkdir -p /tmp/ioc
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
softIoc -d general.db -d MWPC.db -d CB.db -d Scratch.db -d NMR.db -d PairSpec.db -d Target.db -d beamcontrol.db -d APPT.db dump.cmd
