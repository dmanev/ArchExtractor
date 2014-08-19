import re

cMethodProvided = 0
cMethodRequired = 1

def extractLevelOneBlock(string):
    openningBrace=0
    closingBrace=0
    startDataConfig=None
    endDataConfig=None
    result=''
    for brace in re.finditer(r'(?P<OpenningBrace>\()|(?P<ClosingBrace>\))', string):
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

class Method(object):
    def __init__(self):
        super(Method, self).__init__()
        self._name =''
        self._returnType = ''
        self._arguments = ''
    
    def set_name(self, inpName):
        self._name = inpName
    def get_name(self):
        return self._name
    def set_returnType(self, inpReturnType):
        self._returnType = inpReturnType
    def get_returnType(self):
        return self._returnType
    def add_arguments(self, inpArg):
        #self._arguments.append(inpArg)
        self._arguments = inpArg
    def get_arguments(self):
        return self._arguments
    def set_properties(self, inpName, inpReturnType, inpArguments):
        self._name = inpName
        self._returnType = inpReturnType
        self._arguments = inpArguments

class AutosarMethod(Method):
    def __init__(self):
        super(AutosarMethod, self).__init__()
        self._methodType = ''
        self._componentName = ''
        self._portName = ''
        self._operationName = ''

    def set_properties(self, inpName, inpType, inpReturnType, inpArguments, inpProvOrReq):
        super(AutosarMethod, self).set_properties(inpName, inpReturnType, inpArguments)        
        #TODO: find better way to remove '_' at the end of 'Rte_Mode_'
        #rstrip included especially for 'Rte_Mode_' case
        self._methodType = inpType.rstrip('_')
        if cMethodProvided==inpProvOrReq:
            if inpReturnType == 'UnknownProvType':
                seqMethodPort = re.findall(inpType+'_*([a-zA-Z0-9]+)_', inpName, re.I)
                if seqMethodPort:
                    self._portName = seqMethodPort[0]
                seqMethodOperation = re.findall(inpType+'_*[a-zA-Z0-9]+_([a-zA-Z0-9]+)', inpName, re.I)
                if seqMethodOperation:
                    self._operationName = seqMethodOperation[0]                
            else:
                seqMethodComp = re.findall(inpType+'_*([a-zA-Z0-9]+)_', inpName, re.I)
                if seqMethodComp:
                    self._componentName = seqMethodComp[0]
                seqMethodPort = re.findall(inpType+'_*[a-zA-Z0-9]+_([a-zA-Z0-9]+)_', inpName, re.I)
                if seqMethodPort:
                    self._portName = seqMethodPort[0]
                seqMethodOperation = re.findall(inpType+'_*[a-zA-Z0-9]+_[a-zA-Z0-9]+_(\w+)', inpName, re.I)
                if seqMethodOperation:
                    self._operationName = seqMethodOperation[0]
        elif cMethodRequired==inpProvOrReq:
            seqMethodPort = re.findall(inpType+'_*([a-zA-Z0-9]+)_', inpName, re.I)
            if seqMethodPort:
                self._portName = seqMethodPort[0]
            seqMethodOperation = re.findall(inpType+'_*[a-zA-Z0-9]+_([a-zA-Z0-9]+)', inpName, re.I)
            if seqMethodOperation:
                self._operationName = seqMethodOperation[0]

    def get_componentName(self):
        return self._componentName
    def set_componentName(self, inpCompName):
        self._componentName
    def get_methodType(self):
        return self._methodType
    def get_portName(self):
        return self._portName
    def get_operationName(self):
        return self._operationName

