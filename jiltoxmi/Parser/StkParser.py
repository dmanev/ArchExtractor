import re
from DataTypes import JilDataTypes

def indent(value):
    i = 0
    result = ''
    while i < value:
        result += '    '
        i += 1
    return result

def extractLevelOneBlock(string):
    openningBrace=0
    closingBrace=0
    startDataConfig=None
    endDataConfig=None
    result=None
    for brace in re.finditer(r'(?P<OpenningBrace>{)|(?P<ClosingBrace>})', string):
        if brace.group('OpenningBrace'):
            openningBrace+=1
            if not startDataConfig:
                startDataConfig=brace.end()
        if brace.group('ClosingBrace'): 
            closingBrace+=1
            openningBrace-=1
            if startDataConfig and openningBrace==0 and not endDataConfig:
                endDataConfig=brace.end()-1
        if startDataConfig and endDataConfig:
            result=string[startDataConfig:endDataConfig]
    return result

class StkFileParser(object):
    accessModes = {'Defaut' : 'Default',
                   'Default' : 'Default', 
                   'Immediat' : 'Immediate',
                   'Immediate' : 'Immediate',
                   'Differe' : 'Delayed',
                   'Delayed' : 'Delayed'}
    
    def __init__(self):
        super(StkFileParser, self).__init__()
        self._componentName = None
        self._Content = ''        
        self._onControl = []
        self._prodControl = []
        self._inputs = []
        self._outputs = []
        self._jilInputs = {}
        self._jilOutputs = {}
        self._cInputs = {}
        self._cOutputs = {}
        self._defineMap = {}
        self._getters = []
        self._setters = []

    #TODO: Use Util.Lang.CCode.commentRemove instead
    def commentRemove(self):
        i = 0
        withoutComment = ''
        wc_lines = re.split(r'\\\n', self._Content)
        self._Content = ''.join(wc_lines)
        wc_lines = re.split('\n', self._Content)
        new_wc_lines = []
        for str in wc_lines:
            if str!='':
                line = re.sub(r'/\*.*\*/', '', str)
                line = re.sub(r'//.*$', '', line)
                if line != '':
                    new_wc_lines.append(line)
        self._Content = '\n'.join(new_wc_lines)        
        comment = False
        while i < len(self._Content):
            if comment:
                if self._Content[i] == '*' and self._Content[i+1] == '/':  
                    comment = False
                    i = i + 2
                else:
                    i = i + 1                    
            else:
                if self._Content[i] == '/' and self._Content[i+1] == '*':
                    comment = True
                    i = i + 2
                else:
                    withoutComment = withoutComment + self._Content[i]                    
                    i = i + 1
        self._Content = withoutComment

    def jilParse(self, jilFile):
        self._Content = open(jilFile, 'r').read()
        self.commentRemove()
        # default SCC version
        sccVersion = 1
        #self.beautify(jilFile)        
        if re.search(r'OnControl\s*=\s*\w+', self._Content, re.I):
            sccVersion = 2
        elif re.search(r'ProdControl\s*{\s*Name\s*=\s*\"\w+\"\s*;\s*}\s*;', self._Content, re.I):
            sccVersion = 2
        elif re.search(r'ON\s+CONTROL\s+\w+', self._Content, re.I):
            sccVersion = 1
        elif re.search(r'PROD\s+CONTROL\s+\w+', self._Content, re.I):
            sccVersion = 1
            
        if re.search(r'IMPLEMENTATION\s+Implementation', self._Content):
            # don't scan LIB.JIL file or any who contains implementation part
            sccVersion = 0

        if sccVersion == 1:
            componentNameList = re.findall(r'COMPONENT\s+(\w+)', self._Content, re.I)
            if componentNameList:
                self._componentName = componentNameList[0]
            for item in re.findall(r'ON\s+CONTROL\s+(\w+)', self._Content, re.I):
                if item not in self._onControl: 
                    self._onControl.append(item)
            self._onControl.sort()
            for item in re.findall(r'PROD\s+CONTROL\s+(\w+)', self._Content, re.I):
                if item not in self._prodControl:
                    self._prodControl.append(item)
            self._prodControl.sort()
            for seq in re.findall(r'[^\w]IN\s+(\w+)\[{0,1}(\d*)\]{0,1}\s+(\w+)', self._Content, re.I):
                inpType, inpDim, inpName = seq
                self._jilInputs[inpName] = (inpName, inpType, inpDim)            
    #            self._inputs.append((inpName, inpType, inpDim))
            self._inputs.sort()
            for seq in re.findall(r'[^\w]OUT\s+(\w+)\[{0,1}(\d*)\]{0,1}\s+(\w+)', self._Content, re.I):
                outType, outDim, outName = seq
                self._jilOutputs[outName] = (outName, outType, outDim)            
    #            self._outputs.append((outName, outType, outDim))
            self._outputs.sort()
            #extract Data definitions
            if re.search(r'Data\s+(\w+)', self._Content):
                nextItemIsDataConfig = 0
                dataName = None
                for item in re.split(r'(Data\s+\w+)', self._Content):
                    nameMatchObj = re.search(r'Data\s+(\w+)', item)
                    if nameMatchObj:
                        nextItemIsDataConfig = 1
                        dataName = nameMatchObj.group(1)
                    elif nextItemIsDataConfig:
                        nextItemIsDataConfig = 0
                        dataProps = extractLevelOneBlock(item)
                        if dataProps:
                            dataType, dataTypeDim = re.findall(r'\s*Type\s*=\s*([US]\d+)\[{0,1}(\d+|)\]{0,1}', 
                                                               dataProps, re.I)[0]
                            dataType = dataType + 'Bit'
                            if dataTypeDim:
                                self._getters.append((dataName, dataType, 'Default', '256'))
                                self._setters.append((dataName, dataType, 'Default', '256'))
                            else:
                                self._getters.append((dataName, dataType, 'Default', ''))
                                self._setters.append((dataName, dataType, 'Default', ''))
            for item in re.findall(r'Signal\s*(\w+)\s*;', self._Content, re.I):
                dataName = 'TOSSignal' + item
                self._getters.append((dataName, 'U1Bit', 'Default', ''))
                self._setters.append((dataName, '', 'Default', ''))                                
        elif sccVersion == 2:
            componentNameList = re.findall(r'Component\s+(\w+)', self._Content, re.I)
            if componentNameList:
                self._componentName = componentNameList[0]
            for seq in re.findall(r'OnControl\s*=\s*(\w+)\s*\{([\w\s=\";]*)\};', self._Content, re.I):
                dataName, dataProps = seq
                if dataName == 'CallBack' or dataName == 'SetSignal':
                    control = re.findall(r'\s*Ctrl\s*=\s*\"(\w+)\"', dataProps, re.I)[0]
                    if control not in self._onControl:
                        self._onControl.append(control)                   
            self._onControl.sort()
            for item in re.findall(r'ProdControl\s*{\s*Name\s*=\s*\"(\w+)\"\s*;\s*}\s*;', self._Content, re.I):
                if item not in self._prodControl:
                    self._prodControl.append(item)
            self._prodControl.sort()
            #extract Data definitions
            if re.search(r'Data\s+(\w+)', self._Content):
                nextItemIsDataConfig = 0
                dataName = None
                for item in re.split(r'(Data\s+\w+)', self._Content):
                    nameMatchObj = re.search(r'Data\s+(\w+)', item)
                    if nameMatchObj:
                        nextItemIsDataConfig = 1
                        dataName = nameMatchObj.group(1)
                    elif nextItemIsDataConfig:
                        nextItemIsDataConfig = 0
                        dataProps = extractLevelOneBlock(item)
                        if dataProps:
                            dataType, dataTypeDim = re.findall(r'\s*Type\s*=\s*([US]\d+)\[{0,1}(\d+|)\]{0,1}', 
                                                               dataProps, re.I)[0]
                            dataType = dataType + 'Bit'
                            if dataTypeDim:
                                self._getters.append((dataName, dataType, 'Default', '256'))
                                self._setters.append((dataName, dataType, 'Default', '256'))
                            else:
                                self._getters.append((dataName, dataType, 'Default', ''))
                                self._setters.append((dataName, dataType, 'Default', ''))
            for item in re.findall(r'Signal\s*(\w+)\s*;', self._Content, re.I):
                dataName = 'TOSSignal' + item
                self._getters.append((dataName, 'U1Bit', 'Default', ''))
                self._setters.append((dataName, 'None', 'Default', ''))

    def reverseJil(self, jilFile):
        content = ''
        indcnt = 0
        if self._componentName:
            content = 'Component ' + self._componentName
        else:
            content = 'Component ' + 'FillName'
        content += '\n' + indent(indcnt) + '{'
        indcnt += 1
        for onControl in self._onControl:
            content += '\n' + indent(indcnt) + 'OnControl = CallBack'
            content += '\n' + indent(indcnt) + '{'
            indcnt += 1 
            content += '\n' + indent(indcnt) + 'Ctrl=\"'+onControl+'\";'
            content += '\n' + indent(indcnt) + 'Fct=\"\";' # to be filled soon
            indcnt -= 1            
            content += '\n' + indent(indcnt) + '};'
        content += '\n' + indent(indcnt) + ''            
        for prodControl in self._prodControl:
            content += '\n' + indent(indcnt) + 'ProdControl { '
            content += 'Name = \"'+prodControl+'\"; '
            content += '};'
        content += '\n' + indent(indcnt) + ''
        inputs = self._jilInputs.keys()
        inputs.sort()
        for input in inputs:
            inpName, inpType, inpDim = self._jilInputs[input]
            content += '\n' + indent(indcnt) + 'In'
            content += '\n' + indent(indcnt) + '{'
            indcnt += 1
            content += '\n' + indent(indcnt) + 'Data = \"'+inpName+'\";'
            if inpDim:
                content += '\n' + indent(indcnt) + 'Type = '+ JilDataTypes.dataType[inpType]
                content += 'Array'
                content += '\n' + indent(indcnt) + '{'
                indcnt += 1
                content += '\n' + indent(indcnt) + 'Size = '+inpDim+';'
                indcnt -= 1                
                content += '\n' + indent(indcnt) + '};'
            else:
                content += '\n' + indent(indcnt) + 'Type = ' + JilDataTypes.dataType[inpType] +';'
            indcnt -= 1
            content += '\n' + indent(indcnt) + '};'
        content += '\n' + indent(indcnt) + ''
        outputs = self._jilOutputs.keys()
        outputs.sort()
        for output in outputs:
            outName, outType, outDim = self._jilOutputs[output]
            content += '\n' + indent(indcnt) + 'Out'
            content += '\n' + indent(indcnt) + '{'
            indcnt += 1    
            content += '\n' + indent(indcnt) + 'Data = \"'+outName+'\";'
            if outDim:
                content += '\n' + indent(indcnt) + 'Type = '+ JilDataTypes.dataType[outType]
                content += 'Array'
                content += '\n' + indent(indcnt) + '{'
                indcnt += 1                
                content += '\n' + indent(indcnt) + 'Size = '+outDim+';'
                indcnt -= 1                
                content += '\n' + indent(indcnt) + '};'
            else:
                content += '\n' + indent(indcnt) + 'Type = '+ JilDataTypes.dataType[outType] +';'
            indcnt -= 1                                
            content += '\n' + indent(indcnt) + '};'
        indcnt -= 1        
        content += '\n' + indent(indcnt) + '};'
        content += '\n' + indent(indcnt) + ''
        fp = open(jilFile, 'w')
        fp.write(content)
        fp.close()

    def headerParse(self, headerFile):
        self._Content = open(headerFile, 'r').read()
        self.commentRemove()
        #self.beautify(headerFile)
        signalIdentifiers = []
        #English/French version of the 'read' macros        
        for seq in re.findall(r'\s*\#define\s+mDAT(Read|Lire)(Table|Tableau|)([US]\d+Bit)(\w+)' +
                               '('+'|'.join(StkFileParser.accessModes.keys())+')[^\w]', 
                               self._Content):
            gttrLanguage, gttrIsTable, gttrType, gttrName, gttrMode = seq
            gttrMode = StkFileParser.accessModes[gttrMode]
            if (gttrName + gttrMode) not in signalIdentifiers:
                signalIdentifiers.append(gttrName + gttrMode)
            if gttrIsTable:
                self._getters.append((gttrName, gttrType, gttrMode, '256'))
            else:
                self._getters.append((gttrName, gttrType, gttrMode, ''))
        self._getters.sort()
        signalIdentifiers = []
        #English/French version of the 'write' macros
        for seq in re.findall(r'\s*\#define\s+mDAT(Write|Ecrire|)(Table|Tableau|)([US]\d+Bit)(\w+)' +
                               '('+'|'.join(StkFileParser.accessModes.keys())+')[^\w]', 
                               self._Content):
            sttrLanguage, sttrIsTable, sttrType, sttrName, sttrMode = seq
            sttrMode = StkFileParser.accessModes[sttrMode]
            if (sttrName + sttrMode) not in signalIdentifiers:
                signalIdentifiers.append(sttrName + sttrMode)            
            if sttrIsTable:
                self._setters.append((sttrName, sttrType, sttrMode, '256'))
            else:
                self._setters.append((sttrName, sttrType, sttrMode, ''))
        for datControl in re.findall(r'\#define\s+mDATControl(\w+)\s*\(\s*\w+\s*\)', self._Content):
