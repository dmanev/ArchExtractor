
import Infrastructure.PackageableElement

class DataType(Infrastructure.PackageableElement.PackageableElement):
    def __init__(self):
        super(DataType, self).__init__()
        self.lowerLimit = None
        self.upperLimit = None
        pass
    
