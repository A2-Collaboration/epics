from runset import NewRunSet,SimpleText,EpicsEntry,StaticValue,Dummy,EpicsMnp

import curses
from time import sleep

class NcApp:

    def initWins(self):
        sizeOsdy = 10
        if len(self.runsets) > sizeOsdy - 7:
            sizeOsdy = len(self.runsets) + 8

        self.textWin = curses.newwin(len(self.runsets[self.curRunset].lines)+1,
                                      self.runsets[self.curRunset].width+2,
                                      0,
                                      0 )

        self.osd = curses.newwin(sizeOsdy,
                                 self.textWin.getmaxyx()[1] -10,
                                 len(self.runsets[self.curRunset].lines) + 3,
                                 4 )
        self.stdscr.erase()

    def __init__(self,Runsets):
        #load runset
        self.runsets = Runsets
        self.curRunset = 0
        #init curses
        self.stdscr = curses.initscr()
        curses.noecho()
        curses.cbreak()
        curses.curs_set(0)
        self.stdscr.keypad(1)
        #Windows
        self.initWins()
        self.updateText()
        self.putOsdText()

    def quit(self):
        curses.nocbreak()
        curses.echo()
        self.stdscr.keypad(0)
        curses.endwin()
        curses.curs_set(1)

    def getkey(self):
        return self.stdscr.getkey()

    def Update(self,numIt = 10):
        self.osd.erase()
        self.osd.box()
        self.osd.addstr(0,2,"< Updating volatile entries >")
        self.osd.addstr(2,6,"Update in progress, taking " + str(numIt) + " samples.")
        self.textWin.erase()
        self.textWin.addstr(2,6," PLEASE WAIT ")
        self.refresh()

        numepicsrecs = 0
        for line in self.runsets[self.curRunset].lines:
            for entry in line:
                if isinstance(entry,EpicsEntry):
                    entry.value = 0
                    numepicsrecs+=1
        self.osd.addstr(3,6,"Found " + str(numepicsrecs) + " records.")
        self.osd.addstr(5,6,"Now averaging...      ")
        self.refresh()

        for i in range(numIt):
            for line in self.runsets[self.curRunset].lines:
                for entry in line:
                    if isinstance(entry,EpicsEntry):
                        entry.value = entry.value + entry.updatefn()
            self.osd.addstr("#")
            self.refresh()
            sleep(0.5)
        for line in self.runsets[self.curRunset].lines:
            for entry in line:
                if isinstance(entry,EpicsEntry):
                    entry.value = entry.value * 1.0 / numIt

    def updateText(self):
        self.Update()
        self.textWin.erase()

        lnum = 0
        for line in self.runsets[self.curRunset].lines:
            self.textWin.addstr(lnum,0,self.runsets[self.curRunset].formatprint(line))
            lnum+=1
        self.putOsdText()
        self.refresh()
        
    def putOsdText(self):
        self.osd.erase()
        self.osd.box()
        self.osd.addstr(0,2,"< Status for experiment:  " + self.runsets[self.curRunset].name + " >")
        self.osd.addstr(2,6,"Commands:")
        self.osd.addstr(4,16,"return",curses.A_BOLD)
        self.osd.addstr(5,16,"l",curses.A_BOLD)
        self.osd.addstr(7,16,"q",curses.A_BOLD)
        self.osd.addstr(4,24,"- refresh")
        self.osd.addstr(5,24,"- load a runset")
        self.osd.addstr(7,24,"- quit")
        self.refresh()

    def loadRunset(self):

        self.osd.erase()
        self.osd.box()
        self.osd.addstr(0,2,"< Choose runset >")
        self.osd.addstr(2,6,    "Available runsets:")
        for i in range(len(self.runsets)):
            self.osd.addstr(4+i,16,str(i),curses.A_BOLD)
            self.osd.addstr(4+i,24,"- "+self.runsets[i].name)
        self.osd.addstr(5+len(self.runsets),16,"q",curses.A_BOLD)
        self.osd.addstr(5+len(self.runsets),24,"- leave this menu")
        self.refresh()
        while True:
            key = self.stdscr.getkey()
            if key.isdigit():
                if int(key) in range(len(self.runsets)):
                    self.curRunset = int(key)
                    self.initWins()
                    self.updateText()
                    break
            if key == 'q':
                self.putOsdText()
                break
                


    def refresh(self):
        self.stdscr.refresh()
        self.textWin.refresh()
        self.osd.refresh()

    def mainLoop(self):
        while True:
            key = self.stdscr.getkey()

            if key == "\n":
                self.initWins()
                self.updateText()

            elif key == "l":
                self.loadRunset()

            elif key == "q":
                break
        self.quit()
