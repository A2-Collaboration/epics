from epics import caget, PV
import os
from sys import stdout
from configobj import ConfigObj
from time import sleep

def indentPrint(a):
    print("  " + a)

class SimpleText:
    def __init__(self,Text):
        self.text = Text
    def GetStr(self,width):
        fmtstr = "{:<"+str(width)+"}"
        return fmtstr.format(self.text)


class Dummy:
    def GetStr(self,width):
        return " " * width

class StaticValue:
    def __init__(self, EntryName, Value):
        self.name = EntryName
        self.value = Value

    def GetValue(self):
        return self.value

    def GetStr(self,width):
        halfw = int(width/2)
        fmtstr = "{:<"+str(halfw - 1)+"} {:<"+str(halfw -1)+"}"
        return fmtstr.format(self.name+":",self.value)

class QueryValue(StaticValue):
    def __init__(self,Text,Question, initialValue=""):
        self.name = Text
        self.question = Question
        self.value = initialValue

class YesNoValue(StaticValue):
    def __init__(self,Text,Question, YesText="True", NoText="False"):
        self.name = Text
        self.question = Question
        self.value = False
        self.yes = YesText
        self.no = NoText
    def GetStr(self,width):
        halfw = int(width/2)
        fmtstr = "{:<"+str(halfw - 1)+"} {:<"+str(halfw -1)+"}"
        vstr = self.yes
        if not self.value: vstr = self.no
        return fmtstr.format(self.name+":",vstr)

class EpicsEntry:
    def __init__(self, EntryName, EpicsRecord, Unit = "", Scale = 1.0):
        self.name = EntryName
        self.record = PV(EpicsRecord)
        self.value = self.updatefn()
        self.unit = Unit
        self.scale = Scale

    def getAlarm(self):
        if self.record.connected:
            return self.record.severity
        return 3

    def updatefn(self):
        if self.record.connected:
            return self.record.get()
        return float('nan')

    def GetValue(self):
        return self.value

    def GetStr(self,width):
        halfw = int(width/2)
        fmtstr = "{:<"+str(halfw - 1)+"} {:>"+str(halfw -5)+".2f} {:<4}"
        if self.getAlarm() == 3:
            return self.name+":  not connected"
        return fmtstr.format(self.name+":",self.value * self.scale,self.unit)

def mnpget(mult):
    mnp = 0
    for pv in [ "TRIG:MULT:M"+str(m+mult) for m in range(8-mult) ]:
       mnp = mnp + caget(pv)
    return mnp

class EpicsMnp(EpicsEntry):
    def __init__(self,Multiplicity = 1):
        self.name = "M" + str(Multiplicity) + "+"
        self.mult = Multiplicity
        self.value = self.updatefn()
        self.unit = "kHz"
        self.scale = 1.0/1000

    def updatefn(self):
        mnp = 0
        for pv in [ "TRIG:MULT:M"+str(m+self.mult) for m in range(8-self.mult) ]:
           mnp = mnp + caget(pv)
        return mnp
        
    # quick fix...
    def getAlarm(self):
        return 0

    def GetValue(self):
        return self.value

    def GetStr(self,width):
        halfw = int(width/2)
        fmtstr = "{:<"+str(halfw - 1)+"} {:>"+str(halfw -5)+".2f} {:<4}"
        return fmtstr.format(self.name+":",self.value * self.scale,self.unit)

class NewRunSet:
    def __init__(self, Name,  LineWidth = 80):
        self.width = LineWidth
        self.name = Name
        self.lines = []

    def Update(self,numIt = 10):
        print
        print
        print("      Update in progress, taking " + str(numIt) + " samples.")
        print
        stdout.write("Found ")
        numepicsrecs = 0
        for line in self.lines:
            for entry in line:
                if isinstance(entry,EpicsEntry):
                    entry.value = 0
                    numepicsrecs+=1
        stdout.write(str(numepicsrecs))
        stdout.write(" records. Now averaging...     ")
        stdout.flush()
        for i in range(numIt):
            for line in self.lines:
                for entry in line:
                    if isinstance(entry,EpicsEntry):
                        entry.value = entry.value + entry.updatefn()
            stdout.write('#')
            stdout.flush()
            sleep(0.5)
            

        
        for line in self.lines:
            for entry in line:
                if isinstance(entry,EpicsEntry):
                    entry.value = entry.value * 1.0 / numIt

    def formatprint(self,line):
        outstring = ""
        if line:
            columnWidth = int(self.width / len(line))
            for entry in line:
                outstring = outstring + entry.GetStr(columnWidth)
        return outstring


    def Print(self):
        for line in self.lines:
            print(self.formatprint(line))
            #self.formatprint(line)




