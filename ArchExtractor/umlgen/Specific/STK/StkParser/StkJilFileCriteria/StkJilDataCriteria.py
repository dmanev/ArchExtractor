
import re
import PortInterface.ProvidedPort
import PortInterface.RequiredPort
import PortInterface.SenderReceiverInterface
import Datatype.ArrayDataType
import PortInterface.DataElement
import StkParser.StkPortCriteria
import Components.IComponent
import Parser.IPortCriteria

class StkJilDataCriteria(StkParser.StkPortCriteria.StkPortCriteria):
    """STK JIL file data access criteria"""
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 0003536F
        if re.search(r'Data\s+(\w+)', inpTextContent):
            nextItemIsDataConfig = 0
            dataName = None
            for item in re.split(r'(Data\s+\w+)', inpTextContent):
                nameMatchObj = re.search(r'Data\s+(\w+)', item)
                if nameMatchObj:
                    nextItemIsDataConfig = 1
                    dataName = nameMatchObj.group(1)
                elif nextItemIsDataConfig:
                    nextItemIsDataConfig = 0
                    dataProps = self.extractLevelOneBlock(item)
                    if dataProps:
                        dataType, hasArray = re.findall(r'\s*Type\s*=\s*([US]\d+)(Array|)', 
                                                           dataProps, re.I)[0]
                        dtf = self.getDataTypeFactory()
                        DT = dtf.getDataType(dataType)
                        DE = PortInterface.DataElement.DataElement()
                        DE.setName(dataName)
                        if hasArray:
                            arrayProps = self.extractLevelOneBlock(dataType)
                            arraySize = re.findall(r'\s*Size\s*=\s*(\d+)', 
                                                               arrayProps, re.I)[0]
                            arrayDT = dtf.getArrayDataType('Arr'+arraySize+dataType)
                            arrayDT.itsDataType = DT
                            arrayDT.setMaxNumberOfElements(arraySize)
                            DE.itsDataType = arrayDT
                        else:
                            DE.itsDataType = DT
                        pif = self.getPortInterfaceFactory()
                        sendRecvIf = pif.getSenderReceiverIf(dataName, [DE])
                        provPortSetter = PortInterface.ProvidedPort.ProvidedPort(sendRecvIf)
                        provPortSetter.setName("set"+dataName)
                        provPortGetter = PortInterface.ProvidedPort.ProvidedPort(sendRecvIf)
                        provPortGetter.setName("get"+dataName)
                        inoutIComponent.addPort(provPortSetter)
                        inoutIComponent.addPort(provPortGetter)
        return inoutIComponent
        ## Bouml preserved body end 0003536F
        
    def __init__(self):
        super(StkJilDataCriteria, self).__init__()
        pass
    
