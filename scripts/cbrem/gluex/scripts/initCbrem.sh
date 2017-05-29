#!/bin/sh

#source the epics env to get the path to caget etc.
#. /opt/epics/thisEPICS.sh

if [ $# -ne "2" ]; then
    echo "Error $0 needs need args for P and G macros";
    echo "Eg. $0 SIM:CBREM: SIM:GONI:";
    exit;
fi

#P="SIM:CBREM:"
#G="SIM:GONI:"

P=$1;
G=$2;

echo;
echo;

# Flag which of these detectors HODO, MICRO and LOWG are used to make the full picture 
#(0=OFF, 1=ON, 2=Reverse Order,GeV)
caput ${P}HODO_STATE 2
#40 characters max.

#hodoScalerPV="HODO:RAW_SCALER";   
hodoScalerPV="TAGH:disc:scalers:rate_wf";  
hodoMapPV="TAGH:disc:scaler:energy_wf";      #Could be filled from elsewhere, or here (see bottom);

#write these names into the CBREM records
caput "${P}HODO_SCALER_NAME" $hodoScalerPV
caput "${P}HODO_EMAP_NAME" $hodoMapPV

echo;
echo;

caput ${P}MICRO_STATE 2
#40 characters maxe
#write these names into the CBREM records
#microScalerPV="MICRO:RAW_SCALER";
microScalerPV="TAGM:disc:scalers:rate_wf";  
microMapPV="TAGM:disc:scaler:energy_wf";      #Could be filled from elsewhere, or here (see bottom);

caput "${P}MICRO_SCALER_NAME" $microScalerPV
caput "${P}MICRO_EMAP_NAME" $microMapPV

echo;
echo;

caput ${P}LOWG_STATE 0
#lowgScalerPV="bpu_photons_x";
#caput "${P}LOWG_SCALER_NAME" $lowgScalerPV
echo;
echo;

# Read previous references into EPICS from the text files.
amoscalers=`cat ${HOME}/cbrem/data/amo.dat`
caput -a "${P}AMO_SCALERS" ${amoscalers};

echo;
echo;

enhscalers=`cat ${HOME}/cbrem/data/enhRef.dat`
caput -a "${P}ENH_REF" ${enhscalers};

refline=`cat ${HOME}/cbrem/data/enhRefLine.dat`
caput -a "${P}REQ_EDGE_LINE_MAP" ${refline};

echo;
echo;

beam=`caget -t MMSHLDE`           #from accel EPICS
caput "${P}E_BEAM"  ${beam};        #The beam energy in MeV 
caput "${P}REQ_EDGE" 4170.0;      #The required position of the edge MeV.
caput "${P}EDGE.HIGH" 8000.0;     #Alarm levels around the required peak position 
caput "${P}EDGE.HIHI" 8200.0;
caput "${P}EDGE.LOW"  7000.0;
caput "${P}EDGE.LOLO" 6800.0;

#Set up lines on the graph for the reference and curent edge positions
#These need to be waveforms y coords 0 and 20
caput -a "${P}REQ_EDGE_LINE" 2 0 20;
caput -a "${P}EDGE_LINE" 2 0 20;


caput "${P}NORM_ENERGY"  5000.0;  #The energy point to use to normalize the enhancement.
caput "${P}NORM_COUNTS"  2;      #The beam current in nA to class as BEAM on.
caput "${P}COH_INCREMENT" 0.001; #The smallest amount to move the peak (deg)
caput "${P}ORTH_INCREMENT" 0.01; #The smallest amount to move the orthogonals (deg)

caput "${G}RAD:DPITCH" 0.4;      #The tolerance in pitch to decide if PARA or PERP is set
caput "${G}RAD:DYAW"   0.4;      #The tolerance in yaw to decide if PARA or PERP is set

#caput "${G}CROSSX"   241;
#caput "${G}CROSSY"   193;


#list of dead bins in the enhancements (from trial and error).
#Terminate with -1
#                            nchans   list ......
caput -a "${P}DEAD_SCALERS" 1         -1
#caput -a "${P}DEAD_SCALERS" 4        23  129 55 -1

#loop over all the radiators
NRAD=`caget -t "${G}NRAD"`
rad=0

while [ $rad -lt $NRAD ]
do
    rad=`expr $rad + 1`
    id=`caget -t "${G}RAD${rad}:ID"`

    #if id>0 it's a diamond. Look for the setup file end execute.
    if [ $id -gt "0" ] ; then
	echo;
	echo;
	diamscript="${HOME}/cbrem/data/diamond${id}.sh";
	if [ -x $diamscript ]; then
	    echo "Running setup script $diamscript"; 
	    $diamscript; #execute the script
	else
	    echo "WARINING:  Failed to find executable setup file \"$diamscript\" for radiator $rad, ID $id";
	fi
    fi
done

echo;
echo;

#Need to make sure this waveform is added in the cbrem.db 
#filling the hodoscope energy map from here
#caput -a "${hodoMapPV}"  352 87.8  92.0  96.2 100.4 104.5 108.8 113.0 117.2 121.4 125.6 129.8 134.0 138.2 142.5 146.7 150.9 155.1 159.3 163.6 167.9 172.1 176.4 180.6 184.9 189.1 193.4 197.7 201.9 206.2 210.5 214.7 219.0 223.3 227.6 231.9 236.2 240.5 244.8 249.1 253.4 257.7 262.0 266.3 270.6 274.9 279.2 283.6 287.9 292.2 296.5 300.9 305.2 309.5 313.9 318.2 322.5 326.9 331.2 335.6 339.9 344.3 348.6 353.0 357.3 361.7 366.1 370.4 374.7 379.1 383.5 387.9 392.2 396.6 401.0 405.3 409.7 414.1 418.5 422.8 427.2 431.6 436.0 440.3 444.7 449.1 453.5 457.9 462.3 466.6 471.0 475.4 479.7 484.2 488.6 492.9 497.3 501.7 506.1 510.5 514.9 519.3 523.6 528.0 532.3 536.8 541.2 545.6 549.9 554.3 558.7 563.1 567.5 571.8 576.2 580.6 584.9 589.3 593.7 598.1 602.5 606.8 611.2 615.6 619.9 624.3 628.6 633.0 637.3 641.7 646.1 650.4 654.8 659.1 663.5 667.8 672.1 676.5 680.8 685.2 689.4 693.8 698.1 702.5 706.8 711.1 715.4 719.7 724.0 728.3 732.6 736.9 741.2 745.5 749.8 754.1 758.3 762.6 766.9 771.1 775.4 779.7 783.9 788.2 792.4 796.7 800.9 805.1 809.3 813.6 817.8 822.0 826.2 830.4 834.6 838.7 843.0 847.1 851.3 855.5 859.6 863.8 868.0 872.1 876.2 880.4 884.4 888.6 892.7 896.8 900.9 905.0 909.1 913.2 917.3 921.3 925.4 929.4 933.5 937.5 941.6 945.6 949.6 953.6 957.6 961.6 965.6 969.6 973.5 977.5 981.5 985.4 989.4 993.3 997.2 1001.1 1005.1 1009.0 1012.9 1016.7 1020.6 1024.5 1028.3 1032.2 1036.0 1039.8 1043.7 1047.5 1051.3 1055.0 1058.8 1062.6 1066.4 1070.1 1073.9 1077.6 1081.3 1085.1 1088.8 1092.4 1096.1 1099.8 1103.5 1107.1 1110.8 1114.4 1118.0 1121.7 1125.3 1128.8 1132.4 1136.0 1139.6 1143.1 1146.7 1150.2 1153.7 1157.2 1160.7 1164.2 1167.7 1171.1 1174.6 1178.0 1181.5 1184.9 1188.3 1191.7 1195.1 1198.5 1201.8 1205.2 1208.5 1211.8 1215.2 1218.5 1221.7 1225.0 1228.3 1231.6 1234.8 1238.0 1241.3 1244.5 1247.7 1250.8 1254.0 1257.2 1260.4 1263.5 1266.6 1269.8 1272.9 1276.0 1279.0 1282.1 1285.1 1288.2 1291.3 1294.3 1297.3 1300.3 1303.3 1306.3 1309.2 1312.2 1315.2 1318.1 1321.0 1323.9 1326.8 1329.7 1332.6 1335.5 1338.3 1341.2 1344.0 1346.8 1349.6 1352.4 1355.2 1358.0 1360.9 1363.8 1366.7 1369.7 1372.7 1375.8 1379.0 1382.2 1385.4 1388.6 1391.9 1395.1 1398.4 1401.6 1404.8 1407.9 1411.0 1414.1 1417.1 1420.0 1422.9 1425.7 1428.3 1430.9 1433.5 1435.9 1438.2 1440.5 1442.6 1444.7 1446.7

caput "${P}INIT" 1;    #Flag that the initialisation has been done.

#if the installed rad is diamond thi will propogate its values
#as the defaults for calculating new values.
${HOME}/cbrem/scripts/currDiamToReq.sh $P

##start the root process.
#${HOME}/cbrem/scripts/makeEnh.sh start
