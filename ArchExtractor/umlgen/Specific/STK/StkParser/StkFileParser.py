
import os
import re
import Components.BaseComponent
import Parser.BaseFileParser
import PortInterface.IPortCriteria
import Parser.IFileParser
import Components.IComponent

class StkFileParser(Parser.BaseFileParser.BaseFileParser):
    """Base STK File parser"""
    def __init__(self, inpIPortCriteriaList):
        super(StkFileParser, self).__init__(inpIPortCriteriaList)
        ## Bouml preserved body begin 0002FE6F
        pass
        ## Bouml preserved body end 0002FE6F
        
    def getComponentNameList(self, fileName):
        ## Bouml preserved body begin 000282EF
        sResult = ''
        fileName = re.findall(r'^(\w+)\.\w+$', os.path.basename(fileName), re.I)[0]
        fileName = fileName.lower()
        sResult = fileName
        if re.match(r'^\w+[x|p|j]$', fileName, re.I):
            supposed_component = fileName[0:len(fileName)-1]
            CompFactory = self.getComponentFactory()
            tmpCmp = None            
            if  CompFactory.findComponent(supposed_component, tmpCmp):
                sResult = supposed_component
        
        return [sResult]
        ## Bouml preserved body end 000282EF
        
    def updateComponent(self, inpName, filePath, outIComponent):
        ## Bouml preserved body begin 0002E36F
        CompFactory = self.getComponentFactory()
        if(CompFactory):
            outIComponent = CompFactory.getBaseComponent(inpName, outIComponent)
            outIComponent.addFileList([filePath])
            InfrastructFactory = self.getInfrastructureFactory()
            if(InfrastructFactory):
                packPath = os.path.split(filePath)[0]
                package = InfrastructFactory.getAEPackage(packPath)
                package.addElement(outIComponent)
        
        return outIComponent
        ## Bouml preserved body end 0002E36F
        
    def removeComment(self):
        ## Bouml preserved body begin 0002FEEF
        i = 0
        withoutComment = ''
        wc_lines = re.split(r'\\\n', self.fileContent)
        self.fileContent = ''.join(wc_lines)
        wc_lines = re.split('\n', self.fileContent)
        new_wc_lines = []
        for str in wc_lines:
            if str!='':
                line = re.sub(r'/\*.*\*/', '', str)
                line = re.sub(r'//.*$', '', line)
                if line != '':
                    new_wc_lines.append(line)
        self.fileContent = '\n'.join(new_wc_lines)        
        comment = False
        while i < len(self.fileContent):
            if comment:
                if self.fileContent[i] == '*' and self.fileContent[i+1] == '/':  
                    comment = False
                    i = i + 2
                else:
                    i = i + 1                    
            else:
                if self.fileContent[i] == '/' and self.fileContent[i+1] == '*':
                    comment = True
                    i = i + 2
                else:
                    withoutComment = withoutComment + self.fileContent[i]                    
                    i = i + 1
        self.fileContent = withoutComment
        ## Bouml preserved body end 0002FEEF
        
    
