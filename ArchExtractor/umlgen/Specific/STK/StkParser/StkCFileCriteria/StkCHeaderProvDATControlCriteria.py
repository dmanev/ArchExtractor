
import StkParser.StkPortCriteria
import StkPortInterfaces.StkDATControlIf
import PortInterface.ProvidedPort
import re
import Components.IComponent

class StkCHeaderProvDATControlCriteria(StkParser.StkPortCriteria.StkPortCriteria):
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 000389EF
        for datControl in re.findall(r'\#define\s+mDATControl(\w+)\s*\(\s*\w+\s*\)', inpTextContent):
            pif = self.getPortInterfaceFactory()
            dtf = self.getDataTypeFactory()
            clSrvIntIf = pif.getStkDATControlIf(datControl, dtf)               
            provPort = PortInterface.ProvidedPort.ProvidedPort(clSrvIntIf)
            provPort.setName(datControl)
            provPort.setInterface(clSrvIntIf)
            inoutIComponent.addPort(provPort)
        ## Bouml preserved body end 000389EF
        
    def __init__(self):
        super(StkCHeaderProvDATControlCriteria, self).__init__()
        pass
    
