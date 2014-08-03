import struct

class Motor(object):
    _active = False
    _reverse = False
    _interlock = False
    _interlockReverse = False

    _startCount = 0
    _activeTime = 0.0

    _width = 2
    _height = 2

    def __init__(self, name, i, positionX, positionY):
        self.name = name
        self.i = i
        self.positionX = positionX
        self.positionY = positionY
    def __del__(self):
        print("M destroyed")


    def handleData(self, data):
        objectType, objectNr, statusCmd, startCount, activeTime, dummy1, dummy2 = struct.unpack('=4h3f', data)
        if objectNr == self.i:
            self._active = statusCmd == 1
            self._startCount = startCount
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
            (self.positionY + self._height) * 20,
            (self._width + self.positionX) * 20,
            80 + self.positionY * 20,
            fill = "",
            outline = "#808080"
        )

        w.create_rectangle(
            self.positionX * 20,
            self.positionY * 20,
            (self._width + self.positionX) * 20,
            (self._height + self.positionY) * 20,
            fill = "#00ff00" if self._active or self._reverse else "#808080",
            outline = "#404040"
        )

        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + self._height) * 20 + 3,
            anchor="nw",
            text=str(self._startCount) + " x"
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + self._height + 1) * 20 + 3,
            anchor="nw",
            text=str(round(self._activeTime,1)) + " s"
        )
