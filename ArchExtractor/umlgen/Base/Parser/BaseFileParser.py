
import Parser.IFileParser
import re
import PortInterface.IPortCriteria
import Components.IComponent
import Infrastructure.FactoryProvider

class BaseFileParser(Parser.IFileParser.IFileParser, Infrastructure.FactoryProvider.FactoryProvider):
    def getFileFilterCriteria(self):
        return self.fileFilterCriteria
        
    def fileFilter(self, fileName):
        ## Bouml preserved body begin 0002676F
        bResult = False
        if re.match(self.fileFilterCriteria, fileName, re.I):
            bResult = True
            
        return bResult
        ## Bouml preserved body end 0002676F
        
    def __init__(self, inpIPortCriteriaList = None):
        super(BaseFileParser, self).__init__()
        self.fileFilterCriteria = None
        self.fileContent = ''
        self.itsIPortCriteriaList = list()
        ## Bouml preserved body begin 0002AC6F
        self.itsIPortCriteriaList = inpIPortCriteriaList
        for iPortCriteria in self.itsIPortCriteriaList:
            iPortCriteria.setItsSuccessor(self)
        ## Bouml preserved body end 0002AC6F
        
    def preprocessFile(self, inpFilePath):
        ## Bouml preserved body begin 0002C7EF
        pass
        ## Bouml preserved body end 0002C7EF
        
    def fulfillComponentData(self, cmpName, filePath, inoutIComponent):
        ## Bouml preserved body begin 0002E26F
            
        bValidityCheck = self.preprocessFile(filePath)
        
        if(False != bValidityCheck):
            for iPortCriteria in self.itsIPortCriteriaList:
                iPortCriteria.execute(self.fileContent, inoutIComponent)
        return inoutIComponent
        ## Bouml preserved body end 0002E26F
        
    def setItsIPortCriteriaList(self, value):
        self.itsIPortCriteriaList = value
        
    
