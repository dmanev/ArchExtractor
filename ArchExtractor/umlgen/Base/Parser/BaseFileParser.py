
import re
import Parser.IFileParser
import Infrastructure.FactoryProvider
import Parser.BasePortCriteria
import Components.IComponent

class BaseFileParser(Parser.IFileParser.IFileParser, Infrastructure.FactoryProvider.FactoryProvider):
    """Base abstract realization of IFileParser"""
    def __init__(self, inpBasePortCriteriaList = None):
        super(BaseFileParser, self).__init__()
        self.itsBasePortCriteriaList = list()
        #Represents the file criteria for method fileFilter()
        self.fileFilterCriteria = None
        #Stores the content of a file
        self.fileContent = ''
        ## Bouml preserved body begin 0002AC6F
        self.itsBasePortCriteriaList = inpBasePortCriteriaList
        for BPCriteria in self.itsBasePortCriteriaList:
            BPCriteria.setItsSuccessor(self)
        ## Bouml preserved body end 0002AC6F
        
    def fileFilter(self, fileName):
        """Returns True if the given path is of known file extension,
        otherwise returns False"""
        ## Bouml preserved body begin 000566EF
        bResult = False
        if re.match(self.fileFilterCriteria, fileName, re.I):
            bResult = True
            
        return bResult
        ## Bouml preserved body end 000566EF
        
    def preprocessFile(self, inpFilePath):
        """Preprocess input file"""
        ## Bouml preserved body begin 0002C7EF
        pass
        ## Bouml preserved body end 0002C7EF
        
    def fulfillComponentData(self, cmpName, filePath, inoutIComponent):
        """Fulfills Component's data based on the file under analysis"""
        ## Bouml preserved body begin 0005676F
            
        bValidityCheck = self.preprocessFile(filePath)
        
        if(False != bValidityCheck):
            for BPCriteria in self.itsBasePortCriteriaList:
                BPCriteria.execute(self.fileContent, inoutIComponent)
        return inoutIComponent
        ## Bouml preserved body end 0005676F
        
    def getFileFilterCriteria(self):
        return self.fileFilterCriteria
        
    def setItsBasePortCriteriaList(self, value):
        self.itsBasePortCriteriaList = value
        
    
