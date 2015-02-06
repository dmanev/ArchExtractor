# auto-generated test file
import unittest
import umlgen.Specific.STK.StkDataTypes.StkVoid
# Start of user code imports
# End of user code

class StkVoidTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Specific.STK.StkDataTypes.StkVoid.StkVoid()
        # Start of user code setUp
        self._testInstance = umlgen.Specific.STK.StkDataTypes.StkVoid.StkVoid()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test___init__(self):
        # Start of user code __init__
        self.assertEqual(self._testInstance.Name, 'void')
        self.assertEqual(self._testInstance.lowerLimit, 0)
        self.assertEqual(self._testInstance.upperLimit, 0)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
