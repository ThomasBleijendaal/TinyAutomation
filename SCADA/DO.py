import struct
import DI

class DigitalOutput(DI.DigitalInput):
    _interlock = False

    def __del__(self):
        print("DO destroyed")

    def handleData(self, data):
        statusCmd, startCount, activeTime = struct.unpack('=2h1f', data)

        self._active = statusCmd == 1
        self._interlock = statusCmd == 2
        self._count = startCount
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
