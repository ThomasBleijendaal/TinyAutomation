import struct
from Typical import Typical

class PIDController(Typical):
    _active = False
    _deviated = False
    _fast = False
    _input = 0.0
    _sp = 0.0
    _output = 0.0
    _P = 0.0
    _I = 0.0
    _D = 0.0
    _deviationLimit = 0.0

    _width = 6
    _height = 1

    def __init__(self, name, units, positionX, positionY):
        self.name = name
        self.units = units
        self.positionX = positionX
        self.positionY = positionY
    def __del__(self):
        print("PID destroyed")

    def handleData(self,data):
        statusCmd, self._input, self._sp, self._output, self._P, self._I, self._D, self._deviationLimit = struct.unpack('=1h7f', data)

        self._active = bool(statusCmd & 1)
        self._deviated = bool(statusCmd & 2)
        self._fast = bool(statusCmd & 4)

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

