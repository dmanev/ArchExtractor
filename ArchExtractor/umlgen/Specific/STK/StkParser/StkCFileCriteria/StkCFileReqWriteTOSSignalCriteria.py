
import re
import StkPortInterfaces.StkTOSSignalIf
import PortInterface.RequiredPort
import Parser.BasePortCriteria
import Components.IComponent
import Parser.IPortCriteria

class StkCFileReqWriteTOSSignalCriteria(Parser.BasePortCriteria.BasePortCriteria):
    """STK C implementation file reaquired TOSSignal write criteria"""
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 0003BF6F
        for tosSignal in re.findall(r'TOSWriteSignal\s*\(\s*c(TOSSignal\w+)\s*\)', inpTextContent):
            pif = self.getPortInterfaceFactory()
            dtf = self.getDataTypeFactory()
            tosCtrlIf = pif.getStkTOSSignalIf(tosSignal, dtf)
            reqPort = PortInterface.RequiredPort.RequiredPort(tosCtrlIf)
            reqPort.setName(tosSignal)
            reqPort.setInterface(tosCtrlIf)
            inoutIComponent.addPort(reqPort)
        ## Bouml preserved body end 0003BF6F
        
    def __init__(self):
        super(StkCFileReqWriteTOSSignalCriteria, self).__init__()
        pass
    
