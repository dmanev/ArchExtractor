
import PortInterface.IPortInterface
import PortInterface.SenderReceiverInterface
import PortInterface.DataElement
import PortInterface.ClientServerInterface

class PortInterfaceFactory(object):
    def getAbstractPortInterface(self, inpNameIf, inpClass):
        ## Bouml preserved body begin 0003DB6F
        outIPortInterface = None
        if(inpNameIf in self.itsIPortInterfaceMap.keys()):
            outIPortInterface = self.itsIPortInterfaceMap[inpNameIf]
        else:
            outIPortInterface = inpClass()
            outIPortInterface.setName(inpNameIf)            
            self.itsIPortInterfaceMap[inpNameIf] = outIPortInterface
        return outIPortInterface        
        ## Bouml preserved body end 0003DB6F
        
    def getSenderReceiverIf(self, inpNameIf, inpDataElementList):
        ## Bouml preserved body begin 0003D8EF
        outIPortInterface = self.getAbstractPortInterface(inpNameIf+'_If', 
                                                          PortInterface.SenderReceiverInterface.SenderReceiverInterface)
        if(len(outIPortInterface.itsDataElementList) == 0):
            outIPortInterface.itsDataElementList = inpDataElementList
        return outIPortInterface
        ## Bouml preserved body end 0003D8EF
        
    def getClientServerIf(self, inpNameIf):
        ## Bouml preserved body begin 0003D96F
        outIPortInterface = self.getAbstractPortInterface(inpNameIf+'If', 
                                                          PortInterface.ClientServerInterface.ClientServerInterface)
        return outIPortInterface
        ## Bouml preserved body end 0003D96F
        
    def getItsIPortInterfaceMap(self):
        return self.itsIPortInterfaceMap
        
    def __init__(self):
        self.itsIPortInterfaceMap = dict()
        pass
    
