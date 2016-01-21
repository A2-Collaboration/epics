dbLoadDatabase "/opt/epics/modules/streamdevice/dbd/streamApp.dbd"

streamApp_registerRecordDeviceDriver

epicsEnvSet "STREAM_PROTOCOL_PATH", "/opt/epics/iocs/rpi-beamtable/"

#drvAsynSerialPortConfigure ("BEAM:TABLE", "/dev/ttyUSB0")

drvAsynSerialPortConfigure ("BEAM:TABLE", "/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A9014YWT-if00-port0")


asynSetOption ("BEAM:TABLE", 0, "baud", "57600")
asynSetOption ("BEAM:TABLE", 0, "bits", "8")
asynSetOption ("BEAM:TABLE", 0, "parity", "none")
asynSetOption ("BEAM:TABLE", 0, "stop", "1")

dbLoadRecords "beamtable.db","PROTO=beamtable_serial.proto,DEV=BEAM:TABLE"

iocInit

#var streamDebug 1


