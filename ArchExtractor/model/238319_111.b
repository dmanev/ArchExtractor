class StkCFileReqReadDataCriteria
!!!232047.python!!!	execute(in self : , in inpTextContent : string, inout inoutIComponent : IComponent) : IComponent
        signalIdentifiers = []
        for seq in re.findall(r'mDAT(Read|Lire)(Table|Tableau|)\s*\(\s*([US]\d+)Bit\s*' +
                              ',\s*(\w+)\s*',  
                               inpTextContent):
            gttrLanguage, gttrIsTable, gttrType, gttrName = seq

            if (gttrName) not in signalIdentifiers:
                signalIdentifiers.append(gttrName)
                
            DE = PortInterface.DataElement.DataElement()
            DE.setName(gttrName)
            dtf = self.getDataTypeFactory()
            DT = dtf.getDataType(gttrType)

            if gttrIsTable:
                arrayDT = dtf.getArrayDataType('Arr'+gttrType)
                arrayDT.itsDataType = DT
                # array size unknown
                #arrayDT.setMaxNumberOfElements(dataTypeDim)                                
                DE.itsDataType = arrayDT
            else:
                DE.itsDataType = DT
            pif = self.getPortInterfaceFactory()
            sendRecvIf = pif.getSenderReceiverIf(gttrName, [DE])
            reqPortGetter = PortInterface.ProvidedPort.ProvidedPort(sendRecvIf)
            reqPortGetter.setName("get"+gttrName)
            inoutIComponent.addPort(reqPortGetter)  
!!!232047.python!!!	execute(in self : , in inpTextContent : string, inout inoutIComponent : IComponent) : IComponent
        signalIdentifiers = []
        for seq in re.findall(r'mDAT(Read|Lire)(Table|Tableau|)\s*\(\s*([US]\d+)Bit\s*' +
                              ',\s*(\w+)\s*',  
                               inpTextContent):
            gttrLanguage, gttrIsTable, gttrType, gttrName = seq

            if (gttrName) not in signalIdentifiers:
                signalIdentifiers.append(gttrName)
                
            DE = PortInterface.DataElement.DataElement()
            DE.setName(gttrName)
            dtf = self.getDataTypeFactory()
            DT = dtf.getDataType(gttrType)

            if gttrIsTable:
                arrayDT = dtf.getArrayDataType('Arr'+gttrType)
                arrayDT.itsDataType = DT
                # array size unknown
                #arrayDT.setMaxNumberOfElements(dataTypeDim)                                
                DE.itsDataType = arrayDT
            else:
                DE.itsDataType = DT
            pif = self.getPortInterfaceFactory()
            sendRecvIf = pif.getSenderReceiverIf(gttrName, [DE])
            reqPortGetter = PortInterface.RequiredPort.RequiredPort(sendRecvIf)
            reqPortGetter.setName("get"+gttrName)
            inoutIComponent.addPort(reqPortGetter)
