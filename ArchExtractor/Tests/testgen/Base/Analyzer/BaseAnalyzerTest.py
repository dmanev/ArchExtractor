#auto-generated test file
import unittest
import umlgen.Base.Analyzer.BaseAnalyzer
#Start of user code imports
import Parser.BaseFileParser
import Parser.BasePortCriteria
#End of user code

class BaseAnalyzerTest(unittest.TestCase):
    def setUp(self):
        #self._testInstance = umlgen.Base.Analyzer.BaseAnalyzer.BaseAnalyzer()
        #Start of user code setUp
        self.bpc = Parser.BasePortCriteria.BasePortCriteria()
        self.bfp1 = Parser.BaseFileParser.BaseFileParser([self.bpc])
        self.bfp2 = Parser.BaseFileParser.BaseFileParser([self.bpc])
        self._testInstance = umlgen.Base.Analyzer.BaseAnalyzer.BaseAnalyzer([self.bfp1, self.bfp2])
        #End of user code
        pass

    def tearDown(self):
        #Start of user code tearDown
        #End of user code
        pass

    def test__init__(self):
        #Start of user code __init__
        self.assertEqual(self._testInstance.itsBaseFileParserList[0],
                         self.bfp1,
                         "Test first instance of BaseFileParser")
        self.assertEqual(self._testInstance.itsBaseFileParserList[1],
                         self.bfp2,
                         "Test second instance of BaseFileParser")
        #End of user code
        pass

    def testscan(self):
        #Start of user code scan
        #End of user code
        pass

    def testset_itsBaseFileParserList(self):
        #Start of user code set_itsBaseFileParserList
        #End of user code
        pass


if __name__ == '__main__':
    unittest.main()
