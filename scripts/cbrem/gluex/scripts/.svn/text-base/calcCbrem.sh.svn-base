#!/bin/sh
#Script to calculate the coherent and incoherent angles from
#from beam and peak energies
#and corrsponding pitch and yaw angles based on mode and offsets.
beamEnergyPV="MMSHLDE";
Eb="Unknown";
Eg="Unknown";
mradtodeg="0.057295779513";
outfile="/home/hdops/cbrem/data/lastBremCalc.dat"
pngfile="/home/hdops/cbrem/data/lastBremCalc.png"
use_epics="n";
phi="0";
pitch_off="0";
yaw_off="0";
para_mode="1";
perp_mode="1";

if [ $# -lt "2" ]; then
    echo
    echo "Usage:"   
    echo "  $0 <P> <G>"   
    echo "    Read and Write to/from EPICS PVs"
    echo "    P and G are the EPICS macros for goni and cbrem. Eg. HD:CBREM: HD:GONI:";
    echo
    echo "  $0 0  <Beam MeV> <Peak MeV> [phi022 pitch_off yaw_off]" ,,,,,,,,,,,,,,,,,,,,,,,
    echo "  $0 1  <coh deg>  <inc deg>  [phi022 pitch_off yaw_off]"
    echo "    Use command line args to print information"
    exit;
fi


if [ $# -gt "2" ]; then
    phi=$4;pitch_off=$5; yaw_off=$6;

    if [ $1 = "0" ]; then    #calculate i and c from Beam and Edge energy
	
	Eb=$2;
	Eg=$3;
        #The coherent edge from the 022 should be at Eg (c, coh angle)
        #And the one from the orthogonal planes 02-2 at 5/6 Eb (i, inc angle) 
	c=`echo "$Eb $Eg" | awk '{ Eb=$1; Eg=$2; ans=1000.0*26.5601/(2*Eb*Eb*((1/Eg)-(1/Eb))); printf"%5.3f mrad, %6.5f deg\n",ans,ans*0.057}'`;
	i=`echo "$Eb $Eg" | awk '{ Eb=$1; Eg=(5.0/6.0)*$1; ans=1000.0*26.5601/(2*Eb*Eb*((1/Eg)-(1/Eb))); printf"%5.3f mrad, %6.5f deg\n",ans,ans*0.057}'`;

	cmrad=`echo "$c" | awk '{print $3}'`; 
	imrad=` echo "$i" | awk '{print $3}'`; 
	cdeg=`echo "$c" | awk '{print $5}'`; 
	ideg=`echo "$i" | awk '{print $5}'`; 
	
	c=`echo "$c" | awk '{print $5}'`; 
	i=` echo "$i" | awk '{print $5}'`; 
	
    else 
	cmrad=$2; imrad=$3;
	cdeg=`echo "$cmrad" | awk '{print $1*0.057}'`;
	ideg=`echo "$imrad" | awk '{print $1*0.057}'`;
    fi
    
else #2 args, asume they are the P and G EPICS prefixes 
    #flage that we'll be using epics
    use_epics="y";
    #Get the prefixes for goni and cbrem
    P=$1;
    G=$2;
    
    #get the index and id of the curent radiator
    index=`caget -t "${G}RADIATOR_INDEX"`
    id=`caget -t "${G}RADIATOR_ID"`

    #if radiator index or id = 0, then there is no diamond in place, and it makes no sense to do things.
    if [ $index = "0" ] || [ $id = "0" ]; then 
	echo "Exit. There does not seem to be a diamond in position"
	exit;
    fi;

#get the modes and the phi angle
    para_mode=`caget -t "${P}REQ_PARA_MODE"`
    perp_mode=`caget -t "${P}REQ_PERP_MODE"`
    phi=`caget -t "${P}REQ_PHI022"`
    if [ $para_mode = "0" ] || [ $perp_mode = "0" ]; then 
	echo "Exit. para and perp modes must be in the range 1-4"
	exit;
    fi;

#get the offsets
    pitch_off=`caget -t "${P}REQ_OFF_PITCH"`
    yaw_off=`caget -t "${P}REQ_OFF_YAW"`
    
    Eb=`caget -t "$beamEnergyPV"`;
    Eg=`caget -t "${P}REQ_EDGE"`;
   
    #The coherent edge from the 022 should be at Eg (c, coh angle)
    #And the one from the orthogonal planes 02-2 at 5/6 Eb (i, inc angle) 
    c=`echo "$Eb $Eg" | awk '{ Eb=$1; Eg=$2; ans=1000.0*26.5601/(2*Eb*Eb*((1/Eg)-(1/Eb))); printf"c = %5.3f mrad, %6.5f deg\n",ans,ans*0.057}'`;
    i=`echo "$Eb $Eg" | awk '{ Eb=$1; Eg=(5.0/6.0)*$1; ans=1000.0*26.5601/(2*Eb*Eb*((1/Eg)-(1/Eb))); printf"i = %5.3f mrad, %6.5f deg\n",ans,ans*0.057}'`;

    cmrad=`echo "$c" | awk '{print $3}'`; 
    imrad=` echo "$i" | awk '{print $3}'`; 
    cdeg=`echo "$c" | awk '{print $5}'`; 
    ideg=`echo "$i" | awk '{print $5}'`; 
fi

#Update the file with the result of the last calcualtion
echo "#Results of last coherent brem calcualtion" > $outfile;
echo "Eb: $Eb MeV" >> $outfile;
echo "Eg: $Eg MeV" >> $outfile;
echo "c: $cdeg deg     ( =    $cmrad mrad )" >> $outfile;
echo "i: $ideg deg     ( =    $imrad mrad )" >> $outfile;
echo "yaw_off: $yaw_off deg" >> $outfile;
echo "pitch_off: $pitch_off deg" >> $outfile;
#get phi into the -45 - +45 range
phi=`echo $phi | awk '{                                     \
   phi=$1;                                                  \
   if(phi>45.0){while(phi>=45.0)phi-=45.0;}                 \
   else{while(phi<-45.0) phi+=45.0;}                        \
   print phi;                                               \
}'`
echo "phi022: $phi deg" >> $outfile;
echo  >> $outfile;
echo "#Settings for all PARA and PERP modes" >> $outfile;
echo "#modes:    yaw(deg) pitch(deg) yaw(mrad) pitch(mrad)" >> $outfile;

#pass it all to awk to how to move on pitch (theta_h) and yaw (theta_v) axes
#This is really an awk one liner, can't put comments in it
#Make phi into range between -45 and +45
#
#Do the trig depending on the mode, plane etc and give the yaw and pitch values.
#Can't do comments in the midle of embedded awk, so do com="" lines for comments.
echo "$phi      $ideg    $cdeg    $yaw_off $pitch_off" | awk '                      \
 {                                                                                  \
   phi=$1;      i=$2;    c=$3;     voff=$4; hoff=$5;                                \
                                                                                    \
   pname[1]="PARA";pname[2]="PERP";                                                 \
   com="set up the tables of signs for [plane,mode]";                               \
                                                                                    \
   cosphi=cos(phi*0.0174532925);                                                    \
   sinphi=sin(phi*0.0174532925);                                                    \
                                                                                    \
   com="PARA v and h settings for each of the 4 modes";                             \
   v[1,1] =  i*sinphi - c*cosphi + voff; h[1,1] = -i*cosphi - c*sinphi + hoff;      \
   v[1,2] =  i*sinphi + c*cosphi + voff; h[1,2] = -i*cosphi + c*sinphi + hoff;      \
   v[1,3] = -i*sinphi + c*cosphi + voff; h[1,3] =  i*cosphi + c*sinphi + hoff;      \
   v[1,4] = -i*sinphi - c*cosphi + voff; h[1,4] =  i*cosphi - c*sinphi + hoff;      \
                                                                                    \
   v[2,1] =  i*cosphi + c*sinphi + voff; h[2,1] =  i*sinphi - c*cosphi + hoff;      \
   v[2,2] =  i*cosphi - c*sinphi + voff; h[2,2] =  i*sinphi + c*cosphi + hoff;      \
   v[2,3] = -i*cosphi - c*sinphi + voff; h[2,3] = -i*sinphi + c*cosphi + hoff;      \
   v[2,4] = -i*cosphi + c*sinphi + voff; h[2,4] = -i*sinphi - c*cosphi + hoff;      \
                                                                                    \
   for(p=1;p<=2;p++){                                                               \
     for(m=1;m<=4;m++){                                                             \
       printf"%s_%d: %6.5f  %6.5f \n",pname[p],m,v[p,m],h[p,m];                     \
     }                                                                              \
   }                                                                                \
   exit;                                                                            \
}' >> $outfile;

phi=`grep phi022 ${outfile} | awk '{print $2;exit}'`;

paraLabel="PARA_${para_mode}:";
perpLabel="PERP_${perp_mode}:";

para_yaw=`grep ${paraLabel} ${outfile} | awk '{print $2;exit}'`;
para_pitch=`grep ${paraLabel} ${outfile} | awk '{print $3;exit}'`;

perp_yaw=`grep ${perpLabel} ${outfile} | awk '{print $2;exit}'`;
perp_pitch=`grep ${perpLabel} ${outfile} | awk '{print $3;exit}'`;

#if using EPICS write the values
if [ $use_epics = "y" ]; then

    caput  "${P}REQ_IMRAD" "$imrad";
    caput  "${P}REQ_IDEG" "$ideg";

    caput  "${P}REQ_CMRAD" "$cmrad";
    caput  "${P}REQ_CDEG" "$cdeg";

    caput  "${P}REQ_PARA_PITCH" "$para_pitch";
    caput  "${P}REQ_PARA_YAW" "$para_yaw";
    
    caput  "${P}REQ_PERP_PITCH" "$perp_pitch";
    caput  "${P}REQ_PERP_YAW" "$perp_yaw";

fi
pngfilearg="\"$pngfile"\";
#Run root in batch mode to make a png to display.
echo "paramode $para_mode perpmode $perp_mode $phi";

root -b -l -q /home/hdops/cbrem/scripts/drawModes.C'( 1, '$cmrad', '$imrad', '$phi', '$yaw_off', '$pitch_off', '$para_mode', '$perp_mode', '$pngfilearg')';
#root -l drawModes.C'( 1, '$cmrad', '$imrad', '$phi', '$yaw_off', '$pitch_off', '$para_mode', '$perp_mode', '$pngfilearg')'; 
display $pngfile &
exit;

