
import re
import Components.IComponent
import PortInterface.RequiredPort
import StkPortInterfaces.StkControlIf
import Parser.BasePortCriteria

class StkJilOnControlCriteria(Parser.BasePortCriteria.BasePortCriteria):
    """STK JIL file required Control criteria"""
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 0003186F
        for seq in re.findall(r'OnControl\s*=\s*(\w+)\s*\{([\w\s=\";]*)\};', inpTextContent, re.I):
                dataName, dataProps = seq
                if dataName == 'CallBack' or dataName == 'SetSignal':
                    control = re.findall(r'\s*Ctrl\s*=\s*\"(\w+)\"', dataProps, re.I)[0]

                    if control not in inoutIComponent.getItsIPortMap():
                        pif = self.getPortInterfaceFactory()
                        dtf = self.getDataTypeFactory()
                        clSrvIntIf = pif.getStkControlIf(control, dtf)
                        reqPort = PortInterface.RequiredPort.RequiredPort(clSrvIntIf)
                        reqPort.setName(control)
                        reqPort.setInterface(clSrvIntIf)
                        inoutIComponent.addPort(reqPort)

        return inoutIComponent
        ## Bouml preserved body end 0003186F
        
    def __init__(self):
        super(StkJilOnControlCriteria, self).__init__()
        pass
    
