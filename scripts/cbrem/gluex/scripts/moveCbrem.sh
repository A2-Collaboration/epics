#!/bin/sh
#Script to move the coherent peak, or the orthogonal planes.
#This gets called to adjust move coherent peak or orthogonal components up or down in photon energy.
#Would normally be called from CSS or other GUI, but can be tested from the command line

#source the epics env to get the path to caget etc.
#. /opt/epics/thisEPICS.sh


#Function to Move relative on pitch and yaw wait until stopped.
move_pitchyaw()
{
    echo "Moving by $yawrel on yaw"
    echo "Moving by $pitchrel pitch"

    #figure out if this is simulated and set some things appropriately.
    sim=`echo $P | awk '{if ($1 ~"SIM") print "1"; else print "0"}'`

    if [ $sim = "1" ]; then
	movesuf=:MOVN;
	relsuf=:RLV;
    else
	movesuf=.MOVN;
	relsuf=.RLV;
    fi

    pvyaw="${G}YAW${relsuf}";    
    pvpitch="${G}PITCH${relsuf}";    
    pvmoveyaw="${G}YAW${movesuf}";    
    pvmovepitch="${G}PITCH${movesuf}";    
    
    movingyaw=1
    movingpitch=1

#    echo "caput ${pvyaw} ${yawrel}";
#    echo "caput ${pvpitch} ${pitchrel}";
    caput ${pvyaw} ${yawrel};
    caput ${pvpitch} ${pitchrel};
    
    while [ ${movingyaw} -gt 0 ] || [ ${movingpitch} -gt 0 ] 
    do
	sleep 1
	movingpitch=`caget -t ${pvmovepitch}`
	movingyaw=`caget  -t ${pvmoveyaw}`
    done
}

if [ $# -ne "5" ]; then
    echo
    echo "Usage: $0 <P> <G> <type> <size> <direction>"   
    echo "       P and G are the EPICS macros for goni and cbrem. Eg. HD:CBREM: HD:GONI:";
    echo "       <type> is \"peak\" or \"other\"";
    echo "       <size> is \"big\" or \"small\"";
    echo "       <direction> is \"left\" or \"right\"";
    exit;
fi

P=$1;
G=$2;
type=$3;
size=$4;
direction=$5;

#other information comes from EPICS

index=`caget -t "${G}RADIATOR_INDEX"`
id=`caget -t "${G}RADIATOR_ID"`

#if radiator index or id = 0, then there is no diamond in place, and it makes no sense to do things.
if [ $index = "0" ] || [ $id = "0" ]; then 
    echo "Exit. There does not seem to be a diamond in position"
    exit;
fi;


para_mode=`caget -t "${P}PARA_MODE"`
perp_mode=`caget -t "${P}PERP_MODE"`
phi=`caget -t "${P}PHI022"`
coh=`caget -t "${P}COH_INCREMENT"`
inc=`caget -t "${P}ORTH_INCREMENT"`

plane=`caget -t "${P}PLANE"`

if [ $plane = "0" ]; then
    echo "Exit. The current plane is not known, force to PARA or PERP"
    #zenity thing here
    exit;
fi

if [ $para_mode = "0" ] || [ $perp_mode = "0" ]; then
    echo "Exit. The current mode for $coherent scattering is not known. Make sure ${P}DIAM${id}:PARA_MODE and ${P}DIAM${id}:PERP_MODE are set to 1,2,3 or 4";
    #zenity thing here
    exit;
fi


#pass it all to awk to how to move on pitch (theta_h) and yaw (theta_v) axes
#This is really an awk one liner, can't put comments in it
#Make phi into range between 0 and 90.
#Do the trig depending on the mode, plane etc and give the yaw and pitch values.
#               $1     2       3          4         5        6     7   8     9
pitchyaw=`echo "$type $size $direction $para_mode $perp_mode $phi $inc $coh $plane" | awk '{\
   type=$1; size=$2; dir=$3; para_mode=$4; perp_mode= $5; phi=$6; i=$7; c=$8; plane=$9;  \
   while(phi>=90.0)phi-=90.0;                            \
   while(phi<0)phi+=90.0;                                \
                                                         \
                                                         \
   cosphi=cos(phi*0.0174532925);                         \
   sinphi=sin(phi*0.0174532925);                         \
                                                         \
   if(size~"big"){                                       \
     i*=10.0; c*=10.0;                                   \
   }                                                     \
   if(dir~"left"){                                       \
     i*=-1.0; c*=-1.0;                                   \
   }                                                     \
   if(plane==1){                                         \
     if(type~"other"){                                   \
       if((para_mode==1)||(para_mode==2)){               \
         v = - i*sinphi; h = + i*cosphi;                 \
       }                                                 \
       else{                                             \
         v = + i*sinphi; h = - i*cosphi;                 \
       }                                                 \
     }                                                   \
     else{                                               \
       if((para_mode==2)||(para_mode==3)){               \
         v = + c*cosphi; h = + c*sinphi;                 \
       }                                                 \
       else{                                             \
         v = - c*cosphi; h = - c*sinphi;                 \
       }                                                 \
     }                                                   \
   }                                                     \
   else{                                                 \
     if(type~"other"){                                   \
       if((perp_mode==1)||(perp_mode==2)){               \
         v = + i*cosphi; h = + i*sinphi;                 \
       }                                                 \
       else{                                             \
         v = - i*cosphi; h = - i*sinphi;                 \
       }                                                 \
     }                                                   \
     else{                                               \
       if((perp_mode==1)||(perp_mode==4)){               \
         v = + c*sinphi; h = - c*cosphi;                 \
       }                                                 \
       else{                                             \
         v = - c*sinphi; h = + c*cosphi;                 \
       }                                                 \
     }                                                   \
   }                                                     \
                                                         \
   print v,h;                                            \
   exit;                                                 \
}'`

#The answer is a string: "v  h"
#split up using awk
yawrel=`echo "$pitchyaw" | awk '{print $1}'`
pitchrel=`echo "$pitchyaw" | awk '{print $2}'`


#now call the function to move on pitch and yaw
warning="This will do a relative move of $yawrel deg on YAW, and $pitchrel on PITCH\nARE YOU SURE YOU WANT TO DO THIS?";

#if ! zenity --title="Adjust coherent bremsstrahlung conditions" --question --text "$warning" --width 650; then
#    exit;
#fi

#Call the function to move on pitch and yaw
    move_pitchyaw;
exit;
