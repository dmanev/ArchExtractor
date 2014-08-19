
import PortInterface.IPortInterface
import PortInterface.Operation
import Infrastructure.PackageableElement

class ClientServerInterface(PortInterface.IPortInterface.IPortInterface, Infrastructure.PackageableElement.PackageableElement):
    def getItsOperationList(self):
        return self.itsOperationList
        
    def __init__(self):
        super(ClientServerInterface, self).__init__()
        self.itsOperationList = list()
        pass
    
