# auto-generated test file
import unittest
import umlgen.Specific.STK.StkPortInterfaces.StkControlIf
# Start of user code imports
from PortInterface.Operation import Operation
# End of user code

class StkControlIfTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Specific.STK.StkPortInterfaces.StkControlIf.StkControlIf()
        # Start of user code setUp
        self._testInstance = umlgen.Specific.STK.StkPortInterfaces.StkControlIf.StkControlIf()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test___init__(self):
        # Start of user code __init__
        self.assertEqual(self._testInstance.getName(), 'Control')
        self.assertNotEqual(self._testInstance.getItsOperationList(), [])
        self.assertNotEqual(self._testInstance.getItsOperationList(), None)
        for op in self._testInstance.getItsOperationList():
            self.assertIsInstance(op, Operation)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
