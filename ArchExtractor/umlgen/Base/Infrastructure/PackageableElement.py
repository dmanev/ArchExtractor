
import Infrastructure.Identifiable
import Infrastructure.AEPackage

class PackageableElement(Infrastructure.Identifiable.Identifiable):
    """Major class for the meta-model. A class who inherits it
    will be treated as 'Packagable', i.e. it can be directly
    included in 'AEPackage'."""
    def setItsParentPackage(self, value):
        self.itsParentPackage = value
        
    def getItsParentPackage(self):
        return self.itsParentPackage
        
    def __init__(self):
        super(PackageableElement, self).__init__()
        self.itsParentPackage = None
        pass
    
