#!/usr/bin/python
# -*- coding: utf-8 -*-

from Typicals import Typical

from Typicals import AI
from Typicals import AO
from Typicals import DI
from Typicals import DO

#import DO
#import AI
#import AO
#import M
#import PID

from General import General

print("Starting")

general = General()


# todo: get this info from XML
general.Objects.addObject("LS_open", DI.DigitalInput("Open switch",1,1))
general.Objects.addObject("LS_closed", DI.DigitalInput("Close switch",1,6))
general.Objects.addObject("button", DI.DigitalInput("Button",1,11))

general.Objects.addObject("QT_light", AI.AnalogInput("Light sensor","%",6,11))
general.Objects.addObject("QT_light2", AI.AnalogInput("Light sensor","%",14,11))
general.Objects.addObject("QT_insideHumidity", AI.AnalogInput("Inside humidity","%r",6,1))
general.Objects.addObject("QT_outsideHumidity", AI.AnalogInput("Outside humidity","%r",6,6))
general.Objects.addObject("TT_inside", AI.AnalogInput("Inside temperature","°C",14,1))
general.Objects.addObject("TT_outside", AI.AnalogInput("Outside temperature","°C",14,6))
general.Objects.addObject("PT_atmosphere", AI.AnalogInput("Pressure","mbar",22,1))
general.Objects.addObject("TT_atmosphere", AI.AnalogInput("Temperature","°C",22,6))
general.Objects.addObject("TT_heatingPad", AI.AnalogInput("Heat sensor","°C",6,16))

#general.Objects.addObject("M_hatch", M.Motor("Hatch motor",22,11))

general.Objects.addObject("M_evacuator", DO.DigitalOutput("Evacuator",30,1))
general.Objects.addObject("M_agitator", DO.DigitalOutput("Agitator",30,6))

general.Objects.addObject("X_heatingPad", AO.AnalogOutput("Heating pad","%",22,16))

#general.Objects.addObject("TC_heatingPad", PID.PIDController("Heat controller","°C",14,16))

general.start()

