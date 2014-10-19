#!/usr/bin/ipython

import defaults
import sys
import os

#termwidth = os.popen('stty size', 'r').read().split()[1]

command = []

theRunset = defaults.EtaPrime


def Clear():
    sys.stderr.write("\x1b[2J\x1b[H")

def GenMessage():
    msg = [""]
    msg.append("")
    if  theRunset:
        msg.append("========= STATUS for experiment:  " + theRunset.name +  " ===================")
    msg.append("")
    msg.append("  Commands: load <number> - load runset")
    msg.append("            list          - list available runsets")
    msg.append("            quit          - exit programm...")
    #msg.append("            elog          - generate elog entry")
    msg.append("")
    return msg

def command_prompt():
    for l in GenMessage():
        print(l)
    return raw_input("Hit Return to refresh or type a command.   >> ").split()

Clear()
#theRunset.PrintLines()

while ( True):


    if not command:
        if theRunset:
            Clear()
            theRunset.Update()
            Clear()
            theRunset.Print()
        else:
            print
            print("       load proper runset!")
            print
            command = ["list"]
            continue

    elif not command[0].find("list"):
        print
        print "Available Runsets:"
        print
        for rsnum in range(len(defaults.RunsetList)):
            print("  " + str(rsnum) + ":   " +defaults.RunsetList[rsnum].name)

    elif not command[0].find("load"):
        if len(command) == 2:
            if command[1].isdigit():
                rsnum = int(command[1]) 
                if range(len(defaults.RunsetList)).count(rsnum):
                    theRunset = defaults.RunsetList[int(command[1])]
                    theRunset.Update()
                    Clear()
                    theRunset.Print()
                else:
                    print
                    print "          Runset does not exist"
                    print
                    command = ["list"]
                    continue
            else:
                print
                print "          Provide runset by number"
                print
                command = ["list"]
                continue
        else:
            print
            print "          Provide exactly one rumset number"
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
