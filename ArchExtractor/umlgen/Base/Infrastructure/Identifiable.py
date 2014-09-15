

class Identifiable(object):
    """Major class for the meta-model. A class who inherits it
    will be treated as 'Identifiable', i.e. it has a name."""
    def getName(self):
        return self.Name
        
    def setName(self, value):
        self.Name = value
        
    def __init__(self):
        #Name of the element
        self.Name = None
        pass
    
