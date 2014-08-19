
import Parser.IFileParser
import Infrastructure.AEModel
import Analyzer.IAnalyzer
import os
import Infrastructure.FactoryProvider

class BaseAnalyzer(Analyzer.IAnalyzer.IAnalyzer, Infrastructure.FactoryProvider.FactoryProvider):
    def __init__(self, inpIFileParserList = None):
        super(BaseAnalyzer, self).__init__()
        self.itsIFileParserList = list()
        ## Bouml preserved body begin 000265EF
        self.itsIFileParserList = inpIFileParserList
        for iFileParser in self.itsIFileParserList:
            iFileParser.setItsSuccessor(self)
        ## Bouml preserved body end 000265EF
        
    def scan(self, topDir, inoutAEModel):
        ## Bouml preserved body begin 0001F46F
        self.setItsSuccessor(inoutAEModel)
        inoutAEModel.setName(os.path.split(topDir)[1])
        for dirPath, dirList, fileList in os.walk(topDir):
            for fileName in fileList:
                filePath = os.path.join(dirPath,fileName)
                for iFileParser in self.itsIFileParserList:
                    if iFileParser.fileFilter(fileName):
                        cmpNameList = iFileParser.getComponentNameList(fileName)
                        iCmp = None
                        for cmpName in cmpNameList:
                            baseDir = os.path.relpath(filePath, os.path.split(topDir)[0])
                            iCmp = iFileParser.updateComponent(cmpName, baseDir, iCmp)                            
                            iCmp = iFileParser.fulfillComponentData(cmpName, filePath, iCmp)
        return inoutAEModel
        ## Bouml preserved body end 0001F46F
        
    def setItsIFileParserList(self, value):
        self.itsIFileParserList = value
        
    
