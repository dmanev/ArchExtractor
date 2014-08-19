
import re
import StkPortInterfaces.StkTOSSignalIf
import PortInterface.ProvidedPort
import Components.IComponent
import Parser.BasePortCriteria

class StkJilTOSSignalCriteria(Parser.BasePortCriteria.BasePortCriteria):
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 000339EF
        for tosSignal in re.findall(r'Signal\s*(\w+)\s*;', inpTextContent, re.I):
            pif = self.getPortInterfaceFactory()
            dtf = self.getDataTypeFactory()
            tosCtrlIf = pif.getStkTOSSignalIf(tosSignal, dtf)                  
            provPort = PortInterface.ProvidedPort.ProvidedPort(tosCtrlIf)
            provPort.setName(tosSignal)
            provPort.setInterface(tosCtrlIf)
            inoutIComponent.addPort(provPort)
        ## Bouml preserved body end 000339EF
        
    def __init__(self):
        super(StkJilTOSSignalCriteria, self).__init__()
        pass
    
