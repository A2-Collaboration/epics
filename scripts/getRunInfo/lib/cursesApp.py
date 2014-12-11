from runset import NewRunSet,SimpleText,EpicsEntry,StaticValue,Dummy,EpicsMnp,QueryValue,YesNoValue

import curses
import traceback
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
        
        curses.start_color()
        curses.init_pair(1,curses.COLOR_RED,curses.COLOR_BLACK)
        curses.init_pair(2,curses.COLOR_RED,curses.COLOR_YELLOW)
        curses.init_pair(3,curses.COLOR_MAGENTA,curses.COLOR_BLACK)

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

    def Query(self,question):
        self.stdscr.erase()
        self.textWin.erase()
        self.osd.erase()
        self.refresh()
        qWin = curses.newwin( 4,
                              self.runsets[self.curRunset].width-4,
                              2,
                              2 )
        qWin.box()
        qWin.addstr(1,2,question)
        qWin.addstr(2,3," ==> ")
        self.stdscr.refresh()
        qWin.refresh()
        curses.echo()
        curses.curs_set(1)
        returnstr = qWin.getstr(2, 8)
        curses.noecho()
        curses.curs_set(0)
        del qWin
        self.refresh()

        return returnstr

    def QueryYESNO(self,question):
        self.stdscr.erase()
        self.textWin.erase()
        self.osd.erase()
        self.refresh()
        qWin = curses.newwin( 3,
                              self.runsets[self.curRunset].width-4,
                              2,
                              2 )
        qWin.box()
        qWin.addstr(1,2,question + " [ ")
        qWin.addstr("y",curses.A_BOLD)
        qWin.addstr(" / ")
        qWin.addstr("n",curses.A_BOLD)
        qWin.addstr(" ]")

        key = 0
        while key != ord('y') and key != ord('n'):
            key = qWin.getch()
            
        self.stdscr.refresh()
        qWin.refresh()
        del qWin
        self.refresh()
        return key==ord('y')


    def Update(self,numIt = 10):

        numepicsrecs = 0
        for line in self.runsets[self.curRunset].lines:
            for entry in line:
                if isinstance(entry,EpicsEntry):
                    entry.value = 0
                    numepicsrecs+=1
                if isinstance(entry,QueryValue):
                    entry.value = self.Query(entry.question)
                if isinstance(entry,YesNoValue):
                    entry.value = self.QueryYESNO(entry.question)

        self.osd.erase()
        self.osd.box()
        self.osd.addstr(0,2,"< Updating volatile entries >")
        self.osd.addstr(2,6,"Update in progress:") 
        self.textWin.erase()
        self.textWin.addstr(2,6," PLEASE WAIT ")
        self.refresh()
        self.osd.addstr(3,6,"Found " + str(numepicsrecs) + " records, taking " + str(numIt) + " samples.")
        self.osd.addstr(5,6,"Now averaging...      ")
        self.refresh()

        if numepicsrecs:
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
            if line:
                columnWidth = int( self.runsets[self.curRunset].width / len(line) )
                self.textWin.move(lnum,0)
                for entry in line:
                    #self.textWin.addstr(lnum,0,self.runsets[self.curRunset].formatprint(line))
                    if isinstance(entry,EpicsEntry):
                        self.textWin.addstr(entry.GetStr(columnWidth),curses.color_pair(entry.getAlarm())) 
                    else:
                        self.textWin.addstr(entry.GetStr(columnWidth),curses.color_pair(0))
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
        try:
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
        except:
            self.quit()
            traceback.print_exc()
