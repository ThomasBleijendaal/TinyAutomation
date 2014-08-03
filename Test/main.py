#!/usr/bin/python

import DI
import AI
import M

import serial
import time
import struct
from tkinter import *

print("Starting")

ser = serial.Serial('COM3', 115200)

objectType = 0

master = Tk()
w = Canvas(master, width=800, height=600)
w.pack()

LS_open = DI.DigitalInput("Open switch",0,1,1)
LS_closed = DI.DigitalInput("Close switch",1,1,6)
button = DI.DigitalInput("Button",2,1,11)

QT_insideHumidity = AI.AnalogInput("Inside humidity","%r",0,6,1)
QT_outsideHumidity = AI.AnalogInput("Outside humidity","%r",1,6,6)
TT_inside = AI.AnalogInput("Inside temperature","C",2,14,1)
TT_outside = AI.AnalogInput("Outside temperature","C",3,14,6)
PT_atmosphere = AI.AnalogInput("Pressure","mbar",4,22,1)
TT_atmosphere = AI.AnalogInput("Temperature","C",5,22,6)
QT_light = AI.AnalogInput("Light sensor","%",6,6,11)
QT_light2 = AI.AnalogInput("Light sensor","%",7,14,11)

M_hatch = M.Motor("Hatch motor",0,22,11)

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

        if objectType == 1:
            LS_open.handleData(allBytes)
            LS_closed.handleData(allBytes)
            button.handleData(allBytes)
        if objectType == 2:
            QT_insideHumidity.handleData(allBytes)
            QT_outsideHumidity.handleData(allBytes)
            TT_atmosphere.handleData(allBytes)
            TT_inside.handleData(allBytes)
            TT_outside.handleData(allBytes)
            PT_atmosphere.handleData(allBytes)
            QT_light.handleData(allBytes)
            QT_light2.handleData(allBytes)
        if objectType == 3:
            M_hatch.handleData(allBytes)

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
    M_hatch.draw(w)

    j = j + 1

    w.create_text(400,400,text="Cycles= " +str(j),anchor="nw")

    master.after(100,cycle)

try:
    master.after(100,cycle)
    mainloop()
except:
    exit()

