
import StkParser.StkPortCriteria
import re
import StkPortInterfaces.StkDATControlIf
import PortInterface.RequiredPort
import Components.IComponent

class StkCFileReqDATControlCriteria(StkParser.StkPortCriteria.StkPortCriteria):
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 00038B6F
        for datControl in re.findall(r'mDATControl\s*\(\s*(\w+)\s*,\s*\w+\s*\)', inpTextContent):
            pif = self.getPortInterfaceFactory()
            dtf = self.getDataTypeFactory()            
            clSrvIntIf = pif.getStkDATControlIf(datControl, dtf)
            reqPort = PortInterface.RequiredPort.RequiredPort(clSrvIntIf)
            reqPort.setName(datControl)
            reqPort.setInterface(clSrvIntIf)
            inoutIComponent.addPort(reqPort)            
        ## Bouml preserved body end 00038B6F
        
    def __init__(self):
        super(StkCFileReqDATControlCriteria, self).__init__()
        pass
    
