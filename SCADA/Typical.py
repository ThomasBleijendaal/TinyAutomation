class Typical(object):
    name = "{defaultName}"
    i = -1

    positionX = 1
    positionY = 1

    _width = 1
    _height = 1

    def __init__(self, name, i, positionX, positionY):
        self.name = name
        self.i = i
        self.positionX = positionX
        self.positionY = positionY

    def __del__(self):
        print(self.name + " destroyed")


    def handleData(self, data):
        pass

    def draw(self, w):
        pass
