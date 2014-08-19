
import PortInterface.PortInterfaceFactory
import Components.ComponentFactory
import Infrastructure.InfrastructureFactory
import Datatype.DataTypeFactory

class FactoryProvider(object):
    def getPortInterfaceFactory(self):
        ## Bouml preserved body begin 0003DBEF
        outPortInterfaceFactory = None
        if((self.itsSuccessor) and isinstance(self.itsSuccessor, FactoryProvider)):
            outPortInterfaceFactory = self.itsSuccessor.getPortInterfaceFactory()
        return outPortInterfaceFactory
        ## Bouml preserved body end 0003DBEF
        
    def setItsSuccessor(self, value):
        self.itsSuccessor = value
        
    def getComponentFactory(self):
        ## Bouml preserved body begin 0003F8EF
        outComponentFactory = None
        if((self.itsSuccessor) and isinstance(self.itsSuccessor, FactoryProvider)):
            outComponentFactory = self.itsSuccessor.getComponentFactory()
        return outComponentFactory
        ## Bouml preserved body end 0003F8EF
        
    def getInfrastructureFactory(self):
        ## Bouml preserved body begin 000416EF
        outInfrastructureFactory = None
        if((self.itsSuccessor) and isinstance(self.itsSuccessor, FactoryProvider)):
            outInfrastructureFactory = self.itsSuccessor.getInfrastructureFactory()
        return outInfrastructureFactory
        ## Bouml preserved body end 000416EF
        
    def getDataTypeFactory(self):
        ## Bouml preserved body begin 00045C6F
        outDataTypeFactory = None
        if((self.itsSuccessor) and isinstance(self.itsSuccessor, FactoryProvider)):
            outDataTypeFactory = self.itsSuccessor.getDataTypeFactory()
        return outDataTypeFactory
        ## Bouml preserved body end 00045C6F
        
    def __init__(self):
        self.itsSuccessor = None
        pass
    
