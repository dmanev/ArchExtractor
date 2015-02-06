# auto-generated test file
import unittest
import umlgen.Base.Infrastructure.PackageableElement
# Start of user code imports
# End of user code

class PackageableElementTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.Infrastructure.PackageableElement.PackageableElement()
        # Start of user code setUp
        self._testInstance = umlgen.Base.Infrastructure.PackageableElement.PackageableElement()
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test_get_itsParentPackage(self):
        # Start of user code get_itsParentPackage
        self.assertEqual(self._testInstance.getItsParentPackage(), None)
        # End of user code
        pass

    def test_set_itsParentPackage(self):
        # Start of user code set_itsParentPackage
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
