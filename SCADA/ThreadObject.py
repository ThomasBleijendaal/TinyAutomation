class ThreadObject(object):
    _parent = None

    def __init__(self, *parent):
        self._parent = parent[0]