import re
from Parser.AutosarParser import AutosarParserComponent
from Scanner.AutosarScanner import AutosarAnalysedPortsList
from core import Repository, Factory
import Util.OpSys

cUnsuppliedComponent = 'Unsupplied'

class AutosarAPLGen(object):
    #TODO: prefix upper/lower case could be simplified as 're' is used
    portComponentPrefix = {'com>':'Com',
                           'diag>':'Diag',                           
                           'lin>':'Lin',
                           'io>':'Dio',
                           'inputs>':'Dio',
                           'pwm>':'Pwm',
                           'mem>':'MemIf',
                           'nvm>':'NvM',
                           'dem>':'Dem',
                           'ecum>':'SWC_EcuMA',
                           'ecuM>':'SWC_EcuMA',
                           'SwcEcuM>':'SWC_EcuMA',
                           'stateRequest>':'SWC_EcuMA',
                           'pia>':'Pia',
                           'PIA>':'Pia',
                           'lce>':'Lce',
                           'Lce>':'Lce',
                           'calc>':'swc_sf',
                           'sf>':'swc_sf',
                           'Sf>':'swc_sf',
                           'pa>':'swc_sf',
                           'dfz>':'swc_sf_dfz',
                           'Dfz>':'swc_sf_dfz',
                           'SysTime>':'swc_sf',
                           'ai>':'swc_la_integration_fem',
                           'doCold>':'swc_la_integration_fem',
                           'igr>':'swc_pf_igr',
                           'drv>':'swc_pw_driver',
                           'Drv>':'swc_pw_driver',
                           'doorState>':'swc_pw_driver',
                           'hall>':'swc_pw_driver',
                           'win>':'swc_pw_driver',
                           'pw>':'swc_pw_driver',
                           'Pw>':'swc_pw_driver',
                           'door':'swc_pw_driver',
                           'Szt>':'swc_pf_szt',
                           'Ecl>':'swc_ecl',
                           'ecl>':'swc_ecl',
                           'ca>':'swc_ca_master',
                           'doorHandle>':'swc_ca_master',
                           'cl>':'swc_cl',
                           'engine>':'swc_em',
                           'klemmen>':'swc_tc_master',
                           'Trsp>':'swc_tr_transponder',
                           'trsp>':'swc_tr_transponder',
                           'dtc>':'dem',
                           'rc>':'swc_rc_remotecontrol',
                           'RcDfz>':'swc_sf_dfz',
                           'coding>':'Coding',
                           'cp>':'Coding',
                           'MlcCp>':'Coding',
                           'AfsCp>':'Coding',
                           'BlcCp>':'Coding',
                           'ClcCp>':'Coding',
                           'FemCp>':'Coding',
                           'FlcCp>':'Coding',
                           'HbaCp>':'Coding',
                           'cf>':'Crypto',
                           }

