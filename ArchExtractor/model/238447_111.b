class StkCFileReqWriteDataCriteria
!!!232175.python!!!	execute(in self : , in inpTextContent : string, inout inoutIComponent : IComponent) : IComponent
        signalIdentifiers = []      
        #English/French version of the 'write' macros
        for seq in re.findall(r'mDAT(Write|Ecrire)(Table|Tableau|)\s*\(\s*([US]\d+)Bit\s*' +
                              ',\s*(\w+)\s*', 
                               inpTextContent):
            sttrLanguage, sttrIsTable, sttrType, sttrName = seq

            DE = PortInterface.DataElement.DataElement()
            DE.setName(sttrName)
            dtf = self.getDataTypeFactory()
            DT = dtf.getDataType(sttrType)

            if sttrIsTable:
                arrayDT = dtf.getArrayDataType('Arr'+sttrType)            
                arrayDT.itsDataType = DT
                # array size unknown
                #arrayDT.setMaxNumberOfElements(dataTypeDim)                                
                DE.itsDataType = arrayDT
            else:
                DE.itsDataType = DT
            pif = self.getPortInterfaceFactory()
            sendRecvIf = pif.getSenderReceiverIf(sttrName, [DE])
            reqPortGetter = PortInterface.ProvidedPort.ProvidedPort(sendRecvIf)
            reqPortGetter.setName("set"+sttrName)
            inoutIComponent.addPort(reqPortGetter)  
!!!232175.python!!!	execute(in self : , in inpTextContent : string, inout inoutIComponent : IComponent) : IComponent
        signalIdentifiers = []      
        #English/French version of the 'write' macros
        for seq in re.findall(r'mDAT(Write|Ecrire)(Table|Tableau|)\s*\(\s*([US]\d+)Bit\s*' +
                              ',\s*(\w+)\s*', 
                               inpTextContent):
            sttrLanguage, sttrIsTable, sttrType, sttrName = seq

            DE = PortInterface.DataElement.DataElement()
            DE.setName(sttrName)
            dtf = self.getDataTypeFactory()
            DT = dtf.getDataType(sttrType)

            if sttrIsTable:
                arrayDT = dtf.getArrayDataType('Arr'+sttrType)            
                arrayDT.itsDataType = DT
                # array size unknown
                #arrayDT.setMaxNumberOfElements(dataTypeDim)                                
                DE.itsDataType = arrayDT
            else:
                DE.itsDataType = DT
            pif = self.getPortInterfaceFactory()
            sendRecvIf = pif.getSenderReceiverIf(sttrName, [DE])
            reqPortGetter = PortInterface.RequiredPort.RequiredPort(sendRecvIf)
            reqPortGetter.setName("set"+sttrName)
            inoutIComponent.addPort(reqPortGetter)  
