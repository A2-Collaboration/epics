from lib.runset import NewRunSet,SimpleText,RunEntry,RunEntry2,RadEntry,RadEntry2,EpicsEntry,StaticValue,Dummy,EpicsMnp,QueryValue,YesNoValue,Time


EtaPrime = NewRunSet("Etaprime",80)
EtaPrime.lines = [
       [SimpleText("Run XXX - Start: XX:XX End: XX:XX") ],
       [],
       [Dummy(),Dummy(),Dummy(),Dummy(),Time()],
       [StaticValue("Energy","1604 MeV") , StaticValue("Set-Current","60 nA"), StaticValue("Radiator","10 mu copper")],
       [StaticValue("Collimator","4 mm") , StaticValue("Target","Hydrogen"), StaticValue("Trigger","CB Esum>550MeV")],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("EPT OR","TAGG:EPT:Sector0:TRIG:OR","MHz",1.0/1000000),Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000) , EpicsEntry("Ladder /P2","TAGG:EPT:LadderP2Ratio","",1.0),Dummy()],
       [EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0),Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000),Dummy()],
       [],
       [EpicsEntry("CB ESumLow","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000),EpicsMnp()],
       [EpicsEntry("CB ESumHigh","CB:CB:TRIG:ESum_High","kHz",1./1000),Dummy(),                                                 EpicsEntry("M1","TRIG:MULT:M1","kHz",1.0/1000)],
       [Dummy(),                                                       Dummy(),                                                 EpicsEntry("M2","TRIG:MULT:M2","kHz",1.0/1000)],
       [Dummy(),                                                       Dummy(),                                                 EpicsEntry("M3","TRIG:MULT:M3","kHz",1.0/1000)],
       [Dummy(),                                                       Dummy(),                                                 EpicsEntry("M4","TRIG:MULT:M4","kHz",1.0/1000)],
       [Dummy(),                                                       Dummy(),                                                 EpicsEntry("M5","TRIG:MULT:M5","kHz",1.0/1000)],
       [SimpleText("Enpoint-Tagger:"),                                 Dummy(),                                                 EpicsEntry("M6","TRIG:MULT:M6","kHz",1.0/1000)],
       [EpicsEntry("Mag. Field","TAGG:EPT:MagneticField","T"),         Dummy(),                                                 EpicsEntry("M7","TRIG:MULT:M7","kHz",1.0/1000)],
       [],
       [SimpleText("Hydrogen Target:") ],
       [EpicsEntry("Pressure","TARGET:H2:Pcible","mbar"),Dummy(),Dummy()],
       [SimpleText("Temperature:"), EpicsEntry("Target","TARGET:H2:CLTS","K"),EpicsEntry("Liquifier","TARGET:H2:Tsi","K")],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"),Dummy()]
     ]

EtaPrimeTaggeff = NewRunSet("EtaPrime-Taggeff",80)
EtaPrimeTaggeff.lines = [
       [SimpleText("Run XXX - Start: XX:XX End: XX:XX") ],
       [],
       [Dummy(),Dummy(),Dummy(),Dummy(),Time()],
       [],
       [SimpleText("     ========== Tagging Efficiency Run ==========")],
       [],
       [StaticValue("Energy","1604 MeV") , StaticValue("Set-Current","00 nA"), StaticValue("Radiator","10 mu copper")],
       [StaticValue("Collimator","4 mm") , StaticValue("Target","Hydrogen"),   StaticValue("Trigger","CB Esum>550MeV")],
       [],
       [Dummy(),EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000),                       EpicsEntry("EPT OR","TAGG:EPT:Sector0:TRIG:OR","MHz",1.0/1000000)],
       [SimpleText("Enpoint-Tagger:"),EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000),  EpicsEntry("Ladder /P2","TAGG:EPT:LadderP2Ratio","",1.0)],
       [EpicsEntry("Mag. Field","TAGG:EPT:MagneticField","T"),                  Dummy(),     EpicsEntry("LEAD Glass","BEAM:PBGlass","kHz",1.0/1000) ],
       [],
       [EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000),  EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0),               Dummy()],
       [],
       [SimpleText("Hydrogen Target:") ],
       [EpicsEntry("Pressure","TARGET:H2:Pcible","mbar"),Dummy(),Dummy()],
       [SimpleText("Temperature:"), EpicsEntry("Target","TARGET:H2:CLTS","K"),EpicsEntry("Liquifier","TARGET:H2:Tsi","K")],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"),Dummy()]
     ]

