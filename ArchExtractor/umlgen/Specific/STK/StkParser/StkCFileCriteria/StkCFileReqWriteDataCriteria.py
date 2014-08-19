
import StkParser.StkPortCriteria
import Datatype.ArrayDataType
import PortInterface.SenderReceiverInterface
import PortInterface.DataElement
import PortInterface.RequiredPort
import Components.IComponent
import re

class StkCFileReqWriteDataCriteria(StkParser.StkPortCriteria.StkPortCriteria):
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 00038AEF
        signalIdentifiers = []      
        #English/French version of the 'write' macros
        for seq in re.findall(r'mDAT(Write|Ecrire)(Table|Tableau|)\s*\(\s*([US]\d+)Bit\s*' +
                              ',\s*(\w+)\s*', 
                               inpTextContent):
            sttrLanguage, sttrIsTable, sttrType, sttrName = seq

            DE = PortInterface.DataElement.DataElement()
            DE.setName(sttrName)
            dtf = self.getDataTypeFactory()
            DT = dtf.getDataType(sttrType)

            if sttrIsTable:
                arrayDT = dtf.getArrayDataType('Arr'+sttrType)            
                arrayDT.itsDataType = DT
                # array size unknown
                #arrayDT.setMaxNumberOfElements(dataTypeDim)                                
                DE.itsDataType = arrayDT
            else:
                DE.itsDataType = DT
            pif = self.getPortInterfaceFactory()
            sendRecvIf = pif.getSenderReceiverIf(sttrName, [DE])
            reqPortGetter = PortInterface.RequiredPort.RequiredPort(sendRecvIf)
            reqPortGetter.setName("set"+sttrName)
            inoutIComponent.addPort(reqPortGetter)  
        ## Bouml preserved body end 00038AEF
        
    def __init__(self):
        super(StkCFileReqWriteDataCriteria, self).__init__()
        pass
    
