# auto-generated test file
import unittest
import umlgen.Base.SwComponent.Components.IComponent
# Start of user code imports
# End of user code

class IComponentTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.SwComponent.Components.IComponent.IComponent()
        # Start of user code setUp
        self._testInstance = umlgen.Base.SwComponent.Components.IComponent.IComponent()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test_addPort(self):
        # Start of user code addPort
        self._testInstance.addPort("dummyPort")
        '''This is interface class so nothing to test'''
        # End of user code
        pass

    def test_getFileList(self):
        # Start of user code getFileList
        self._testInstance.getFileList()
        '''This is interface class so nothing to test'''
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
