/*
 * TRexPrimaryGeneratorAction.cc
 *
 *  Created on: Jun 15, 2014
 *      Author: sklupp
 */

#include "TRexPrimaryGeneratorAction.hh"
#include "TRexSettings.hh"

TRexPrimaryGeneratorAction::TRexPrimaryGeneratorAction() {
	// set the primary generator
	SetGenerator();
}

TRexPrimaryGeneratorAction::~TRexPrimaryGeneratorAction() {
	// TODO Auto-generated destructor stub
}

void TRexPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent){
	fCurrentGenerator->GeneratePrimaries(anEvent);
}

void TRexPrimaryGeneratorAction::SetGenerator(){
	std::string generatorName = TRexSettings::Get()->GetPrimaryGenerator();
	if(generatorName == "TestSource"){
		std::cout << "\nUsing test source ....\n" << std::endl;
		fCurrentGenerator = new TRexTestSource;
	}
	else if(generatorName == "Rutherford"){
		std::cout << "\nUsing Rutherford scattering ....\n" << std::endl;
		fCurrentGenerator = new TRexRutherford;
	}
	else if(generatorName == "AngularDistribution"){
		std::cout << "\nUsing given angular distribution ....\n" << std::endl;
		fCurrentGenerator = new TRexAngularDistribution;
	}
	else if(generatorName == "AlphaSource"){
		std::cout << "\nUsing alpha source ....\n" << std::endl;
		fCurrentGenerator = new TRexAlphaSource;
	}
}

void TRexPrimaryGeneratorAction::SetTree(TTree* tree){
	fCurrentGenerator->SetTree(tree);
	fCurrentGenerator->CreateTreeBranches();
}
