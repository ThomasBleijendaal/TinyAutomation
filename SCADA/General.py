import Communication, Presentation, ObjectHandler

# these objects handle the general functionality of the SCADA system
# only Objects is public

class General(object):
    Objects = None
    _Communication = None
    _Presentation = None

    def __init__(self):
        self.Objects = ObjectHandler.ObjectHandler(self)
        self._Presentation = Presentation.Presentation(self)
        self._Communication = Communication.Communication(self)

    def start(self):
        try:
            self._Communication.start()

        except Exception as e:
            print(str(e))

        try:
            self._Presentation.start()

        except Exception as e:
            print(str(e))

    def loop(self):
        try:
            data = self._Communication.readData()
            if data.__sizeof__() > 0:
                self.Objects.handleData(data)

            #todo change this dirty shortcut
            self.Objects.draw(self._Presentation._w)

        except Exception as e:
            print(str(e))