class AutosarParserComponent(object):
    def __init__(self):
        self._componentName = ''
        self._swcFileName   = ''
        self._autosarScanComponent = None        
        
        self._reqRte_Calls = {}
        self._provRte_Calls = {}        
        self._reqRte_Calprm = {}
        self._provRte_Calprm = {}
        self._reqRte_COMCbk = {}
        self._provRte_COMCbk = {}
        self._reqRte_Mode = {}
        self._provRte_Mode = {}
        self._reqRte_Read = {}
        self._provRte_Read = {}
        self._reqRte_Send = {}
        self._provRte_Send = {}
        self._reqRte_Switch = {}
        self._provRte_Switch = {}
        self._reqRte_Write = {}
        self._provRte_Write = {}
        self._provRTEDefine = {}
        self._provRTERunnable = {}
        self._reqRTERunnable = {}  
        #TODO: replace all 'List' in names of Dictionaries with 'Dict'
        self._provMethodList = {} 
        self._reqMethodList = {}
        self._reqComponentList = {}             

    def _importMethod(self, methodRawContent, methodTypeName, provMethodListP, reqMethodListP):
        methodReturnType = ''
        methodName = ''
        methodArguments = ''

        seqMethod = re.findall(re.compile('(.*)('+methodTypeName+'.*)', re.I), methodRawContent)
        try:
            prevExpr, operation = seqMethod[0]
        except IndexError:
            print 'IndexError in: %s, content: %s ' % __name__, methodRawContent
        seqIsProvMethod = re.findall(r'(\w*)\s+$', prevExpr, re.I)
        methodObj = AutosarMethod()
        if not seqIsProvMethod:
            print 'SeqIsProvMethod==Null:'+self.get_componentName()+'(\''+methodRawContent+'\'),(\''+prevExpr+'\')'
        elif seqIsProvMethod and ('define' == seqIsProvMethod[0]):
            #print 'define operation:'+operation
            seqMethodName = re.findall(re.compile('('+methodTypeName+'[\w_]*)\s*\(', re.I), operation)
            if seqMethodName:
                methodName = seqMethodName[0]
            methodArguments = 'NotParsedArguments'
            methodReturnType = 'UnknownProvType'
            methodObj.set_properties(methodName, methodTypeName, methodReturnType, methodArguments, cMethodProvided)
            if not methodObj.get_name() in provMethodListP.keys():
                provMethodListP[methodObj.get_name()] = methodObj
                self._provMethodList[methodObj.get_name()] = methodObj                                    
        elif seqIsProvMethod[0] and ('return' != seqIsProvMethod[0]):
            methodReturnType = seqIsProvMethod[0]
            seqMethodName = re.findall(r'('+methodTypeName+'[\w_]*)\s*\(', operation, re.I)
            if seqMethodName:
                methodName = seqMethodName[0]
            seqMethodArgs = re.findall(methodTypeName+'[\w_]*\s*(\(.*)$', operation, re.I)
            if seqMethodArgs:
                methodArguments = extractLevelOneBlock(seqMethodArgs[0])
            if (methodName != '') and (methodReturnType != ''): 
                methodObj.set_properties(methodName, methodTypeName, methodReturnType, methodArguments, cMethodProvided)
                if not methodObj.get_name() in provMethodListP.keys():
                    provMethodListP[methodObj.get_name()] = methodObj
                    self._provMethodList[methodObj.get_name()] = methodObj
        else:
            seqMethodName = re.findall(r'('+methodTypeName+'[\w_]*)\s*\(', operation, re.I)
            if seqMethodName:
                methodName = seqMethodName[0]
            seqMethodArgs = re.findall(methodTypeName+'[\w_]*\s*(\(.*)$', operation, re.I)
            if seqMethodArgs:
                methodArguments = extractLevelOneBlock(seqMethodArgs[0])
            if (methodName != ''): 
                methodObj.set_properties(methodName, methodTypeName, 'UnknownReqType', methodArguments, cMethodRequired)
                if not methodObj.get_name() in reqMethodListP.keys():
                    reqMethodListP[methodObj.get_name()] = methodObj
                    self._reqMethodList[methodObj.get_name()] = methodObj                     

    def add_Rte_Call(self, inpRteCall):
        self._importMethod(inpRteCall, 'Rte_Call', self._provRte_Calls, self._reqRte_Calls)

    def add_Rte_Calprm(self, inpRteCalprm):
        self._importMethod(inpRteCalprm, 'Rte_Calprm', self._provRte_Calprm, self._reqRte_Calprm)

    def add_Rte_COMCbk(self, intRteCOMCbk):
        self._importMethod(intRteCOMCbk, 'Rte_COMCbk', self._provRte_COMCbk, self._reqRte_COMCbk)        

    def add_Rte_Mode(self, intRteMode):
        # '_' is appended intentionally after Rte_Mode. Be cautious with source for analysis
        self._importMethod(intRteMode, 'Rte_Mode_', self._provRte_Mode, self._reqRte_Mode)        

    def add_Rte_Read(self, intRteRead):
        self._importMethod(intRteRead, 'Rte_Read', self._provRte_Read, self._reqRte_Read)        

    def add_Rte_Send(self, intRteSend):
        self._importMethod(intRteSend, 'Rte_Send', self._provRte_Send, self._reqRte_Send)        

    def add_Rte_Switch(self, intRteSwitch):
        self._importMethod(intRteSwitch, 'Rte_Switch', self._provRte_Switch, self._reqRte_Switch)        

    def add_Rte_Write(self, intRteWrite):
        self._importMethod(intRteWrite, 'Rte_Write', self._provRte_Write, self._reqRte_Write)        

    def add_RTEDefine(self, intRteRTEDefine):
        returnType = 'UnknownRTEDefType'
        methodName = ''
        methodArguments = ''

        seqRteRTEDefine = re.findall(r'(RTEDefine.*)', intRteRTEDefine, re.I)
        operation = seqRteRTEDefine[0]
        methodObj = AutosarMethod()
        if operation!='':
            seqMethodName = re.findall(r'(RTEDefine[\w_]*)\s*\(', operation, re.I)
            if seqMethodName:
                methodName = seqMethodName[0]
            seqMethodArgs = re.findall(r'RTEDefine[\w_]*\s*(\(.*)$', operation, re.I)
            if seqMethodArgs:
                methodArguments = extractLevelOneBlock(seqMethodArgs[0])

            if (methodName != ''):
                methodObj.set_properties(methodName, 'RTEDefine', returnType, methodArguments, cMethodProvided)                 
                self._provRTEDefine[methodObj.get_name()] = methodObj
                self._provMethodList[methodObj.get_name()] = methodObj                

    def add_RTERunnable(self, intRTERunnable):
        methodReturnType = 'UnknownRTERunType'
        methodName = ''
        methodArguments = ''

        seqRTERunnable = re.findall(r'(.*)(RTERunnable.*)', intRTERunnable, re.I)
        prevExpr, operation = seqRTERunnable[0]
        seqProvRTERunnable = re.findall(r'(\w*)\s+$', prevExpr, re.I)
        methodObj = AutosarMethod()
        if seqProvRTERunnable[0] and ('return' != seqProvRTERunnable[0]):
            methodReturnType = seqProvRTERunnable[0]
            seqMethodName = re.findall(r'(RTERunnable[\w_]*)\s*\(', operation, re.I)
            if seqMethodName:
                methodName = seqMethodName[0]
            seqMethodArgs = re.findall(r'RTERunnable[\w_]*\s*(\(.*)$', operation, re.I)
            if seqMethodArgs:
                methodArguments = extractLevelOneBlock(seqMethodArgs[0])

            if (methodName != '') and (methodReturnType != ''): 
                methodObj.set_properties(methodName, 'RTERunnable', methodReturnType, methodArguments, cMethodProvided)                
                if not methodObj.get_name() in self._provRTERunnable.keys():
                    self._provRTERunnable[methodObj.get_name()] = methodObj
                    # Not included for the moment
                    #self._provMethodList[methodObj.get_name()] = methodObj                    
        else:
            seqMethodName = re.findall(r'(RTERunnable[\w_]*)\s*\(', operation, re.I)
            if seqMethodName:
                methodName = seqMethodName[0]
            seqMethodArgs = re.findall(r'RTERunnable[\w_]*\s*(\(.*)$', operation, re.I)
            if seqMethodArgs:
                methodArguments = extractLevelOneBlock(seqMethodArgs[0])

            if (methodName != ''): 
                methodObj.set_properties(methodName, methodReturnType, methodArguments)
                if not methodObj.get_name() in self._reqRTERunnable.keys():
                    self._reqRTERunnable[methodObj.get_name()] = methodObj

    #TODO: Replace the dictionary values with specified class object storing
    #required class object and list of required methods 
    def add_reqComponent(self, inpComponentName, inpMethod):
        if not inpComponentName in self._reqComponentList:
            self._reqComponentList[inpComponentName] = {}
            self._reqComponentList[inpComponentName][inpMethod.get_name()] = inpMethod 
        else:
            if not inpMethod.get_name() in self._reqComponentList[inpComponentName].keys():
                self._reqComponentList[inpComponentName][inpMethod.get_name()] = inpMethod

    def importAutosarScanComponent(self, scanComponent):
        self._autosarScanComponent = scanComponent
        self._componentName = scanComponent.get_name()        
        self._swcFileName = scanComponent.get_swcFileName()

        for Rte_Call in self._autosarScanComponent.get_Rte_Calls():
            self.add_Rte_Call(Rte_Call)

        for Rte_Calprm in self._autosarScanComponent.get_Rte_Calprm():
            self.add_Rte_Calprm(Rte_Calprm)

        for Rte_COMCbk in self._autosarScanComponent.get_Rte_COMCbk():
            self.add_Rte_COMCbk(Rte_COMCbk)
            
        for Rte_Mode in self._autosarScanComponent.get_Rte_Mode():
            self.add_Rte_Mode(Rte_Mode)

        for Rte_Read in self._autosarScanComponent.get_Rte_Read():
            self.add_Rte_Read(Rte_Read)

        for Rte_Send in self._autosarScanComponent.get_Rte_Send():
            self.add_Rte_Send(Rte_Send)
            
        for Rte_Switch in self._autosarScanComponent.get_Rte_Switch():
            self.add_Rte_Switch(Rte_Switch)

        for RTEDefine in self._autosarScanComponent.get_RTEDefine():
            self.add_RTEDefine(RTEDefine)

        for RTERunnable in self._autosarScanComponent.get_RTERunnable():
            self.add_RTERunnable(RTERunnable)

    def printInStrRequired(self):
        str = ''
        compPath = self._autosarScanComponent.get_path()        
        reqClassKeys = self._reqComponentList.keys()
        reqClassKeys.sort()
        for className in reqClassKeys:
            fpClassMeths = self._reqComponentList[className].keys()
            fpClassMeths.sort()
            seqReqCompSwcName = re.findall(r'\./([\w_]*)/', className, re.I)
            if seqReqCompSwcName:
                reqCompSwcName = seqReqCompSwcName[0]
            else:
                reqCompSwcName = className.split('.')[0] 
            for methodName in fpClassMeths:
                method = self._reqComponentList[className][methodName]
                str += ( self._autosarScanComponent.get_swcName()+'\t'
                        +self._autosarScanComponent.get_name()+'\t'
                        +reqCompSwcName+'\t'
                        +method.get_methodType()+'\t'
                        +method.get_portName()+'\t'
                        +method.get_operationName()+'\t'
                        +method.get_returnType()+'\t'
                        #+method.get_name()+'\t'
                        +method.get_arguments()+'\t'
                        +compPath+'\n')  
        return str

    def printInStrProvided(self):
        str = ''
        compPath = self._autosarScanComponent.get_path()
        providedMethodList = self._provMethodList.keys()
        providedMethodList.sort()
        for methodName in providedMethodList:
            method = self._provMethodList[methodName]
            try:
                str += ( self._autosarScanComponent.get_swcName()+'\t'
                        +self._autosarScanComponent.get_name()+'\t'
                        +method.get_methodType()+'\t'
                        +method.get_portName()+'\t'
                        +method.get_operationName()+'\t'
                        +method.get_returnType()+'\t'
                        +method.get_arguments()+'\t'
                        +compPath+'\n')
            except AttributeError:
                print 'Attribute Error: ' + __name__  
        return str

    def get_componentName(self):
        return self._componentName
    
    def get_swcFileName(self):
        return self._swcFileName

    def get_provRte_Calls(self):
        return self._provRte_Calls

    def get_reqRte_Calls(self):
        return self._reqRte_Calls

    def get_provRte_Calprm(self):
        return self._provRte_Calprm

    def get_reqRte_Calprm(self):
        return self._reqRte_Calprm

    def get_provRte_COMCbk(self):
        return self._provRte_COMCbk

    def get_reqRte_COMCbk(self):
        return self._reqRte_COMCbk

    def get_provRte_Mode(self):
        return self._provRte_Mode

    def get_reqRte_Mode(self):
        return self._reqRte_Mode
    
    def get_provRte_Read(self):
        return self._provRte_Read

    def get_reqRte_Read(self):
        return self._reqRte_Read
    
    def get_provRte_Send(self):
        return self._provRte_Send

    def get_reqRte_Send(self):
        return self._reqRte_Send

    def get_provRte_Switch(self):
        return self._provRte_Switch

    def get_reqRte_Switch(self):
        return self._reqRte_Switch

    def get_provRte_Write(self):
        return self._provRte_Write

    def get_reqRte_Write(self):
        return self._reqRte_Write

    def get_provRTEDefine(self):
        return self._provRTEDefine

    def get_reqRTEDefine(self):
        return self._reqRTEDefine

    def get_provRTERunnable(self):
        return self._provRTERunnable

    def get_reqRTERunnable(self):
        return self._reqRTERunnable
    
    def get_reqMethodList(self):
        return self._reqMethodList
    
    def get_reqComponentList(self):
        return self._reqComponentList
        