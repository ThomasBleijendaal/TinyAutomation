#!/usr/bin/python
# -*- coding: utf-8 -*-

import DI
import DO
import AI
import AO
import M
import PID

from General import General

print("Starting")

general = General()


# todo: get this info from XML
general.Objects.addObject("LS_open", DI.DigitalInput("Open switch",0,1,1))
general.Objects.addObject("LS_closed", DI.DigitalInput("Close switch",1,1,6))
general.Objects.addObject("button", DI.DigitalInput("Button",2,1,11))

general.Objects.addObject("QT_light", AI.AnalogInput("Light sensor","%",0,6,11))
general.Objects.addObject("QT_light2", AI.AnalogInput("Light sensor","%",1,14,11))
general.Objects.addObject("QT_insideHumidity", AI.AnalogInput("Inside humidity","%r",2,6,1))
general.Objects.addObject("QT_outsideHumidity", AI.AnalogInput("Outside humidity","%r",3,6,6))
general.Objects.addObject("TT_inside", AI.AnalogInput("Inside temperature","°C",4,14,1))
general.Objects.addObject("TT_outside", AI.AnalogInput("Outside temperature","°C",5,14,6))
general.Objects.addObject("PT_atmosphere", AI.AnalogInput("Pressure","mbar",6,22,1))
general.Objects.addObject("TT_atmosphere", AI.AnalogInput("Temperature","°C",7,22,6))
general.Objects.addObject("TT_heatingPad", AI.AnalogInput("Heat sensor","°C",8,6,16))

general.Objects.addObject("M_hatch", M.Motor("Hatch motor",0,22,11))

general.Objects.addObject("M_evacuator", DO.DigitalOutput("Evacuator",0,30,1))
general.Objects.addObject("M_agitator", DO.DigitalOutput("Agitator",1,30,6))

general.Objects.addObject("X_heatingPad", AO.AnalogOutput("Heating pad","%",0,22,16))

general.Objects.addObject("TC_heatingPad", PID.PIDController("Heat controller","°C",0,14,16))

general.start()

