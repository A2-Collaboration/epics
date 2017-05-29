#-----------------------------------------------------------------------------
#
#          *** libRootEzca.so a root shared lib for ezca  ***
#
#	Ken Livingston	 5th Oct 2012	1st version
#
#----------------------------------------------------------------------------
#
#
#
#OS_NAME     := $(shell ./Uname)
EPICS_HOST_ARCH      = linux-x86_64
OS_NAME      = $(EPICS_HOST_ARCH)
DIRS	    := $(mkdir -p bin/$(OS_NAME) lib/$(OS_NAME)) 
# Directories
IR = $(ROOTSYS)/include
O = obj/$(OS_NAME)
B = bin/$(OS_NAME)
L = lib/$(OS_NAME)
EZCA = src

# ROOT libraries etc.
ROOTLIBS     := $(shell root-config --glibs) -lEG
#-lGuiBld -lGuiHtml -lGX11 -lGX11TTF
ROOTCFLAGS   := $(shell root-config --cflags)
#
# Compile/Link Flags
# Remember there is an alias makedeb which turns on debug mode
#
CCCOMP     = g++
CXXFLAGS  =  -Wall -fPIC -I. $(ROOTCFLAGS)
LDXXFLAGS =  -shared -o $L/$@

EPICSSO = libRootEzca.so
EZCALIBS = -L$(EPICS_BASE)/lib/$(EPICS_HOST_ARCH) -L$(EPICS_EXTENSIONS)/lib/$(EPICS_HOST_ARCH) -lca -lCom -lezca
EZCAINC = -I$(EZCA) -I$(EPICS_BASE)/include -I$(EPICS_BASE)/include/os/Linux -I$(EPICS_BASE)/include/compiler/gcc -I$(EPICS_EXTENSIONS)/src/ezca
EPICSFLAGS = -DACQUROOT_EPICS $(EZCAINC)
EPICSLIB = -L$(L) -lRootEzca

#
#-----------------------------------------------------------------------------
#
#	Do the whole lot
#
all: libRootEzca.so
##This is to build the ROOT shared library for EPICS 

libRootEzca.so:  dirs $(EZCA)/ezcaRootDict.cc $(O)/ezcaRoot.o $(O)/ezcaRootDict.o 
	$(CCCOMP) $(LDXXFLAGS) $(EZCALIBS) $(O)/ezcaRoot.o $(O)/ezcaRootDict.o
	@echo "$@ done"
	@echo "##-----------------------------------------------------------"

$(EZCA)/ezcaRootDict.cc: $(EZCA)/ezcaRoot.h $(EZCA)/ezcaRootLinkDef.h
	@echo "Generating dictionary $@..."
	@rootcint  -f $@ -c $^
	@echo "##-----------------------------------------------------------"

$(O)/ezcaRoot.o: $(EZCA)/ezcaRoot.cc  
	$(CCCOMP) $(CXXFLAGS) $(EZCAINC) $(INCFLAGS) -o $@ -c $<

$(O)/ezcaRootDict.o: $(EZCA)/ezcaRootDict.cc  
	$(CCCOMP) $(CXXFLAGS) $(EZCAINC) $(INCFLAGS) -o $@ -c $<

dirs:   
	mkdir -p obj/$(OS_NAME) bin/$(OS_NAME) lib/$(OS_NAME)

clean: 
	rm  -f obj/$(OS_NAME)/* bin/$(OS_NAME)/* lib/$(OS_NAME)/libRootEzca.so src/ezcaRootDict.cc src/ezcaRootDict.h

%.o: %.cc
	$(CCCOMP) $(CXXFLAGS) $(EPICSFLAGS) $(INCFLAGS) $(CAENVME_COMP) -o $(O)/$@ -c $< 

