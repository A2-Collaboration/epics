#!/bin/sh
#source the epics env to get the pathe to caget etc.
#. /opt/epics/thisEPICS.sh

if [ $# -ne "1" ]; then
    echo "Error $0 needs need arg for P macro";
    echo "Eg. $0 SIM:CBREM:";
    exit;
fi

P=$1;

scalers=`caget -t "${P}ENH_SCALERS"`;
edge=`caget -t "${P}EDGE_LINE_MAP"`;
#echo "${P}ENH_REF" "${scalers}";
caput -a "${P}ENH_REF" ${scalers};
caput -a "${P}REQ_EDGE_LINE_MAP" ${edge};
echo "${scalers}" > ${HOME}/cbrem/data/enhRef.dat;
echo "${edge}" > ${HOME}/cbrem/data/enhRefLine.dat;
