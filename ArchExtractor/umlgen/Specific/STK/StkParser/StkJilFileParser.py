
import re
import StkParser.StkFileParser
import PortInterface.IPortCriteria
import Parser.BaseFileParser

class StkJilFileParser(StkParser.StkFileParser.StkFileParser):
    """JIL format file parser"""
    def __init__(self, inpIPortCriteriaList):
        super(StkJilFileParser, self).__init__(inpIPortCriteriaList)
        ## Bouml preserved body begin 0002FDEF
        self.fileFilterCriteria = r'\w+\.jil$'
        ## Bouml preserved body end 0002FDEF
        
    def preprocessFile(self, inpFilePath):
        ## Bouml preserved body begin 0002E3EF
        bResult = True
        self.fileContent = open(inpFilePath, 'r').read()
        
        self.removeComment()
        
        # don't scan LIB.JIL file or any who contains implementation part
        if re.search(r'IMPLEMENTATION\s+Implementation', self.fileContent):
            bResult = False
        
        return bResult
        ## Bouml preserved body end 0002E3EF
        
    
