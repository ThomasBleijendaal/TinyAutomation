from tkinter import *
import serial, time, struct

# these objects handle the general functionality of the SCADA system
# only Objects is public

class General(object):
    Objects = None
    _Communication = None
    _Presentation = None

    def __init__(self):
        self.Objects = ObjectHandler(self)
        self._Presentation = Presentation(self)
        self._Communication = Communication(self)

    def start(self):
        try:
            self._Communication.start()

        except Exception as e:
            print(str(e))

        try:
            self._Presentation.start()

        except Exception as e:
            print(str(e))

    def loop(self):
        try:
            data = self._Communication.readData()
            if data.__sizeof__() > 0:
                self.Objects.handleData(data)

            #todo change this dirty shortcut
            self.Objects.draw(self._Presentation._w)

        except Exception as e:
            print(str(e))

class ObjectHandler(object):
    _parent = None

    _objects = {}
    _nameToObject = {}
    #todo: replace with typicalID from typical
    _typicalToI = {"DigitalInput" : 1, "AnalogInput" : 2, "Motor" : 3, "DigitalOutput" : 4, "AnalogOutput" : 5, "PIDController" : 6}

    def __init__(self, *parent):
        self._parent = parent[0]

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
        w.delete(ALL)

        for typical in self._objects:
            for i in self._objects[typical]:
                self._objects[typical][i].draw(w)


class Communication(object):
    _parent = None

    _connection = None
    data = None

    def __init__(self, *parent):
        self._parent = parent[0]

    def start(self):
        self._connection = serial.Serial('COM3', 115200)

        #todo: replace this with check
        time.sleep(5)

        self._connection.flushInput()

    def readData(self):
        while self._connection.inWaiting() >= 8:
            headerBytes = self._connection.read(4)

            header, identifier = struct.unpack('=2h', headerBytes)

            if header != 1234:
                self._connection.flushInput()
                print(header)
                print("headerbreak")
                break

            id = identifier % 100
            identifier -= id

            typical = int((identifier % 1000) / 100)
            identifier -= typical * 100

            payloadSize = int(identifier / 1000)
            if payloadSize % 2:
                typical += 10
                payloadSize -= 1

            print(payloadSize)

            payload = self._connection.read(payloadSize)
            footerBytes = self._connection.read(2)

            print(payload)

            footer = struct.unpack('=h', footerBytes)[0]

            if footer != 4321:
                self._connection.flushInput()
                print(footer)
                print("footerbreak")
                break

            yield [
                typical,
                id,
                payload
            ]

    def sendData(self,typical,i,sendBytes):
        data = struct.pack('=2h16c',typical,i,sendBytes)

        self._connection.write(data)



class Presentation(object):
    _parent = None

    _master = None
    #todo rename _w
    _w = None

    def __init__(self, *parent):
        self._parent = parent[0]

    def interrupt(self):
        self._parent.loop()

        self._master.after(100,self.interrupt)

    def start(self):
        self._master = Tk()
        self._w = Canvas(self._master, width=1280, height=720)
        self._w.pack()

        self.interrupt()

        mainloop()




