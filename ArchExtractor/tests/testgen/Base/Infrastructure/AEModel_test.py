# auto-generated test file
import unittest
import umlgen.Base.Infrastructure.AEModel
# Start of user code imports
from Infrastructure.InfrastructureFactory import InfrastructureFactory
from Components.ComponentFactory import ComponentFactory
# End of user code

class AEModelTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.Infrastructure.AEModel.AEModel()
        # Start of user code setUp
        self._testInstance = umlgen.Base.Infrastructure.AEModel.AEModel(InfrastructureFactory())
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown
        # End of user code
        pass

    def test___init__(self):
        # Start of user code __init__
        self.assertIsInstance(self._testInstance.getInfrastructureFactory(),
                              InfrastructureFactory)
        self.assertEqual(self._testInstance.getPackageList(), [])
        # End of user code
        pass

    def test_getComponentFactory(self):
        # Start of user code getComponentFactory
        # End of user code
        pass

    def test_getDataTypeFactory(self):
        # Start of user code getDataTypeFactory
        # End of user code
        pass

    def test_getInfrastructureFactory(self):
        # Start of user code getInfrastructureFactory
        # End of user code
        pass

    def test_getPackageList(self):
        # Start of user code getPackageList
        # End of user code
        pass

    def test_getPortInterfaceFactory(self):
        # Start of user code getPortInterfaceFactory
        # End of user code
        pass

    def test_set_itsComponentFactory(self):
        # Start of user code set_itsComponentFactory
        self._testInstance.setItsComponentFactory(ComponentFactory())
        self.assertIsInstance(self._testInstance.getComponentFactory(),
                              ComponentFactory)
        # End of user code
        pass

    def test_set_itsDataTypeFactory(self):
        # Start of user code set_itsDataTypeFactory
        # End of user code
        pass

    def test_set_itsInfrastructureFactory(self):
        # Start of user code set_itsInfrastructureFactory
        self._testInstance.setItsInfrastructureFactory(InfrastructureFactory())
        self.assertIsInstance(self._testInstance.getInfrastructureFactory(),
                              InfrastructureFactory)
        # End of user code
        pass

    def test_set_itsPortInterfaceFactory(self):
        # Start of user code set_itsPortInterfaceFactory
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
