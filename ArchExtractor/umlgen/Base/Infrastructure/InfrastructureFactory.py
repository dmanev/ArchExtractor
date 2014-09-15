
import os
import Infrastructure.AEPackage
import Infrastructure.AEModel

class InfrastructureFactory(object):
    """Method Factory for the meta-model elements in
    package 'Infrastructure'"""
    def getAEPackage(self, inpPackagePath):
        """Returns 'AEPackage' by given input 'AEPackage' path.
        If it does not exists yet it creates it."""
        ## Bouml preserved body begin 000415EF
        outAEPackage = None
        if(inpPackagePath in self.itsAEPackageMap.keys()):
            outAEPackage = self.itsAEPackageMap[inpPackagePath]
        else:
            # Package does not exist so we have to create one
            leftPath, rightPath = os.path.split(inpPackagePath)
            newPackNameList = [rightPath]
            # Start to strip the given path and find the first appearance of 
            # matching path and existing package
            while (leftPath) and (leftPath not in self.itsAEPackageMap.keys()):
                leftPath, rightPath = os.path.split(leftPath)
                newPackNameList.insert(0, rightPath)
            # If leftPath is not empty then it exists in the package map
            rootPack = None
            if(leftPath):
                rootPack = self.itsAEPackageMap[leftPath]
            else:
                # else we have to create root package
                leftPath = newPackNameList.pop(0)
                rootPack = Infrastructure.AEPackage.AEPackage(leftPath)
                self.itsAEPackageMap[leftPath] = rootPack
                
            # continue creating the missed packages from the input path
            for newPackName in newPackNameList:
                newPack = Infrastructure.AEPackage.AEPackage(newPackName)
                leftPath = os.path.join(leftPath, newPackName)
                self.itsAEPackageMap[leftPath] = newPack
                rootPack.getItsAEPackageList().append(newPack)
                newPack.setItsParentPackage(rootPack)
                rootPack = newPack
            
            outAEPackage = rootPack

        return outAEPackage
        ## Bouml preserved body end 000415EF
        
    def getAEModel(self):
        """Returns AEModel from the factory.
        If it does not exists yet it creates it."""
        ## Bouml preserved body begin 0004376F
        outAEModel = Infrastructure.AEModel.AEModel(self)
        
        return outAEModel
        ## Bouml preserved body end 0004376F
        
    def getRootPackageList(self, outRootPackageList):
        """Returns list of root packages (AEPackage)"""
        ## Bouml preserved body begin 0004396F
        outRootPackageList = []
        for pack in self.itsAEPackageMap.values():
            if(not pack.getItsParentPackage()):
                outRootPackageList.append(pack)
        return outRootPackageList
        ## Bouml preserved body end 0004396F
        
    def __init__(self):
        self.itsAEPackageMap = dict()
        pass
    
