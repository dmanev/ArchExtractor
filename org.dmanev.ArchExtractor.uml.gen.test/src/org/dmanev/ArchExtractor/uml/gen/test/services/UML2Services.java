package org.dmanev.ArchExtractor.uml.gen.test.services;

import org.eclipse.uml2.uml.Model;
import org.eclipse.uml2.uml.Component;
import org.eclipse.uml2.uml.Artifact;
import org.eclipse.uml2.uml.Package;
import org.eclipse.uml2.uml.Element;

import java.io.File;
import java.util.ArrayList;

public class UML2Services {
	
	private ArrayList<Component> collectComponentsFromPackage(Package pack){
		ArrayList<Component> elResult = new ArrayList<Component>();
		
		for (Package nestPack : pack.getNestedPackages()) {
			elResult.addAll(collectComponentsFromPackage(nestPack));
		}
		for (Element el : pack.getOwnedElements()){
			if(el instanceof Component){
				elResult.add((Component)el);
			}
		}
		
		return elResult;
	}
	
	public ArrayList<Component> getAllComponentsRecursively(Model inpModel)
			throws java.lang.IllegalArgumentException {
		
		ArrayList<Component> elResult = new ArrayList<Component>(); 
		
		for(Package nestPack : inpModel.getNestedPackages()) {
			elResult.addAll(collectComponentsFromPackage(nestPack));
		}
		
		return elResult;		
	}
	
	private ArrayList<Artifact> collectArtifactsFromPackage(Package pack){
		ArrayList<Artifact> elResult = new ArrayList<Artifact>();
		
		for (Package nestPack : pack.getNestedPackages()) {
			elResult.addAll(collectArtifactsFromPackage(nestPack));
		}
		for (Element el : pack.getOwnedElements()){
			if(el instanceof Artifact){
				elResult.add((Artifact)el);
			}
		}
		
		return elResult;
	}
	
	public ArrayList<Artifact> getAllArtifactsRecursively(Model inpModel)
			throws java.lang.IllegalArgumentException {
		
		ArrayList<Artifact> elResult = new ArrayList<Artifact>(); 
		
		for(Package nestPack : inpModel.getNestedPackages()) {
			elResult.addAll(collectArtifactsFromPackage(nestPack));
		}
		
		return elResult;		
	}	

	public String getElementPath(Element inpElement)
			throws java.lang.IllegalArgumentException {
		String sResult="";

		if(inpElement.getOwner() == null){
			sResult = "";
		} else {
			sResult += getElementPath(inpElement.getOwner().getNearestPackage()) + File.separator 
						+inpElement.getOwner().getNearestPackage().getName();
		}

		return sResult;
	}
}
