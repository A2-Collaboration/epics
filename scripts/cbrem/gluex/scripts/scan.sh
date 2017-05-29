#!/bin/sh
#source the epics env to get the pathe to caget etc.
#. /opt/epics/thisEPICS.sh

#Here's the approximate process
#check GONI EPICS Scan flag is set to 1
#go to initial position
#loop over all steps
#  in each step, check first that the beam current is on
#  move
#  wait
#  read the scalers
#

G="HD:GONI:"
P="HD:CBREM:"
enhfile="${HOME}/cbrem/data/enh.dat"
scalerPVName=`caget -t ${P}MICRO_SCALER_NAME`
threshold="1000";
print_usage(){
    echo "usage:"
    echo "$0 <axis> <pos1> <step> <nstep> <yawvoff> <pitchoff> <time>";
    echo "Where:"
    echo "<axis>      = axis to be scanned: must be one of X,Y,Z,ROLL,PITCH,YAW,STONE";
    echo "              STONE means Stonehenge scan (cone of radius <pos1> mrad by moving ROLL and PITCH)";
    echo "<pos1>      = starting position on the axis (= cone radius if <axis>= STONE)";
    echo "<step>      = amount to move in each step (not relevant for <axis>=STONE";
    echo "<nstep>     = no of steps in the scan";
    echo "<yawvoff>   = offset in YAW from previous Stonehenge Plot, only relevant for <axis>=STONE";
    echo "<pitchoff>  = offset in PITCH from previous Stonehenge Plot, only relevant for <axis>=STONE";
    echo "<time>      = time (s) to wait between each step";
#    echo "<nchan>     = no of channels in the hodoscope array";
    echo 
    echo "Here are some examples:"
    echo "$0 X    -20.0 1.0 100 0.00 0.00 2   (scan from -20.0 in 100 steps of 1mm on the X axis, 2s wait between steps)"
    echo
    echo "$0 STONE  3.0 0.0 180 0.01 0.02 2   (Stonehenge with cone radius 3deg, 180 x 2 deg steps, voff=0.01, pitchoff=0.02, 2s wait )"
    exit;
}

#Move and wait until stopped on scan axis #not ready
move()
{
    moving=0
    pvmove="${axispv}${movesuf}"    
    while [ ${moving} -gt 0 ]
    do
	#echo $moving
	sleep 1
	moving=`caget -t ${pvmove}`
    done
}

#Move and wait until stopped for stonehenge.
move_stone()
{
    movingyaw=1;
    movingpitch=1;

#comment in to test
#    echo "caput ${pvyaw} ${yawpos}";
#    echo "caput ${pvpitch} ${pitchpos}";
#    movingyaw=0;
#    movingpitch=0;

# comment in for real
    caput ${pvyaw} ${yawpos};
    caput ${pvpitch} ${pitchpos};
    
    while [ ${movingyaw} -gt 0 ] || [ ${movingpitch} -gt 0 ] 
    do
	sleep 1
	movingpitch=`caget -t ${pvmovepitch}`
	movingyaw=`caget  -t ${pvmoveyaw}`
    done
}

########################################################################
# This is the start here ###############################################

# if arg1 == "epics" then the script should take its info from EPICS records.
if [ $1 = "epics" ]; then
    axis=`caget -t "${P}SCAN_AXIS"`
    pos1=`caget -t "${P}SCAN_POS1"`
    step=`caget -t "${P}SCAN_STEP"`
    nstep=`caget -t "${P}SCAN_NSTEP"`
    yawoff=`caget -t "${P}SCAN_YAW_OFF"`
    pitchoff=`caget -t "${P}SCAN_PITCH_OFF"`
    time=`caget -t "${P}SCAN_TIME"`
