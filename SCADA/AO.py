import struct
from Typical import Typical

class AnalogOutput(Typical):
    _active = False
    _interlock = False
    _startCount = 0
    _activeTime = 0.0
    _output = 0.0

    _width = 6
    _height = 1

    def __init__(self, name, units, i, positionX, positionY):
        self.name = name
        self.units = units
        self.i = i
        self.positionX = positionX
        self.positionY = positionY

    def handleData(self,data):
        statusCmd, startCount, activeTime, output, dummy2 = struct.unpack('=2h3f', data)

        self._active = bool(statusCmd & 1)
        self._interlock = bool(statusCmd & 2)

        self._startCount = startCount
        self._activeTime = activeTime
        self._output = output

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
            (self._height + self.positionY) * 20,
            fill = "#00ff00" if self._active else "#0080d0" if self._interlock else "#808080",
            outline = "#404040"
        )

        if self._interlock:
            w.create_text(
                (self.positionX + self._width) * 20 - 5,
                self.positionY * 20 + 3,
                anchor="ne",
                text="ITL",
                fill="#000000"
            )

        w.create_text(
            self.positionX * 20 + 5,
            self.positionY * 20 + 3,
            anchor="nw",
            text=str(round(self._output,1)) + " " + self.units
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 1) * 20 + 3,
            anchor="nw",
            text=str(round(self._activeTime,1)) + " s"
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 2) * 20 + 3,
            anchor="nw",
            text=str(round(self._startCount,1)) + " x"
        )

