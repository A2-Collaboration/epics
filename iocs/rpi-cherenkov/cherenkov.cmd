dbLoadDatabase "/opt/epics/modules/streamdevice/dbd/streamApp.dbd"

streamApp_registerRecordDeviceDriver

epicsEnvSet "STREAM_PROTOCOL_PATH", "/opt/epics/iocs/rpi-cherenkov/"

#drvAsynSerialPortConfigure ("CHERENKOV", "/dev/ttyUSB0")

drvAsynSerialPortConfigure ("CHERENKOV", "/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A103R38C-if00-port0")


asynSetOption ("CHERENKOV", 0, "baud", "38400")
asynSetOption ("CHERENKOV", 0, "bits", "8")
asynSetOption ("CHERENKOV", 0, "parity", "none")
asynSetOption ("CHERENKOV", 0, "stop", "1")

dbLoadRecords "cherenkov.db","PROTO=cherenkov_serial.proto,DEV=CHERENKOV"

iocInit

#var streamDebug 1


