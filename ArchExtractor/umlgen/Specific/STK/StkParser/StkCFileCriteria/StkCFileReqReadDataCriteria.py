
import re
import Datatype.ArrayDataType
import PortInterface.SenderReceiverInterface
import PortInterface.DataElement
import PortInterface.RequiredPort
import StkParser.StkPortCriteria
import Components.IComponent
import Parser.IPortCriteria

class StkCFileReqReadDataCriteria(StkParser.StkPortCriteria.StkPortCriteria):
    """STK C implementation file reaquired data read criteria"""
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 00038A6F
        signalIdentifiers = []
        for seq in re.findall(r'mDAT(Read|Lire)(Table|Tableau|)\s*\(\s*([US]\d+)Bit\s*' +
                              ',\s*(\w+)\s*',  
                               inpTextContent):
            gttrLanguage, gttrIsTable, gttrType, gttrName = seq

            if (gttrName) not in signalIdentifiers:
                signalIdentifiers.append(gttrName)
                
            DE = PortInterface.DataElement.DataElement()
            DE.setName(gttrName)
            dtf = self.getDataTypeFactory()
            DT = dtf.getDataType(gttrType)

            if gttrIsTable:
                arrayDT = dtf.getArrayDataType('Arr'+gttrType)
                arrayDT.itsDataType = DT
                # array size unknown
                #arrayDT.setMaxNumberOfElements(dataTypeDim)                                
                DE.itsDataType = arrayDT
            else:
                DE.itsDataType = DT
            pif = self.getPortInterfaceFactory()
            sendRecvIf = pif.getSenderReceiverIf(gttrName, [DE])
            reqPortGetter = PortInterface.RequiredPort.RequiredPort(sendRecvIf)
            reqPortGetter.setName("get"+gttrName)
            inoutIComponent.addPort(reqPortGetter)
        ## Bouml preserved body end 00038A6F
        
    def __init__(self):
        super(StkCFileReqReadDataCriteria, self).__init__()
        pass
    
