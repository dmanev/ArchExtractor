
import Infrastructure.Identifiable
import PortInterface.ParamData
import Datatype.DataType

class Operation(Infrastructure.Identifiable.Identifiable):
    """Represents 'Operation' from the meta-model"""
    def __init__(self):
        super(Operation, self).__init__()
        self.itsParamList = list()
        self.itsDataType = Datatype.DataType.DataType()
        ## Bouml preserved body begin 0003396F
        self.itsDataType = None
        ## Bouml preserved body end 0003396F
        
    def getItsParamList(self):
        return self.itsParamList
        
    def setItsParamList(self, value):
        self.itsParamList = value
        
    def getItsDataType(self):
        return self.itsDataType
        
    def setItsDataType(self, value):
        self.itsDataType = value
        
    