#            if (sttrName + sttrMode) not in signalIdentifiers:
#                signalIdentifiers.append(sttrName + sttrMode)            
            self._setters.append(('DATControl' + datControl, 'U8Bit', '', ''))
        self._setters.sort()
        #English/French version of the 'read' macros
        for seq in re.findall(r'mDAT(Read|Lire)(Table|Tableau|)\s*\(\s*([US]\d+Bit)\s*' +
                              ',\s*(\w+)\s*',  
                               self._Content):
            gttrLanguage, gttrIsTable, gttrType, gttrName = seq
#            gttrMode = StkFileParser.accessModes[gttrMode]
            if (gttrName) not in signalIdentifiers:
                signalIdentifiers.append(gttrName)
            if gttrIsTable:
                self._cInputs[gttrName] = (gttrName, gttrType, '256')
            else:
                self._cInputs[gttrName] = (gttrName, gttrType, '')
        signalIdentifiers = []      
        #English/French version of the 'write' macros
        for seq in re.findall(r'mDAT(Write|Ecrire)(Table|Tableau|)\s*\(\s*([US]\d+Bit)\s*' +
                              ',\s*(\w+)\s*', 
                               self._Content):
#            sttrLanguage, sttrIsTable, sttrType, sttrName, sttrTableIndex, sttrMode = seq
            sttrLanguage, sttrIsTable, sttrType, sttrName = seq
