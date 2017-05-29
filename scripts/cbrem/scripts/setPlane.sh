#!/bin/sh
#Script to set the coherent peak to para (1) or perp (2)
#
#source the epics env to get the pathe to caget etc.
. /opt/epics/thisEPICS.sh

if [ $# -ne "3" ]; then
    echo
    echo "Usage: $0 <P> <G> <plane>"   
    echo "       P and G are the EPICS macros for goni and cbrem. Eg. HD:CBREM: HD:GONI:";
    echo "       <plane> = PARA or PERP"
fi

P=$1;
G=$2;
plane=$3;


if [ $plane = "PARA" ] || [ $plane = "PERP" ]; then
    pitch=`caget -t ${P}${plane}_PITCH`
    yaw=`caget -t ${P}${plane}_YAW`

    #call the function to move on pitch and yaw
    warning="This will put the crystal in the ${plane} setting by going to:\n YAW = $yaw, and PITCH = $pitch \nARE YOU SURE YOU WANT TO DO THIS?";
    if ! zenity --title="Adjust coherent bremsstrahlung conditions" --question --text "$warning" --width 650 --height 100; then
	exit;
    fi

    caput "${G}PITCH" $pitch;
    caput "${G}YAW" $yaw;


    exit;

fi

echo "ERROR plane \"${plane}\" not known";
exit;