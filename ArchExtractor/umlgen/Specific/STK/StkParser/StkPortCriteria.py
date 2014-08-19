
import Parser.BasePortCriteria
import re
import StkDataTypes.StkDataTypeFactory

class StkPortCriteria(Parser.BasePortCriteria.BasePortCriteria):
    def __init__(self):
        super(StkPortCriteria, self).__init__()
        ## Bouml preserved body begin 00036E6F
        self.itsAccessModes = {}
        self.registerAccessModes()
        ## Bouml preserved body end 00036E6F
        
    def registerAccessModes(self):
        ## Bouml preserved body begin 00036DEF
        self.itsAccessModes = {'Defaut' : 'Default',
                               'Default' : 'Default', 
                               'Immediat' : 'Immediate',
                               'Immediate' : 'Immediate',
                               'Differe' : 'Delayed',
                               'Delayed' : 'Delayed'}
        ## Bouml preserved body end 00036DEF
        
    def extractLevelOneBlock(self, inpText):
        ## Bouml preserved body begin 000353EF
        openningBrace=0
        closingBrace=0
        startDataConfig=None
        endDataConfig=None
        result=None
        for brace in re.finditer(r'(?P<OpenningBrace>{)|(?P<ClosingBrace>})', inpText):
            if brace.group('OpenningBrace'):
                openningBrace+=1
                if not startDataConfig:
                    startDataConfig=brace.end()
            if brace.group('ClosingBrace'): 
                closingBrace+=1
                openningBrace-=1
                if startDataConfig and openningBrace==0 and not endDataConfig:
                    endDataConfig=brace.end()-1
            if startDataConfig and endDataConfig:
                result=inpText[startDataConfig:endDataConfig]
        return result
        ## Bouml preserved body end 000353EF
        
    
