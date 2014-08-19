
import Components.IComponent
import re
import Parser.BasePortCriteria

class StkJilComponentCriteria(Parser.BasePortCriteria.BasePortCriteria):
    def execute(self, inpTextContent, inoutIComponent):
        ## Bouml preserved body begin 0002FD6F
        componentNameList = re.findall(r'Component\s+(\w+)', inpTextContent, re.I)
        if componentNameList:
                if(inoutIComponent.getName() != componentNameList[0].lower()):
                    #TODO: make it with error management system
                    print 'ERR: ' + inoutIComponent.getName() + ' name differs in JIL file definition(' + componentNameList[0] + ')'
        ## Bouml preserved body end 0002FD6F
        
    def __init__(self):
        super(StkJilComponentCriteria, self).__init__()
        pass
    
