
import PortInterface.IPort
import PortInterface.IPortInterface
import Infrastructure.Identifiable

class RequiredPort(PortInterface.IPort.IPort, Infrastructure.Identifiable.Identifiable):
    def __init__(self, inpIPortIf):
        super(RequiredPort, self).__init__()
        self.itsIPortInterface = PortInterface.IPortInterface.IPortInterface()
        ## Bouml preserved body begin 00028BEF
        self.itsIPortInterface = inpIPortIf 
        ## Bouml preserved body end 00028BEF
        
    def getInterface(self):
        ## Bouml preserved body begin 000319EF
        return self.itsIPortInterface
        ## Bouml preserved body end 000319EF
        
    def setInterface(self, inpIf):
        ## Bouml preserved body begin 00031A6F
        self.itsIPortInterface = inpIf
        ## Bouml preserved body end 00031A6F
        
    
