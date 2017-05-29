#!/bin/sh 
#Script to calculate the new X,Y,ROLL setting to keep radiator in beam when rotation by D_ROLL
#

if [ $# -lt "2" ]; then
    echo
    echo "Usage:"   
    echo "  $0 <P> <G> [DELTA_ROLL]"
    echo "  P and G are the EPICS macros for goni and cbrem. Eg. HD:CBREM: HD:GONI:";
    echo "  DELTA_ROLL is the change from the current ROLL value. (-45 < D_ROLL < 45 )"
    echo "  if not given on cmd line, it will come from EPICS value";
    exit
fi

#subfile="$APP/goniApp/Db/goni.substitutions"
subfile="/gluonfs1/gluex/controls/epics/R3-14-12-3-1/app/goniApp/Db/goni.substitutions"
#appdir="$APP/goniApp"
appdir="/gluonfs1/gluex/controls/epics/R3-14-12-3-1/app/goniApp"
resultfile="${HOME}/cbrem/data/last_delta_phi.dat";

P=$1;
G=$2;

if [ $# = "2" ]; then

    DROLL=`caget -t ${P}DELTA_ROLL`
else
    DROLL=$3;
fi


echo "# This is $resultfile" > $resultfile;
echo  >> $resultfile;
echo "# A change of ROLL by $DROLL deg would require the following new X,Y,ROLL valus" >> $resultfile;
echo "# to get the radiator into the beam at the new ROLL setting." >> $resultfile;
echo "# Possible replacement lines are marked with #s." >> $resultfile;
echo >> $resultfile;
echo "# These would be applied as follows:" >> $resultfile;
echo "Edit the numbers for the radiator(s) you want to change in this file:" >> $resultfile;
echo $subfile; >> $resultfile;
echo "Then do \"make\" in this directory: $appdir"; >> $resultfile;
echo "and restart the goni ioc to pick up the new settings for the radiator(s)"; >> $resultfile;
echo ; >> $resultfile;

grep "{P" $subfile | grep -v "CROSSX" >> $resultfile;
#do the calculation in embedded awk
awk -v DROLL=$DROLL -v G=$G 'BEGIN{FS=","}{\
  if(($1!~"#")&&($1~G)){\
    for(n=4;n<=8;n++)gsub(" ","",$n);\
    X=$5; Y=$6;ROLL=$7; R=$8;\
    ROLL2=ROLL+DROLL;\
    name=sprintf("%s,",$3);\
    X2=X-R*(cos(0.0174532925*ROLL)-cos(0.0174532925*ROLL2));\
    Y2=Y-R*(sin(0.0174532925*ROLL)-sin(0.0174532925*ROLL2));\
    printf"%s,%s,%-21s %s, %8.3f, %8.3f, %8.3f, %8.3f }\n",$1,$2,name,$4,$5,$6,$7,$8;\
    sub(" ","#",$1);\
    printf"%s,%s,%-21s %s, %8.3f, %8.3f, %8.3f, %8.3f }\n\n",$1,$2,name,$4,X2,Y2,ROLL2,$8;\
  }
   if(($1!~"#")&&($0~"goni.db")) exit;
}' $subfile >> $resultfile;
echo;

cat $resultfile;

zenity --text-info --title "Contents of $resultfile " --width 800 --height 800 --filename $resultfile;


exit;