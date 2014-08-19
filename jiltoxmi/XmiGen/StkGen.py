import re
import Util.OpSys
from Parser.StkParser import StkFileParser
from DataTypes import JilDataTypes
from Scanner.StkScanner import StkComponentList
from xmi.core import Repository, Factory, VisibilityKind, Parameter
from xmi.dumper import Dumper

class FootprintClass(object):
    def __init__(self):
        super(FootprintClass, self)
        self._inputs    = []
        self._outputs   = []
        self._prodControls = []
        self._onControls = []
        self._getters = []
        self._setters = []
        self._umlClass = None
        self._requiredClass = {}

    def importParserObj(self, parserObj):
        for seq in parserObj.get_inputs():
            inpName, inpType, inpDim = seq
            if inpDim:
                self._inputs.append(inpName+inpType+'256')
            else:
                self._inputs.append(inpName+inpType)
        for seq in parserObj.get_outputs():
            outName, outType, outDim = seq
            if outDim:
                self._outputs.append(outName+outType+'256')
            else:
                self._outputs.append(outName+outType)
        self._onControls = parserObj.get_onControls()
        self._prodControls = parserObj.get_prodControls()
        for seq in parserObj.get_getters():
            getrName, getrType, getrMethod, getrDim = seq
            newGetter = getrName+getrType+getrDim
            if newGetter not in self._getters: 
                self._getters.append(newGetter)
        for seq in parserObj.get_setters():
            setrName, setrType, setrMethod, setrDim = seq
            newSetter = setrName+setrType+setrDim
            if newSetter not in self._setters:                
                self._setters.append(setrName+setrType+setrDim)

    def sort(self):
        self._inputs.sort()
        self._outputs.sort()
        self._prodControls.sort()
        self._onControls.sort()
        self._getters.sort()
        self._setters.sort()

    def add_input(self, inpName):
        self._inputs.append(inpName)
    def get_inputs(self):
        return self._inputs
    def add_output(self, outName):
        self._outputs.append(outName)
    def get_outputs(self):
        return self._outputs
    def add_prodControl(self, pcName):
        self._prodControls.append(pcName)
    def get_prodControls(self):
        return self._prodControls
    def add_onControl(self, ocName):
        self._onControls.append(ocName)
    def get_onControls(self):
        return self._onControls
    def add_getter(self, gttrName):
        self._getters.append(gttrName)
    def get_getters(self):
        return self._getters
    def add_setter(self, sttrName):
        self._setters.append(sttrName)
    def get_setters(self):
        return self._setters
    def set_umlClass(self, umlClass):
        self._umlClass = umlClass
    def get_umlClass(self):
        return self._umlClass
    def add_requiredClass(self, fpClass):
        self._requiredClass[fpClass.get_umlClass().name] = fpClass
    def get_requiredClass(self, ClassName):
        if ClassName in self._requiredClass.keys():
            return self._requiredClass[ClassName]
        else:
            self._requiredClass[ClassName] = FootprintClass()
            return self._requiredClass[ClassName]
    def get_requiredClasses(self):
        return self._requiredClass
    def printInStr(self, indent=''):
        str = indent + 'Class: ' + self._umlClass.name
        str += indent +  'Requires methods from the following classes:'
        reqClassKeys = self._requiredClass.keys()
        reqClassKeys.sort()
        for className in reqClassKeys:
            str += '\n' + indent + '\tClass: ' + className
            fpClass = self._requiredClass[className]
            fpClass.sort()
            for input in fpClass.get_inputs():
                inpName, inpType, inpDim = re.findall(r'(\w+)([US]\d+Bit|None)(\d+|)', input)[0]
                if inpDim:
                    str += '\n' + indent + '\t\tget' + inpName + '(in Index: U8Bit): ' + inpType
                else:
                    if inpType != 'None':                    
                        str += '\n' + indent + '\t\tget' + inpName + '(): ' + inpType
                    else:
                        str += '\n' + indent + '\t\tget' + inpName + '()'
            for output in fpClass.get_outputs():
                outName, outType, outDim = re.findall(r'(\w+)([US]\d+Bit|None)(\d+|)', output)[0]                
                if outDim:
                    str += '\n' + indent + '\t\tset' + outName + '(in Index: U8Bit, in Value: ' + outType + ' )'
                else:
                    if outType != 'None':             
                        str += '\n' + indent + '\t\tset' + outName + '(in Value: ' + outType + ' )'
                    else:
                        str += '\n' + indent + '\t\tset' + outName + '()'
            for onControl in fpClass.get_onControls():
                str += '\n' + indent + '\t\tOnControl' + onControl + '()'
        str += '\n' + indent +  'Provides the following methods:'
        for setter in self._setters:
            sttrName, sttrType, sttrDim = re.findall(r'(\w+)([US]\d+Bit|None)(\d+|)', setter)[0]
            if sttrDim:
                str += '\n' + indent + '\t\tset' + sttrName + '(in Index: U8Bit, in Value: ' + sttrType + ' )' 
            else:
                if sttrType != 'None':
                    str += '\n' + indent + '\t\tset' + sttrName + '(in Value: ' + sttrType + ' )'
                else:
                    str += '\n' + indent + '\t\tset' + sttrName + '()'
        for getter in self._getters:
            gttrName, gttrType, gttrDim = re.findall(r'(\w+)([US]\d+Bit|None)(\d+|)', getter)[0]                
            if gttrDim:
                str += '\n' + indent + '\t\tget' + gttrName + '(in Index: U8Bit): ' + gttrType
            else:
                if gttrType != 'None':
                    str += '\n' + indent + '\t\tget' + gttrName + '(): ' + gttrType
                else:
                    str += '\n' + indent + '\t\tget' + gttrName + '()'
        for prodControl in self._prodControls:
            str += '\n' + indent + '\t\tProdControl' + prodControl + '()'
        str += '\n'             
                    
        return str

