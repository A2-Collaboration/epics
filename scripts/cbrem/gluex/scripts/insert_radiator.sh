#!/bin/sh

P="HD:GONI:"
fullpath="/home/a2cb/EPICS/CountingRoom_CSS/Goni"

#source the epics env to get the pathe to caget etc.
#. /opt/epics/thisEPICS.sh

usage()
{
    echo 
    echo "$0 <index>    installs the radiator of the given index"
    echo "$0 -h         print this message"
    echo
    echo "The goniometer and radiators are controlled by EPICS - see the Slow Controls page on the Glue wiki at"
    echo "https://halldweb1.jlab.org/wiki/index.php/Slow_controls"
    echo
    echo "Here's the information on the currently available radiators"
    echo "from running this command: ${fullpath}/get_goni_info.sh"
    echo
    "${fullpath}/get_goni_info.sh"
    echo
    echo "If there were errors check that the GONI EPICS ioc is running".
}

wait_stop()
{
moving="1"
axis="${1}.MOVN"

while [ ${moving} -gt 0 ]
do
#    echo $moving
    sleep 1
    moving=`caget -t ${axis}`
done

}

if [ $# -lt "1" ]; then
   usage
   exit
else
    if [ $1 = "-h" ]; then
	usage
	exit
    fi
fi

#Pop up a warning dialogue to check that the beam is off.
if ! zenity --title="Warning: The Beam must be off to intall radiator" --question --text "Is the beam off?" --width 650; then
   exit
fi

rnum=$1

XAXIS="${P}X"
YAXIS="${P}Y"
ROLLAXIS="${P}ROLL"


RADX="${P}RAD${rnum}:X"
RADY="${P}RAD${rnum}:Y"
RADROLL="${P}RAD${rnum}:ROLL"
RADNAME="${P}RAD${rnum}:NAME"


x=`caget -t ${RADX}`
y=`caget -t ${RADY}`
azi=`caget -t ${RADROLL}`

#Move only one axis at a time. 
echo "caput ${XAXIS} ${x}"
caput ${XAXIS} ${x}
wait_stop ${XAXIS}
echo "caput ${YAXIS} ${y}"
caput ${YAXIS} ${y}
wait_stop ${YAXIS}
echo "caput ${ROLLAXIS} ${azi}"
caput ${ROLLAXIS} ${azi}
wait_stop ${ROLLAXIS}

#if the installed rad is diamond this will propogate its values
#as the defaults for calculating new values.
${HOME}/cbrem/scripts/currDiamToReq.sh "HD:CBREM:"

exit
