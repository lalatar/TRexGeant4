/*
 * TRexPrimaryGeneratorAction.hh
 *
 *  Created on: Jun 15, 2014
 *      Author: sklupp
 */

#ifndef TREXPRIMARYGENERATORACTION_HH_
#define TREXPRIMARYGENERATORACTION_HH_

#include "TRexBaseGenerator.hh"
#include "TRexTestSource.hh"
#include "TRexAlphaSource.hh"
#include "TRexRutherford.hh"
#include "TRexAngularDistribution.hh"

#include "MBglobals.hh"
#include "MiniBallSource.hh"

#include "TTree.h"

#include "G4VUserPrimaryGeneratorAction.hh"

class TRexPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
	TRexPrimaryGeneratorAction();
	virtual ~TRexPrimaryGeneratorAction();

	void GeneratePrimaries(G4Event *anEvent);
	TRexBaseGenerator* GetGenerator() {return fCurrentGenerator; };

	void SetTree(TTree *tree);

private:
	void SetGenerator();

	TRexBaseGenerator* fCurrentGenerator;
};

#endif /* TREXPRIMARYGENERATORACTION_HH_ */
