
import StkParser.StkFileParser
import PortInterface.IPortCriteria

class StkCImpFileParser(StkParser.StkFileParser.StkFileParser):
    def __init__(self, inpIPortCriteriaList):
        super(StkCImpFileParser, self).__init__(inpIPortCriteriaList)
        ## Bouml preserved body begin 0003A4EF
        self.fileFilterCriteria = r'\w+\.c$'
        ## Bouml preserved body end 0003A4EF
        
    def preprocessFile(self, inpFilePath):
        ## Bouml preserved body begin 0003A56F
        bResult = True
        self.fileContent = open(inpFilePath, 'r').read()
        
        self.removeComment()
        
        return bResult
        ## Bouml preserved body end 0003A56F
        
    
