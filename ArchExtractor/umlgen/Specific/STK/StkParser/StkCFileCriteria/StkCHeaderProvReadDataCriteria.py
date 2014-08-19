
import re
import PortInterface.ProvidedPort
import PortInterface.SenderReceiverInterface
import PortInterface.DataElement
import Datatype.ArrayDataType
import Components.IComponent
import StkParser.StkPortCriteria

class StkCHeaderProvReadDataCriteria(StkParser.StkPortCriteria.StkPortCriteria):
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 00036D6F
        signalIdentifiers = []
        #English/French version of the 'read' macros        
        for seq in re.findall(r'\s*\#define\s+mDAT(Read|Lire)(Table|Tableau|)([US]\d+)Bit(\w+)' +
                               '('+'|'.join(self.itsAccessModes.keys())+')[^\w]', 
                               inpTextContent):
            gttrLanguage, gttrIsTable, gttrType, gttrName, gttrMode = seq
            gttrMode = self.itsAccessModes[gttrMode]
            if (gttrName + gttrMode) not in signalIdentifiers:
                signalIdentifiers.append(gttrName + gttrMode)
                
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
            provPortGetter = PortInterface.ProvidedPort.ProvidedPort(sendRecvIf)
            provPortGetter.setName("get"+gttrName)
            inoutIComponent.addPort(provPortGetter)                
        ## Bouml preserved body end 00036D6F
        
    def __init__(self):
        super(StkCHeaderProvReadDataCriteria, self).__init__()
        pass
    
