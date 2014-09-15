
import Datatype.CompositeDataType
import Datatype.DataType

class ArrayDataType(Datatype.CompositeDataType.CompositeDataType):
    """Represents array data element"""
    def getMaxNumberOfElements(self):
        return self.maxNumberOfElements
        
    def setMaxNumberOfElements(self, value):
        self.maxNumberOfElements = value
        
    def getItsDataType(self):
        return self.itsDataType
        
    def setItsDataType(self, value):
        self.itsDataType = value
        
    def __init__(self):
        super(ArrayDataType, self).__init__()
        self.itsDataType = None
        self.maxNumberOfElements = None
        pass
    