class StkGen(object):

    jilTypes = None

    def __init__(self, top):
        super(StkGen, self)
        #self._jilParsed = JilParser(filename)
        self._repository = Repository()
        self._factory = Factory(self._repository)
        StkGen.jilTypes = JilDataTypes(self._factory)
        self._componentList = StkComponentList()
        self._componentList.buildScan(top)
        self._top = top

    def importParserObj(self, componentClass, parseObj):
        for seq in parseObj.get_inputs():
            inpName, inpType, inpDim = seq
            inputOp = self._factory.create_Operation()
            inputOp.name = 'get' + inpName
            inputOp.set_isUnique(False)
            inputOp.set_type(StkGen.jilTypes.get_DataTypeByName(inpType))
            if inpDim:
                inpPar = Parameter(None, False, False, None, None, 
                                   StkGen.jilTypes.get_DataTypeByName('U8Bit'), 'Index')
                inputOp.add_ownedParameter(inpPar)
            inputOp.set_visibility(VisibilityKind().private)
            componentClass.add_ownedOperation(inputOp)
        for seq in parseObj.get_outputs():
            outName, outType, outDim = seq
            outputOp = self._factory.create_Operation()
            outputOp.name = 'set' + outName
            outputOp.set_isUnique(False)
            if outDim:
                outPar = Parameter(None, False, False, None, None, 
                                   StkGen.jilTypes.get_DataTypeByName('U8Bit'), 'Index')
                outputOp.add_ownedParameter(outPar)
            outPar = Parameter(None, False, False, None, None, 
                               StkGen.jilTypes.get_DataTypeByName(outType), 'Value')
            outputOp.add_ownedParameter(outPar)
            outputOp.set_visibility(VisibilityKind().private)            
            componentClass.add_ownedOperation(outputOp)
        for str in parseObj.get_prodControls():
            prodControlOp = self._factory.create_Operation()
            prodControlOp.name = 'prodControl' + str
            prodControlOp.set_isUnique(False)
            prodControlOp.set_visibility(VisibilityKind().private)            
            componentClass.add_ownedOperation(prodControlOp)
        for str in parseObj.get_onControls():
            onControlOp = self._factory.create_Operation()
            onControlOp.name = 'onControl' + str
            onControlOp.set_isUnique(False)
            componentClass.add_ownedOperation(onControlOp)
        for seq in parseObj.get_getters():
            getrName, getrType, getrMethod, getrDim = seq
            getrOp = self._factory.create_Operation()
            getrOp.name = 'get' + getrName + getrMethod
            getrOp.set_isUnique(False)
            getrOp.set_type(StkGen.jilTypes.get_DataTypeByName(getrType))
            if getrDim:
                getrPar = Parameter(None, False, False, None, None, 
                                   StkGen.jilTypes.get_DataTypeByName('U8Bit'), 'Index')
                getrOp.add_ownedParameter(getrPar)
            getrOp.set_visibility(VisibilityKind().public)
            componentClass.add_ownedOperation(getrOp)
        for seq in parseObj.get_setters():
            setrName, setrType, setrMethod, setrDim = seq
            setrOp = self._factory.create_Operation()
            setrOp.name = 'set' + setrName + setrMethod
            setrOp.set_isUnique(False)
            setrOp.set_type(StkGen.jilTypes.get_DataTypeByName(setrType))
            if setrDim:
                setrPar = Parameter(None, False, False, None, None, 
                                   StkGen.jilTypes.get_DataTypeByName('U8Bit'), 'Index')
                setrOp.add_ownedParameter(setrPar)
            setrOp.set_visibility(VisibilityKind().public)
            componentClass.add_ownedOperation(setrOp)

    def xmize(self):
        projPack = self._factory.create_Package()
        projPack.name = 'Project'

        footprintClassList = {}
        compList = {}

        layerListKeys = self._componentList.get_layerList().keys();
        layerListKeys.sort()
        for layer in layerListKeys:
            layerPack = self._factory.create_Package()
            layerPack.name = layer
            projPack.add_nestedPackage(layerPack)
            componentList = self._componentList.get_layerList()[layer]
            componentList.sort()
            for item in componentList:
                projClass = self._factory.create_Class()                                        
                projClass.name = item
                fpClass = FootprintClass()
                parserObj = StkFileParser()
                for jilFile in self._componentList.get_component(item).get_jilFiles():                  
                    parserObj.jilParse(jilFile)
                    #parserObj.reverseJil(jilFile+ '_')
                for headerFile in self._componentList.get_component(item).get_headerFiles():
                    parserObj.headerParse(headerFile)
                for cFile in self._componentList.get_component(item).get_cFiles():
                    parserObj.cParse(cFile)                
                parserObj.checkJilToCMapping()                    
                if not parserObj.isEmpty():
                    self.importParserObj(projClass, parserObj)
                    fpClass.importParserObj(parserObj)

                layerPack.ownedType.append(projClass)
                if  projClass.get_ownedAttribute() or projClass.get_ownedOperation():
                    projComponent = self._factory.create_Component()
                    projComponent.name = 'cmp_'+item
                    projComponent.add_providedClass(projClass)
                    layerPack.ownedType.append(projComponent)
                    fpClass.set_umlClass(projClass)
                    footprintClassList[item] = fpClass
                    compList[item] = projComponent          

        getterList = {}
        setterList = {}
        prodControlList = {}

        for item in footprintClassList.keys():
            fpClass = footprintClassList[item]
            for getter in fpClass.get_getters():
                getterList[getter] = fpClass
            for setter in fpClass.get_setters():
                setterList[setter] = fpClass
            for prodControl in fpClass.get_prodControls():
                prodControlList[prodControl] = fpClass

        for item in footprintClassList.keys():
            fpClass = footprintClassList[item]
            for input in fpClass.get_inputs():
                if input in getterList.keys():
                    if fpClass.get_umlClass() != getterList[input].get_umlClass():
                        compList[fpClass.get_umlClass().name].add_requiredClass(getterList[input].get_umlClass())
                        fpClass.get_requiredClass(getterList[input].get_umlClass().name).add_input(input)
                    else:
                        print "Class: ", fpClass.get_umlClass().name, " uses its' interface" 
                else:
                    print 'Input: ', input, '(of Class: ',fpClass.get_umlClass().name, ') is not provided' 
            for output in fpClass.get_outputs():
                if output in setterList.keys():
                    if fpClass.get_umlClass() != setterList[output].get_umlClass():
                        compList[fpClass.get_umlClass().name].add_requiredClass(setterList[output].get_umlClass())
                        fpClass.get_requiredClass(setterList[output].get_umlClass().name).add_output(output)                        
                    else:
                        print "Class: ", fpClass.get_umlClass().name, " uses its' interface"
                else:
                    print 'Output: ', output, '(of Class: ',fpClass.get_umlClass().name, ') is not provided'
            for onControl in fpClass.get_onControls():
                if onControl in prodControlList.keys():
                    if fpClass.get_umlClass() != prodControlList[onControl].get_umlClass():
                        compList[fpClass.get_umlClass().name].add_requiredClass(prodControlList[onControl].get_umlClass())
                        fpClass.get_requiredClass(prodControlList[onControl].get_umlClass().name).add_onControl(onControl)                        
                    else:   
                        print "Class: ", fpClass.get_umlClass().name, " uses its' interface"
                else:
                    print 'onControl: ', onControl, '(of Class: ',fpClass.get_umlClass().name, ') is not provided'

#        for item in compList.keys():
#            for reqClass in compList[item].get_requiredClass():
#                if reqClass.name == 'dat_dtc':
#                    print compList[item].name

#        for item in footprintClassList['dat_rke'].get_setters():
#            str = re.findall(r'(\w+)[US]\d+Bit*', item)[0]
#            print str

        fp = open(self._top + Util.OpSys.pathDelimiter() + projPack.name + '.txt', 'w')
        for layer in layerListKeys:
            componentList = self._componentList.get_layerList()[layer]
            componentList.sort()
            fp.write('Layer: ' + layer + '\n')
            indent = '\t'
            for item in componentList:
                if item in footprintClassList.keys():
                    fp.write( footprintClassList[item].printInStr(indent) + '\n')
        fp.close()

#        if 'dat_fpl' in footprintClassList['dat_trp'].get_requiredClasses().keys():
#            fpClass = footprintClassList['dat_trp'].get_requiredClasses()['dat_fpl']
#            for input in fpClass.get_inputs():
#                print input 
#            for output in fpClass.get_outputs():
#                print output
#            for onControl in fpClass.get_onControls():
#                print onControl

        Dumper().dump(self._repository, self._top + Util.OpSys.pathDelimiter() + projPack.name + '.xmi')
