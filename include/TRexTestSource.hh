/*
 * TRexTestSource.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

//Simulates a quadruple alpha source

#ifndef TREXTESTSOURCE_HH_
#define TREXTESTSOURCE_HH_

#include "TRexBaseGenerator.hh"

#include "G4Proton.hh"

#include "Randomize.hh"

#include "math.h"

class G4ParticleGun;

class TRexTestSource : public TRexBaseGenerator {
public:
	TRexTestSource();
	virtual ~TRexTestSource();

	void GeneratePrimaries(G4Event *anEvent);
	//void CreateTreeBranches(TTree &tree);
	//void FillTree(TTree &tree);
	void CreateTreeBranches();

private:
	// shoot fReactionX, fReactionY, fReactionZ of the source
	void ShootReactionPosition();

	// shoot fThetaCM and fPhi isotropically 
	void CreateIsotropicDistribution();

	G4ParticleGun* particleGun;

	G4double fReactionEnergy;
	G4double fReactionX, fReactionY, fReactionZ;
	G4double fThetaCM, fPhi;
};

#endif /* TREXTESTSOURCE_HH_ */