# ==================== OLD STUFF ======================================================

class RunSet:

    def __init__(self, configFileName, section):

        cfg = ConfigObj(configFileName)

        self.Exp        = cfg[section]['Experiment']
        self.Energy     = cfg[section]['Energy']
        self.Target     = cfg[section]['Target']
        self.Collimator = cfg[section]['Collimator']
        self.Trigger    = cfg[section]['Trigger']
        self.Radiator   = cfg[section]['Radiator']
        self.Plane      = cfg[section]['Plane']
        self.Edge       = cfg[section]['Edge']
        self.Author     = cfg[section]['Authors']
        self.LogGroups  = self.GenLGList(cfg[section]['LogGroups'])

    def GenLGList(self,logList):
        theList = []
        for cfgstr in logList:
            if cfgstr.find("TriggerTaggTAPS") == 0:
                theList.append(TriggerTaggTAPS())
            elif cfgstr.find("Line:") == 0:
                theList.append(CustomLine(cfgstr.replace("Line:","")))
            elif cfgstr.find("CB:") == 0:
                theList.append(CB(int(cfgstr.replace("CB:",""))))
            elif cfgstr.find("H2Target") == 0:
                theList.append(H2Target())
            elif cfgstr.find("TaggEff") == 0:
                theList.append(TaggEff())
            elif cfgstr.find("TaggEffBkg1") == 0:
                theList.append(TaggEffBkg1())
            elif cfgstr.find("TaggEffBkg2") == 0:
                theList.append(TaggEffBkg2())
            else:
                theList.append(CustomLine("CHECK CONFIGFILE in section LogGroups"))
        return theList

    def GenElog(self):
        elog_cmd = "echo '" + "\n".join(self.GenLogText()) + "' | "
        elog_cmd = elog_cmd + "/opt/elog/bin/elog -h elog.office.a2.kph -u a2online a2messung "
        elog_cmd = elog_cmd + "-l 'Main Group Logbook' -a Experiment='" + self.Exp + "' "
        elog_cmd = elog_cmd + "-a Author='" + self.Author + "' -a Type=Routine "
        elog_cmd = elog_cmd + "-a Subject='Run XXXX'"
        if os.system(elog_cmd) == 0:
            print
            print(" ======  Elog entry generated.  ====== ")
            print("|                                     |")
            print("| FILL IN NAMES, TIMES AND RUN-NUMBER |")
            print("|                                     |")
            print("|          CHECK VALUES!!             |")
            print(" ===================================== ")
            print
        return elog_cmd


    def Update(self,numit=10):
        for lg in self.LogGroups:
            lg.Update(numit)

    def Preable(self):
        lines = [""]
        lines.append("Run XXX - Start: XX:XX End: XX:XX")

        lines.append("")

        lines.append("Energy: {:<8}      Current: {:>8.2f} nA  Radiator: {:<8}".format(self.Energy,caget("BEAM:FaradayCup")/1000,self.Radiator))
        lines.append("Collimator: {0:<8}  Target:  {1:>11}  Trigger:  {2:<8}".format(self.Collimator,self.Target,self.Trigger))
        lines.append("")
        return lines

    def GenLogText(self):
        lines = self.Preable()
        for lg in self.LogGroups:
            for line in lg.GenLines():
                lines.append(line)
        return lines

    def PrintLines(self):
        map(indentPrint,self.GenLogText())


class GenericLogGroup:
    
    PVs = ['']

    def __init__(self):
        self.Values = [ 0 for e in range(len(self.PVs)) ]
        self.Update()

    def GenLines(self):
        return [ "GENERIC LINE: IMPLEMNT FUNCTION!!!" ]

    def Update(self,numit = 10):
        if self.PVs != ['']:
            print
            print
            print("      Update in progress, taking " + str(numit) + " samples for:")
            print(self.PVs)
            for i in range(len(self.Values)):
                self.Values[i] = 0
            for iteration in range(numit):
                self.Values = [ self.Values[i] + caget(self.PVs[i]) for i in range(len(self.PVs)) ]
                sleep(0.3)
            self.Values = map(lambda x: x / numit, self.Values)




