#!/bin/sh
#source epics setup if required

#source the epics env to get the pathe to caget etc.
. /opt/epics/thisEPICS.sh

#Here's the approximate process
#check GONI EPICS Scan flag is set to 1
#go to initial position
#loop over all steps
#  in each step, check first that the beam current is on
#  move
#  wait
#  read the scalers
#

G="BEAM:GONI:"
P="BEAM:CBREM:"

print_usage(){
    echo "usage:"
    echo "$0 <axis> <pos1> <step> <nstep> <yawoff> <pitchoff> <time>";
    echo "Where:"
    echo "<axis>  = axis to be scanned: must be one of X,Y,Z,ROLL,PITCH,YAW,STONE";
    echo "          STONE means Stonehenge scan (cone of radius <pos1> mrad by moving ROLL and PITCH)";
    echo "<pos1>  = starting position on the axis (= cone radius if <axis>= STONE)";
    echo "<step>  = amount to move in each step (not relevant for <axis>=STONE";
    echo "<nstep> = no of steps in the scan";
    echo "<yawoff>  = offset in v (YAW) from previous Stonehenge Plot, only relevant for <axis>=STONE";
    echo "<pitchoff>  = offset in h (PITCH) from previous Stonehenge Plot, only relevant for <axis>=STONE";
    echo "<time>  = time (s) to wait between each step";
    echo "<nchan> = no of channels in the hodoscope array";
    echo 
    echo "Here are some examples:"
    echo "$0 X    -20.0 1.0 100 0.00 0.00 2   (scan from -20.0 in 100 steps of 1mm on the X axis, 2s wait between steps)"
    echo
    echo "$0 STONE  3.0 0.0 180 0.01 0.02 2   (Stonehenge with cone radius 3deg, 180 x 2 deg steps, yawoff=0.01, pitchoff=0.02, 2s wait )"
    exit;
}

#Move and wait until stopped on scan axis
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
    movingyaw=1
    movingpitch=1

#    echo "caput ${pvyaw} ${yawpos}";
#    echo "caput ${pvpitch} ${pitchpos}";
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

#check that there are 7 arguments                                                                                                                             
if [ $# = "0" ]; then
    print_usage;
    exit;
fi



# if arg1 == "epics" then the script should take its info from EPICS records.
if [ $1 = "epics" ]; then
    axis=`caget -t "${P}SCAN_AXIS"`
    pos1=`caget -t "${P}SCAN_POS1"`
    step=`caget -t "${P}SCAN_STEP"`
    nstep=`caget -t "${P}SCAN_NSTEP"`
    yawoff=`caget -t "${P}SCAN_VOFF"`
    pitchoff=`caget -t "${P}SCAN_HOFF"`
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
    yawoff=$5;
    pitchoff=$6;
    time=$7;

    #and write them to EPICS

    caput -t "${P}SCAN_AXIS" "$axis";
    caput -t "${P}SCAN_POS1" "$pos1";
    caput -t "${P}SCAN_STEP" "$step";
    caput -t "${P}SCAN_NSTEP" "$nstep";
    caput -t "${P}SCAN_VOFF" "$yawoff";
    caput -t "${P}SCAN_HOFF" "$pitchoff";
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

  
rad_index=`caget -t "${G}RADIATOR_ID"`;
rad_id=`caget -t "${G}RADIATOR_INDEX"`;

axispv="${G}${axis}";

#make filename with spaces stripped out 
outfile=`echo "${HOME}/cbrem/data/RadScanIndex${rad_index}_ID${rad_id}_${axis}_${shortdate}.txt" | awk '{gsub(" ","-");print $0}'`;

echo "$outfile";

#no of channels to be read
nchan=`caget -t "${P}N_SCALERS"`;

#  fscanf(fp,"%d%d%f%f%f%f%f%f%f\n",	//read scan details#
#	  &xRange,
#	 &steps,
#	 &start,
#	 &stepSize,
#	 &vother,
#	 &hother,
#	 //	 &type,
#	 &yawoff,
#	 &pitchoff,
#	 &aoff);
# //	 &lL, 
#//	 &uL);
#352 90 0.000000 4.000000 80.000000 80.000000 0.000000 0.000000 0.000000 360.000000


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
  
    echo "$nchan $nstep 0.0 $phistep $pos1 $pos1 $yawoff $pitchoff 0.0" > $outfile;

    #init the step number
    s=0;
    while [ ${s} -lt ${nstep} ]
    do
	phi=`echo "$s $phistep" | awk '{print $1*$2}'`;
	phirad=`echo "$phi $degtorad" | awk '{print $1*$2}'`;
	yawpos=`echo $pos1 $phirad $yawoff | awk '{printf"%4.3f",$1*cos($2)+$3}'`;
	pitchpos=`echo $pos1 $phirad $pitchoff | awk '{printf"%4.3f", $1*sin($2)+$3}'`;
	echo "Step $s";
	#move the goniometer to the correct position
	move_stone;
	#sleep for the time required for a scaler buffer to accummulate
	sleep $time
	
	
	caget -t "${P}ENH_SCALERS" > ${HOME}/cbrem/data/scalers.dat
	awk -v chan=$nchan '{for(n=2;n<=chan+1;n++){printf"%5.3f\n",$n}}' ${HOME}/cbrem/data/scalers.dat >> $outfile; 
	
	
	s=`expr $s + 1`;	
    done
else
    echo "Other scan";
fi

exit
