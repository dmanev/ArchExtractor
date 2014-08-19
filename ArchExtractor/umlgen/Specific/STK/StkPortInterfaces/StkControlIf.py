
import PortInterface.ClientServerInterface
import PortInterface.Operation

class StkControlIf(PortInterface.ClientServerInterface.ClientServerInterface):
    def __init__(self):
        super(StkControlIf, self).__init__()
        ## Bouml preserved body begin 00031EEF
        self.setName('Control')
        ctrlOp = PortInterface.Operation.Operation()
        ctrlOp.setName('Envoke')
        self.itsOperationList = [ctrlOp] 
        ## Bouml preserved body end 00031EEF
        
    
