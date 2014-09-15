
import PortInterface.PortInterfaceFactory
import Components.ComponentFactory
import Infrastructure.InfrastructureFactory
import Datatype.DataTypeFactory

class FactoryProvider(object):
    """FactoryProvider is an implementation of a 'Handler' in 
    'Chain of responsibility' design pattern.
    It either will provide the requested factories for object
    or it will pass the request to its 'Successor' object."""
    def getPortInterfaceFactory(self):
        """returns PortInterfaceFactory"""
        ## Bouml preserved body begin 0003DBEF
        outPortInterfaceFactory = None
        if((self.itsSuccessor) and isinstance(self.itsSuccessor, FactoryProvider)):
            outPortInterfaceFactory = self.itsSuccessor.getPortInterfaceFactory()
        return outPortInterfaceFactory
        ## Bouml preserved body end 0003DBEF
        
    def getComponentFactory(self):
        """Returns ComponentFactory"""
        ## Bouml preserved body begin 0003F8EF
        outComponentFactory = None
        if((self.itsSuccessor) and isinstance(self.itsSuccessor, FactoryProvider)):
            outComponentFactory = self.itsSuccessor.getComponentFactory()
        return outComponentFactory
        ## Bouml preserved body end 0003F8EF
        
    def getInfrastructureFactory(self):
        """Returns InfrastructureFactory"""
        ## Bouml preserved body begin 000416EF
        outInfrastructureFactory = None
        if((self.itsSuccessor) and isinstance(self.itsSuccessor, FactoryProvider)):
            outInfrastructureFactory = self.itsSuccessor.getInfrastructureFactory()
        return outInfrastructureFactory
        ## Bouml preserved body end 000416EF
        
    def getDataTypeFactory(self):
        """Returns DataTypeFactory"""
        ## Bouml preserved body begin 00045C6F
        outDataTypeFactory = None
        if((self.itsSuccessor) and isinstance(self.itsSuccessor, FactoryProvider)):
            outDataTypeFactory = self.itsSuccessor.getDataTypeFactory()
        return outDataTypeFactory
        ## Bouml preserved body end 00045C6F
        
    def setItsSuccessor(self, value):
        """setter for the "Successor" of the object."""
        self.itsSuccessor = value
        
    def __init__(self):
        #Represents the 'Successor' in 'Chain of responsibility' design pattern
        self.itsSuccessor = None
        pass
    
