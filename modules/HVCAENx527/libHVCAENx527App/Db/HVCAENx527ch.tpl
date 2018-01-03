#
# Copyright Canadian Light Source, Inc.  All rights reserved.
#    - see licence.txt and licence_CAEN.txt for limitations on use.
#
# The following are for setting channel parameters
# in user space
#
record( stringout, "$(PSNAME):$(CHANNUM):name")
{
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) ChName")
}
record( ao, "$(PSNAME):$(CHANNUM):v0set")
{
	field( DESC, "Primary voltage setting")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) V0Set")
	field( PREC, "2")
}
record( ao, "$(PSNAME):$(CHANNUM):v1set")
{
	field( DESC, "Secondary voltage setting")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) V1Set")
	field( PREC, "2")
}
record( ao, "$(PSNAME):$(CHANNUM):i0set")
{
	field( DESC, "Primary current limit")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) I0Set")
}
record( ao, "$(PSNAME):$(CHANNUM):i1set")
{
	field( DESC, "Secondary current limit")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) I1Set")
}
record( ao, "$(PSNAME):$(CHANNUM):rampup")
{
	field( DESC, "Voltage ramp-up rate")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) RUp")
}
record( ao, "$(PSNAME):$(CHANNUM):rampdn")
{
	field( DESC, "Voltage ramp-down rate")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) RDWn")
}
record( ao, "$(PSNAME):$(CHANNUM):trip")
{
	field( DESC, "Trip timeout")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) Trip")
}
record( ao, "$(PSNAME):$(CHANNUM):svmax")
{
	field( DESC, "Software voltage limit")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) SVMax")
}
record( bo, "$(PSNAME):$(CHANNUM):pwonoff")
{
	field( DESC, "Power on/off")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) Pw")
	field( ZNAM, "Off")
	field( ONAM, "On")
}
record( bo, "$(PSNAME):$(CHANNUM):pwupmode")
{
	field( DESC, "Power-up mode")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) POn")
	field( ZNAM, "Disable")
	field( ONAM, "Enable")
}
record( bo, "$(PSNAME):$(CHANNUM):pwdnmode")
{
	field( DESC, "Power-down mode")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) PDwn")
	field( ZNAM, "KILL")
	field( ONAM, "Ramp")
}
record( longout, "$(PSNAME):$(CHANNUM):tripint")
{
	field( DESC, "Internal trip connections")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) TripInt")
}
record( longout, "$(PSNAME):$(CHANNUM):tripext")
{
	field( DESC, "External trip connections")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( OUT, "@$(CHADDR) TripExt")
}
#
# The following are for monitoring channel parameters (e.g. feedback)
# in user space
#
record( stringin, "$(PSNAME):$(CHANNUM):name:fbk")
{
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) ChName")
	field( SCAN, "Event")
	field( PINI, "1")
	field( VAL, "$(PSNAME):$(CHANNUM)")
}
record( ai, "$(PSNAME):$(CHANNUM):v0set:fbk")
{
	field( DESC, "Primary voltage setting")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) V0Set")
	field( SCAN, "Event")
	field( PREC, "2")
}
record( ai, "$(PSNAME):$(CHANNUM):v1set:fbk")
{
	field( DESC, "Secondary voltage setting")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) V1Set")
	field( SCAN, "Event")
	field( PREC, "2")
}
record( ai, "$(PSNAME):$(CHANNUM):i0set:fbk")
{
	field( DESC, "Primary current limit")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) I0Set")
	field( SCAN, "Event")
}
record( ai, "$(PSNAME):$(CHANNUM):i1set:fbk")
{
	field( DESC, "Secondary current limit")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) I1Set")
	field( SCAN, "Event")
}
record( ai, "$(PSNAME):$(CHANNUM):rampup:fbk")
{
	field( DESC, "Voltage ramp-up rate")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) RUp")
	field( SCAN, "Event")
}
record( ai, "$(PSNAME):$(CHANNUM):rampdn:fbk")
{
	field( DESC, "Voltage ramp-down rate")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) RDWn")
	field( SCAN, "Event")
}
record( ai, "$(PSNAME):$(CHANNUM):trip:fbk")
{
	field( DESC, "Trip timeout")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) Trip")
	field( SCAN, "Event")
}
record( ai, "$(PSNAME):$(CHANNUM):svmax:fbk")
{
	field( DESC, "Software voltage limit")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) SVMax")
	field( SCAN, "Event")
}
record( ai, "$(PSNAME):$(CHANNUM):vmon")
{
	field( DESC, "Measured voltage")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) VMon")
	field( SCAN, "Event")
	field( PREC, "2")
}
record( ai, "$(PSNAME):$(CHANNUM):imon")
{
	field( DESC, "Measured current")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) IMon")
	field( SCAN, "Event")
	field( HIGH, "90")
	field( HIHI, "100")
	field( HSV, "MINOR")
	field( HHSV, "MAJOR")
	field( PREC, "2")
}
record( ao, "$(PSNAME):$(CHANNUM):imon:warn")
{
	field( DTYP, "Raw Soft Channel")
	field( OMSL, "closed_loop")
	field( DOL, "$(PSNAME):$(CHANNUM):i0set:fbk CP")
	field( LINR, "LINEAR")
	field( ASLO, "0.90")
	field( PREC, "2")
	field( EGU, "uA")
	field( OUT, "$(PSNAME):$(CHANNUM):imon.HIGH PP")
}
record( ao, "$(PSNAME):$(CHANNUM):imon:alarm")
{
	field( DTYP, "Raw Soft Channel")
	field( OMSL, "closed_loop")
	field( DOL, "$(PSNAME):$(CHANNUM):i0set:fbk CP")
	field( LINR, "LINEAR")
	field( ASLO, "1")
	field( PREC, "2")
	field( EGU, "uA")
	field( OUT, "$(PSNAME):$(CHANNUM):imon.HIHI PP")
}
record( mbbi, "$(PSNAME):$(CHANNUM):status")
{
	field( DESC, "Status")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) Status")
	field( SCAN, "Event")
	field( ZRVL, "0")	field( ZRST, "Off")
	field( ONVL, "1")	field( ONST, "On")
	field( TWVL, "2")	field( TWST, "Ramping Up")
	field( THVL, "3")	field( THST, "Ramping Down")
	field( FRVL, "4")	field( FRST, "Over-Current")
	field( FVVL, "5")	field( FVST, "Over-Voltage")
	field( SXVL, "6")	field( SXST, "Under-Voltage")
	field( SVVL, "7")	field( SVST, "External Trip")
	field( EIVL, "8")	field( EIST, "Max V")
	field( NIVL, "9")	field( NIST, "Ext. Disable")
	field( TEVL, "10")	field( TEST, "Internal Trip")
	field( ELVL, "11")	field( ELST, "Calib. Error")
	field( TVVL, "12")	field( TVST, "Unplugged")
	field( ZRSV, "NO_ALARM")
	field( ONSV, "MINOR")
	field( TWSV, "MINOR")
	field( THSV, "MINOR")
	field( FRSV, "MAJOR")
	field( FVSV, "MAJOR")
	field( SXSV, "MAJOR")
	field( SVSV, "MAJOR")
	field( EISV, "MAJOR")
	field( NISV, "MAJOR")
	field( TESV, "MAJOR")
	field( ELSV, "MAJOR")
	field( TVSV, "MAJOR")
}
record( bi, "$(PSNAME):$(CHANNUM):pwonoff:fbk")
{
	field( DESC, "Power on/off")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) Pw")
	field( SCAN, "Event")
	field( ZNAM, "Off")
	field( ONAM, "On")
}
record( bi, "$(PSNAME):$(CHANNUM):pwupmode:fbk")
{
	field( DESC, "Power-up mode")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) POn")
	field( SCAN, "Event")
	field( ZNAM, "Disabled")
	field( ONAM, "Enabled")
}
record( bi, "$(PSNAME):$(CHANNUM):pwdnmode:fbk")
{
	field( DESC, "Power-down mode")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) PDwn")
	field( SCAN, "Event")
	field( ZNAM, "KILL")
	field( ONAM, "Ramp")
}
record( longin, "$(PSNAME):$(CHANNUM):tripint:fbk")
{
	field( DESC, "Internal trip connections")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) TripInt")
	field( SCAN, "Event")
}
record( longin, "$(PSNAME):$(CHANNUM):tripext:fbk")
{
	field( DESC, "External trip connections")
	field( DTYP, "CAEN x527 generic HV Channel")
	field( INP, "@$(CHADDR) TripExt")
	field( SCAN, "Event")
}
#
# The following are for higher level operations on channel parameters
#
# RU! at initialization, the calc record sends a zero to the v0set
# Initialize all setpoints to the crate values to fix this
record( bo, "$(PSNAME):$(CHANNUM):v0set:up")
{
	field( OUT, "$(PSNAME):$(CHANNUM):v0set:calc PP")
	field( PINI, "1")
	field( VAL, "0")
}
record( bo, "$(PSNAME):$(CHANNUM):v0set:dn")
{
	field( OUT, "$(PSNAME):$(CHANNUM):v0set:calc PP")
	field( PINI, "1")
	field( VAL, "0")
}
record( ao, "$(PSNAME):$(CHANNUM):v0set:deltav")
{
	field( PINI, "1")
	field( VAL, "5")
	field( PREC, "2")
	field( EGU, "V")
}
#record( calc, "$(PSNAME):$(CHANNUM):v0set:calc")
#{
#	field( INPA, "$(PSNAME):$(CHANNUM):v0set")
#	field( INPB, "$(PSNAME):$(CHANNUM):v0set:up")
#	field( INPC, "$(PSNAME):$(CHANNUM):v0set:dn")
#	field( INPD, "$(PSNAME):$(CHANNUM):v0set:deltav")
#	field( CALC, "A+D*(B-C)")
#	field( FLNK, "$(PSNAME):$(CHANNUM):v0set:fwd")
#}
#record( ao, "$(PSNAME):$(CHANNUM):v0set:fwd")
#{
#	field( OMSL, "closed_loop")
#	field( DOL, "$(PSNAME):$(CHANNUM):v0set:calc")
#	field( OUT, "$(PSNAME):$(CHANNUM):v0set PP")
#}
record( calcout, "$(PSNAME):$(CHANNUM):v0set:calc")
{
	#field( OOPT, "On Change")
	field( INPA, "$(PSNAME):$(CHANNUM):v0set")
	field( INPB, "$(PSNAME):$(CHANNUM):v0set:up")
	field( INPC, "$(PSNAME):$(CHANNUM):v0set:dn")
	field( INPD, "$(PSNAME):$(CHANNUM):v0set:deltav")
	field( CALC, "A+D*(B-C)")
	field( OUT, "$(PSNAME):$(CHANNUM):v0set PP")
	field( PREC, "2")
}