#            sttrMode = StkFileParser.accessModes[sttrMode]           
            if sttrName not in signalIdentifiers:
                signalIdentifiers.append(sttrName)            
            if sttrIsTable:
                self._cOutputs[sttrName] = (sttrName, sttrType, '256')
            else:
                self._cOutputs[sttrName] = (sttrName, sttrType, '')
        for datControl in re.findall(r'mDATControl\s*\(\s*(\w+)\s*,\s*\w+\s*\)', self._Content):
            datControl = 'DATControl' + datControl
            self._cOutputs[datControl] = (datControl, 'U8Bit', '')
        for seq in re.findall('#define\s+(\w+)\s+(\w+)', self._Content):
            cName, cReferance = seq
            self._defineMap[cName] = cReferance

    def cParse(self, cFile):
        self._Content = open(cFile, 'r').read()
        self.commentRemove()
        #self.beautify(cFile)
        signalIdentifiers = []
        #English/French version of the 'read' macros
        for seq in re.findall(r'mDAT(Read|Lire)(Table|Tableau|)\s*\(\s*([US]\d+Bit)\s*' +
                              ',\s*(\w+)\s*', 
                               self._Content):
            gttrLanguage, gttrIsTable, gttrType, gttrName = seq
#            gttrMode = StkFileParser.accessModes[gttrMode]
            if (gttrName) not in signalIdentifiers:
                signalIdentifiers.append(gttrName)
            if gttrIsTable:
                self._cInputs[gttrName] = (gttrName, gttrType, '256')
            else:
                self._cInputs[gttrName] = (gttrName, gttrType, '')
        signalIdentifiers = []      
        #English/French version of the 'write' macros
        for seq in re.findall(r'mDAT(Write|Ecrire)(Table|Tableau|)\s*\(\s*([US]\d+Bit)\s*' +
                              ',\s*(\w+)\s*',  
                               self._Content):
            sttrLanguage, sttrIsTable, sttrType, sttrName = seq
