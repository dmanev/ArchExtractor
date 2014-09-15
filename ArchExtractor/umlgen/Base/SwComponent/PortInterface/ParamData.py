
import Datatype.DataType
import Infrastructure.Identifiable

class ParamData(Infrastructure.Identifiable.Identifiable):
    """Represents 'ParamData' from the meta-model"""
    def getItsDataType(self):
        return self.itsDataType
        
    def setItsDataType(self, value):
        self.itsDataType = value
        
    def __init__(self):
        super(ParamData, self).__init__()
        self.itsDataType = Datatype.DataType.DataType()
        pass
    
