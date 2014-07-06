import struct

class DigitalInput(object):
    _active = False
    _switchCount = 0
    _activeTime = 0.0

    _width = 3
    _height = 1

    def __init__(self, name, i, positionX, positionY):
        self.name = name
        self.i = i
        self.positionX = positionX
        self.positionY = positionY
    def __del__(self):
        print("DI destroyed")


    def handleData(self, data):
        objectType, objectNr, statusCmd, switchCount, activeTime, dummy1, dummy2 = struct.unpack('=4h3f', data)
        if objectNr == self.i:
            self._active = statusCmd == 1
            self._switchCount = switchCount
            self._activeTime = activeTime


    def draw(self,w):

        w.create_text(
            self.positionX * 20,
            self.positionY * 20 - 15,
            anchor="nw",
            text=self.name,
            fill="#808080"
        )

        w.create_rectangle(
            self.positionX * 20,
            (self.positionY + 1) * 20,
            (self._width + self.positionX) * 20,
            60 + self.positionY * 20,
            fill = "",
            outline = "#808080"
        )

        w.create_rectangle(
            self.positionX * 20,
            self.positionY * 20,
            (self._width + self.positionX) * 20,
            (self._height + self.positionX) * 20,
            fill = "#00ff00" if self._active else "#808080",
            outline = "#404040"
        )

        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 1) * 20 + 5,
            anchor="nw",
            text=str(self._switchCount) + " x"
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 2) * 20 + 5,
            anchor="nw",
            text=str(round(self._activeTime,1)) + " s"
        )

        #if self.active:
        #    w.create_rectangle(50,25,150,75,fill="green")
        #else:
        #    w.create_rectangle(50,25,150,75,fill="gray")
