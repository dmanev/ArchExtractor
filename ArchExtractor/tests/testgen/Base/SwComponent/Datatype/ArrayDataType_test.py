# auto-generated test file
import unittest
import umlgen.Base.SwComponent.Datatype.ArrayDataType
# Start of user code imports
# End of user code

class ArrayDataTypeTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.SwComponent.Datatype.ArrayDataType.ArrayDataType()
        # Start of user code setUp
        self._testInstance = umlgen.Base.SwComponent.Datatype.ArrayDataType.ArrayDataType()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def testget_itsDataType(self):
        # Start of user code get_itsDataType
        self.assertEqual(self._testInstance.getItsDataType(), None)
        # End of user code
        pass

    def testget_maxNumberOfElements(self):
        # Start of user code get_maxNumberOfElements
        self.assertEqual(self._testInstance.getMaxNumberOfElements(), None)
        # End of user code
        pass

    def testset_itsDataType(self):
        # Start of user code set_itsDataType
        self._testInstance.setItsDataType("DummyDataType")
        self.assertEqual(self._testInstance.getItsDataType(), "DummyDataType")
        # End of user code
        pass

    def testset_maxNumberOfElements(self):
        # Start of user code set_maxNumberOfElements
        self._testInstance.setMaxNumberOfElements(123)
        self.assertEqual(self._testInstance.getMaxNumberOfElements(), 123)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
