#auto-generated test file
import unittest
import umlgen.Base.Analyzer.IAnalyzer
#Start of user code imports
#End of user code

class IAnalyzerTest(unittest.TestCase):
    def setUp(self):
        #self._testInstance = umlgen.Base.Analyzer.IAnalyzer.IAnalyzer()
        #Start of user code setUp
        self._testInstance = umlgen.Base.Analyzer.IAnalyzer.IAnalyzer()
        #End of user code
        pass

    def tearDown(self):
        #Start of user code tearDown
        #End of user code
        pass

    def testscan(self):
        #Start of user code scan
        dummyModel = "123"
        self.assertEqual(self._testInstance.scan("topDir", dummyModel),
                         dummyModel,
                         "dummyModel value should be the\
                          result of the interface")
        #End of user code
        pass


if __name__ == '__main__':
    unittest.main()
