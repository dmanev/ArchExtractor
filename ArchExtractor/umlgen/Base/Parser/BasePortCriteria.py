
import PortInterface.IPortCriteria
import Infrastructure.FactoryProvider

class BasePortCriteria(PortInterface.IPortCriteria.IPortCriteria, Infrastructure.FactoryProvider.FactoryProvider):
    def __init__(self):
        super(BasePortCriteria, self).__init__()
        pass
    
