
import Infrastructure.Identifiable
import Infrastructure.AEPackage

class PackageableElement(Infrastructure.Identifiable.Identifiable):
    def setItsParentPackage(self, value):
        self.itsParentPackage = value
        
    def getItsParentPackage(self):
        return self.itsParentPackage
        
    def __init__(self):
        super(PackageableElement, self).__init__()
        self.itsParentPackage = None
        pass
    
