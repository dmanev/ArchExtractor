# auto-generated test file
import unittest
import umlgen.Base.Parser.IFileParser
# Start of user code imports
# End of user code

class IFileParserTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.Parser.IFileParser.IFileParser()
        # Start of user code setUp
        self._testInstance = umlgen.Base.Parser.IFileParser.IFileParser()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def testfileFilter(self):
        # Start of user code fileFilter
        self._testInstance.fileFilter("TestFileName")
        '''This is interface class so nothing to test'''
        # End of user code
        pass

    def testfulfillComponentData(self):
        # Start of user code fulfillComponentData
        self._testInstance.fulfillComponentData("TestCmpName",
                                                "File/Path",
                                                None)
        '''This is interface class so nothing to test'''
        # End of user code
        pass

    def testgetComponentNameList(self):
        # Start of user code getComponentNameList
        self._testInstance.getComponentNameList("TestFileName")
        '''This is interface class so nothing to test'''
        # End of user code
        pass

    def testupdateComponent(self):
        # Start of user code updateComponent
        self._testInstance.updateComponent("NoName", "File/Path", None)
        '''This is interface class so nothing to test'''
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