else
    #check that there are 7 arguments
    if [ $# -ne "7" ]; then
	print_usage;
	exit;
    fi

    #give them nice names
    axis=$1;
    pos1=$2;
    step=$3;
    nstep=$4
    yawpoff=$5;
    pitchoff=$6;
    time=$7;

    #and write them to EPICS

    caput -t "${P}SCAN_AXIS" "$axis";
    caput -t "${P}SCAN_POS1" "$pos1";
    caput -t "${P}SCAN_STEP" "$step";
    caput -t "${P}SCAN_NSTEP" "$nstep";
    caput -t "${P}SCAN_YAW_OFF" "$yawoff";
    caput -t "${P}SCAN_PITCH_OFF" "$pitchoff";
    caput -t "${P}SCAN_TIME" "$time";
fi


#check that the axis is sensible
if  [ ${axis} != "X" ]  && [ ${axis} != "Y" ]  && [ ${axis} != "ROLL" ] && [ ${axis} != "PITCH" ] && [ ${axis} != "YAW" ] && [ ${axis} != "STONE" ] ; then
    echo 
    echo "ERROR: \"${axis} \" is an unknown axis";
    echo
    print_usage;
fi


shortdate=`date '+%d_%m_%y:%H_%M'`


#figure out if this is simulated and set some things appropriately.
sim=`echo $P | awk '{if ($1 ~"SIM") print "1"; else print "0"}'`

if [ $sim = "1" ]; then
    movesuf=:MOVN;
else
    movesuf=.MOVN;
fi

  
rad_id=`caget -t "${G}RADIATOR_ID"`;
rad_index=`caget -t "${G}RADIATOR_INDEX"`;

axispv="${G}${axis}";

#make filename with spaces stripped out 
outfile=`echo "${HOME}/cbrem/data/RadScanIndex${rad_index}_ID${rad_id}_${axis}_${shortdate}.txt" | awk '{gsub(" ","-");print $0}'`;

echo "$outfile";

#no of channels to be read
nchan=`caget -t "${P}N_SCALERS"`;


#If Stonehenge scan
if [ ${axis} = "STONE" ]; then
    pvyaw="${G}YAW";    
    pvpitch="${G}PITCH";    
    pvmoveyaw="${G}YAW${movesuf}";    
    pvmovepitch="${G}PITCH${movesuf}";    

    #the size in radians for each step round the cone
    degtorad="0.0174532925";

    phistep=`echo "$nstep" | awk '{printf"%3.2f", 360.0/$nstep}'`; 

    warning="This will start a Stonehenge scan of cone angle $pos1 deg,\n${nstep} steps of $phistep deg\n yawoff = $yawoff, pitchoff = $pitchoff, ${time}s per scaler read\nARE YOU SURE YOU WANT TO DO THIS?";
    if ! zenity --title="Stonegenge scan" --question --text "$warning" --width 650; then
	exit;
    fi
  
    #flag that scan is underway
    caput -t "${P}SCAN_STATE" "1";

    echo "$nchan $nstep 0.0 $phistep $pos1 $pos1 $yawoff $pitchoff 0.0" > $outfile;

    #init the step number
    s=0;
    while [ ${s} -lt ${nstep} ]
    do

	#check to see if the scan is ended by EPICS 
	state=`caget -t "${P}SCAN_STATE"`
	if [ $state = "0" ]; then
	    exit;
	fi;
	
	phi=`echo "$s $phistep" | awk '{print $1*$2}'`;
	phirad=`echo "$phi $degtorad" | awk '{print $1*$2}'`;
	yawpos=`echo $pos1 $phirad $yawoff | awk '{printf"%4.3f",$1*cos($2)+$3}'`;
	pitchpos=`echo $pos1 $phirad $pitchoff | awk '{printf"%4.3f", $1*sin($2)+$3}'`;
	echo "Step $s";
	#write the step to epics
	caput -t "${P}SCAN_STEP" "$s";
	#move the goniometer to the correct position
	move_stone;
	#sleep for the time required for a scaler buffer to accummulate
	sleep $time
	
	#keep reading until enough counts in a group of hodo channels to prove the beam is on

	read=`caget -t ${scalerPVName} | gawk -v thresh=${threshold} '{for(n=10;n<=20;n++){tot+=$n}if(tot>thresh)print tot; else print 0;exit}'`	    
	echo "${scalerPVName} read=$read";
	while [ ${read} = "0" ]
	do
	    #check to see if the scan is ended by EPICS 
	    state=`caget -t "${P}SCAN_STATE"`
	    if [ $state = "0" ]; then
		exit;
	    fi;
	    read=`caget -t ${scalerPVName} | gawk  -v thresh=${threshold} '{for(n=10;n<=20;n++){tot+=$n}if(tot>thresh)print tot; else print 0;exit}'`	    
	    echo "Waiting for beam";
	    sleep $time
	done
	
	caget -t "${P}ENH_SCALERS" > ${enhfile}
	awk -v chan=$nchan '{for(n=2;n<=chan+1;n++){printf"%5.3f\n",$n}}' ${enhfile} >> $outfile; 
	
	s=`expr $s + 1`;	
    done
else
    echo "Other scan";
fi

#flag that the scan is over
caput -t "${P}SCAN_STEP" "0";
caput -t "${P}SCAN_STATE" "0";

exit
