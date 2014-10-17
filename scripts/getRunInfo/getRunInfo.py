#!/usr/bin/python

from epics import caget
import sys
import runset
from runset import RunSet
from configobj import ConfigObj

#configfile = "/home/a2cb/scripts/getRunInfo/runsets.cfg"
configfile = "runsets.cfg"

command = ["load", "default"]

#theRunset = RunSet(configfile,'default')

def Clear():
    sys.stderr.write("\x1b[2J\x1b[H")


def GenMessage():
    msg = [""]
    msg.append("")
    if  theRunset:
        msg.append("========= STATUS for experiment:  " + theRunset.Exp +  " ===================")
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

def list_runsets():
    cfg = ConfigObj(configfile)
    #Clear()
    print 
    for line in cfg.sections:
        print line
    print

def load_runset(runsetstr):
    cfg = ConfigObj(configfile)
    if cfg.sections.count(runsetstr) == 0:
        print
        print("     Runset does not exist")
        print
        return False
    if cfg.sections.count(runsetstr) > 1:
        print
        print("     More than one config for runset " + runsetstr)
        print
        return False
    else:
         return RunSet(configfile,runsetstr)

Clear()
#theRunset.PrintLines()

while ( True):


    if not command:
        if theRunset:
            theRunset.Update()
            Clear()
            theRunset.PrintLines()
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
            theRunset.PrintLines()
        else:
            print
            print("       load proper runset!")
            print
            command = ["list"]
            continue

    elif not command[0].find("quit"):
        break

    elif not command[0].find("list"):
        list_runsets()

    elif not command[0].find("elog"):
        theRunset.GenElog()
    
    elif not command[0].find("load"):
        if len(command) == 2:
            theRunset = load_runset(command[1])
            if not theRunset:
                command = ["list"]
                continue
            else:
                Clear()
                theRunset.PrintLines()
        else:
            Clear()
            print
            print("       provide exactly 1 runset!")
            print
    
    else:
        Clear()
        print
        print("       Unknown command")
        print

    command = command_prompt();
