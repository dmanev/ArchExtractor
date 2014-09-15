
import Datatype.DataType
import Datatype.ArrayDataType

class DataTypeFactory(object):
    """Factory for data type elements"""
    def getDataType(self, inpDataTypeName):
        """Returns DataType element by given name.
        If the name does not exist it creates it."""
        ## Bouml preserved body begin 0004586F
        outDataType = None
        if(inpDataTypeName in self.itsDataTypeMap):
            outDataType = self.itsDataTypeMap[inpDataTypeName]
        else:
            outDataType = Datatype.DataType.DataType()
            outDataType.setName(inpDataTypeName)
            self.itsDataTypeMap[inpDataTypeName] = outDataType
        
        return outDataType
        ## Bouml preserved body end 0004586F
        
    def getArrayDataType(self, inpDataTypeName):
        """Returns ArrayDataType element by given name.
        If the name does not exist it creates it."""
        ## Bouml preserved body begin 000457EF
        outArrayDataType = None
        if(inpDataTypeName in self.itsDataTypeMap):
            outArrayDataType = self.itsDataTypeMap[inpDataTypeName]
        else:
            outArrayDataType = Datatype.ArrayDataType.ArrayDataType()
            outArrayDataType.setName(inpDataTypeName)
            self.itsDataTypeMap[inpDataTypeName] = outArrayDataType

        return outArrayDataType
        ## Bouml preserved body end 000457EF
        
    def getItsDataTypeMap(self):
        return self.itsDataTypeMap
        
    def __init__(self):
        self.itsDataTypeMap = dict()
        pass
    
