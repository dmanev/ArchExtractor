
import Infrastructure.Identifiable
import Infrastructure.PackageableElement

class AEPackage(Infrastructure.Identifiable.Identifiable):
    def __init__(self, inpName):
        super(AEPackage, self).__init__()
        self.itsElementMap = dict()
        self.itsAEPackageList = list()
        self.itsParentPackage = None
        ## Bouml preserved body begin 000419EF
        self.setName(inpName)
        ## Bouml preserved body end 000419EF
        
    def addElement(self, inpElement):
        ## Bouml preserved body begin 00041A6F
        if(isinstance(inpElement, Infrastructure.PackageableElement.PackageableElement)):
            if(inpElement.getName() not in self.itsElementMap.keys()):
                self.itsElementMap[inpElement.getName()] = inpElement
                inpElement.setItsParentPackage(self)
        ## Bouml preserved body end 00041A6F
        
    def getElementList(self):
        ## Bouml preserved body begin 00043B6F
        return self.itsElementMap.values()
        ## Bouml preserved body end 00043B6F
        
    def getItsAEPackageList(self):
        return self.itsAEPackageList
        
    def setItsAEPackageList(self, value):
        self.itsAEPackageList = value
        
    def getItsParentPackage(self):
        return self.itsParentPackage
        
    def setItsParentPackage(self, value):
        self.itsParentPackage = value
        
    
