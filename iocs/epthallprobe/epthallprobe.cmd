dbLoadDatabase "/opt/epics/modules/streamdevice/dbd/streamApp.dbd"

streamApp_registerRecordDeviceDriver

epicsEnvSet "STREAM_PROTOCOL_PATH", "/opt/epics/iocs/epthallprobe/"

drvAsynIPPortConfigure ("TAGG:EPT", "x2s0.office.a2.kph:1337")

dbLoadRecords "epthallprobe.db","PROTO=epthallprobe_serial.proto,DEV=TAGG:EPT"

iocInit

#var streamDebug 1
