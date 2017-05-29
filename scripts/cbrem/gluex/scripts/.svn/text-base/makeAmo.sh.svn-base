#!/bin/sh

#source the epics env to get the pathe to caget etc.
#. /opt/epics/thisEPICS.sh


if [ $# -ne "1" ]; then
    echo "Error $0 needs need arg for P macro";
    echo "Eg. $0 SIM:CBREM:";
    exit;
fi

P=$1;

#
scalers=`caget -t "${P}RAW_SCALERS"`;
caput -a "${P}AMO_SCALERS" ${scalers};
echo "${scalers}" > ${HOME}/cbrem/data/amo.dat;
