#!/bin/sh

#source the epics env to get the pathe to caget etc.
. /opt/epics/thisEPICS.sh

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

# Flag which of these detectors HODO, MICRO and LOWG are used to make the full picture (0=OFF, 1=ON)
caput ${P}HODO_STATE 1
#40 characters max.

hodoScalerPV="TAGGER:RAW_SCALER";  #the .dat tell it to use a file as opposed to a waveform array 
hodoMapPV="TAGGER:HODO_EMAP";      #Could be filled from elsewhere, or here (see bottom);

#write these names into the CBREM records
caput "${P}HODO_SCALER_NAME" $hodoScalerPV
caput "${P}HODO_EMAP_NAME" $hodoMapPV

echo;
echo;

caput ${P}MICRO_STATE 0
#40 characters max.
#write these names into the CBREM records
#microScalerPV="X:MICRO_SCALERS";
#microMapPV="X:MICRO_EMAP";
#caput "${P}MICRO_SCALER_NAME" $microScalerPV
#caput "${P}MICRO_EMAP_NAME" $microMapPV

echo;
echo;

caput ${P}LOWG_STATE 0
#lowgScalerPV="X:LOWG_SCALER";
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

caput "${P}E_BEAM"  1577.0;      #The beam energy in MeV.
caput "${P}REQ_EDGE" 450.0;      #The required position of the edge MeV.
caput "${P}EDGE.HIGH" 455.0;     #Alarm levels around the required peak position 
caput "${P}EDGE.HIHI" 460.0;
caput "${P}EDGE.LOW"  445.0;
caput "${P}EDGE.LOLO" 440.0;

#Set up lines on the graph for the reference and curent edge positions
#These need to be waveforms y coords 0 and 20
caput -a "${P}REQ_EDGE_LINE" 2 0 20;
caput -a "${P}EDGE_LINE" 2 0 20;


caput "${P}NORM_ENERGY"  600.0;  #The energy point to use to normalize the enhancement.
caput "${P}COH_INCREMENT" 0.001; #The smallest amount to move the peak (deg)
caput "${P}ORTH_INCREMENT" 0.01; #The smallest amount to move the orthogonals (deg)
caput "${G}RAD:DPITCH" 0.2;      #The tolerance in pitch to decide if PARA or PERP is set
caput "${G}RAD:DYAW"   0.2;      #The tolerance in yaw to decide if PARA or PERP is set

#list of dead bins in the enhancements (from trial and error).
#                            nchans   list ......
#caput -a "${P}DEAD_SCALERS" 4        23  129 55 17

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
caput -a "${hodoMapPV}"  352 87.8  92.0  96.2 100.4 104.5 108.8 113.0 117.2 121.4 125.6 129.8 134.0 138.2 142.5 146.7 150.9 155.1 159.3 163.6 167.9 172.1 176.4 180.6 184.9 189.1 193.4 197.7 201.9 206.2 210.5 214.7 219.0 223.3 227.6 231.9 236.2 240.5 244.8 249.1 253.4 257.7 262.0 266.3 270.6 274.9 279.2 283.6 287.9 292.2 296.5 300.9 305.2 309.5 313.9 318.2 322.5 326.9 331.2 335.6 339.9 344.3 348.6 353.0 357.3 361.7 366.1 370.4 374.7 379.1 383.5 387.9 392.2 396.6 401.0 405.3 409.7 414.1 418.5 422.8 427.2 431.6 436.0 440.3 444.7 449.1 453.5 457.9 462.3 466.6 471.0 475.4 479.7 484.2 488.6 492.9 497.3 501.7 506.1 510.5 514.9 519.3 523.6 528.0 532.3 536.8 541.2 545.6 549.9 554.3 558.7 563.1 567.5 571.8 576.2 580.6 584.9 589.3 593.7 598.1 602.5 606.8 611.2 615.6 619.9 624.3 628.6 633.0 637.3 641.7 646.1 650.4 654.8 659.1 663.5 667.8 672.1 676.5 680.8 685.2 689.4 693.8 698.1 702.5 706.8 711.1 715.4 719.7 724.0 728.3 732.6 736.9 741.2 745.5 749.8 754.1 758.3 762.6 766.9 771.1 775.4 779.7 783.9 788.2 792.4 796.7 800.9 805.1 809.3 813.6 817.8 822.0 826.2 830.4 834.6 838.7 843.0 847.1 851.3 855.5 859.6 863.8 868.0 872.1 876.2 880.4 884.4 888.6 892.7 896.8 900.9 905.0 909.1 913.2 917.3 921.3 925.4 929.4 933.5 937.5 941.6 945.6 949.6 953.6 957.6 961.6 965.6 969.6 973.5 977.5 981.5 985.4 989.4 993.3 997.2 1001.1 1005.1 1009.0 1012.9 1016.7 1020.6 1024.5 1028.3 1032.2 1036.0 1039.8 1043.7 1047.5 1051.3 1055.0 1058.8 1062.6 1066.4 1070.1 1073.9 1077.6 1081.3 1085.1 1088.8 1092.4 1096.1 1099.8 1103.5 1107.1 1110.8 1114.4 1118.0 1121.7 1125.3 1128.8 1132.4 1136.0 1139.6 1143.1 1146.7 1150.2 1153.7 1157.2 1160.7 1164.2 1167.7 1171.1 1174.6 1178.0 1181.5 1184.9 1188.3 1191.7 1195.1 1198.5 1201.8 1205.2 1208.5 1211.8 1215.2 1218.5 1221.7 1225.0 1228.3 1231.6 1234.8 1238.0 1241.3 1244.5 1247.7 1250.8 1254.0 1257.2 1260.4 1263.5 1266.6 1269.8 1272.9 1276.0 1279.0 1282.1 1285.1 1288.2 1291.3 1294.3 1297.3 1300.3 1303.3 1306.3 1309.2 1312.2 1315.2 1318.1 1321.0 1323.9 1326.8 1329.7 1332.6 1335.5 1338.3 1341.2 1344.0 1346.8 1349.6 1352.4 1355.2 1358.0 1360.9 1363.8 1366.7 1369.7 1372.7 1375.8 1379.0 1382.2 1385.4 1388.6 1391.9 1395.1 1398.4 1401.6 1404.8 1407.9 1411.0 1414.1 1417.1 1420.0 1422.9 1425.7 1428.3 1430.9 1433.5 1435.9 1438.2 1440.5 1442.6 1444.7 1446.7

