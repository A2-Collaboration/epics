dbLoadDatabase "/opt/epics/modules/stream/streamDevice/streamApp/O.Common/streamApp.dbd"

streamApp_registerRecordDeviceDriver

epicsEnvSet "STREAM_PROTOCOL_PATH", "/opt/epics/iocs/rpi-cherenkov/"

drvAsynSerialPortConfigure ("TAGG:EPT", "/dev/serial/by-id/usb-")
asynSetOption ("TAGG:EPT", 0, "baud", "9600")
asynSetOption ("TAGG:EPT", 0, "bits", "8")
asynSetOption ("TAGG:EPT", 0, "parity", "none")
asynSetOption ("TAGG:EPT", 0, "stop", "1")

dbLoadRecords "cherenkov.db","PROTO=cherenkov_serial.proto,DEV=CHERENKOV"

iocInit

#var streamDebug 1

