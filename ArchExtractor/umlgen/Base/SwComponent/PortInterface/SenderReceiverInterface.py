
import PortInterface.IPortInterface
import PortInterface.DataElement
import Infrastructure.PackageableElement

class SenderReceiverInterface(PortInterface.IPortInterface.IPortInterface, Infrastructure.PackageableElement.PackageableElement):
    """Represents 'SenderReceiverInterface' from the meta-model"""
    def getItsDataElementList(self):
        return self.itsDataElementList
        
    def setItsDataElementList(self, value):
        self.itsDataElementList = value
        
    def __init__(self):
        super(SenderReceiverInterface, self).__init__()
        self.itsDataElementList = list()
        pass
    
