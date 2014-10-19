#!/usr/bin/ipython

from runset import NewRunSet,SimpleText,EpicsEntry,StaticValue,Dummy,EpicsMnp
import sys
import os

#termwidth = os.popen('stty size', 'r').read().split()[1]

command = ["load", "default"]

theRunset = NewRunSet("ETAPRIME",80)

theRunset.lines = [
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
              [SimpleText("Taps Fan failure status: <check crate!>") ]
            ]

def Clear():
    sys.stderr.write("\x1b[2J\x1b[H")

def GenMessage():
    msg = [""]
    msg.append("")
    #if  theRunset:
        #msg.append("========= STATUS for experiment:  " + theRunset.Exp +  " ===================")
    msg.append("========= STATUS for experiment   ===================")
    msg.append("")
    msg.append("  Commands: load <runset> - load runset from configfile")
    msg.append("            list          - list available runsets")
    msg.append("            elog          - generate elog entry")
    msg.append("")
    return msg

def command_prompt():
    for l in GenMessage():
        print(l)
    return raw_input("Hit Return to refresh or type 'quit'...   >> ").split()

Clear()
#theRunset.PrintLines()

while ( True):


    if not command:
        if theRunset:
            theRunset.Update(1)
            Clear()
            theRunset.Print()
        else:
            print
            print("       load proper runset!")
            print
            command = ["list"]
            continue


    elif not command[0].find("quit"):
        break
    
    else:
        Clear()
        print
        print("       Unknown command")
        print

    command = command_prompt();
