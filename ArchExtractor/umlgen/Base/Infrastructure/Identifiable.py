

class Identifiable(object):
    def getName(self):
        return self.Name
        
    def setName(self, value):
        self.Name = value
        
    def __init__(self):
        self.Name = None
        pass
    
