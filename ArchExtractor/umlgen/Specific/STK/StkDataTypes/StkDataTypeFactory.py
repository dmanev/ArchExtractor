
import Datatype.DataTypeFactory
import StkDataTypes.StkVoid
import StkDataTypes.StkU1
import StkDataTypes.StkU8
import StkDataTypes.StkS8
import StkDataTypes.StkU16
import StkDataTypes.StkS16
import StkDataTypes.StkU32
import StkDataTypes.StkS32

class StkDataTypeFactory(Datatype.DataTypeFactory.DataTypeFactory):
    def __init__(self):
        super(StkDataTypeFactory, self).__init__()
        ## Bouml preserved body begin 0004616F
        #Initialize the STK DataTypes
        for methodName in dir(self):
            if methodName.startswith('getStk'):
                getattr(self, methodName)()
        ## Bouml preserved body end 0004616F
        
    def getStkVoid(self):
        ## Bouml preserved body begin 000458EF
        outDataType = self.getDataType('void')
        outDataType.lowerLimit = None
        outDataType.upperLimit = None
        return outDataType
        ## Bouml preserved body end 000458EF
        
    def getStkU1(self):
        ## Bouml preserved body begin 0004596F
        outDataType = self.getDataType('U1')
        outDataType.lowerLimit = '0'
        outDataType.upperLimit = '1'
        return outDataType
        ## Bouml preserved body end 0004596F
        
    def getStkU8(self):
        ## Bouml preserved body begin 000459EF
        outDataType = self.getDataType('U8')
        outDataType.lowerLimit = '0'
        outDataType.upperLimit = '255'
        return outDataType
        ## Bouml preserved body end 000459EF
        
    def getStkS8(self):
        ## Bouml preserved body begin 00045A6F
        outDataType = self.getDataType('S8')
        outDataType.lowerLimit = '-126'
        outDataType.upperLimit = '127'
        return outDataType
        ## Bouml preserved body end 00045A6F
        
    def getStkS16(self):
        ## Bouml preserved body begin 00045AEF
        outDataType = self.getDataType('S16')
        outDataType.lowerLimit = '-32766'
        outDataType.upperLimit = '32767'
        return outDataType
        ## Bouml preserved body end 00045AEF
        
    def getStkU16(self):
        ## Bouml preserved body begin 000460EF
        outDataType = self.getDataType('U16')
        outDataType.lowerLimit = '0'
        outDataType.upperLimit = '65535'
        return outDataType
        ## Bouml preserved body end 000460EF
        
    def getStkU32(self):
        ## Bouml preserved body begin 00045B6F
        outDataType = self.getDataType('U32')
        outDataType.lowerLimit = '0'
        outDataType.upperLimit = '4294967295'
        return outDataType
        ## Bouml preserved body end 00045B6F
        
    def getStkS32(self):
        ## Bouml preserved body begin 00045BEF
        outDataType = self.getDataType('S32')
        self.lowerLimit = '-2147483646'
        self.upperLimit = '2147483647'
        return outDataType
        ## Bouml preserved body end 00045BEF
        
    
