# auto-generated test file
import unittest
import umlgen.Specific.STK.StkDataTypes.StkS8
# Start of user code imports
# End of user code

class StkS8Test(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Specific.STK.StkDataTypes.StkS8.StkS8()
        # Start of user code setUp
        self._testInstance = umlgen.Specific.STK.StkDataTypes.StkS8.StkS8()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test__init__(self):
        # Start of user code __init__
        self.assertEqual(self._testInstance.Name, 'S8')
        self.assertEqual(self._testInstance.lowerLimit, -126)
        self.assertEqual(self._testInstance.upperLimit, 127)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
