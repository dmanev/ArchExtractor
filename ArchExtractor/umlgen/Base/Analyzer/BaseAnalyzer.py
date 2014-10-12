
import Analyzer.IAnalyzer
import os
import Parser.BaseFileParser
import Infrastructure.FactoryProvider
import Infrastructure.AEModel

class BaseAnalyzer(Analyzer.IAnalyzer.IAnalyzer, Infrastructure.FactoryProvider.FactoryProvider):
    """Base Analyzer class"""
    def __init__(self, inpBFParserList = []):
        super(BaseAnalyzer, self).__init__()
        self.itsBaseFileParserList = list()
        ## Bouml preserved body begin 000265EF
        self.itsBaseFileParserList = inpBFParserList
        for bfParser in self.itsBaseFileParserList:
            bfParser.setItsSuccessor(self)
        ## Bouml preserved body end 000265EF
        
    def scan(self, topDir, inoutAEModel):
        """Start walking over the "topDir" project's files.
        Resulting model artefacts to be filled in 'inoutAEModel'"""
        ## Bouml preserved body begin 000565EF
        self.setItsSuccessor(inoutAEModel)
        inoutAEModel.setName(os.path.split(topDir)[1])
        for dirPath, dirList, fileList in os.walk(topDir):
            for fileName in fileList:
                filePath = os.path.join(dirPath,fileName)
                for BFParser in self.itsBaseFileParserList:
                    if BFParser.fileFilter(fileName):
                        cmpNameList = BFParser.getComponentNameList(fileName)
                        iCmp = None
                        for cmpName in cmpNameList:
                            baseDir = os.path.relpath(filePath, os.path.split(topDir)[0])
                            iCmp = BFParser.updateComponent(cmpName, baseDir, iCmp)                            
                            iCmp = BFParser.fulfillComponentData(cmpName, filePath, iCmp)
        return inoutAEModel
        ## Bouml preserved body end 000565EF
        
    def setItsBaseFileParserList(self, value):
        self.itsBaseFileParserList = value
        
    
