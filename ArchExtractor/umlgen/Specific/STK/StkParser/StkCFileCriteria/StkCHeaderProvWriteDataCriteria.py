
import StkParser.StkPortCriteria
import re
import PortInterface.ProvidedPort
import Datatype.ArrayDataType
import PortInterface.SenderReceiverInterface
import PortInterface.DataElement
import Components.IComponent
import PortInterface.IPortCriteria

class StkCHeaderProvWriteDataCriteria(StkParser.StkPortCriteria.StkPortCriteria):
    """STK C Header file provided data write criteria"""
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 000388EF
        signalIdentifiers = []
        #English/French version of the 'write' macros
        for seq in re.findall(r'\s*\#define\s+mDAT(Write|Ecrire|)(Table|Tableau|)([US]\d+)Bit(\w+)' +
                               '('+'|'.join(self.itsAccessModes.keys())+')[^\w]', 
                               inpTextContent):
            sttrLanguage, sttrIsTable, sttrType, sttrName, sttrMode = seq
            sttrMode = self.itsAccessModes[sttrMode]
            if (sttrName + sttrMode) not in signalIdentifiers:
                signalIdentifiers.append(sttrName + sttrMode)
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
                DE = PortInterface.DataElement.DataElement()
                DE.setName(sttrName)
                DE.itsDataType = DT
            pif = self.getPortInterfaceFactory()
            sendRecvIf = pif.getSenderReceiverIf(sttrName, [DE])
            provPortGetter = PortInterface.ProvidedPort.ProvidedPort(sendRecvIf)
            provPortGetter.setName("set"+sttrName)
            inoutIComponent.addPort(provPortGetter)  
        ## Bouml preserved body end 000388EF
        
    def __init__(self):
        super(StkCHeaderProvWriteDataCriteria, self).__init__()
        pass
    
