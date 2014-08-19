'''
Created on May 13, 2014

@author: mitko
'''

import lxml.etree as ET
import re

xml_filename = "./Tester/Build/Build.xmi"
xsl_filename = "./Tester/Build/BoUml2Eclipse.xsl"
out_filename = "./Tester/Build/Build.out.uml"

oldNsUML = r'xmlns:uml="http://schema.omg.org/spec/UML/2.1"'
newNsUML = r'xmlns:uml="http://www.eclipse.org/uml2/4.0.0/UML"'

oldNsXMI = r'xmlns:xmi="http://schema.omg.org/spec/XMI/2.1"'
newNsXMI = r'xmlns:xmi="http://www.omg.org/spec/XMI/20110701"'

def updateNamespaces(inpStr):
    sResult = re.sub(oldNsXMI, newNsXMI, inpStr)
    sResult = re.sub(oldNsUML, newNsUML, sResult)    

    return sResult

if __name__ == '__main__':
    dom = ET.parse(xml_filename)
    xslt = ET.parse(xsl_filename)
    transform = ET.XSLT(xslt)
    newdom = transform(dom)
    out_xml = updateNamespaces(ET.tostring(newdom, pretty_print=True))
    open(out_filename, 'w').write(out_xml)
