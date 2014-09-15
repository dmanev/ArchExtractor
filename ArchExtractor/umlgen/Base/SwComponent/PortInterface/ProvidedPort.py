
import PortInterface.IPort
import Infrastructure.Identifiable
import PortInterface.IPortInterface

class ProvidedPort(PortInterface.IPort.IPort, Infrastructure.Identifiable.Identifiable):
    """Represents 'ProvidedPort' from the meta-model"""
    def __init__(self, inpIPortIf):
        super(ProvidedPort, self).__init__()
        self.itsIPortInterface = PortInterface.IPortInterface.IPortInterface()
        ## Bouml preserved body begin 00028B6F
        self.itsIPortInterface = inpIPortIf
        ## Bouml preserved body end 00028B6F
        
    def getInterface(self):
        ## Bouml preserved body begin 000318EF
        return self.itsIPortInterface
        ## Bouml preserved body end 000318EF
        
    def setInterface(self, inpIf):
        ## Bouml preserved body begin 0003196F
        self.itsIPortInterface = inpIf
        ## Bouml preserved body end 0003196F
        
    
