import re
import os
from Util.Lang import CCode

class AutosarScanComponent (object):
    def __init__(self, Name):
        super(AutosarScanComponent, self).__init__()
        self._swcFileName = ''
        self._scannedFileList = []
        self._swcName = ''
        self._name = Name
        self._path = ''
        self._Rte_Calls = []
        self._Rte_Calprm = []
        self._Rte_COMCbk = []
        self._Rte_Mode = []
        self._Rte_Read = []
        self._Rte_Send = []
        self._Rte_Switch = []
        self._Rte_Write = []
        self._RTEDefine = []
        self._RTERunnable = []

    def set_name(self, Name):
        self._name = Name
    def get_name(self):
        return self._name
    def get_swcName(self):
        return self._swcName 
    def get_scannedFileList(self):
        return self._scannedFileList
    def add_scannedFile(self, inpFileName):
        self._scannedFileList.append(inpFileName)
    def set_path(self, inpPath):
        if (self._path != '') and (self._path != inpPath):
            raise NameError('Same Component found on two different paths: '
                            +self._path+' and '+inpPath )
        else:
            self._path = inpPath
            seqSwcName = re.findall(r'\./([\w_]*)', inpPath, re.I) 
            self._swcName = seqSwcName[0] 
    def get_path(self):
        return self._path
    def get_Rte_Calls(self):
        return self._Rte_Calls
    def add_Rte_Call(self, rteCall):
        if not rteCall in self._Rte_Calls:
            self._Rte_Calls.append(rteCall)
    def get_Rte_Calprm(self):
        return self._Rte_Calprm
    def add_Rte_Calprm(self, rteCalprm):
        if not rteCalprm in self._Rte_Calprm:
            self._Rte_Calprm.append(rteCalprm)
    def get_Rte_COMCbk(self):
        return self._Rte_COMCbk
    def add_Rte_COMCbk(self, rteComCbk):
        if not rteComCbk in self._Rte_COMCbk:
            self._Rte_COMCbk.append(rteComCbk)
    def get_Rte_Mode(self):
        return self._Rte_Mode
    def add_Rte_Mode(self, rteMode):
        if not rteMode in self._Rte_Mode:
            self._Rte_Mode.append(rteMode)
    def get_Rte_Read(self):
        return self._Rte_Read
    def add_Rte_Read(self, rteRead):
        if not rteRead in self._Rte_Read:
            self._Rte_Read.append(rteRead)
    def get_Rte_Send(self):
        return self._Rte_Send
    def add_Rte_Send(self, rteSend):
        if not rteSend in self._Rte_Send:
            self._Rte_Send.append(rteSend)
    def get_Rte_Switch(self):
        return self._Rte_Switch
    def add_Rte_Switch(self, rteSwitch):
        if not rteSwitch in self._Rte_Switch:
            self._Rte_Switch.append(rteSwitch)
    def get_Rte_Write(self):
        return self._Rte_Write
    def add_Rte_Write(self, rteWrite):
        if not rteWrite in self._Rte_Write:
            self._Rte_Write.append(rteWrite)
    def get_RTEDefine(self):
        return self._RTEDefine
    def add_RTEDefine(self, rteDefine):
        if not rteDefine in self._RTEDefine:
            self._RTEDefine.append(rteDefine)
    def get_RTERunnable(self):
        return self._RTERunnable
    def add_RTERunnable(self, rteRunnable):
        if not rteRunnable in self._RTERunnable:
            self._RTERunnable.append(rteRunnable)                                            
    def set_swcFileName(self, fileName):
        if (self._swcFileName != '') and (self._swcFileName != fileName):
            raise NameError('Same Component file name in two different paths: '
                            +self._swcFileName+' and '+fileName )
        else:            
            self._swcFileName = fileName
    def get_swcFileName(self):
        return self._swcFileName

