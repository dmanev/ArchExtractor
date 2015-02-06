# auto-generated test file
import unittest
import umlgen.Base.Analyzer.BaseAnalyzer
# Start of user code imports
import os

import Parser.BaseFileParser
import Components.BaseComponent

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

class BaseAnalyzerTest(unittest.TestCase):
    def setUp(self):
        # self._testInstance = umlgen.Base.Analyzer.BaseAnalyzer.BaseAnalyzer()
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
        self._testInstance = self.baseAnalyzer

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

    def test__init__(self):
        # Start of user code __init__
        for bfp in self._testInstance.itsBaseFileParserList:
            self.assertIsInstance(bfp, Parser.BaseFileParser.BaseFileParser)
        # End of user code
        pass

    def testscan(self):
        # Start of user code scan
        self.aeModel = self.baseAnalyzer.scan(self._testDirPath, self.aeModel)
        self.assertEqual(self.aeModel.getName(), "Build")
        lvlOnePack = self.aeModel.getPackageList()
        self.assertItemsEqual(["Build"],
                              [pack.getName() for pack in lvlOnePack])

        lvlTwoPack = lvlOnePack[0].getItsAEPackageList()
        self.assertItemsEqual(["SOURCES"],
                              [pack.getName() for pack in lvlTwoPack])

        lvlThreePack = lvlTwoPack[0].getItsAEPackageList()
        self.assertItemsEqual(["DAT", "LAP"],
                              [pack.getName() for pack in lvlThreePack])

        lapPack = lvlThreePack[0]
        datPack = lvlThreePack[1]
        self.assertEqual(lapPack.getName(), "LAP")
        self.assertEqual(datPack.getName(), "DAT")
        self.assertItemsEqual(["lap_tfc", "lap_sup", "lap_supp"],
                              lapPack.itsElementMap.keys())
        self.assertItemsEqual(["dat", "dat_ana", "dat_cmn", "dat_cpu",
                               "dat_cpup", "dat_din", "dat_dou", "dat_kwp",
                               "dat_pan", "dat_pee", "dat_peep", "dat_pin",
                               "dat_pin_", "dat_pou", "dat_pwm", "datparam",
                               "dat_fake"],
                              datPack.itsElementMap.keys())
        for element in lapPack.getElementList():
            self.assertIsInstance(element,
                                  Components.BaseComponent.BaseComponent)
        for element in datPack.getElementList():
            self.assertIsInstance(element,
                                  Components.BaseComponent.BaseComponent)
        # End of user code
        pass

    def testset_itsBaseFileParserList(self):
        # Start of user code set_itsBaseFileParserList
        self._testInstance.setItsBaseFileParserList(
            self.baseAnalyzer.itsBaseFileParserList)
        for fp in self.baseAnalyzer.itsBaseFileParserList:
            self.assertIsInstance(fp, Parser.BaseFileParser.BaseFileParser)
        # End of user code
        pass


if __name__ == '__main__':
    unittest.main()
