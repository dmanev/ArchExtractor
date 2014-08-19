<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xlink="http://www.w3.org/1999/xlink"
	xmlns:uml="http://schema.omg.org/spec/UML/2.1" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1"
	>

<!-- 	xmlns:uml="http://schema.omg.org/spec/UML/2.1" 
		
		xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" -->
	
<!-- 	xmlns:uml="http://www.eclipse.org/uml2/4.0.0/UML"
 
		xmlns:xmi="http://www.omg.org/spec/XMI/20110701" -->

	<xsl:template match="node()|@*">
		<xsl:copy>
			<xsl:apply-templates select="node()|@*" />
		</xsl:copy>
	</xsl:template>
	
	<xsl:template match="xmi:Documentation" />
	
    <xsl:template match="/xmi:XMI/uml:Model">
        <xsl:copy>
            <xsl:attribute name="xmi:version">20110701</xsl:attribute>
            <xsl:apply-templates select="@*|node()"/>
        </xsl:copy>
    </xsl:template>
    
	<xsl:template match="ownedOperation/@isUnique" />   

	<xsl:template match="/xmi:XMI">
		<xsl:apply-templates />
	</xsl:template>    

</xsl:stylesheet>