class AutosarAnalysedPortsList(object):
    def __init__(self):
        super(AutosarAnalysedPortsList, self).__init__()
        self._file_list = []
        self._comp_dict = {}
        #self._layer_list = {}

    def _findCompPath(self, inpCompName):
        compPath = ''
        pathListStr = '\n'.join(self._comp_dict.keys())
        seqPath = re.findall(r'(\./.*'+inpCompName+')', pathListStr, re.I)
        if seqPath:        
            compPath = seqPath[0]
        else:
            compPath = './unidentified'
        return compPath
    
    def get_fileList(self):
        return self._file_list    

    def add_componentFromAAPL(self, compPath, compFileName):
        compName = compFileName.split('.')[0]
        compFullPath = compPath + '/' + compFileName
        if compFullPath not in self._comp_dict.keys():
            self._comp_dict[compFullPath] = AutosarScanComponent(compName)
            self._comp_dict[compFullPath].set_swcFileName(compFileName)
            self._comp_dict[compFullPath].set_path(compPath)

    def add_componentFromRtiInc(self, compFileName):
        compName = compFileName.split('.')[0]
        #find component Path
        compPath = self._findCompPath(compName)
        compFullPath = compPath + '/' + compFileName
        if compFullPath not in self._comp_dict.keys():
            self._comp_dict[compFullPath] = AutosarScanComponent(compName)
            self._comp_dict[compFullPath].set_swcFileName(compFileName)
            self._comp_dict[compFullPath].set_path(compPath)
        return self._comp_dict[compFullPath]

    def get_component(self, compPath):
        if compPath in self._comp_dict.keys():
            return self._comp_dict[compPath]
        else:
            self._comp_dict[compPath] = AutosarScanComponent(compPath)
            return self._comp_dict[compPath]
    def get_componentDict(self):
        return  self._comp_dict

    def analyseAAPLFile(self, fileName):
        fileText = open(fileName, 'r').read()
        fileLines = fileText.split('\n')
        for item in fileLines: 
            # file format specific comment removing
            item = item.split('//')[0]
            item = re.sub(r'/\*.*\*/', '', item)
            item = re.sub(r'/\*.*$', '', item)
            # Rte_Call
            seqRteCall = re.findall(r'(\./.*)/(\w+\.\w):(.*)(Rte_Call.*)', item, re.I)
            seqRteCalprm = re.findall(r'(\./.*)/(\w+\.\w):(.*)(Rte_Calprm.*)', item, re.I)
            seqRteCOMCbk = re.findall(r'(\./.*)/(\w+\.\w):(.*)(Rte_COMCbk.*)', item, re.I) 
            # '_' is appended intentionally after Rte_Mode. Be cautious with source for analysis            
            seqRteMode = re.findall(r'(\./.*)/(\w+\.\w):(.*)(Rte_Mode_.*)', item, re.I)
            seqRteRead = re.findall(r'(\./.*)/(\w+\.\w):(.*)(Rte_Read.*)', item, re.I)
            seqRteSend = re.findall(r'(\./.*)/(\w+\.\w):(.*)(Rte_Send.*)', item, re.I)
            seqRteSwitch = re.findall(r'(\./.*)/(\w+\.\w):(.*)(Rte_Switch.*)', item, re.I)                                                
            seqRteWrite = re.findall(r'(\./.*)/(\w+\.\w):(.*)(Rte_Write.*)', item, re.I)            
            seqRTEDefine = re.findall(r'(\./.*)/(\w+\.\w):(.*)(RTEDefine.*)', item, re.I)
            seqRTERunnable = re.findall(r'(\./.*)/(\w+\.\w):(.*)(RTERunnable.*)', item, re.I)                                   
            currComp=None
            if seqRteCall:
                compPath, compFileName, prevExpr, operation = seqRteCall[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_Rte_Call(prevExpr + ' ' + operation)
            if seqRteCalprm:
                compPath, compFileName, prevExpr, operation = seqRteCalprm[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_Rte_Calprm(prevExpr + ' ' + operation)                
            if seqRteCOMCbk:
                compPath, compFileName, prevExpr, operation = seqRteCOMCbk[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_Rte_COMCbk(prevExpr + ' ' + operation)
            if seqRteMode:
                compPath, compFileName, prevExpr, operation = seqRteMode[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_Rte_Mode(prevExpr + ' ' + operation)                            
            if seqRteRead:
                compPath, compFileName, prevExpr, operation = seqRteRead[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_Rte_Read(prevExpr + ' ' + operation)                            
            if seqRteSend:
                compPath, compFileName, prevExpr, operation = seqRteSend[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_Rte_Send(prevExpr + ' ' + operation)                            
            if seqRteSwitch:
                compPath, compFileName, prevExpr, operation = seqRteSwitch[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_Rte_Switch(prevExpr + ' ' + operation)                            
            if seqRteWrite:
                compPath, compFileName, prevExpr, operation = seqRteWrite[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_Rte_Write(prevExpr + ' ' + operation)                            
            if seqRTEDefine:
                compPath, compFileName, prevExpr, operation = seqRTEDefine[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_RTEDefine(prevExpr + ' ' + operation)
            if seqRTERunnable:
                compPath, compFileName, prevExpr, operation = seqRTERunnable[0]
                #print compPath, compFileName, prevExpr, operation
                self.add_componentFromAAPL(compPath, compFileName)
                currComp = self.get_component(compPath + '/' + compFileName)
                currComp.add_RTERunnable(prevExpr + ' ' + operation)
            
            if currComp:
                currComp.add_scannedFile(fileName)                

    def analyseIncRteFile(self, inpPath, fileName):
        fullFilePath = inpPath + '\\' + fileName
        fileText = open(fullFilePath, 'r').read()
        cCodeContent = CCode().commentRemove(fileText)
        for RteCallOp in re.findall(r'(#define\s+Rte_Call.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)                
            currComp.add_Rte_Call(RteCallOp)
            currComp.add_scannedFile(fullFilePath)                   
        for RteCalprmOp in re.findall(r'(#define\s+Rte_Calprm.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_Rte_Calprm(RteCalprmOp)                
            currComp.add_scannedFile(fullFilePath)                
        for RteCOMCbkOp in re.findall(r'(#define\s+Rte_COMCbk.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_Rte_COMCbk(RteCOMCbkOp)
            currComp.add_scannedFile(fullFilePath)             
        # '_' is appended intentionally after Rte_Mode. Be cautious with source for analysis            
        for RteModeOp in re.findall(r'(#define\s+Rte_Mode_.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_Rte_Mode(RteModeOp)                            
            currComp.add_scannedFile(fullFilePath)                        
        for RteReadOp in re.findall(r'(#define\s+Rte_Read.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_Rte_Read(RteReadOp)
            currComp.add_scannedFile(fullFilePath)                          
        for RteSendOp in re.findall(r'(#define\s+Rte_Send.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_Rte_Send(RteSendOp)                            
            currComp.add_scannedFile(fullFilePath)
        for RteSwitchOp in re.findall(r'(#define\s+Rte_Switch.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_Rte_Switch(RteSwitchOp)                            
            currComp.add_scannedFile(fullFilePath)
        for RteWriteOp in re.findall(r'(#define\s+Rte_Write.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_Rte_Write(RteWriteOp)
            currComp.add_scannedFile(fullFilePath)
        for RteDefineOp in re.findall(r'(#define\s+RTEDefine.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_RTEDefine(RteDefineOp)
            currComp.add_scannedFile(fullFilePath)
        for RteRunnableOp in re.findall(r'(#define\s+RTERunnable.*)', cCodeContent, re.I):
            currComp = self.add_componentFromRtiInc(fileName)
            currComp.add_RTERunnable(RteRunnableOp)
            currComp.add_scannedFile(fullFilePath)            

    def buildScanHandler(self, arg, top, names):
        for item in names:
            if re.match(r'\w+\.(txt)$', item, re.I):
                self._file_list.append(top+'\\'+item)
                self.analyseAAPLFile(top+'\\'+item)
            elif re.match(r'\w+\.(h)$', item, re.I): 
                self._file_list.append(top+'\\'+item)
                self.analyseIncRteFile(top, item)

    def buildScan(self, top):
        os.path.walk(top, self.buildScanHandler, None)
#        for item in self._file_list:
#            print item            
#        for item in self._comp_dict.keys():
#            print item #, self._comp_dict[item].get_name()
#        print len(self._comp_dict.keys())
#
#        comp = self.get_component('./SWC_pw/SourceCode/SwcPwIntegrationRem.c')
#        for item in comp.get_RTERunnable():
#            print item
#        print len(comp.get_RTERunnable())
