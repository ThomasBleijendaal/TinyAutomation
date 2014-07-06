import struct

class AnalogInput(object):
    _lolo = False
    _lo = False
    _hi = False
    _hihi = False
    _bta = False

    _value = 0.0
    _min = 0.0
    _max = 0.0

    _width = 6
    _height = 1

    def __init__(self, name, units, i, positionX, positionY):
        self.name = name
        self.units = units
        self.i = i
        self.positionX = positionX
        self.positionY = positionY
    def __del__(self):
        print("AI destroyed")

    def handleData(self,data):
        objectType, objectNr, statusCmd, value, min, max, dummy1 = struct.unpack('=3h3f1h', data)

        print(data)

        if objectNr == self.i:
            self._lolo = bool(statusCmd & 1)
            self._lo = bool(statusCmd & 2)
            self._hi = bool(statusCmd & 4)
            self._hihi = bool(statusCmd & 8)
            self._bta = bool(statusCmd & 16)

            self._value = value
            self._min = min
            self._max = max

    def draw(self,w):
        if self._lolo or self._hihi:
            outline = "#ff0000"
            fill = "#ff8080"
        elif self._lo or self._hi:
            outline = "#ffd000"
            fill = "#ffff80"
        elif self._bta:
            outline = "#ff00ff"
            fill = "#ff80ff"
        else:
            outline = "#404040"
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
            self.positionY * 20 + 5,
            anchor="nw",
            text=str(round(self._value,1)) + " " + self.units
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 1) * 20 + 5,
            anchor="nw",
            text="Min: " + str(round(self._min,1)) + " " + self.units
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 2) * 20 + 5,
            anchor="nw",
            text="Max: " + str(round(self._max,1)) + " " + self.units
        )