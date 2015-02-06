# auto-generated test file
import unittest
import umlgen.Base.SwComponent.PortInterface.IPort
# Start of user code imports
# End of user code

class IPortTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.SwComponent.PortInterface.IPort.IPort()
        # Start of user code setUp
        self._testInstance = umlgen.Base.SwComponent.PortInterface.IPort.IPort()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test_getInterface(self):
        # Start of user code getInterface
        self._testInstance.getInterface()
        '''This is interface class so nothing to test'''
        # End of user code
        pass

    def test_setInterface(self):
        # Start of user code setInterface
        self._testInstance.setInterface("dummyIf")
        '''This is interface class so nothing to test'''
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
