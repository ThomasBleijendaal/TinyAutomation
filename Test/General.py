import AI, AO, DI, DO, M, PID

class ObjectHandler(object):
    _objects = []

    def __init__(self):
        pass

    def addObject(self,name, o):
        self._objects[name] = o

    def __getattr__(self,name):
        return self._objects[name]

class Communication(object):

    def __init__(self):
        pass

