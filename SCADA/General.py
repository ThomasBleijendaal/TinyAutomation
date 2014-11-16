from ThreadObjects import Communication, Presentation, ObjectHandler

# these objects handle the general functionality of the SCADA system
# only Objects is public

class General(object):
    Objects = None
    Communication = None
    Presentation = None

    def __init__(self):
        self.Objects = ObjectHandler.ObjectHandler(self)
        self.Presentation = Presentation.Presentation(self)
        self.Communication = Communication.Communication(self)

    def start(self):
        try:
            self.Communication.start()

        except Exception as e:
            print(str(e))

        try:
            self.Presentation.start()

        except Exception as e:
            print(str(e))

    def loop(self):
        try:
            data = self.Communication.readData()
            if data.__sizeof__() > 0:
                self.Objects.handleData(data)

            #todo change this dirty shortcut
            self.Objects.draw(self.Presentation._w)

        except Exception as e:
            print(str(e))




