# auto-generated test file
import unittest
import umlgen.Base.SwComponent.Components.BaseComponent
# Start of user code imports
# End of user code

class BaseComponentTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.SwComponent.Components.BaseComponent.BaseComponent()
        # Start of user code setUp
        self._testInstance = umlgen.Base.SwComponent.Components.BaseComponent.BaseComponent("TestCmp")
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test___init__(self):
        # Start of user code __init__
        # End of user code
        pass

    def test_addFileList(self):
        # Start of user code addFileList
        # End of user code
        pass

    def test_addPort(self):
        # Start of user code addPort
        # End of user code
        pass

    def test_get_fileList(self):
        # Start of user code get_fileList
        self.assertEqual(self._testInstance.getFileList(), [])
        # End of user code
        pass

    def test_get_itsIPortMap(self):
        # Start of user code get_itsIPortMap
        # End of user code
        pass

    def test_set_fileList(self):
        # Start of user code set_fileList
        fileList = ["File1", "File2", "File3"]
        self._testInstance.setFileList(fileList)
        self.assertListEqual(self._testInstance.getFileList(),
                             fileList)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
