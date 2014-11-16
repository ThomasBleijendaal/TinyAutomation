from tkinter import *
from ThreadObject import *

class Presentation(ThreadObject):
    _master = None
    #todo rename _w to canvas
    _w = None

    def interrupt(self):
        self._parent.loop()

        self._master.after(100,self.interrupt)

    def start(self):
        self._master = Tk()
        self._w = Canvas(self._master, width=1280, height=720)
        self._w.pack()

        self.interrupt()

        mainloop()
