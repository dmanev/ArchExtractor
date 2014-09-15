
import Infrastructure.PackageableElement

class DataType(Infrastructure.PackageableElement.PackageableElement):
    """Represents 'DataType' from the meta-model"""
    def __init__(self):
        super(DataType, self).__init__()
        #Lower limit of the data type element
        self.lowerLimit = None
        #Upper limit of the data type element
        self.upperLimit = None
        pass
    
