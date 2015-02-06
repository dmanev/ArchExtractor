# auto-generated test file
import unittest
import umlgen.Base.Infrastructure.AEPackage
# Start of user code imports
# End of user code

class AEPackageTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.Infrastructure.AEPackage.AEPackage()
        # Start of user code setUp
        self._testInstance = umlgen.Base.Infrastructure.AEPackage.AEPackage("DummyPack")
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

    def test_addElement(self):
        # Start of user code addElement
        # End of user code
        pass

    def test_getElementList(self):
        # Start of user code getElementList
        # End of user code
        pass

    def test_get_itsAEPackageList(self):
        # Start of user code get_itsAEPackageList
        # End of user code
        pass

    def test_get_itsParentPackage(self):
        # Start of user code get_itsParentPackage
        # End of user code
        pass

    def test_set_itsAEPackageList(self):
        # Start of user code set_itsAEPackageList
        dummyPackList = ["dummyPack1", "dummyPack2"]
        self._testInstance.setItsAEPackageList(dummyPackList)
        self.assertListEqual(self._testInstance.getItsAEPackageList(),
                             dummyPackList)
        # End of user code
        pass

    def test_set_itsParentPackage(self):
        # Start of user code set_itsParentPackage
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
