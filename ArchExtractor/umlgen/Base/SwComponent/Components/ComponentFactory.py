
import Components.BaseComponent
import Components.IComponent

class ComponentFactory(object):
    """Method Factory for the meta-model elements in
    package 'Component'"""
    def getBaseComponent(self, inpNameCmp, outIComponent):
        """Returns BaseComponent by given Name.
        If the Name is not available it creates it."""
        ## Bouml preserved body begin 0003F86F
        outIComponent = None
        if(inpNameCmp in self.itsIComponentMap.keys()):
            outIComponent = self.itsIComponentMap[inpNameCmp]
        else:
            outIComponent = Components.BaseComponent.BaseComponent(inpNameCmp)
            self.itsIComponentMap[inpNameCmp] = outIComponent
        return outIComponent
        ## Bouml preserved body end 0003F86F
        
    def findComponent(self, inpNameCmp, outIComponent):
        """Finds a BaseComponent by Name"""
        ## Bouml preserved body begin 0003FC6F
        outIComponent = None
        if(inpNameCmp in self.itsIComponentMap.keys()):
            outIComponent = self.itsIComponentMap[inpNameCmp]

        return outIComponent
        ## Bouml preserved body end 0003FC6F
        
    def __init__(self):
        self.itsIComponentMap = dict()
        pass
    
