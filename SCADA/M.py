import struct
from Typical import Typical

class Motor(Typical):
    _active = False
    _reverse = False
    _interlock = False
    _interlockReverse = False

    _startCount = 0
    _activeTime = 0.0

    _width = 6
    _height = 1

    def handleData(self, data):
        statusCmd, startCount, activeTime, dummy1, dummy2 = struct.unpack('=2h3f', data)

        self._active = statusCmd & 0x01
        self._reverse = statusCmd & 0x02
        self._interlock = statusCmd & 0x04
        self._interlockReverse = statusCmd & 0x08
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
            (self._height + 2 + self.positionY) * 20,
            fill = "",
            outline = "#808080"
        )

        w.create_rectangle(
            self.positionX * 20,
            self.positionY * 20,
            (self._width + self.positionX) * 20,
            (self._height + self.positionY) * 20,
            fill = "#00ff00"
                if self._active or self._reverse else "#0080d0"
                if self._interlock or self._interlockReverse
                else "#808080",
            outline = "#404040"
        )

        if self._interlock or self._interlockReverse:
            w.create_text(
                (self.positionX + self._width) * 20 - 5,
                self.positionY * 20 + 3,
                anchor="ne",
                text="ITL" if self._interlock and self._interlockReverse else "forward ITL" if self._interlock else "reverse ITL",
                fill="#000000"
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
