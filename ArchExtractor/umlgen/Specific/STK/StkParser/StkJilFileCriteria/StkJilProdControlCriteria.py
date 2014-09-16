
import re
import StkPortInterfaces.StkControlIf
import PortInterface.ProvidedPort
import Parser.BasePortCriteria
import Components.IComponent
import PortInterface.IPortCriteria

class StkJilProdControlCriteria(Parser.BasePortCriteria.BasePortCriteria):
    """STK JIL file provided Control criteria"""
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 0003386F
        for control in re.findall(r'ProdControl\s*{\s*Name\s*=\s*\"(\w+)\"\s*;\s*}\s*;', inpTextContent, re.I):
            if control not in inoutIComponent.getItsIPortMap():
                pif = self.getPortInterfaceFactory()
                clSrvIntIf = pif.getStkControlIf(control)                
                provPort = PortInterface.ProvidedPort.ProvidedPort(clSrvIntIf)
                provPort.setName(control)
                provPort.setInterface(clSrvIntIf)
                inoutIComponent.addPort(provPort)                        
        ## Bouml preserved body end 0003386F
        
    def __init__(self):
        super(StkJilProdControlCriteria, self).__init__()
        pass
    
