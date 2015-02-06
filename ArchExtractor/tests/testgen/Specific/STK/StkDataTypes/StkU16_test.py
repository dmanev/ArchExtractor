# auto-generated test file
import unittest
import umlgen.Specific.STK.StkDataTypes.StkU16
# Start of user code imports
# End of user code

class StkU16Test(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Specific.STK.StkDataTypes.StkU16.StkU16()
        # Start of user code setUp
        self._testInstance = umlgen.Specific.STK.StkDataTypes.StkU16.StkU16()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test__init__(self):
        # Start of user code __init__
        self.assertEqual(self._testInstance.Name, 'U16')
        self.assertEqual(self._testInstance.lowerLimit, 0)
        self.assertEqual(self._testInstance.upperLimit, 65535)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
