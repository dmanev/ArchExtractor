
import PortInterface.IPortInterface
import PortInterface.DataElement
import Infrastructure.PackageableElement

class SenderReceiverInterface(PortInterface.IPortInterface.IPortInterface, Infrastructure.PackageableElement.PackageableElement):
    def getItsDataElementList(self):
        return self.itsDataElementList
        
    def setItsDataElementList(self, value):
        self.itsDataElementList = value
        
    def __init__(self):
        super(SenderReceiverInterface, self).__init__()
        self.itsDataElementList = list()
        pass
    
