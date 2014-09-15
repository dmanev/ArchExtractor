
import PortInterface.SenderReceiverInterface
import PortInterface.ClientServerInterface
import PortInterface.IPortInterface
import PortInterface.DataElement

class PortInterfaceFactory(object):
    """Method Factory for the meta-model elements in
    package 'PortInterface'"""
    def getAbstractPortInterface(self, inpNameIf, inpClass):
        """Abstract Factory method which returns instance of IPortInterface
        based on given name and child class of IPortInterface"""
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
        """Factory method which returns 'SenderReceiverInterface' object element"""
        ## Bouml preserved body begin 0003D8EF
        outIPortInterface = self.getAbstractPortInterface(inpNameIf+'_If', 
                                                          PortInterface.SenderReceiverInterface.SenderReceiverInterface)
        if(len(outIPortInterface.itsDataElementList) == 0):
            outIPortInterface.itsDataElementList = inpDataElementList
        return outIPortInterface
        ## Bouml preserved body end 0003D8EF
        
    def getClientServerIf(self, inpNameIf):
        """Factory method which returns 'ClientServerInterface' object element"""
        ## Bouml preserved body begin 0003D96F
        outIPortInterface = self.getAbstractPortInterface(inpNameIf+'If', 
                                                          PortInterface.ClientServerInterface.ClientServerInterface)
        return outIPortInterface
        ## Bouml preserved body end 0003D96F
        
    def getItsIPortInterfaceMap(self):
        return self.itsIPortInterfaceMap
        
    def __init__(self):
        #A map storing all interfaces created with the Factory
        #of type <string, IPortInterface>
        self.itsIPortInterfaceMap = dict()
        pass
    
