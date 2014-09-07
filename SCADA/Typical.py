class Typical(object):
    name = "{defaultName}"
    id = -1

    positionX = 1
    positionY = 1

    _width = 1
    _height = 1

    def __init__(self, name, positionX, positionY):
        self.name = name
        self.positionX = positionX
        self.positionY = positionY

    def __del__(self):
        print(self.name + " destroyed")

    def setId(self, id):
        self.id = id

    def handleData(self, data):
        pass

    def draw(self, w):
        pass