G_E_Neutron = NewRunSet("G_E_Neutron",100)
G_E_Neutron.lines = [
       [SimpleText("Run XXX - Start: XX:XX End: XX:XX")],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Set-Current","0.6/1.2 nA (Dia/Moe) "), EpicsEntry("Radiator","BEAM:GONI:RADIATOR_INDEX","(5 = Dia, 6 = Moe)",1), Dummy()],
       [StaticValue("Collimator","2 mm"), StaticValue("Target","D-Butanol"), StaticValue("Trigger","CB Esum OR (BaF2 M1+ vetoed by C)"), Dummy()],
       [],
       [EpicsEntry("Polar. Plane","BEAM:CBREM:PLANE","(1 = Para, 2 = Perp)",1), Dummy(), Dummy(), Dummy()],
       [EpicsEntry("Coherent Edge","BEAM:CBREM:EDGE","MeV",1), Dummy(), Dummy(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","MHz",1.0/1000000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("CB ESum","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), EpicsEntry("M1+","TRIG:MULT:M1","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()]
       ]
G_E_Neutron2 = NewRunSet("G_E_Neutron",100)
G_E_Neutron2.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Collimator","2 mm"), StaticValue("Set-Current","2 nA - Moeller"), Dummy()],
       [StaticValue("Target","D-Butanol"), StaticValue("Targ. Pol.","Positive"), StaticValue("Trigger","CB Esum OR (BaF2 M1+ vetoed by C)"), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("M1","TRIG:MULT:M1","kHz",1.0/1000), EpicsEntry("M2","TRIG:MULT:M2","kHz",1.0/1000), EpicsEntry("M3","TRIG:MULT:M3","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

T_F_transverse_dbutanol = NewRunSet("T_F_transverse_dbutanol",100)
T_F_transverse_dbutanol.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Collimator","2.5 mm"), StaticValue("Set-Current","12.5 nA - Moeller"), Dummy()],
       [StaticValue("Target","Carbon"), StaticValue("Targ. Pol.","---"), StaticValue("Trigger","CB Esum OR TAPS M2+"), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("M1","TRIG:MULT:M1","kHz",1.0/1000), EpicsEntry("M2","TRIG:MULT:M2","kHz",1.0/1000), EpicsEntry("M3","TRIG:MULT:M3","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("TAPS LED2M2+","TAPS:BAF:TRIG:LED2:M2Plus","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

Moeller = NewRunSet("Moeller",100)
Moeller.lines = [
    [RunEntry()],
    [],
    [StaticValue("Energy","1557 MeV"), StaticValue("Set-Current","13.5 nA"), StaticValue("Radiator","Moeller"), Dummy()],
    [StaticValue("Collimator","2 mm"), StaticValue("Target","D-Butanol"), StaticValue("Trigger","M2+ AND ESum>350"), Dummy()],
    [],
    [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","MHz",1.0/1000000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
    [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
    [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
    [EpicsEntry("M1","TRIG:MULT:M1","kHz",1.0/1000), EpicsEntry("M2","TRIG:MULT:M2","kHz",1.0/1000), EpicsEntry("M3","TRIG:MULT:M3","kHz",1.0/1000), Dummy()],
    [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
    [],
    [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
    [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
    [],
    [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"),Dummy(), Dummy()],
    [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()], 
    ]
 

G_E_Proton = NewRunSet("G_E_Proton",100)
G_E_Proton.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Collimator","2 mm"), StaticValue("Set-Current","2.5/3.3 nA (Dia/Moe) "), Dummy()],
       [StaticValue("Target","Butanol"), StaticValue("Targ. Pol.","Positive"), StaticValue("Trigger","CB Esum OR (BaF2 M1+ vetoed by C)"), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("M1","TRIG:MULT:M1","kHz",1.0/1000), EpicsEntry("M2","TRIG:MULT:M2","kHz",1.0/1000), EpicsEntry("M3","TRIG:MULT:M3","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

Sigma2z = NewRunSet("Sigma2z",100)
Sigma2z.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","450 MeV"), StaticValue("Collimator","2.5 mm"), StaticValue("Set-Current","20 nA"), Dummy()],
       [StaticValue("Target","Carbon"), StaticValue("Targ. Pol.","-"), StaticValue("Trigger","CB Esum > 70 MeV"), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [EpicsEntry("Pi0/10k","GEN:MON:Pi0PerScRead","",1.0), Dummy(), Dummy(), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

SolidTarg = NewRunSet("SolidTarg",100)
SolidTarg.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Collimator","2.5 mm"), StaticValue("Set-Current","4.5 nA"), Dummy()],
       [StaticValue("Target","Carbon, 20 mm"), StaticValue("Trigger","CB Esum > 350 MeV, M2+"), Dummy(), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [EpicsEntry("Pi0/10k","GEN:MON:Pi0PerScRead","",1.0), Dummy(), Dummy(), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

PMTtest = NewRunSet("PMTtest",100)
PMTtest.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","855 MeV"), StaticValue("Collimator","2.5 mm"), StaticValue("Set-Current","x nA"), Dummy()],
       [StaticValue("Target","Aluminum"), StaticValue("Trigger","CB Esum > 100 MeV M2+"), Dummy(), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [EpicsEntry("Pi0/10k","GEN:MON:Pi0PerScRead","",1.0), Dummy(), Dummy(), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

APPT_Test = NewRunSet("APPT_Test",100)
APPT_Test.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","855 MeV"), StaticValue("Collimator","1.5 mm"), StaticValue("Set-Current","2.5 nA"), Dummy()],
       [StaticValue("Target","APPT"), StaticValue("Targ. Pol.","NA"), StaticValue("Trigger","CB Esum > 60 MeV"), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [EpicsEntry("Pi0/10k","GEN:MON:Pi0PerScRead","",1.0), Dummy(), Dummy(), Dummy()],
       [],
#       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
#       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

Active_Target = NewRunSet("Active_Target",100)
Active_Target.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","450 MeV"), StaticValue("Collimator","2.5 mm"), StaticValue("Set-Current","5 nA"), Dummy()],
       [StaticValue("Target","APPT"), StaticValue("Targ. Pol.","Negative"), StaticValue("Trigger","CB Esum > 30 MeV"), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [EpicsEntry("Pi0/10k","GEN:MON:Pi0PerScRead","",1.0), Dummy(), Dummy(), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

Recoil_Obs_Pol_Amor = NewRunSet("Recoil_Obs_Pol_Amor",100)
Recoil_Obs_Pol_Amor.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Collimator","3 mm"), StaticValue("Set-Current","2.7 nA"), Dummy()],
       [StaticValue("Target","LD2"), StaticValue("Trigger","CB Esum > 100 MeV AND M2+"), Dummy(), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [EpicsEntry("Pi0/10k","GEN:MON:Pi0PerScRead","",1.0), Dummy(), Dummy(), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [EpicsEntry("LD2 Target Temperature","TARGET:H2:CLTS","K"), EpicsEntry("LD2 Target Pressure","TARGET:H2:Pcible","mbar"), Dummy()],
       [EpicsEntry("Liquifier Temperature ","TARGET:H2:Tsi","K"), Dummy(), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

Recoil_Obs_Pol_Diam = NewRunSet("Recoil_Obs_Pol_Diam",100)
Recoil_Obs_Pol_Diam.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Collimator","3 mm"), StaticValue("Set-Current","1.7 nA"), Dummy()],
       [StaticValue("Target","LD2"), StaticValue("Trigger","CB Esum > 100 MeV AND M2+"), Dummy(), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [EpicsEntry("Pi0/10k","GEN:MON:Pi0PerScRead","",1.0), Dummy(), Dummy(), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [EpicsEntry("LD2 Target Temperature","TARGET:H2:CLTS","K"), EpicsEntry("LD2 Target Pressure","TARGET:H2:Pcible","mbar"), Dummy()],
       [EpicsEntry("Liquifier Temperature ","TARGET:H2:Tsi","K"), Dummy(), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

Eta_4He = NewRunSet("Eta_4He",100)
Eta_4He.lines = [
       [RunEntry()],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Collimator","3 mm"), StaticValue("Set-Current","9 nA"), Dummy()],
       [StaticValue("Target","4He"), StaticValue("Trigger","(CB Esum > 300 MeV AND M2+) OR TAPS M2+"), Dummy(), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("Tagger OR","TAGG:TAGG:ReferenceOR","kHz",1.0/1000), EpicsEntry("Ladder /P2","TAGG:TAGG:LadderP2Ratio","",1.0), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("ESum Low","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("ESum High","CB:CB:TRIG:ESum_High","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000), Dummy()],
       [EpicsEntry("TAPS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [EpicsEntry("TAPS LED2","TAPS:BAF:TRIG:LED2:M2Plus","kHz",1.0/1000), EpicsEntry("Pi0/10k","GEN:MON:Pi0PerScRead","",1.0), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [EpicsEntry("Temperature of target pot","TARGET:HE:PT100_4","K"), EpicsEntry("4He Target Pressure","TARGET:HE:P_TCELL_Vac","mbar"), Dummy()],
       [EpicsEntry("Target temp","TARGET:HE:RuO2L","K"), Dummy(), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       [YesNoValue("Helicity Information","Check POL QUELLE Moudule: ok? ","OK","stop run for fixing"), Dummy(), Dummy()],
       ]

TaggEff = NewRunSet("TaggEff",100)
TaggEff.lines = [
       [RunEntry()],
       [],
       [SimpleText("     ========== Tagging Efficency Run ==========")],
       [],
       [StaticValue("Energy","1557 MeV"), StaticValue("Collimator","3 mm"), StaticValue("Set-Current","0 nA"), Dummy()],
       [StaticValue("Target","4He"), StaticValue("Trigger","Pb-Glass"), Dummy(), Dummy()],
       [],
       [RadEntry2(), Dummy()],
       [],
       [EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0), Dummy()],
       [EpicsEntry("LEAD Glass","BEAM:PBGlass","kHz",1.0/1000), EpicsEntry("NMR","TAGG:MagneticField","mT",1000), Dummy()],
       [],
       [EpicsEntry("MWPC CH0 HV","CB:MWPC:HV:CH0:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH0 Imon","CB:MWPC:HV:CH0:Imon:RBV","uA",1.0), Dummy()],
       [EpicsEntry("MWPC CH1 HV","CB:MWPC:HV:CH1:Vmon:RBV","V",1.0), EpicsEntry("MWPC CH1 Imon","CB:MWPC:HV:CH1:Imon:RBV","uA",1.0), Dummy()],
       [],
       [EpicsEntry("Target Temperature","TARGET:HE:PT100_4","K"), EpicsEntry("4He Target Pressure","TARGET:HE:P_TCELL_Vac","mbar"), Dummy()],
       [],
       [YesNoValue("Taps Fan failure status","Check crate: TAPS fan status ok? ","OK","stop run for fixing"),Dummy()]
     ]

ShiftSummary = NewRunSet("Shiftsummary",80)
ShiftSummary.lines = [
        [SimpleText("    ========== Shift summary ==================") ],
        [],
        [QueryValue("Shift crew","Who was on shift?"),Dummy()],
        [QueryValue("Type", "Type of shift? (early,late,night)"),Dummy()],
        [],
        [SimpleText("==> Summary:")],
        [],
        [SimpleText("==> Data Taken:")],
        [QueryValue("Good files","How many good files?"),Dummy()],
        [QueryValue("Maybe files","How many maybe files?"),Dummy()],
        [QueryValue("Bad files","How many bad files?"),Dummy()],
        [QueryValue("Accumulated data","Enter sum over filesize of good/maybe files:"),Dummy()],
        [],
        [SimpleText("==> Problems"),Dummy(),Dummy()],
        [],
        [SimpleText("==> Things done during this shift:")],
        [],
        [SimpleText("==> Things to do / pending requests:")]
        ]

RunsetList = [Eta_4He, TaggEff, ShiftSummary ]

