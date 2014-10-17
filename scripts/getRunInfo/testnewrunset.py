#!/usr/bin/ipython

from runset import NewRunSet,SimpleText,EpicsEntry,StaticValue
import sys
import os

#termwidth = os.popen('stty size', 'r').read().split()[1]

command = ["load", "default"]

theRunset = NewRunSet("ETAPRIME")

theRunset.lines = [
              [SimpleText("=======================") ],
              [StaticValue("name1","val1") , StaticValue("nam2","v2")],
              [EpicsEntry("Faraday","BEAM:FaradayCup","nA",1./1000), EpicsEntry("Faraday","BEAM:FaradayCup","nA",1.0/1000),EpicsEntry("Faraday","BEAM:FaradayCup","nA")]
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
            theRunset.Update()
            Clear()
            theRunset.Print()
        else:
            print
            print("       load proper runset!")
            print
            command = ["list"]
            continue

    elif not command[0].find("fast"):
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

    #elif not command[0].find("list"):
        #list_runsets()

    #elif not command[0].find("elog"):
        #theRunset.GenElog()
    
    #elif not command[0].find("load"):
        #if len(command) == 2:
            #theRunset = load_runset(command[1])
            #if not theRunset:
                #command = ["list"]
                #continue
            #else:
                #Clear()
                #theRunset.PrintLines()
        #else:
            #Clear()
            #print
            #print("       provide exactly 1 runset!")
            #print
    
    else:
        Clear()
        print
        print("       Unknown command")
        print

    command = command_prompt();
