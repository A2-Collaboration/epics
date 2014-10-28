from lib.runset import NewRunSet,SimpleText,EpicsEntry,StaticValue,Dummy,EpicsMnp,QueryValue,YesNoValue


EtaPrime = NewRunSet("Etaprime",80)
EtaPrime.lines = [
       [SimpleText("Run XXX - Start: XX:XX End: XX:XX") ],
       [],
       [StaticValue("Energy","1604 MeV") , StaticValue("Set-Current","60 nA"), StaticValue("Radiator","10 mu copper")],
       [StaticValue("Collimator","4 mm") , StaticValue("Target","Hydrogen"), StaticValue("Trigger","CB Esum>550MeV")],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("EPT OR","TAGG:EPT:Sector0:TRIG:OR","MHz",1.0/1000000),Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000) , EpicsEntry("Ladder /P2","TAGG:EPT:LadderP2Ratio","",1.0),Dummy()],
       [EpicsEntry("Interrupt","TRIG:Trigger","kHz",1./1000), EpicsEntry("Livetime","TRIG:TotalLivetime","%",1.0),Dummy()],
       [EpicsEntry("TPAS CFD","TAPS:BAF:TRIG:CFD:OR","kHz",1./1000), EpicsEntry("TAPS LED1","TAPS:BAF:TRIG:LED1:OR","kHz",1.0/1000),Dummy()],
       [],
       [EpicsEntry("CB ESum","CB:CB:TRIG:ESum_Low","kHz",1./1000), EpicsEntry("Fast Clear","TRIG:FastClear","kHz",1.0/1000),EpicsMnp()],
       [Dummy(),Dummy(),EpicsEntry("M1","TRIG:MULT:M1","kHz",1.0/1000)],
       [Dummy(),Dummy(),EpicsEntry("M2","TRIG:MULT:M2","kHz",1.0/1000)],
       [Dummy(),Dummy(),EpicsEntry("M3","TRIG:MULT:M3","kHz",1.0/1000)],
       [Dummy(),Dummy(),EpicsEntry("M4","TRIG:MULT:M4","kHz",1.0/1000)],
       [Dummy(),Dummy(),EpicsEntry("M5","TRIG:MULT:M5","kHz",1.0/1000)],
       [Dummy(),Dummy(),EpicsEntry("M6","TRIG:MULT:M6","kHz",1.0/1000)],
       [Dummy(),Dummy(),EpicsEntry("M7","TRIG:MULT:M7","kHz",1.0/1000)],
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
       [SimpleText("     ========== Tagging Efficency Run ==========")],
       [],
       [StaticValue("Energy","1604 MeV") , StaticValue("Set-Current","00 nA"), StaticValue("Radiator","10 mu copper")],
       [StaticValue("Collimator","4 mm") , StaticValue("Target","Hydrogen"),   StaticValue("Trigger","CB Esum>550MeV")],
       [],
       [EpicsEntry("P2 Rate","BEAM:IonChamber","kHz",1./1000), EpicsEntry("EPT OR","TAGG:EPT:Sector0:TRIG:OR","MHz",1.0/1000000), Dummy()],
       [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000),  EpicsEntry("Ladder /P2","TAGG:EPT:LadderP2Ratio","",1.0),          Dummy()],
       [Dummy(),                                               EpicsEntry("LEAD Glass","BEAM:PBGlass","kHz",1.0/1000),            Dummy()],
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
        [SimpleText("========= Shift summary ===============") ],
        [],
        [QueryValue("Shift crew","Who was on shift?"),Dummy()],
        [QueryValue("Type", "Type of shift? (early,day,night)"),Dummy()],
        [],
        [SimpleText("==> Summary:")],
        [],
        [YesNoValue("==> Problems","Any problems during Your shift?","","none"),Dummy(),Dummy()],
        [],
        [SimpleText("==> Data Taken:")],
        [QueryValue("Good files","How many good files?"),Dummy()],
        [QueryValue("Bad files","How many bad files?"),Dummy()],
        [QueryValue("Accumulated data","Enter sum over filesize of good files:"),Dummy()],
        [],
        [SimpleText("==> Notes:")]
        ]

RunsetList = [ EtaPrime , EtaPrimeTaggeff, ShiftSummary ]
