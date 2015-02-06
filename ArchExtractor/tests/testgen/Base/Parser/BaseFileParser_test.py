# auto-generated test file
import unittest
import umlgen.Base.Parser.BaseFileParser
# Start of user code imports
from Parser.BasePortCriteria import BasePortCriteria
# End of user code

class BaseFileParserTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.Parser.BaseFileParser.BaseFileParser()
        # Start of user code setUp
        bpc = BasePortCriteria()
        self._testInstance = umlgen.Base.Parser.BaseFileParser.BaseFileParser([bpc])
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test__init__(self):
        # Start of user code __init__
        # End of user code
        pass

    def testfileFilter(self):
        # Start of user code fileFilter
        # End of user code
        pass

    def testfulfillComponentData(self):
        # Start of user code fulfillComponentData
        # End of user code
        pass

    def testget_fileFilterCriteria(self):
        # Start of user code get_fileFilterCriteria
        self.assertEqual(self._testInstance.getFileFilterCriteria(), None)
        # End of user code
        pass

    def testpreprocessFile(self):
        # Start of user code preprocessFile
        self._testInstance.preprocessFile("File/Path")
        '''This function is not implemented'''
        # End of user code
        pass

    def testset_itsBasePortCriteriaList(self):
        # Start of user code set_itsBasePortCriteriaList
        self._testInstance.setItsBasePortCriteriaList([BasePortCriteria(),
                                                       BasePortCriteria()])
        for bpc in self._testInstance.itsBasePortCriteriaList:
            self.assertIsInstance(bpc, BasePortCriteria)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
