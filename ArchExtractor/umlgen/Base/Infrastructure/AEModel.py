
import Infrastructure.Identifiable
import Infrastructure.AEPackage
import Infrastructure.InfrastructureFactory
import Datatype.DataTypeFactory
import PortInterface.PortInterfaceFactory
import Components.ComponentFactory
import Infrastructure.FactoryProvider

class AEModel(Infrastructure.Identifiable.Identifiable, Infrastructure.FactoryProvider.FactoryProvider):
    def __init__(self, inpInfrastructureFactory):
        super(AEModel, self).__init__()
        self.itsAEPackageList = None
        self.itsInfrastructureFactory = Infrastructure.InfrastructureFactory.InfrastructureFactory()
        self.itsDataTypeFactory = Datatype.DataTypeFactory.DataTypeFactory()
        self.itsPortInterfaceFactory = PortInterface.PortInterfaceFactory.PortInterfaceFactory()
        self.itsComponentFactory = Components.ComponentFactory.ComponentFactory()
        ## Bouml preserved body begin 000437EF
        if(isinstance(inpInfrastructureFactory, 
                      Infrastructure.InfrastructureFactory.InfrastructureFactory)):
            self.itsInfrastructureFactory = inpInfrastructureFactory;
        ## Bouml preserved body end 000437EF
        
    def getPackageList(self):
        ## Bouml preserved body begin 000438EF
        outPackageList = None
        outPackageList = self.itsInfrastructureFactory.getRootPackageList(outPackageList) 
        return outPackageList
        ## Bouml preserved body end 000438EF
        
    def getPortInterfaceFactory(self):
        ## Bouml preserved body begin 00045CEF
        outPortInterfaceFactory = self.itsPortInterfaceFactory

        return outPortInterfaceFactory
        ## Bouml preserved body end 00045CEF
        
    def getComponentFactory(self):
        ## Bouml preserved body begin 00045D6F
        outComponentFactory = self.itsComponentFactory

        return outComponentFactory
        ## Bouml preserved body end 00045D6F
        
    def getInfrastructureFactory(self):
        ## Bouml preserved body begin 00045DEF
        outInfrastructureFactory = self.itsInfrastructureFactory

        return outInfrastructureFactory
        ## Bouml preserved body end 00045DEF
        
    def getDataTypeFactory(self):
        ## Bouml preserved body begin 00045E6F
        outDataTypeFactory = self.itsDataTypeFactory
        
        return outDataTypeFactory
        ## Bouml preserved body end 00045E6F
        
    def setItsInfrastructureFactory(self, value):
        self.itsInfrastructureFactory = value
        
    def setItsPortInterfaceFactory(self, value):
        self.itsPortInterfaceFactory = value
        
    def setItsComponentFactory(self, value):
        self.itsComponentFactory = value
        
    def setItsDataTypeFactory(self, value):
        self.itsDataTypeFactory = value
        
    
