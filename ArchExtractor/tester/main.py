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

if __name__ == '__main__':

    directory = '../../jilTester/Tester/Build'

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

    ba = BaseAnalyzer([JilFp, CHeaderFp, CFileFp])

    infFactory = InfrastructureFactory()
    aeModel = infFactory.getAEModel()
    aeModel.setItsPortInterfaceFactory(StkPortInterfaceFactory())
    aeModel.setItsDataTypeFactory(StkDataTypeFactory())

    aeModel = ba.scan(directory, aeModel)

    xmiConv = XMIConverter()
    xmiMdlRepo = None
    xmiMdlRepo = xmiConv.convert(aeModel, xmiMdlRepo)

    Dumper('AEModel').dump(xmiMdlRepo,
                           os.path.join(directory, aeModel.getName() + '.xmi'))
