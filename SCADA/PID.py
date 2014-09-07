import struct
from Typical import Typical

class PIDController(Typical):
    _active = False
    _deviated = False
    _fast = False
    _sp = 0.0

    _width = 6
    _height = 1

    def __init__(self, name, units, i, positionX, positionY):
        self.name = name
        self.units = units
        self.i = i
        self.positionX = positionX
        self.positionY = positionY
    def __del__(self):
        print("PID destroyed")

    def handleData(self,data):
        statusCmd, sp = struct.unpack('=1h1f', data)

        self._active = bool(statusCmd & 1)
        self._deviated = bool(statusCmd & 2)
        self._fast = bool(statusCmd & 4)

        self._sp = sp

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
            40 + self.positionY * 20,
            fill = "",
            outline = "#808080"
        )

        w.create_rectangle(
            self.positionX * 20,
            self.positionY * 20,
            (self._width + self.positionX) * 20,
            (self._height + self.positionY) * 20,
            fill = "#ff0000" if self._deviated else "#00ff00" if self._active else "#808080",
            outline = "#404040"
        )

        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 1) * 20 + 3,
            anchor="nw",
            text="SP: "  + str(round(self._sp,1)) + self.units
        )

