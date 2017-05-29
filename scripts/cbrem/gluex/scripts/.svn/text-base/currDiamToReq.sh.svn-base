#!/bin/sh

#source the epics env to get the path to caget etc.
#. /opt/epics/thisEPICS.sh

if [ $# -ne "1" ]; then
    echo "Error $0 needs need args for P and G macros";
    echo "Eg. $0 SIM:CBREM: SIM:GONI:";
    exit;
fi

P=$1;

#check that the CBREM is up and running
id=`caget -t ${P}ID |& awk '{if($0~"timed out")print 0; else print $0}'`

if [ $id -gt "0" ]; then
    para_mode=`caget -t "${P}PARA_MODE"`;
    perp_mode=`caget -t "${P}PERP_MODE"`;
    phi=`caget -t "${P}PHI022"`;
    para_pitch=`caget -t "${P}PARA_PITCH"`;
    para_yaw=`caget -t "${P}PARA_YAW"`;
    perp_pitch=`caget -t "${P}PERP_PITCH"`;
    perp_yaw=`caget -t "${P}PERP_YAW"`;
    off_pitch=`caget -t "${P}OFF_PITCH"`;
    off_yaw=`caget -t "${P}OFF_YAW"`;

    caput "${P}REQ_PARA_MODE" "$para_mode";
    caput "${P}REQ_PERP_MODE" "$perp_mode";

    caput "${P}REQ_OFF_PITCH" "$off_pitch";
    caput "${P}REQ_OFF_YAW"   "$off_yaw";
    
    caput "${P}REQ_PARA_PITCH" "$para_pitch";
    caput "${P}REQ_PARA_YAW" "$para_yaw";
    
    caput "${P}REQ_PERP_PITCH" "$para_pitch";
    caput "${P}REQ_PERP_YAW" "$para_yaw";
    
    caput "${P}REQ_PHI022" "$phi";

fi


exit;