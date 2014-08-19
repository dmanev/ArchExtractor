
import Components.IComponent
import PortInterface.IPort
import Infrastructure.PackageableElement

class BaseComponent(Components.IComponent.IComponent, Infrastructure.PackageableElement.PackageableElement):
    def __init__(self, inpName):
        super(BaseComponent, self).__init__()
        self.itsIPortMap = dict()
        self.fileList = list()
        ## Bouml preserved body begin 0002846F
        self.Name = inpName
        ## Bouml preserved body end 0002846F
        
    def addPort(self, inpIPort):
        ## Bouml preserved body begin 00031D6F
        if inpIPort.getName() not in self.itsIPortMap.keys():
            self.itsIPortMap[inpIPort.getName()] = inpIPort
        ## Bouml preserved body end 00031D6F
        
    def getFileList(self):
        return self.fileList
        
    def setFileList(self, value):
        self.fileList = value
        
    def addFileList(self, inpFileList):
        ## Bouml preserved body begin 0003FA6F
        self.fileList.extend(inpFileList)
        ## Bouml preserved body end 0003FA6F
        
    def getItsIPortMap(self):
        return self.itsIPortMap
        
    
