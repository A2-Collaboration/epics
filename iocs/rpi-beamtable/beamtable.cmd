dbLoadDatabase "/opt/epics/modules/streamdevice/dbd/streamApp.dbd"

streamApp_registerRecordDeviceDriver

epicsEnvSet "STREAM_PROTOCOL_PATH", "/opt/epics/iocs/rpi-beamtable/"

#drvAsynSerialPortConfigure ("BEAMTABLE", "/dev/ttyUSB0")

drvAsynSerialPortConfigure ("BEAMTABLE", "/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A9014YWT-if00-port0")


asynSetOption ("BEAMTABLE", 0, "baud", "57600")
asynSetOption ("BEAMTABLE", 0, "bits", "8")
asynSetOption ("BEAMTABLE", 0, "parity", "none")
asynSetOption ("BEAMTABLE", 0, "stop", "1")

dbLoadRecords "beamtable.db","PROTO=beamtable_serial.proto,DEV=BEAM:TABLE"

iocInit

#var streamDebug 1


