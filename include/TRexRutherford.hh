/*
 * TRexRutherford.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */


#ifndef TREXRUTHERFORD_HH_
#define TREXRUTHERFORD_HH_

#include "TRexBeam.hh"
#include "G4ParticleGun.hh"

#include "Randomize.hh"
#include "TMath.h"


class TRexRutherford : public TRexBeam {
public:
	TRexRutherford();
	virtual ~TRexRutherford();

	void GeneratePrimaries(G4Event *anEvent);
	
private:
	void ShootEjectileAndRecoilDirections();
	void CalculateScatteringProbability();
	void DoKinematicCalculation();

	G4double fNorm;
	G4double fEcm, fTcm;
	G4double fTcm3, fTcm4;
	G4double fPcm3, fPcm4;
	G4double fBeta, fGamma;
	G4double fBetaCm3, fBetaCm4;
};

#endif /* TREXRUTHERFORD_HH_ */
