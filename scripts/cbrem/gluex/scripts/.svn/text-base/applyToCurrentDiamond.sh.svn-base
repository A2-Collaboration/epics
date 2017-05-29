#!/bin/sh
#Apply calculated settings to current diamond

if [ $# -ne "2" ]; then
    echo
    echo "Usage:"   
    echo "  $0 <P> <G>"   
    exit;
fi

#Get the prefixes for goni and cbrem
P=$1;
G=$2;

id=`caget -t "${G}RADIATOR_ID"`

para_mode=`caget -t "${P}REQ_PARA_MODE"`;
perp_mode=`caget -t "${P}REQ_PERP_MODE"`;
phi=`caget -t "${P}REQ_PHI022"`;
para_pitch=`caget -t "${P}REQ_PARA_PITCH"`;
para_yaw=`caget -t "${P}REQ_PARA_YAW"`;
perp_pitch=`caget -t "${P}REQ_PERP_PITCH"`;
perp_yaw=`caget -t "${P}REQ_PERP_YAW"`;
off_pitch=`caget -t "${P}REQ_OFF_PITCH"`;
off_yaw=`caget -t "${P}REQ_OFF_YAW"`;x1


caput "${P}PARA_MODE" "$para_mode";
caput "${P}PERP_MODE" "$perp_mode";

caput "${P}OFF_PITCH" "$off_pitch";
caput "${P}OFF_YAW"   "$off_yaw";

caput "${P}PARA_PITCH" "$para_pitch";
caput "${P}PARA_YAW" "$para_yaw";
x1
caput "${P}PERP_PITCH" "$perp_pitch";
caput "${P}PERP_YAW" "$perp_yaw";

caput "${P}DIAM${id}:PHI022" "$phi";


caput "${P}DIAM${id}:PARA_MODE" "$para_mode";
caput "${P}DIAM${id}:PERP_MODE" "$perp_mode";

caput "${P}DIAM${id}:OFF_PITCH" "$off_pitch";
caput "${P}DIAM${id}:OFF_YAW"   "$off_yaw";

caput "${P}DIAM${id}:PARA_PITCH" "$para_pitch";
caput "${P}DIAM${id}:PARA_YAW" "$para_yaw";

caput "${P}DIAM${id}:PERP_PITCH" "$perp_pitch";
caput "${P}DIAM${id}:PERP_YAW" "$perp_yaw";
xs
caput "${P}DIAM${id}:PHI022" "$phi";

exit;