#            sttrMode = StkFileParser.accessModes[sttrMode]           
            if (sttrName) not in signalIdentifiers:
                signalIdentifiers.append(sttrName)            
            if sttrIsTable:
                self._cOutputs[sttrName] = (sttrName, sttrType, '256')
            else:
                self._cOutputs[sttrName] = (sttrName, sttrType, '')
        for datControl in re.findall(r'mDATControl\s*\(\s*(\w+)\s*,\s*\w+\s*\)', self._Content):
            datControl = 'DATControl' + datControl
            self._cOutputs[datControl] = (datControl, 'U8Bit', '')
        for signalName in re.findall(r'TOSWriteSignal\s*\(\s*c(TOSSignal\w+)\s*\)', self._Content):
                self._cOutputs[signalName] = (signalName, 'None', '')
        for signalName in re.findall(r'TOSReadSignal\s*\(\s*c(TOSSignal\w+)\s*\)', self._Content):
                self._cInputs[signalName] = (signalName, 'U1Bit', '')                
        for seq in re.findall('#define\s+(\w+)\s+(\w+)', self._Content):
            cName, cReferance = seq
            self._defineMap[cName] = cReferance

    def checkJilToCMapping(self):
        getters = []
        setters = []
        reverseDefineMap = {}

        for seq in self._getters:
            gttrName, gttrType, gttrMode, gttrDim = seq
            getters.append(gttrName)
        for seq in self._setters:
            sttrName, sttrType, sttrMode, sttrDim = seq
            setters.append(sttrName)

        for item in self._defineMap.keys():
            if      ((item not in self._cInputs)
                and (item not in self._cOutputs)):
                del self._defineMap[item]
            else:
                reverseDefineMap[self._defineMap[item]] = item

