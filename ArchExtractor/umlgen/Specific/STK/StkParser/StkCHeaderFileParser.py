
import StkParser.StkFileParser
import Parser.IPortCriteria
import Parser.BaseFileParser

class StkCHeaderFileParser(StkParser.StkFileParser.StkFileParser):
    """C header file parser"""
    def __init__(self, inpIPortCriteriaList):
        super(StkCHeaderFileParser, self).__init__(inpIPortCriteriaList)
        ## Bouml preserved body begin 00036EEF
        self.fileFilterCriteria = r'\w+\.h$'
        ## Bouml preserved body end 00036EEF
        
    def preprocessFile(self, inpFilePath):
        ## Bouml preserved body begin 00036F6F
        bResult = True
        self.fileContent = open(inpFilePath, 'r').read()
        
        self.removeComment()
        
        return bResult
        ## Bouml preserved body end 00036F6F
        
    
