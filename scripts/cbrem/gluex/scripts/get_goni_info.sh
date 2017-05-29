#!/bin/sh
P="HD:GONI:"
#source the epics env to get the pathe to caget etc.
#. /opt/epics/thisEPICS.sh

NRAD=`caget -t "${P}NRAD"`

echo "The goni has ${NRAD} radiators"

rad=0

printf "Index\t%20s\t%16s\t%16s\t%16s\t%s\n" "Name" "X axis(mm)" "Y axis(mm)" "Roll axis (deg)" "ID"

 
while [ $rad -lt $NRAD ]
do
  rad=`expr $rad + 1`
  RADX="${P}RAD${rad}:X"
  RADY="${P}RAD${rad}:Y"
  RADROLL="${P}RAD${rad}:ROLL"
  RADDX="${P}RAD:DX"
  RADDY="${P}RAD:DY"
  RADDROLL="${P}RAD:DROLL"
  RADNAME="${P}RAD${rad}:NAME"
  RADID="${P}RAD${rad}:ID"

  x=`caget -t ${RADX}`
  y=`caget -t ${RADY}`
  azi=`caget -t ${RADROLL}`
  dx=`caget -t ${RADDX}`
  dy=`caget -t ${RADDY}`
  dazi=`caget -t ${RADDROLL}`
  name=`caget -t ${RADNAME}`
  id=`caget -t ${RADID}`

  printf "%d\t%20s\t%8.3f +/- %5.3f\t%8.3f +/- %5.3f\t%8.3f +/- %5.3f\t%d\n" "$rad" "$name" "$x" "$dx" "$y" "$dy" "$azi" "$dazi" "$id"
done
