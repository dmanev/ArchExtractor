class XMIConverter
!!!275823.python!!!	__init__(inout self : )
        self.interfaceCreateMap = {PortInterface.SenderReceiverInterface.SenderReceiverInterface:
                                        XMIConverter.importSenderReceiverInterface,
                                   PortInterface.ClientServerInterface.ClientServerInterface:
                                        XMIConverter.importClientServerInterface}
        self.xmiTypesMap = dict()
!!!327535.python!!!	getXMIBaseDataType(in self : )
        xmiDtCls = self.xmiFactory.create_Class()
        xmiDtCls.name = 'DataType'
        xmiPropLL = self.xmiFactory.create_Property()
        xmiPropLL.name = 'lowerLimit'
        xmiPropLL.set_type(xmi.core.Integer())
        xmiDtCls.add_ownedAttribute(xmiPropLL)
        xmiPropUL = self.xmiFactory.create_Property()
        xmiPropUL.name = 'upperLimit'
        xmiPropUL.set_type(xmi.core.Integer())
        xmiDtCls.add_ownedAttribute(xmiPropUL)
        if xmiDtCls.name not in self.xmiTypesMap:
            self.xmiTypesMap[xmiDtCls.name] = xmiDtCls
        return xmiDtCls
!!!334063.python!!!	getXMIBaseArrayDataType(in self : )
        xmiArrDtCls = self.xmiFactory.create_Class()
        xmiArrDtCls.name = 'ArrayDataType'
        xmiPropMNE = self.xmiFactory.create_Property()
        xmiPropMNE.name = 'maxNumberOfElements'
        xmiPropMNE.set_type(xmi.core.Integer())
        xmiArrDtCls.add_ownedAttribute(xmiPropMNE)
        xmiPropDT = self.xmiFactory.create_Property()
        xmiPropDT.name = 'dataType'
        xmiPropDT.set_type(self.xmiTypesMap['DataType'])
        xmiArrDtCls.add_ownedAttribute(xmiPropDT)
        if xmiArrDtCls.name not in self.xmiTypesMap:
            self.xmiTypesMap[xmiArrDtCls.name] = xmiArrDtCls
        return xmiArrDtCls
!!!283887.python!!!	importBaseComponent(in self : , in inpBaseComponent : BaseComponent, inout inoutXmiPackage : )
        xmiComponent = self.xmiFactory.create_Component()
        xmiComponent.name = inpBaseComponent.getName()
        for portName in sorted(inpBaseComponent.getItsIPortMap()):
            port = inpBaseComponent.getItsIPortMap()[portName]
            xmiInterface = self.xmiTypesMap[port.getInterface().getName()]          
            if(isinstance(port, PortInterface.ProvidedPort.ProvidedPort)):
                xmiComponent.add_providedClass(xmiInterface)
            elif(isinstance(port, PortInterface.RequiredPort.RequiredPort)):
                xmiComponent.add_requiredClass(xmiInterface)
            else:
                pass
        inoutXmiPackage.add_ownedType(xmiComponent)
        return inoutXmiPackage
!!!284143.python!!!	importSenderReceiverInterface(in self : , in inpSRIf : SenderReceiverInterface, inout inoutXmiPackage : )
        xmiIfCls = self.xmiFactory.create_Class()
        xmiIfCls.name = inpSRIf.getName()
        inoutXmiPackage.add_ownedType(xmiIfCls)
        self.xmiTypesMap[xmiIfCls.name] = xmiIfCls        
        for dataElement in inpSRIf.getItsDataElementList():
            xmiProp = self.xmiFactory.create_Property()
            xmiProp.name = dataElement.getName()
            dtName = dataElement.getItsDataType().getName()
            xmiDT = self.xmiTypesMap[dtName]
            xmiProp.set_type(xmiDT)
            xmiIfCls.add_ownedAttribute(xmiProp)        
        return inoutXmiPackage
