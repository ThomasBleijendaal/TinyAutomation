import struct
from Typicals.Typical import Typical

class AnalogInput(Typical):
    _lolo = False
    _lo = False
    _hi = False
    _hihi = False
    _bta = False

    _value = 0.0
    _min = 0.0
    _max = 0.0
    _average = 0.0

    _width = 6
    _height = 1

    def __init__(self, name, units, positionX, positionY):
        self.name = name
        self.units = units
        self.positionX = positionX
        self.positionY = positionY

    def handleData(self,data):
        statusCmd, self._value, self._min, self._max, self._average = struct.unpack('=1h4f', data)

        self._lolo = bool(statusCmd & 1)
        self._lo = bool(statusCmd & 2)
        self._hi = bool(statusCmd & 4)
        self._hihi = bool(statusCmd & 8)
        self._bta = bool(statusCmd & 16)

    def draw(self,w):
        if self._lolo or self._hihi:
            outline = "#ff0000"
            text = "HH" if self._hihi else "LL"
            fill = "#ff8080"
        elif self._lo or self._hi:
            outline = "#ff8000"
            text = "H" if self._hi else "L"
            fill = "#ffff80"
        elif self._bta:
            outline = "#ff00ff"
            text = "BTA"
            fill = "#ff80ff"
        else:
            outline = "#404040"
            text = ""
            fill = "#808080"

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
            fill = fill,
            outline = outline
        )

        w.create_text(
            self.positionX * 20 + 5,
            self.positionY * 20 + 3,
            anchor="nw",
            text=str(round(self._value,1)) + " " + self.units
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 1) * 20 + 3,
            anchor="nw",
            text="Min: " + str(round(self._min,1)) + " " + self.units
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 2) * 20 + 3,
            anchor="nw",
            text="Max: " + str(round(self._max,1)) + " " + self.units
        )

        if text != "":
            w.create_text(
                (self.positionX + self._width) * 20 - 5,
                self.positionY * 20 + 3,
                anchor="ne",
                text=text,
                fill=outline
            )
