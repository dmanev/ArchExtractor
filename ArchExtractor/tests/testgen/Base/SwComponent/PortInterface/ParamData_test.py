# auto-generated test file
import unittest
import umlgen.Base.SwComponent.PortInterface.ParamData
# Start of user code imports
from Datatype.DataType import DataType
# End of user code

class ParamDataTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.SwComponent.PortInterface.ParamData.ParamData()
        # Start of user code setUp
        self._testInstance = umlgen.Base.SwComponent.PortInterface.ParamData.ParamData()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def testget_itsDataType(self):
        # Start of user code get_itsDataType
        # End of user code
        pass

    def testset_itsDataType(self):
        # Start of user code set_itsDataType
        self._testInstance.setItsDataType(DataType())
        self.assertIsInstance(self._testInstance.getItsDataType(),
                              DataType)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
