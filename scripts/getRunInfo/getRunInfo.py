#!/usr/bin/python

from lib.cursesApp import NcApp
from defaults import RunsetList


nc = NcApp(RunsetList)

nc.mainLoop()
