# auto-generated test file
import unittest
import umlgen.Specific.STK.StkDataTypes.StkS16
# Start of user code imports
# End of user code

class StkS16Test(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Specific.STK.StkDataTypes.StkS16.StkS16()
        # Start of user code setUp
        self._testInstance = umlgen.Specific.STK.StkDataTypes.StkS16.StkS16()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test___init__(self):
        # Start of user code __init__
        self.assertEqual(self._testInstance.Name, 'S16')
        self.assertEqual(self._testInstance.lowerLimit, -32766)
        self.assertEqual(self._testInstance.upperLimit, 32767)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