#        for item in self._jilInputs.keys():
#            if      ((item not in self._cInputs)
#                and (item not in self._defineMap.values())):
#                print 'Input:',item,'(of Class:',self._componentName,') defined in JIL, but not used in \'C\' file !'
#            else:
#                self._inputs.append(self._jilInputs[item])
#                if item in self._defineMap.values():                    
#                    inputs.append(reverseDefineMap[item])
#                else:
#                    inputs.append(item)
#
#        for item in self._jilOutputs.keys():
#            if      ((item not in self._cOutputs)
#                and (item not in self._defineMap.values())):
#                print 'Output:',item,'(of Class:',self._componentName,') defined in JIL, but not used in \'C\' file !'
#            else:
#                self._outputs.append(self._jilOutputs[item])
#                if item in self._defineMap.values():                    
#                    outputs.append(reverseDefineMap[item])
#                else:
#                    outputs.append(item)

        for item in self._cInputs.keys():
                if item in self._defineMap.values():                    
#                    outputs.append(reverseDefineMap[item])
                    print 'Input:',item,'(of Class:',self._componentName,') is referenced with name defined in component!'
                    self._inputs.append(self._cInputs[item])                    
                else:
                    self._inputs.append(self._cInputs[item])

        for item in self._cOutputs.keys():
                if item in self._defineMap.values():                    
#                    outputs.append(reverseDefineMap[item])
                    print 'Output:',item,'(of Class:',self._componentName,') is referenced with name defined in component!'
                    self._outputs.append(self._cOutputs[item])                    
                else:
                    self._outputs.append(self._cOutputs[item])

    def beautify(self, fileName):
        indcnt = 0
        lines = open(fileName, 'r').readlines()
        newLines = []
        for line in lines:
            oldindent, content, endspace = re.findall(r'^(\s*)(.*)(\s*)$', line)[0]
            if content:
                firstChar = content[0]
                if '{' == firstChar:
                    newLines.append(indent(indcnt) + content)            
                    indcnt+=1
                elif '}' == firstChar:
                    indcnt-=1
                    newLines.append(indent(indcnt) + content)
                else:
                    newLines.append(indent(indcnt) + content)                      
            else:
                newLines.append('')
        fp = open(fileName, 'w')
        fp.write('\n'.join(newLines))
        fp.write('\n')        
        fp.close()

    def isEmpty(self):
        if (self._inputs or self._outputs or self._onControl or 
            self._prodControl or self._getters or self._setters):
            return False
        else:
            return True

    def get_componentName(self):
        return self._componentName
    def get_onControls(self):
        return self._onControl
    def get_prodControls(self):
        return self._prodControl    
    def get_inputs(self):
        return self._inputs
    def get_outputs(self):
        return self._outputs
    def get_cInputs(self):
        return self._cInputs
    def get_cOutputs(self):
        return self._cOutputs
    def get_defineMap(self):
        return self._defineMap
    def get_getters(self):
        return self._getters
    def get_setters(self):
        return self._setters
        