!!!284271.python!!!	importClientServerInterface(in self : , in inpCSIf : ClientServerInterface, inout inoutXmiPackage : )
        xmiIfCls = self.xmiFactory.create_Class()
        xmiIfCls.name = inpCSIf.getName()
        inoutXmiPackage.add_ownedType(xmiIfCls)
        self.xmiTypesMap[xmiIfCls.name] = xmiIfCls
        for op in inpCSIf.getItsOperationList():
            xmiOp = self.xmiFactory.create_Operation()
            xmiOp.name = op.getName()
            if op.getItsDataType():
                xmiOp.type = self.xmiTypesMap[op.getItsDataType().getName()]
            for prm in op.getItsParamList():
                xmiPrm = self.xmiFactory.create_Parameter()
                xmiPrm.name = prm.getName()
                xmiPrm.type = self.xmiTypesMap[prm.getItsDataType().getName()]
                xmiOp.add_ownedParameter(xmiPrm)
            xmiIfCls.add_ownedOperation(xmiOp)
        return inoutXmiPackage        
!!!277231.python!!!	importAEPackage(in self : , in inpAEPackage : , inout inoutXmiPackage : )
        newXmiPackage = self.xmiFactory.create_Package()
        newXmiPackage.name = inpAEPackage.getName()

        inoutXmiPackage.add_nestedPackage(newXmiPackage)

        for subPack in sorted(inpAEPackage.getItsAEPackageList()):
            self.importAEPackage(subPack, newXmiPackage)

        for element in sorted(inpAEPackage.getElementList()):
            if(isinstance(element, Components.BaseComponent.BaseComponent)):
                newXmiPackage = self.importBaseComponent(element, newXmiPackage)

        return inoutXmiPackage
!!!300271.python!!!	importTypes(in self : , in inpAEModel : AEModel, inout inoutXmiPackage : )
        dtf = inpAEModel.getDataTypeFactory()
        ifPack = self.xmiFactory.create_Package()
        ifPack.name = "DataTypes"
        inoutXmiPackage.add_nestedPackage(ifPack)
        ifPack.add_ownedType(self.getXMIBaseDataType())
        ifPack.add_ownedType(self.getXMIBaseArrayDataType())

        dtList = [dt for dt in dtf.getItsDataTypeMap().values() 
                    if type(dt) is Datatype.DataType.DataType]
        arrDtList = [dt for dt in dtf.getItsDataTypeMap().values()
                        if type(dt) is Datatype.ArrayDataType.ArrayDataType]

        for dt in dtList:
            xmiDtCls = self.xmiFactory.create_Class()
            xmiDtCls.name = dt.getName()
            xmiDtCls.add_superClass(self.xmiTypesMap['DataType'])
            xmiPropLL = self.xmiFactory.create_Property()
            xmiPropLL.name = 'lowerLimit'
            xmiPropLL.set_type(xmi.core.Integer())
            xmiPropLL.set_default(dt.lowerLimit)
            xmiDtCls.add_ownedAttribute(xmiPropLL)
            xmiPropUL = self.xmiFactory.create_Property()
            xmiPropUL.name = 'upperLimit'
            xmiPropUL.set_type(xmi.core.Integer())
            xmiPropUL.set_default(dt.upperLimit)
            xmiDtCls.add_ownedAttribute(xmiPropUL)
            ifPack.add_ownedType(xmiDtCls)
            self.xmiTypesMap[dt.getName()] = xmiDtCls

        for arrDt in arrDtList:
            xmiDtCls = self.xmiFactory.create_Class()
            xmiDtCls.add_superClass(self.xmiTypesMap['ArrayDataType'])
            xmiDtCls.name = arrDt.getName()            
            xmiDT = self.xmiFactory.create_Property()
            xmiDT.name = 'dataType'
            xmiDT.set_type(self.xmiTypesMap[arrDt.getItsDataType().getName()])
            xmiDtCls.add_ownedAttribute(xmiDT)
            ifPack.add_ownedType(xmiDtCls)
            self.xmiTypesMap[arrDt.getName()] = xmiDtCls

        return inoutXmiPackage
!!!300527.python!!!	importInterfaces(in self : , in inpAEModel : AEModel, inout inoutXmiPackage : )
        pif = inpAEModel.getPortInterfaceFactory()
        xmiIfPack = self.xmiFactory.create_Package()
        xmiIfPack.name = "Interfaces"
        inoutXmiPackage.add_nestedPackage(xmiIfPack)
        for ifName in sorted(pif.getItsIPortInterfaceMap()):
            aeInterface = pif.getItsIPortInterfaceMap()[ifName]
            if type(aeInterface) in self.interfaceCreateMap:
                xmiIfPack = self.interfaceCreateMap[type(aeInterface)](self, aeInterface, xmiIfPack)

        return inoutXmiPackage
