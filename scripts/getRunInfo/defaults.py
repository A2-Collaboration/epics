from lib.runset import NewRunSet,SimpleText,EpicsEntry,StaticValue,Dummy,EpicsMnp,QueryValue,YesNoValue,Time


EtaPrime = NewRunSet("Etaprime",80)
EtaPrime.lines = [
       [SimpleText("Run XXX - Start: XX:XX End: XX:XX"),Dummy(),Time() ],
       [],
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
       [SimpleText("Run XXX - Start: XX:XX End: XX:XX"),Dummy(),Time() ],
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
        [QueryValue("Bad files","How many bad files?"),Dummy()],
        [QueryValue("Accumulated data","Enter sum over filesize of good files:"),Dummy()],
        [],
        [SimpleText("==> Problems"),Dummy(),Dummy()],
        [],
        [SimpleText("==> Things done during this shift:")],
        [],
        [SimpleText("==> Things to do / pending requests:")]
        ]

RunsetList = [ EtaPrime , EtaPrimeTaggeff, ShiftSummary ]
