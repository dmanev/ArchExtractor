'''
Created on Oct 23, 2013

@author: mitko
'''

from umlgen.Base.Analyzer.BaseAnalyzer import BaseAnalyzer
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

from umlgen.Base.SwComponent.Components.ComponentFactory import ComponentFactory
from umlgen.Base.Infrastructure.InfrastructureFactory import InfrastructureFactory
from umlgen.Specific.STK.StkPortInterfaces.StkPortInterfaceFactory import StkPortInterfaceFactory
from umlgen.Specific.STK.StkDataTypes.StkDataTypeFactory import StkDataTypeFactory  

from umlgen.Base.ModelConverter.XMIConverter import XMIConverter
from xmi.dumper import Dumper

import os


class ArchExtractor(object):
    def __init__(self):
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

        self.baseAnalyzer = BaseAnalyzer([JilFp, CHeaderFp, CFileFp])

        self.infFactory = InfrastructureFactory()
        self.aeModel = self.infFactory.getAEModel()
        self.aeModel.setItsPortInterfaceFactory(StkPortInterfaceFactory())
        self.aeModel.setItsDataTypeFactory(StkDataTypeFactory())

    def analyze(self, dirPath):
        self.aeModel = self.baseAnalyzer.scan(dirPath, self.aeModel)

        xmiConv = XMIConverter()
        xmiMdlRepo = None
        xmiMdlRepo = xmiConv.convert(self.aeModel, xmiMdlRepo)

        Dumper('AEModel').dump(xmiMdlRepo,
                               os.path.join(dirPath,
                                            self.aeModel.getName() + '.xmi'))

        return self.aeModel


if __name__ == '__main__':

    directory = '../../jilTester/Tester/Build'

    archExtract = ArchExtractor()
    archExtract.analyze(directory)
