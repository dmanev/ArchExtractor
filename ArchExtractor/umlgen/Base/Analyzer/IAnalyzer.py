
import Infrastructure.AEModel

class IAnalyzer(object):
    """Base Analyzer interface"""
    def scan(self, topDir, inoutAEModel):
        """Start walking over the "topDir" project's files.
        Resulting model artefacts to be filled in 'inoutAEModel'"""
        ## Bouml preserved body begin 0001F76F
        return inoutAEModel
        ## Bouml preserved body end 0001F76F
        
    def __init__(self):
        pass
    
