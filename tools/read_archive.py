#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

import MySQLdb as mdb

import pylab as plt
import datetime

class ArchiveReader:
    host="slowcontrol.online.a2.kph"
    user="report"
    passwd="$report"
    db="archive"
    con=0

    def __del__(self):
        if self.con:
            self.con.close()
    
    def Connect(self):
        try:
            self.con = mdb.connect(self.host, self.user, self.passwd, self.db)
        except mdb.Error, e:
            print "Error %d: %s" % (e.args[0],e.args[1])
            self.con=0

    def isConnected(self):
        return (self.con!=0)
    
    def GetPVIndex(self, PV):
        
        if( not self.isConnected()):
            return

        cur = self.con.cursor()
        cur.execute("SELECT channel_id FROM channel WHERE name=\"" + PV + "\"")
        rows = cur.fetchone();

        if( not rows or len(rows) == 0 ):
            sys.stderr.write(PV + " is not in database.\n")
            return -1

        return rows[0]

    def Fetch(self, PV, start=0, stop=0):
        
        if( not self.isConnected()):
            return 0

        id=self.GetPVIndex(PV)
        if( id == -1 ):
            return []

        cur = self.con.cursor()
        
        query="SELECT smpl_time, float_val FROM sample WHERE channel_id=" + str(id)

        if(start!=0):
            query+=" AND smpl_time > \'" + start + "\'"
        if(stop!=0):
            query+=" AND smpl_time < \'" + stop + "\'"
        
        query+=" ORDER BY smpl_time"

        cur.execute(query)
        rows = cur.fetchall()

        cur.close()

        return rows

        
    def Dump(self, PV, start=0, stop=0):
        self.DumpRows(self.Fetch(PV, start, stop))

    def DumpRows(self, rows):
        for row in rows:
            print row[0], row[1]

    def PlotRows(self, rows, name, filename=""):
        plt.plot([row[0] for row in rows], [row[1] for row in rows])
        plt.title(name)
        plt.xlabel("Time")
        plt.grid(True)

        if( filename ):
            print "Save to " + filename + "\n"
            plt.savefig(filename)
        else:
            plt.show()

    def Plot(self, PV, start=0, stop=0, filename=""):
        self.PlotRows(self.Fetch(PV,start,stop),PV, filename)



if len(sys.argv) < 5:
    sys.stderr.write('Usage: ' + sys.argv[0] + ' <PV> <plot|dump> "start" "stop"\n')
    sys.exit(1)

arch=ArchiveReader()
arch.Connect()

pv = sys.argv[1]
cmd = sys.argv[2]
start = sys.argv[3]
stop = sys.argv[4]

if( cmd == "plot" ):
    arch.Plot(pv, start, stop)
elif( cmd == "dump" ):
    arch.Dump(pv, start, stop)
elif( cmd == "plotsave" ):
    filename = pv+" "+start+ " "+stop+".png"
    filename = filename.replace(":","-")
    filename = filename.replace(" ","_")
    #filename="a.png"
    arch.Plot(pv, start, stop, filename)
else:
    sys.stderr.write("Invalid command: " + sys.argv[2] + "\n")
    sys.exit(1)
