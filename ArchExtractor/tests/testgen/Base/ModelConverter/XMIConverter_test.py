# auto-generated test file
import unittest
import umlgen.Base.ModelConverter.XMIConverter
# Start of user code imports
import os
import umlgen.Base.Analyzer.BaseAnalyzer

from umlgen.Specific.STK.StkParser.StkJilFileParser import StkJilFileParser
from umlgen.Specific.STK.StkParser.StkJilFileCriteria.StkJilComponentCriteria import StkJilComponentCriteria
from umlgen.Specific.STK.StkParser.StkJilFileCriteria.StkJilOnCotrolCriteria import StkJilOnControlCriteria
from umlgen.Specific.STK.StkParser.StkJilFileCriteria.StkJilProdControlCriteria import StkJilProdControlCriteria
from umlgen.Specific.STK.StkParser.StkJilFileCriteria.StkJilTOSSignalCriteria import StkJilTOSSignalCriteria
from umlgen.Specific.STK.StkParser.StkJilFileCriteria.StkJilDataCriteria import StkJilDataCriteria

from umlgen.Specific.STK.StkParser.StkCHeaderFileParser import StkCHeaderFileParser
from umlgen.Specific.STK.StkParser.StkCImplFileParser import StkCImpFileParser 
from umlgen.Specific.STK.StkParser.StkCFileCriteria.StkCHeaderProvReadDataCriteria import StkCHeaderProvReadDataCriteria
from umlgen.Specific.STK.StkParser.StkCFileCriteria.StkCHeaderProvWriteDataCriteria import StkCHeaderProvWriteDataCriteria
from umlgen.Specific.STK.StkParser.StkCFileCriteria.StkCHeaderProvDATControlCriteria import StkCHeaderProvDATControlCriteria
from umlgen.Specific.STK.StkParser.StkCFileCriteria.StkCFileReqReadDataCriteria import StkCFileReqReadDataCriteria
from umlgen.Specific.STK.StkParser.StkCFileCriteria.StkCFileReqWriteDataCriteria import StkCFileReqWriteDataCriteria
from umlgen.Specific.STK.StkParser.StkCFileCriteria.StkCFileReqDATControlCriteria import StkCFileReqDATControlCriteria
from umlgen.Specific.STK.StkParser.StkCFileCriteria.StkCFileReqReadTOSSignalCriteria import StkCFileReqReadTOSSignalCriteria
from umlgen.Specific.STK.StkParser.StkCFileCriteria.StkCFileReqWriteTOSSignalCriteria import StkCFileReqWriteTOSSignalCriteria

from umlgen.Base.Infrastructure.InfrastructureFactory import InfrastructureFactory
from umlgen.Specific.STK.StkPortInterfaces.StkPortInterfaceFactory import StkPortInterfaceFactory
from umlgen.Specific.STK.StkDataTypes.StkDataTypeFactory import StkDataTypeFactory

from umlgen.Base.ModelConverter.XMIConverter import XMIConverter
# End of user code

class XMIConverterTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.ModelConverter.XMIConverter.XMIConverter()
        # Start of user code setUp
        JilCmpCriteria = StkJilComponentCriteria()
        JilOnCtrlCriteria = StkJilOnControlCriteria()
        JilProdCtrlCriteria = StkJilProdControlCriteria()
        JilTOSCtrlCriteria = StkJilTOSSignalCriteria()
        JilDataCriteria = StkJilDataCriteria()

        JilFp = StkJilFileParser([JilCmpCriteria,
                                  JilOnCtrlCriteria,
                                  JilProdCtrlCriteria,
                                  JilTOSCtrlCriteria,
                                  JilDataCriteria])

        CHeaderProvRDCriteria = StkCHeaderProvReadDataCriteria()
        CHeaderProvWTCriteria = StkCHeaderProvWriteDataCriteria()
        CHeaderProvDATCtrlCriteria = StkCHeaderProvDATControlCriteria()
        CFileReqRDCriteria = StkCFileReqReadDataCriteria()
        CFileReqWTCriteria = StkCFileReqWriteDataCriteria()
        CFileReqDATCtrlCriteria = StkCFileReqDATControlCriteria()
        CFileReqRDTOSSignalCriteria = StkCFileReqReadTOSSignalCriteria()
        CFileReqWTTOSSignalCriteria = StkCFileReqWriteTOSSignalCriteria()

        CHeaderFp = StkCHeaderFileParser([CHeaderProvRDCriteria,
                                          CHeaderProvWTCriteria,
                                          CHeaderProvDATCtrlCriteria,
                                          CFileReqRDCriteria,
                                          CFileReqWTCriteria,
                                          CFileReqDATCtrlCriteria])

        CFileFp = StkCImpFileParser([CFileReqRDCriteria,
                                     CFileReqWTCriteria,
                                     CFileReqDATCtrlCriteria,
                                     CFileReqRDTOSSignalCriteria,
                                     CFileReqWTTOSSignalCriteria])

        self.baseAnalyzer = umlgen.Base.Analyzer.BaseAnalyzer.BaseAnalyzer([JilFp, CHeaderFp, CFileFp])

        self.infFactory = InfrastructureFactory()
        self.aeModel = self.infFactory.getAEModel()
        self.aeModel.setItsPortInterfaceFactory(StkPortInterfaceFactory())
        self.aeModel.setItsDataTypeFactory(StkDataTypeFactory())
        self.xmiConverter = XMIConverter()
        self._testInstance = self.xmiConverter

        # Make data dir available in case test is being run in testsuit
        self._storedPath = os.getcwd()
        currentFileDir = os.path.dirname(os.path.realpath(__file__))
        os.chdir(currentFileDir)
        self._testDirPath = "../../../data/Build"
        # End of user code
        pass

    def tearDown(self):
        # Start of user code tearDown

        # Revert to initially stored directory
        os.chdir(self._storedPath)
        # End of user code
        pass

    def test___init__(self):
        # Start of user code __init__
        self.assertEqual(self._testInstance.xmiFactory, None)
        self.assertEqual(self._testInstance.xmiTypesMap, {})
        # End of user code
        pass

    def test_convert(self):
        # Start of user code convert

        # Fulfill model data
        self.aeModel = self.baseAnalyzer.scan(self._testDirPath, self.aeModel)
        # Convert to XMI model
        self._xmiMdlRepo = None
        self._xmiMdlRepo = self.xmiConverter.convert(self.aeModel,
                                                     self._xmiMdlRepo)
        # End of user code
        pass

    def test_getXMIBaseArrayDataType(self):
        # Start of user code getXMIBaseArrayDataType
        # End of user code
        pass

    def test_getXMIBaseDataType(self):
        # Start of user code getXMIBaseDataType
        # End of user code
        pass

    def test_importAEPackage(self):
        # Start of user code importAEPackage
        # End of user code
        pass

    def test_importBaseComponent(self):
        # Start of user code importBaseComponent
        # End of user code
        pass

    def test_importBaseInterfaces(self):
        # Start of user code importBaseInterfaces
        # End of user code
        pass

    def test_importClientServerInterface(self):
        # Start of user code importClientServerInterface
        # Fulfill model data
        self.aeModel = self.baseAnalyzer.scan(self._testDirPath, self.aeModel)

        pif = self.aeModel.getPortInterfaceFactory()
        ctrlIf = pif.getItsIPortInterfaceMap()["Ctrl_DATEnterActiveState_If"]
        self.assertNotEqual(ctrlIf.getItsOperationList(), None)

        op = ctrlIf.getItsOperationList()[0]
        self.assertEqual(op.getName(), "Invoke")

        dtf = self.aeModel.getDataTypeFactory()
        self.assertNotEqual(dtf.getItsDataTypeMap(), None)
        self.assertIn("void", dtf.getItsDataTypeMap().keys())
        # Set datatype for the operation

        # Convert to XMI model
        self._xmiMdlRepo = None
        self._xmiMdlRepo = self.xmiConverter.convert(self.aeModel,
                                                     self._xmiMdlRepo)
        # End of user code
        pass

    def test_importInterfaces(self):
        # Start of user code importInterfaces
        # End of user code
        pass

    def test_importSenderReceiverInterface(self):
        # Start of user code importSenderReceiverInterface
        # End of user code
        pass

    def test_importTypes(self):
        # Start of user code importTypes
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
