class Singleton:
    __single = None
    def __init__( self ):
        if Singleton.__single:
            raise Singleton.__single
        Singleton.__single = self

class JilDataTypes(Singleton):
    dataType = {'':'',
                'None':'',
                'void':'void',
                'U1Bit':'U1',
                'U8Bit':'U8',
                'S8Bit':'S8',
                'U16Bit':'U16',
                'S16Bit':'S16',
                'U32Bit':'U32',
                'S32Bit':'S32',
                'U1':'U1',
                'U8':'U8',
                'S8':'S8',
                'U16':'U16',
                'S16':'S16',
                'U32':'U32',
                'S32':'S32'}
    dataTypeDict = {}
    factory = None
    def __init__(self, factory):
        Singleton.__init__(self)
        self.factory = factory
        for name in self.dataType.keys():
            jilType = self.factory.create_DataType() 
            jilType.name = name            
            self.dataTypeDict[name] = jilType
    def get_NewJilType(self, type):
        return JilDataTypes.dataType[type]
    def get_DataTypeByName(self, name):
        return self.dataTypeDict[self.dataType[name]]
     