#caput -a "${hodoMapPV}"  352 49.6 52.0 54.4 56.8 59.1 61.5 63.9 66.3 68.7 71.2 73.6 76.0 78.4 80.8 83.2 85.6 88.0 90.4 92.9 95.3 97.7 100.2 102.6 105.0 107.4 109.9 112.3 114.7 117.2 119.6 122.0 124.5 127.0 129.4 131.8 134.3 136.7 139.2 141.7 144.1 146.6 149.0 151.5 153.9 156.4 158.9 161.3 163.8 166.3 168.7 171.2 173.7 176.1 178.6 181.1 183.5 186.0 188.5 191.0 193.5 195.9 198.4 200.9 203.4 205.9 208.4 210.8 213.3 215.8 218.3 220.8 223.3 225.8 228.3 230.8 233.2 235.7 238.2 240.7 243.2 245.7 248.2 250.7 253.2 255.7 258.2 260.7 263.2 265.7 268.2 270.7 273.1 275.7 278.1 280.6 283.1 285.6 288.1 290.6 293.1 295.6 298.1 300.6 303.1 305.6 308.1 310.6 313.1 315.6 318.1 320.6 323.1 325.6 328.0 330.5 333.0 335.5 338.0 340.5 343.0 345.5 347.9 350.4 352.9 355.4 357.9 360.4 362.8 365.3 367.8 370.3 372.7 375.2 377.7 380.1 382.6 385.1 387.5 390.0 392.4 394.9 397.4 399.8 402.3 404.8 407.2 409.7 412.1 414.5 417.0 419.4 421.8 424.3 426.7 429.2 431.6 434.0 436.5 438.9 441.3 443.7 446.1 448.6 450.9 453.4 455.8 458.2 460.6 463.0 465.4 467.8 470.2 472.5 474.9 477.3 479.7 482.1 484.4 486.8 489.2 491.5 493.9 496.2 498.6 500.9 503.2 505.6 507.9 510.3 512.6 514.9 517.3 519.6 521.9 524.2 526.5 528.8 531.1 533.4 535.7 538.0 540.2 542.5 544.8 547.1 549.3 551.6 553.8 556.1 558.3 560.6 562.8 565.0 567.3 569.5 571.7 573.9 576.1 578.3 580.5 582.7 584.9 587.1 589.3 591.4 593.6 595.8 597.9 600.0 602.2 604.3 606.5 608.6 610.7 612.9 615.0 617.1 619.2 621.2 623.4 625.4 627.5 629.6 631.7 633.7 635.8 637.8 639.9 641.9 643.9 646.0 648.0 650.0 652.0 654.0 656.0 658.0 659.9 661.9 663.9 665.9 667.8 669.8 671.7 673.6 675.6 677.5 679.4 681.3 683.2 685.1 687.0 688.9 690.8 692.7 694.5 696.4 698.2 700.1 701.9 703.7 705.6 707.4 709.2 711.0 712.8 714.6 716.4 718.2 719.9 721.7 723.4 725.2 726.9 728.7 730.4 732.1 733.9 735.6 737.3 739.0 740.7 742.4 744.0 745.7 747.4 749.0 750.7 752.3 754.0 755.6 757.2 758.9 760.5 762.1 763.7 765.3 766.9 768.4 770.0 771.6 773.2 774.8 776.5 778.2 779.9 781.7 783.4 785.2 787.0 788.9 790.7 792.6 794.4 796.2 798.0 799.8 801.6 803.3 805.0 806.6 808.2 809.8 811.3 812.8 814.2 815.6 816.9 818.1 819.4 820.5 821.7

caput "${P}INIT" 1;    #Flag that the initialisation has been done.

#start the root process.
${HOME}/cbrem/scripts/makeEnh.sh start
