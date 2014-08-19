import re
import os
import Util

class ComponentFiles (object):
    def __init__(self, Name):
        super(ComponentFiles, self).__init__()
        self._name = Name
        self._layer = None
        self._jilFiles = []        
        self._headerFiles = []
        self._cFiles = []

    def set_name(self, Name):
        self._name = Name
    def get_name(self):
        return self._name
    def set_layer(self, fileName):
        directory = os.path.dirname(fileName)
        if directory:
            self._layer = os.path.split(directory)[1]
    def get_layer(self):
        return self._layer
    def get_jilFiles(self):
        return self._jilFiles
    def add_jilFile(self, jilFile):
        self._jilFiles.append(jilFile)
        self.set_layer(jilFile)
    def get_headerFiles(self):
        return self._headerFiles
    def add_headerFile(self, headerFile):
        self._headerFiles.append(headerFile)
        self.set_layer(headerFile)
    def get_cFiles(self):
        return self._cFiles
    def add_cFile(self, cFile):
        self._cFiles.append(cFile)
        self.set_layer(cFile)        
    def add_fileName(self, fileName):
        fileExt = re.findall(r'^\w+\.(c|h|jil)$', os.path.basename(fileName), re.I)[0]
        fileExt = fileExt.lower()
        if fileExt == 'jil':
            self.add_jilFile(fileName)
        elif fileExt == 'h':
            self.add_headerFile(fileName)
        elif fileExt == 'c':
            self.add_cFile(fileName)
        else:
            pass

class StkComponentList(object):
    def __init__(self):
        super(StkComponentList, self).__init__()
        self._comp_list = {}
        self._layer_list = {}

    def add_component(self, ComponentName):
        if ComponentName not in self._comp_list.keys():
            self._comp_list[ComponentName] = ComponentFiles(ComponentName)
    def get_component(self, ComponentName):
        if ComponentName in self._comp_list.keys():
            return self._comp_list[ComponentName]
        else:
            self._comp_list[ComponentName] = ComponentFiles(ComponentName)
            return self._comp_list[ComponentName]
    def get_componentList(self):
        return self._comp_list    
    def get_layerList(self):
        return self._layer_list

    def buildScanHandler(self, arg, top, names):
        for item in names:
            if re.match(r'\w+\.(c|h|jil)$', item, re.I):
                fileName = re.findall(r'^(\w+)\.\w+$', os.path.basename(item), re.I)[0]
                fileName = fileName.lower()
                if re.match(r'^\w+[x|p|j]$', fileName, re.I):
                    supposed_component = fileName[0:len(fileName)-1]
                    if supposed_component in self.get_componentList().keys():
                        self.get_component(supposed_component).add_fileName(top+Util.OpSys.pathDelimiter()+item)
                    else:
                        self.get_component(fileName).add_fileName(top+Util.OpSys.pathDelimiter()+item)
                else:
                    self.get_component(fileName).add_fileName(top+Util.OpSys.pathDelimiter()+item)

    def buildScan(self, top):
        os.path.walk(top, self.buildScanHandler, None)
        for item in self._comp_list.keys():
            layer = self._comp_list[item].get_layer()
            if layer:
                if layer not in self._layer_list.keys():
                    self._layer_list[layer] = [item]
                else:
                    self._layer_list[layer].append(item)
            else:
                self._layer_list['NoLayer'].append(item)
