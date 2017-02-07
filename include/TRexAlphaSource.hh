/*
 * TRexAlphaSource.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

//Simulates a quadruple alpha source

#ifndef TREXALPHASOURCE_HH_
#define TREXALPHASOURCE_HH_

#include "TRexBaseGenerator.hh"

#include "G4Alpha.hh"

#include "Randomize.hh"

#include "math.h"

class G4ParticleGun;

class TRexAlphaSource : public TRexBaseGenerator {
public:
	TRexAlphaSource();
	virtual ~TRexAlphaSource();

	void GeneratePrimaries(G4Event *anEvent);
	//void CreateTreeBranches(TTree &tree);
	//void FillTree(TTree &tree);
	void CreateTreeBranches();

private:
	// shoot fReactionX, fReactionY, fReactionZ at the surface of the alpha source
	void ShootReactionPosition();

	// shoot fThetaCM and fPhi isotropically in a half sphere
	void CreateIsotropicDistribution();

	G4ParticleGun* particleGun;

	G4double fReactionEnergy;
	G4double fReactionX, fReactionY, fReactionZ;
	G4double fThetaCM, fPhi;
};

#endif /* TREXALPHASOURCE_HH_ */
