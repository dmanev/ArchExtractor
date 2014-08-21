<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xlink="http://www.w3.org/1999/xlink"
	xmlns:uml="http://schema.omg.org/spec/UML/2.1" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1"
	>

    <xsl:output method="xml" indent="yes" />
	<xsl:strip-space elements="*" />

	<!-- UML Primitive types definition -->
	<xsl:param name="importUMLPrimitiveTypes">
		<xsl:element name="packageImport">
			<xsl:attribute name="xmi:type">uml:PackageImport</xsl:attribute>
			<!-- Hard-coded "random" number. TODO: implement real UUID generation -->
			<xsl:attribute name="xmi:id">_qtlzMChbEeSHnqNh5PpH-A</xsl:attribute>
			<xsl:element name="importedPackage">
				<xsl:attribute name="xmi:type">uml:Model</xsl:attribute>
				<xsl:attribute name="href">pathmap://UML_LIBRARIES/UMLPrimitiveTypes.library.uml#_0</xsl:attribute>
			</xsl:element>
		</xsl:element>
	</xsl:param>

	<!-- String replace template -->
	<xsl:template name="string-replace-all">
		<xsl:param name="text" />
		<xsl:param name="replace" />
		<xsl:param name="by" />
		<xsl:choose>
			<xsl:when test="contains($text, $replace)">
				<xsl:value-of select="substring-before($text,$replace)" />
				<xsl:value-of select="$by" />
				<xsl:call-template name="string-replace-all">
					<xsl:with-param name="text"
						select="substring-after($text,$replace)" />
					<xsl:with-param name="replace" select="$replace" />
					<xsl:with-param name="by" select="$by" />
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$text" />
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="node()|@*">
		<xsl:copy>
			<xsl:apply-templates select="node()|@*" />
		</xsl:copy>
	</xsl:template>

    <!-- Remove xmi:Documentation tag -->	
	<xsl:template match="xmi:Documentation" />
	
	<!-- uml:Model modifications -->
    <xsl:template match="/xmi:XMI/uml:Model">
        <xsl:copy>
            <!-- Include xmi:version tag compliant with Eclipse -->
            <xsl:attribute name="xmi:version">20110701</xsl:attribute>
            
            <xsl:apply-templates select="@*"/>

            <!-- Import UML Library Primitive Types -->
            <xsl:copy-of select="$importUMLPrimitiveTypes"/>
            
            <xsl:apply-templates select="node()"/> 
        </xsl:copy>
    </xsl:template>

    <!-- Remove xmi:XMI tag and preserve the rest -->
	<xsl:template match="/xmi:XMI">
		<xsl:apply-templates />
	</xsl:template>
    
    <!-- Remove packagedElement's attribute "nestingPackage" -->
    <xsl:template match="packagedElement/@nestingPackage" />
    	
    <!-- Remove ownedOperation's attribute "isUnique" -->
    <xsl:template match="ownedOperation/@isUnique" />

	<!-- Replace "http://schema.omg.org/spec/UML/2.1/uml.xml" with "pathmap://UML_LIBRARIES/UMLPrimitiveTypes.library.uml" -->
	<xsl:template match="@*[contains(., 'http://schema.omg.org/spec/UML/2.1/uml.xml')]">
        <xsl:variable name="inputText">
            <xsl:value-of select="." />         
        </xsl:variable>	
        <xsl:attribute name="{name()}" namespace="{namespace-uri()}">
            <xsl:call-template name="string-replace-all">
                <xsl:with-param name="text" select="$inputText" />
                <xsl:with-param name="replace" select="'http://schema.omg.org/spec/UML/2.1/uml.xml'" />
                <xsl:with-param name="by" select="'pathmap://UML_LIBRARIES/UMLPrimitiveTypes.library.uml'" />
            </xsl:call-template>
        </xsl:attribute>
    </xsl:template>

    <!-- Remove ownedAttribute's attribute "class" -->
    <xsl:template match="ownedAttribute/@class" />

    <!-- Remove ownedAttribute's attribute "isUnique" -->
    <xsl:template match="ownedAttribute/@isUnique" />

    <!-- Remove ownedAttribute's attribute "xmi:type" -->
    <xsl:template match="ownedAttribute/@xmi:type" />
    
    <!-- Remove ownedOperation's attribute "class" -->
    <xsl:template match="ownedOperation/@class" />

    <!-- Replace Interface classes attribute "xmi:type" from "uml:Class" to "uml:Interface" -->
    <xsl:template match="packagedElement[@name='Interfaces']/packagedElement[@xmi:type='uml:Class']/@xmi:type">
        <xsl:attribute name="xmi:type" namespace="{namespace-uri()}">uml:Interface</xsl:attribute>        
    </xsl:template>

</xsl:stylesheet>