!!!275695.python!!!	convert(in self : , in inpAEModel : AEModel, out outXMIMdlRepo : )
        outXMIMdlRepo = xmi.core.Repository()
        self.xmiFactory = xmi.core.Factory(outXMIMdlRepo)

        xmiProjPackage = self.xmiFactory.create_Package()
        xmiProjPackage.name = inpAEModel.getName()
        
        self.importTypes(inpAEModel, xmiProjPackage)
        
        self.importInterfaces(inpAEModel, xmiProjPackage)

        for pack in sorted(inpAEModel.getPackageList()):
            self.importAEPackage(pack, xmiProjPackage)

        return outXMIMdlRepo
!!!284143.python!!!	importSenderReceiverInterface(in self : , in inpSRIf : SenderReceiverInterface, inout inoutXmiPackage : )
        xmiIfCls = self.xmiFactory.create_Class()
        xmiIfCls.name = inpSRIf.getName()
        inoutXmiPackage.add_ownedType(xmiIfCls)
        self.xmiTypesMap[xmiIfCls.name] = xmiIfCls
		# Show inheritense in model
        superClassName = inpSRIf.__class__.__name__
        if superClassName in self.xmiTypesMap:
            xmiIfCls.add_superClass(self.xmiTypesMap[superClassName])
        for dataElement in inpSRIf.getItsDataElementList():
            xmiProp = self.xmiFactory.create_Property()
            xmiProp.name = dataElement.getName()
            dtName = dataElement.getItsDataType().getName()
            xmiDT = self.xmiTypesMap[dtName]
            xmiProp.set_type(xmiDT)
            xmiIfCls.add_ownedAttribute(xmiProp)
        return inoutXmiPackage
!!!284271.python!!!	importClientServerInterface(in self : , in inpCSIf : ClientServerInterface, inout inoutXmiPackage : )
        xmiIfCls = self.xmiFactory.create_Class()
        xmiIfCls.name = inpCSIf.getName()
        inoutXmiPackage.add_ownedType(xmiIfCls)
        self.xmiTypesMap[xmiIfCls.name] = xmiIfCls
		# Show inheritense in model
        superClassName = inpCSIf.__class__.__name__
        if superClassName in self.xmiTypesMap:
            xmiIfCls.add_superClass(self.xmiTypesMap[superClassName])
        for op in inpCSIf.getItsOperationList():
            xmiOp = self.xmiFactory.create_Operation()
            xmiOp.name = op.getName()
            if op.getItsDataType():
                xmiOp.type = self.xmiTypesMap[op.getItsDataType().getName()]
            for prm in op.getItsParamList():
                xmiPrm = self.xmiFactory.create_Parameter()
                xmiPrm.name = prm.getName()
                xmiPrm.type = self.xmiTypesMap[prm.getItsDataType().getName()]
                xmiOp.add_ownedParameter(xmiPrm)
            xmiIfCls.add_ownedOperation(xmiOp)
        return inoutXmiPackage        
!!!300527.python!!!	importInterfaces(in self : , in inpAEModel : AEModel, inout inoutXmiPackage : )
        pif = inpAEModel.getPortInterfaceFactory()
        xmiIfPack = self.xmiFactory.create_Package()
        xmiIfPack.name = "Interfaces"
        inoutXmiPackage.add_nestedPackage(xmiIfPack)
        # Import base interfaces SenderReceiverInterface
        # and ClientServerInterface.
        # Needed to show the inheritance of the rest of
        # the interfaces. Those could be surpassed with
        # the use of <<stereotypes>>, but such are missing
        # from current XMI implementation
        self.importBaseInterfaces(xmiIfPack)
        for ifName in sorted(pif.getItsIPortInterfaceMap()):
            aeInterface = pif.getItsIPortInterfaceMap()[ifName]
            if type(aeInterface) in self.interfaceCreateMap:
                xmiIfPack = self.interfaceCreateMap[type(aeInterface)](self,
                                                                       aeInterface,
                                                                       xmiIfPack)

        return inoutXmiPackage
