# auto-generated test file
import unittest
import umlgen.Base.SwComponent.PortInterface.PortInterfaceFactory
# Start of user code imports
import os

import umlgen.Base.Analyzer.BaseAnalyzer
from PortInterface.ClientServerInterface import ClientServerInterface 

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
# End of user code

class PortInterfaceFactoryTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.SwComponent.PortInterface.PortInterfaceFactory.PortInterfaceFactory()
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
        self._testInstance = self.aeModel.getPortInterfaceFactory()

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

    def testgetAbstractPortInterface(self):
        # Start of user code getAbstractPortInterface
        # End of user code
        pass

    def testgetClientServerIf(self):
        # Start of user code getClientServerIf
        # Fulfill model data
        self.aeModel = self.baseAnalyzer.scan(self._testDirPath, self.aeModel)

        csIf = self._testInstance.getClientServerIf("TestIf")
        self.assertIsInstance(csIf, ClientServerInterface)
        # End of user code
        pass

    def testgetSenderReceiverIf(self):
        # Start of user code getSenderReceiverIf
        # End of user code
        pass

    def testget_itsIPortInterfaceMap(self):
        # Start of user code get_itsIPortInterfaceMap
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
