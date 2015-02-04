# auto-generated test file
import unittest
import umlgen.Specific.STK.StkPortInterfaces.StkTOSSignalIf
# Start of user code imports
# End of user code

class StkTOSSignalIfTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Specific.STK.StkPortInterfaces.StkTOSSignalIf.StkTOSSignalIf()
        # Start of user code setUp
        self._testInstance = umlgen.Specific.STK.StkPortInterfaces.StkTOSSignalIf.StkTOSSignalIf()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test__init__(self):
        # Start of user code __init__
        self.assertEqual(self._testInstance.getName(), 'TOSSignal')
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