#TODO: In all dictionaries, named <prefix>List or List<postfix> 'List'
# to be replaced with 'Dict'  
    def __init__(self, top):
        super(AutosarAPLGen, self)
        self._repository = Repository()
        self._factory = Factory(self._repository)
        self._AAPL = AutosarAnalysedPortsList()
        self._AAPL.buildScan(top)
        self._AAPLTop = top
        self._compDict = {}
        self._processPortCompPrefix()

    def _processPortCompPrefix(self):
        newDict = {}
        for item in AutosarAPLGen.portComponentPrefix.keys():
            newItem = ''
            if item.endswith('>'):
                newItem = r'^('+item.replace('>', ')([A-Z0-9]|$)')
            else:
                newItem = r'^('+item+'$)'
            newDict[newItem] = AutosarAPLGen.portComponentPrefix[item]
        AutosarAPLGen.portComponentPrefix = newDict

    def componentAssumption(self):
        for compName in self._compDict.keys():
            comp = self._compDict[compName]
            reqCompDict = comp.get_reqComponentList()
            for reqComp in reqCompDict.keys():
                if reqComp==cUnsuppliedComponent:
                    reqCompMethodDict = comp.get_reqComponentList()[reqComp]
                    for methodName in reqCompMethodDict.keys():
                        method = reqCompMethodDict[methodName]
                        for compPref in AutosarAPLGen.portComponentPrefix.keys():
                            seqStartsWith = re.findall(compPref, 
                                                       method.get_portName())
                            if len(seqStartsWith):
                                comp.add_reqComponent(AutosarAPLGen.portComponentPrefix[compPref],
                                                      method)
                                del reqCompMethodDict[methodName]

    def xmize(self):

        for scanCompName in self._AAPL.get_componentDict().keys():
            scanComp = self._AAPL.get_componentDict()[scanCompName]
            autosarComp = AutosarParserComponent()
            self._compDict[scanComp.get_swcFileName()] = autosarComp
            autosarComp.importAutosarScanComponent(scanComp)

        provRte_CallList = {}        
        provRte_CalprmList = {}
        provRte_COMCbkList = {}
        provRte_ModeList = {}
        provRte_ReadList = {}
        provRte_SendList = {}
        provRte_SwitchList = {}
        provRte_WriteList = {}
        provRTEDefineList = {}
        provRTERunnableList = {}

        for item in self._compDict.keys():
            fpClass = self._compDict[item]
            for provRte_CallsName in fpClass.get_provRte_Calls().keys():
                provRte_CallList[provRte_CallsName] = fpClass
            for provRte_CalprmName in fpClass.get_provRte_Calprm().keys():
                provRte_CalprmList[provRte_CalprmName] = fpClass
            for provRte_COMCbkName in fpClass.get_provRte_COMCbk().keys():
                provRte_COMCbkList[provRte_COMCbkName] = fpClass
            for provRte_ModeName in fpClass.get_provRte_Mode().keys():
                provRte_ModeList[provRte_ModeName] = fpClass
            for provRte_ReadName in fpClass.get_provRte_Read().keys():
                provRte_ReadList[provRte_ReadName] = fpClass
            for provRte_SendName in fpClass.get_provRte_Send().keys():
                provRte_SendList[provRte_SendName] = fpClass
            for provRte_SwitchName in fpClass.get_provRte_Switch().keys():
                provRte_SwitchList[provRte_SwitchName] = fpClass   
            for provRte_WriteName in fpClass.get_provRte_Write().keys():
                provRte_WriteList[provRte_WriteName] = fpClass
            for provRTEDefineName in fpClass.get_provRTEDefine().keys():
                provRTEDefineList[provRTEDefineName] = fpClass
            for provRTERunnableName in fpClass.get_provRTERunnable().keys():
                provRTERunnableList[provRTERunnableName] = fpClass

        for item in self._compDict.keys():
            fpClass = self._compDict[item]
            #TODO: The following for ... in ...: sections to be simplified
            # with one function call            
            for reqRte_Call in fpClass.get_reqRte_Calls().keys():
                if reqRte_Call in provRte_CallList.keys():
                    if fpClass != provRte_CallList[reqRte_Call]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRte_CallList[reqRte_Call].get_swcFileName(), 
                                                                               provRte_CallList[reqRte_Call].get_provRte_Calls()[reqRte_Call])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRte_Call, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRte_Calls()[reqRte_Call])
            for reqRte_Calprm in fpClass.get_reqRte_Calprm().keys():
                if reqRte_Calprm in provRte_CalprmList.keys():
                    if fpClass != provRte_CalprmList[reqRte_Calprm]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRte_CalprmList[reqRte_Calprm].get_swcFileName(), 
                                                                               provRte_CalprmList[reqRte_Calprm].get_provRte_Calprm()[reqRte_Calprm])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRte_Calprm, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRte_Calprm()[reqRte_Calprm])
            for reqRte_COMCbk in fpClass.get_reqRte_COMCbk().keys():
                if reqRte_COMCbk in provRte_COMCbkList.keys():
                    if fpClass != provRte_COMCbkList[reqRte_COMCbk]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRte_COMCbkList[reqRte_COMCbk].get_swcFileName(), 
                                                                               provRte_COMCbkList[reqRte_COMCbk].get_provRte_COMCbk()[reqRte_COMCbk])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRte_COMCbk, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRte_COMCbk()[reqRte_COMCbk])                    
            for reqRte_Mode in fpClass.get_reqRte_Mode().keys():
                if reqRte_Mode in provRte_ModeList.keys():
                    if fpClass != provRte_ModeList[reqRte_Mode]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRte_ModeList[reqRte_Mode].get_swcFileName(), 
                                                                               provRte_ModeList[reqRte_Mode].get_provRte_Mode()[reqRte_Mode])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRte_Mode, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRte_Mode()[reqRte_Mode])
            for reqRte_Read in fpClass.get_reqRte_Read().keys():
                if reqRte_Read in provRte_ReadList.keys():
                    if fpClass != provRte_ReadList[reqRte_Read]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRte_ReadList[reqRte_Read].get_swcFileName(), 
                                                                               provRte_ReadList[reqRte_Read].get_provRte_Read()[reqRte_Read])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRte_Read, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRte_Read()[reqRte_Read])                    
            for reqRte_Send in fpClass.get_reqRte_Send().keys():
                if reqRte_Send in provRte_SendList.keys():
                    if fpClass != provRte_SendList[reqRte_Send]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRte_SendList[reqRte_Send].get_swcFileName(), 
                                                                               provRte_SendList[reqRte_Send].get_provRte_Send()[reqRte_Send])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRte_Send, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRte_Send()[reqRte_Send])                    

            for reqRte_Switch in fpClass.get_reqRte_Switch().keys():
                if reqRte_Switch in provRte_SwitchList.keys():
                    if fpClass != provRte_SwitchList[reqRte_Switch]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRte_SwitchList[reqRte_Switch].get_swcFileName(), 
                                                                               provRte_SwitchList[reqRte_Switch].get_provRte_Switch()[reqRte_Switch])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRte_Switch, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRte_Switch()[reqRte_Switch])                    

            for reqRte_Write in fpClass.get_reqRte_Write().keys():
                if reqRte_Write in provRte_WriteList.keys():
                    if fpClass != provRte_WriteList[reqRte_Write]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRte_WriteList[reqRte_Write].get_swcFileName(), 
                                                                               provRte_WriteList[reqRte_Write].get_provRte_Write()[reqRte_Write])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRte_Write, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRte_Write()[reqRte_Write])                    

            for reqRTERunnable in fpClass.get_reqRTERunnable().keys():
                if reqRTERunnable in provRTERunnableList.keys():
                    if fpClass != provRTERunnableList[reqRTERunnable]:
                        self._compDict[fpClass.get_swcFileName()].add_reqComponent(provRTERunnableList[reqRTERunnable].get_swcFileName(), 
                                                                               provRTERunnableList[reqRTERunnable].get_provRTERunnable()[reqRTERunnable])
                    else:
                        print "Class: ", fpClass.get_swcFileName(), " uses its' interface" 
                else:
                    print 'Input: ', reqRTERunnable, '(of Class: ',fpClass.get_swcFileName(), ') is not provided'
                    self._compDict[fpClass.get_swcFileName()].add_reqComponent(cUnsuppliedComponent, 
                                                                           fpClass.get_reqRTERunnable()[reqRTERunnable])                    

        self.componentAssumption()

        fileReq = open(self._AAPLTop + Util.OpSys.pathDelimiter() + 'ReqMethods.txt', 'w')
        fileProv = open(self._AAPLTop + Util.OpSys.pathDelimiter() + 'ProvMethods.txt', 'w')
        compListNames = self._compDict.keys()
        compListNames.sort()
        for compName in compListNames:
            fileReq.write(self._compDict[compName].printInStrRequired())
            fileProv.write(self._compDict[compName].printInStrProvided())
        fileReq.close()
        fileProv.close()
