
import Datatype.DataType
import Infrastructure.Identifiable

class DataElement(Infrastructure.Identifiable.Identifiable):
    def getItsDataType(self):
        return self.itsDataType
        
    def setItsDataType(self, value):
        self.itsDataType = value
        
    def __init__(self):
        super(DataElement, self).__init__()
        self.itsDataType = Datatype.DataType.DataType()
        pass
    
