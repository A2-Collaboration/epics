#!/bin/sh
scriptdir="/opt/epics/scripts/hvcaen";

print_usage(){
    echo
    echo "Usage:"   
    echo "  $0 <Mainframe> <load|save> [filename.sh]"   
    echo "   Current Mainframes are: HVTAGGER"
    echo
    echo "Eg: $0 HVTAGGER load HVTAGGER_V0.sh"
    echo "    $0 HVTAGGER load"
    echo "    if no [filename.sh] arg, then it comes from EPICS caget Mainframe:loadfile"
    exit;
}

if [ $# -lt "2" ]; then
    print_usage;
fi

mf=$1;
ls=$2;

#allowed mainframes
if [ ${mf} != "HVTAGGER" ] && [ ${mf} != "HVPID" ] ; then
    print_usage;
fi

#allowed options - must be load or save
if [ ${ls} != "load" ] && [ ${ls} != "save" ] ; then
    print_usage;
fi

#if there's a filename on the command line use that
if [ $# = "3" ]; then
    file=$3;
else
#if not, get it from EPICS
    file=`caget -t "${mf}:loadfile"`
fi

fullfile="${scriptdir}/${file}"


#load
if [ ${ls} = "load" ] ; then
    #check that the executable exists and execute it - shell script full of caputs
    if [ -x ${fullfile} ] ; then
	if [ -f ${fullfile} ]; then
	    warning="This will overwrite the current V0Settings and set new alarm limits";
	    if ! zenity --title="Loading parameters" --question --text "$warning" --width 650; then
		exit;
	    fi
	fi
	
	echo "running command ${fullfile}";
	${fullfile};
    else
	echo "Error: ${fullfile} doesn't exist, or is not executable";
	print_usage;
    fi
#save
else
    if [ -f ${fullfile} ]; then
	warning="${fullfile} already exists. Do you want to overwrite?";
	if ! zenity --title="Saving parameters" --question --text "$warning" --width 650; then
	    exit;
	fi
    fi
    
    fulldate=`date`
    echo "# Executable to restore parameters to CAENx527 Mainframe ${mf}" > ${fullfile};
    echo "# created by the command $0 on ${fulldate}"                    >> ${fullfile};
    
    #save is different for each Mainframe
    #so need an "if" for each

    if [ ${mf} = "HVTAGGER" ] ; then
        #The tagger MF has 8 x 48 A1932s - all the same, so its easy to loop over the whole thing.
	modslots="0 2 4 6 8 10 12 14"
	chans="49"
	for m in ${modslots};
	do
	    c=0;

	    #i0set is only for slot 000 in eachc module, sets the current limit.
	    pvname=`printf "%s:%02d:000" "${mf}" "${m}"`;
	    #echo $pvname;
	    I0=`caget -t "${pvname}:i0set:fbk"`;
	    echo "caput ${pvname}:i0set ${I0}" >> ${fullfile};

	    while [ ${c} -lt ${chans} ]
	    do
		#construct the channel name and read thew value
		pvname=`printf "%s:%02d:%03d" "${mf}" "${m}" "${c}"`;
		V0=`caget -t "${pvname}:v0set:fbk"`;
		echo "Saving setttings for ${pvname}"
		echo "caput ${pvname}:v0set ${V0}" >> ${fullfile};
		
		#make alarm levels
#		HIGH=`echo $V0 | awk '{printf"%5.1f",1.02*$1}'`;
#		HIHI=`echo $V0 | awk '{printf"%5.1f",1.04*$1}'`;
#		LOW=`echo $V0 | awk '{printf"%5.1f",0.98*$1}'`;
#		LOLO=`echo $V0 | awk '{printf"%5.1f",0.96*$1}'`;
		
#		echo "caput ${pvname}:vmon.HIHI ${HIHI}" >> ${fullfile};
#		echo "caput ${pvname}:vmon.HIGH ${HIGH}" >> ${fullfile};
#		echo "caput ${pvname}:vmon.LOW ${LOW}" >> ${fullfile};
#		echo "caput ${pvname}:vmon.LOLO ${LOLO}" >> ${fullfile};
	  
		c=`expr $c + 1`;
	    done
	done
    fi

    if [ ${mf} = "HVPID" ] ; then
        #The HVPID has different modules in different slots.
        #Have a string for each slot id, and another string for the no of channels in each slot 
	modslots=" 3  4";
	channels="12 24";
	#an index for the position in these strings.
	s=1;
	#loop over all the module slots
	for m in ${modslots};
	do
	    #figure out the no of chans in the slot
	    chans=`echo ${channels} | awk -v ind=${s} '{print $ind}'`
	    c=0;
	    while [ ${c} -lt ${chans} ]
	    do
		#construct the channel name and read the values
		pvname=`printf "%s:%02d:%03d" "${mf}" "${m}" "${c}"`;
		V0=`caget -t "${pvname}:v0set:fbk"`;
		echo "Saving setttings for ${pvname}"
		echo "caput ${pvname}:v0set ${V0}" >> ${fullfile};

		I0=`caget -t "${pvname}:i0set:fbk"`;
		echo "Saving setttings for ${pvname}"
		echo "caput ${pvname}:i0set ${I0}" >> ${fullfile};
		c=`expr $c + 1`;
	    done
	    #increment slot 
	    s=`expr $s + 1`;
	done
    fi
    
    #make the file executable
    chmod +x ${fullfile};
    
fi
exit;
    
