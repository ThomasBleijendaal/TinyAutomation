#!/usr/bin/python
# -*- coding: utf-8 -*-

import DI
import DO
import AI
import AO
import M
import PID

import serial
import time
import struct

import General

from tkinter import *

print("Starting")

ser = serial.Serial('COM3', 115200)

objectType = 0

master = Tk()
w = Canvas(master, width=1280, height=720)
w.pack()

ObjectHandler = General.ObjectHandler

ObjectHandler.addObject("LS_open", DI.DigitalInput("Open switch",0,1,1))
ObjectHandler.LS_open.draw(w)


LS_open = DI.DigitalInput("Open switch",0,1,1)
LS_closed = DI.DigitalInput("Close switch",1,1,6)
button = DI.DigitalInput("Button",2,1,11)

QT_insideHumidity = AI.AnalogInput("Inside humidity","%r",0,6,1)
QT_outsideHumidity = AI.AnalogInput("Outside humidity","%r",1,6,6)
TT_inside = AI.AnalogInput("Inside temperature","°C",2,14,1)
TT_outside = AI.AnalogInput("Outside temperature","°C",3,14,6)
PT_atmosphere = AI.AnalogInput("Pressure","mbar",4,22,1)
TT_atmosphere = AI.AnalogInput("Temperature","°C",5,22,6)
QT_light = AI.AnalogInput("Light sensor","%",6,6,11)
QT_light2 = AI.AnalogInput("Light sensor","%",7,14,11)
TT_heatingPad = AI.AnalogInput("Heat sensor","°C",8,6,16)

M_hatch = M.Motor("Hatch motor",0,22,11)

M_evacuator = DO.DigitalOutput("Evacuator",0,30,1)
M_agitator = DO.DigitalOutput("Agitator",1,30,6)

X_heatingPad = AO.AnalogOutput("Heating pad","%",0,22,16)

TC_heatingPad = PID.PIDController("Heat controller","°C",0,14,16)

time.sleep(5)

ser.flushInput()

j = 0

def cycle():
    global j

    i = 0

    while ser.inWaiting() > 24 and ++i < 10:
        readBytes = ser.read(24)

        allBytesSplit = struct.unpack('12h',readBytes)

        # very ugly
        allBytes = struct.pack('10h',allBytesSplit[1],allBytesSplit[2],allBytesSplit[3],allBytesSplit[4],allBytesSplit[5],
                         allBytesSplit[6],allBytesSplit[7],allBytesSplit[8],allBytesSplit[9],allBytesSplit[10])

        print(allBytesSplit)

        if int(allBytesSplit[0]) != 1234 or int(allBytesSplit[11]) != 4321:
            ser.flushInput()
            break

        objectType = allBytesSplit[1]

        # even more ugly
        if objectType == 1:
            LS_open.handleData(allBytes)
            LS_closed.handleData(allBytes)
            button.handleData(allBytes)
        elif objectType == 2:
            QT_insideHumidity.handleData(allBytes)
            QT_outsideHumidity.handleData(allBytes)
            TT_atmosphere.handleData(allBytes)
            TT_inside.handleData(allBytes)
            TT_outside.handleData(allBytes)
            PT_atmosphere.handleData(allBytes)
            QT_light.handleData(allBytes)
            QT_light2.handleData(allBytes)
            TT_heatingPad.handleData(allBytes)
        elif objectType == 3:
            M_hatch.handleData(allBytes)
        elif objectType == 4:
            M_evacuator.handleData(allBytes)
            M_agitator.handleData(allBytes)
        elif objectType == 5:
            X_heatingPad.handleData(allBytes)
        elif objectType == 6:
            TC_heatingPad.handleData(allBytes)

    w.delete(ALL)

    LS_open.draw(w)
    LS_closed.draw(w)
    button.draw(w)
    QT_insideHumidity.draw(w)
    QT_outsideHumidity.draw(w)
    TT_atmosphere.draw(w)
    TT_inside.draw(w)
    TT_outside.draw(w)
    PT_atmosphere.draw(w)
    QT_light.draw(w)
    QT_light2.draw(w)
    TT_heatingPad.draw(w)
    M_hatch.draw(w)
    M_agitator.draw(w)
    M_evacuator.draw(w)
    X_heatingPad.draw(w)
    TC_heatingPad.draw(w)

    j = j + 1

    w.create_text(400,400,text="Cycles= " +str(j),anchor="nw")

    master.after(100,cycle)

try:
    master.after(100,cycle)
    mainloop()
except:
    exit()

