
import PortInterface.PortInterfaceFactory
import StkPortInterfaces.StkControlIf
import StkPortInterfaces.StkTOSSignalIf
import StkPortInterfaces.StkDATControlIf
import Datatype.DataTypeFactory
import PortInterface.ClientServerInterface
import PortInterface.SenderReceiverInterface

class StkPortInterfaceFactory(PortInterface.PortInterfaceFactory.PortInterfaceFactory):
    def getStkControlIf(self, inpNameIf):
        ## Bouml preserved body begin 0003D9EF
        outIPortInterface = self.getAbstractPortInterface('Ctrl_'+inpNameIf+'_If', 
                                                          PortInterface.ClientServerInterface.ClientServerInterface)
        if(len(outIPortInterface.getItsOperationList()) == 0):
            ctrlOp = PortInterface.Operation.Operation()
            ctrlOp.setName('Invoke')
            outIPortInterface.itsOperationList = [ctrlOp]

        return outIPortInterface        
        ## Bouml preserved body end 0003D9EF
        
    def getStkTOSSignalIf(self, inpNameIf, inpDataTypeFactory):
        ## Bouml preserved body begin 0003DA6F
        outIPortInterface = self.getAbstractPortInterface('TOSSig_'+inpNameIf+'_If',
                                                          PortInterface.SenderReceiverInterface.SenderReceiverInterface)

        if(len(outIPortInterface.getItsDataElementList()) == 0):
            DE = PortInterface.DataElement.DataElement()
            DE.setName(inpNameIf)
            DT = inpDataTypeFactory.getDataType('U1')
            DE.itsDataType = DT
            outIPortInterface.setItsDataElementList([DE])

        return outIPortInterface
        ## Bouml preserved body end 0003DA6F
        
    def getStkDATControlIf(self, inpNameIf, inpDataTypeFactory):
        ## Bouml preserved body begin 0003DAEF
        outIPortInterface = self.getAbstractPortInterface('DATCtrl_'+inpNameIf+'_If', 
                                                          PortInterface.ClientServerInterface.ClientServerInterface)
        if(len(outIPortInterface.getItsOperationList()) == 0):
            ctrlOp = PortInterface.Operation.Operation()
            ctrlOp.setName('Invoke')
            param = PortInterface.ParamData.ParamData()
            param.itsDataType = inpDataTypeFactory.getStkU8()
            param.setName('SubControlSelector')
            ctrlOp.setItsParamList([param])
            outIPortInterface.itsOperationList = [ctrlOp]

        return outIPortInterface
        ## Bouml preserved body end 0003DAEF
        
    def __init__(self):
        super(StkPortInterfaceFactory, self).__init__()
        pass
    