class TriggerTaggTAPS(GenericLogGroup):
    PVs = ["BEAM:IonChamber", "TAGG:EPT:Sector0:TRIG:OR", "BEAM:FaradayCup", "TAGG:EPT:LadderP2Ratio","TRIG:Trigger","TRIG:TotalLivetime","TAPS:BAF:TRIG:CFD:OR","TAPS:BAF:TRIG:LED1:OR"]

    def GenLines(self):
        formtstr = "{:<10} {:>8.2f} {:<3}  {:<12} {:>8.2f} {:<3}"
        lines = []
        lines.append(formtstr.format("P2 Rate:",   self.Values[0]/1000, "kHz", "EPT OR:" ,     self.Values[1]/1000000, "MHz"))
        lines.append(formtstr.format("Faraday:",   self.Values[2]/1000, "nA",  "Ladder / P2:", self.Values[3], ""))
        lines.append(formtstr.format("Interrupt:", self.Values[4]/1000, "kHz", "Livetime:",   self.Values[5], "%"))
        lines.append(formtstr.format("TAPS CFD:",  self.Values[6]/1000, "kHz", "TAPS LED1:",   self.Values[7]/1000, "kHz"))
        return lines


class CB(GenericLogGroup):
    PVs = ["CB:CB:TRIG:ESum_Low","TRIG:FastClear"]
    for pv in [ "TRIG:MULT:M"+str(m+1) for m in range(7) ]:
        PVs.append(pv)
    def __init__(self,mult):
        self.mult = mult
        self.Values = [ 0 for e in range(len(self.PVs)) ]
        self.Update()

    def GenLines(self):
        lines = []
        lines.append("{:<10} {:>8.2f} {:<3}  {:<12} {:>8.2f} {:<3}  {:<4} {:>8.2f} {:<3}".format("CB ESum:", self.Values[0]/1000,"kHz","Fast Clear:",self.Values[1]/1000,"kHz","M1+:",sum(self.Values,2)/1000,"kHz"))
        for m in range(self.mult):
            lines.append("{:<50}  {:<4} {:>8.2f} {:<3}".format("","M"+str(m+1)+":",self.Values[2+m]/1000,"kHz"))
        return lines

class MWPC(GenericLogGroup):
    PVs = [ "CB:MWPC:HV:CH1:VOLT:READ",
            "CB:MWPC:HV:CH2:VOLT:READ",
            "CB:MWPC:HV:CH1:CURR:READ",
            "CB:MWPC:HV:CH2:CURR:READ" ]

    def GenLines(self):
        lines = []
        lines.append("{:<6}    {:>6} V    {:>6} nA".format("MWPC1:", self.Values[0],self.Values[2]))
        lines.append("{:<6}    {:>6} V    {:>6} nA".format("MWPC2:",self.Values[1],self.Values[3]))
        return lines

class TaggEff(GenericLogGroup):
    PVs = [ "BEAM:PBGlass" ]

    def GenLines(self):
        lines = []
        lines.append("Tagging efficiency: Lead Glass: {:.3f} kHz".format(self.Values[0]/1000))
        return lines

class TaggEffBkg1(GenericLogGroup):
    PVs = [ "BEAM:PBGlass" ]

    def GenLines(self):
        lines = []
        lines.append("First background for tagging efficiency: Lead Glass: {:.3f} kHz".format(self.Values[0]/1000))
        return lines

class TaggEffBkg2(GenericLogGroup):
    PVs = [ "BEAM:PBGlass" ]

    def GenLines(self):
        lines = []
        lines.append("Second background for tagging efficiency: Lead Glass: {:.3f} kHz".format(self.Values[0]/1000))
        return lines

class H2Target(GenericLogGroup):
    PVs = [ "TARGET:H2:Tsi",
            "TARGET:H2:CLTS",
            "TARGET:H2:Pcible"
             ]
    def GenLines(self):
        lines = ["Hydrogen Target:"]
        lines.append("{:} {:>8} mbar".format("Pressure:", self.Values[2]))
        lines.append("{:<12} {:>10} {:>8} K    {:>12} {:>8} K".format(   "Temperatur:", "Target:", self.Values[0], "Liquifier:", self.Values[1]))

        return lines

class CustomLine(GenericLogGroup):

    def __init__(self,line):
        self.Values = [ 0 for e in range(len(self.PVs)) ]
        self.line = line
        self.Update()

    def GenLines(self):
        return [self.line]

