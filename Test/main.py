#!/usr/bin/python

import serial
import time
import struct

print("Starting")

def packInts(intList):
    return struct.pack('h' * len(intList), *intList)
def unpackInts(bytes):
    return struct.unpack('3h', bytes)

def packFloats(floatList):
    return struct.pack('f' * len(floatList), *floatList)
def unpackFloats(bytes):
    return struct.unpack('3f', bytes)

ser = serial.Serial('COM3', 115200)

objectType = 0
objectNr = 0
cmd = 0
status = 0
previousStatus = 0
clicks = 0

data1 = 10.0
data2 = 20.0
data3 = 30.0

intBytes = 6
realBytes = 12

time.sleep(5)

while 1:
    #intData = packInts([objectType, objectNr, cmd])
    #realData = packFloats([data1, data2, data3])

    #intBytes = ser.write(intData)
    #realBytes = ser.write(realData)

    #try:
    objectType, objectNr, status = unpackInts(ser.read(intBytes))
    data1, data2, data3 = unpackFloats(ser.read(realBytes))
    #except:
    #    print("Failure")
    #    continue

    if previousStatus != status:
        print("BUTTON ")
        clicks += 1
        print(clicks)
        previousStatus = status

