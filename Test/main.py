#!/usr/bin/python

import DI
import AI

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

button = DI.DigitalInput("Button",0,1,1)
pressure = AI.AnalogInput("Pressure","mbar",0,5,1)
temperature = AI.AnalogInput("Temperature","C",1,12,1)


print(struct.calcsize('=3h3f'))

print(struct.calcsize('3f'))

print(struct.calcsize('3h'))


time.sleep(5)

def cycle():

    i = 0

    while(ser.inWaiting() > 0 and ++i < 10):
        allBytes = ser.read(20)


        allBytesSplit = struct.unpack('10h',allBytes)
        objectType = allBytesSplit[0]

        if objectType == 1:
            button.handleData(allBytes)
        if objectType == 2:
            pressure.handleData(allBytes)
            temperature.handleData(allBytes)

    w.delete(ALL)

    button.draw(w)
    pressure.draw(w)
    temperature.draw(w)

    master.after(100,cycle)

try:
    master.after(100,cycle)
    mainloop()
except:
    exit()

