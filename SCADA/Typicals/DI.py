import struct
from Typicals.Typical import Typical

class DigitalInput(Typical):
    _active = False
    _count = 0
    _activeTime = 0.0

    _width = 3
    _height = 1

    def handleData(self, data):
        statusCmd, self._switchCount, self._activeTime = struct.unpack('=2h1f', data)

        self._active = statusCmd == 1


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
            fill = "#00ff00" if self._active else "#808080",
            outline = "#404040"
        )

        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 1) * 20 + 3,
            anchor="nw",
            text=str(self._count) + " x"
        )
        w.create_text(
            self.positionX * 20 + 5,
            (self.positionY + 2) * 20 + 3,
            anchor="nw",
            text=str(round(self._activeTime,1)) + " s"
        )