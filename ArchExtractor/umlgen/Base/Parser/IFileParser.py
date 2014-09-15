
import Components.IComponent

class IFileParser(object):
    """Abstract class (Interface) representing all file parsers in the system"""
    def updateComponent(self, inpName, filePath, outIComponent):
        """This method will find or create a component based on 
        the path given"""
        ## Bouml preserved body begin 0002E16F
        pass
        ## Bouml preserved body end 0002E16F
        
    def getComponentNameList(self, fileName):
        """Returns Components' name list"""
        ## Bouml preserved body begin 0001F96F
        pass
        ## Bouml preserved body end 0001F96F
        
    def fulfillComponentData(self, cmpName, filePath, inoutIComponent):
        """Fulfills Component's data based on the file under analysis"""
        ## Bouml preserved body begin 0002476F
        pass
        ## Bouml preserved body end 0002476F
        
    def fileFilter(self, fileName):
        """Returns True if the given path is of known file extension,
        otherwise returns False"""
        ## Bouml preserved body begin 000249EF
        pass
        ## Bouml preserved body end 000249EF
        
    def __init__(self):
        pass
    
