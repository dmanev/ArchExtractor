
import Parser.BasePortCriteria
import re
import StkPortInterfaces.StkTOSSignalIf
import PortInterface.RequiredPort
import Components.IComponent
import PortInterface.IPortCriteria

class StkCFileReqReadTOSSignalCriteria(Parser.BasePortCriteria.BasePortCriteria):
    """STK C implementation file reaquired TOSSignal read criteria"""
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 0003BEEF
        for tosSignal in re.findall(r'TOSReadSignal\s*\(\s*c(TOSSignal\w+)\s*\)', inpTextContent):
            pif = self.getPortInterfaceFactory()
            dtf = self.getDataTypeFactory()
            tosCtrlIf = pif.getStkTOSSignalIf(tosSignal, dtf)               
            reqPort = PortInterface.RequiredPort.RequiredPort(tosCtrlIf)
            reqPort.setName(tosSignal)
            reqPort.setInterface(tosCtrlIf)
            inoutIComponent.addPort(reqPort)            
        ## Bouml preserved body end 0003BEEF
        
    def __init__(self):
        super(StkCFileReqReadTOSSignalCriteria, self).__init__()
        pass
    
