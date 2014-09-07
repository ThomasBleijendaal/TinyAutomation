from tkinter import *
from GeneralObject import *

class ObjectHandler(GeneralObject):
    _objects = {}
    _nameToObject = {}
    #todo: replace with typicalID from typical
    _typicalToI = {"DigitalInput" : 1, "AnalogInput" : 2, "Motor" : 3, "DigitalOutput" : 4, "AnalogOutput" : 5, "PIDController" : 6}

    def addObject(self, name, o):
        typical = self._typicalToI[o.__class__.__name__]

        if(not typical in self._objects):
            self._objects[typical] = {}

        self._objects[typical][o.i] =  o

        self._nameToObject[name] = {}
        self._nameToObject[name]["i"] = o.i
        self._nameToObject[name]["typical"] = typical

    def handleData(self, dataSet):
        for typical, id, data in dataSet:
            self._objects[typical][id].handleData(data)

    def draw(self,w):
        #todo: this doesn't belong here
        w.delete(ALL)

        for typical in self._objects:
            for i in self._objects[typical]:
                self._objects[typical][i].draw(w)