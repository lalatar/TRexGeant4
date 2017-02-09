/*
 * TRexBarrelDeltaESingleSensitiveDetector.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRexBarrelDeltaESingleSensitiveDetector.hh"
#include "TRexSettings.hh"

//TRexBarrelDeltaESingleSensitiveDetector::TRexBarrelDeltaESingleSensitiveDetector() {
//}

TRexBarrelDeltaESingleSensitiveDetector::TRexBarrelDeltaESingleSensitiveDetector(G4String name, G4String direction, int id):
	G4VSensitiveDetector(name) {
	fName = name;
	fDirection = direction;
	fID = id;
	fCollectionID = -1;

	fBaseName = fName;
	fBaseName.erase(fBaseName.end()-1, fBaseName.end());

	collectionName.insert("Collection" + name);

	fBarrelDeltaESingle = new ParticleMC();

	if(fBaseName == "FBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetFBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetFBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetFBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetFBarrelDeltaESingleEnergyResolution();
	} else if(fBaseName == "SecondFBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetSecondFBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetSecondFBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetSecondFBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetSecondFBarrelDeltaESingleEnergyResolution();
	} else if(fBaseName == "MBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetMBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetMBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetMBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetMBarrelDeltaESingleEnergyResolution();
	} else if(fBaseName == "BBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetBBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetBBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetBBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetBBarrelDeltaESingleEnergyResolution();
	} else if(fBaseName == "SecondBBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetSecondBBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetSecondBBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetSecondBBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetSecondBBarrelDeltaESingleEnergyResolution();
	} else {
		std::cerr << "Detector Name " << fBaseName << " is wrong!" << std::endl;
	}

	//histoXvsY = new TH2F(Form("histoXvsY_%d", fID), "histoXvsY", 600, -30, 30, 700, 0, 70);
	//histoZ = new TH1F(Form("histoZ_%d", fID), "histoZ", 500, 0, 50);
}

TRexBarrelDeltaESingleSensitiveDetector::~TRexBarrelDeltaESingleSensitiveDetector() {
	// TODO Auto-generated destructor stub

	//histoXvsY->SaveAs(Form("histoXvsY_%d.root", fID));
	//histoZ->SaveAs(Form("histoZ_%d.root", fID));

	delete fBarrelDeltaESingle;
	//delete fHitCollection;
}

// initialize event
void TRexBarrelDeltaESingleSensitiveDetector::Initialize(G4HCofThisEvent *HCE) {
	//G4std::cout << "Initialize sensitive detector" << G4std::endl;

	fHitCollection = new TRexHitsCollection(SensitiveDetectorName, collectionName[0]);

	if(fCollectionID < 0) {
		fCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}

	HCE->AddHitsCollection(fCollectionID, fHitCollection);
}

// process hits
G4bool TRexBarrelDeltaESingleSensitiveDetector::ProcessHits(G4Step *aStep,
		G4TouchableHistory *ROHist) {
	return ProcessHits_constStep(aStep, ROHist);
}

G4bool TRexBarrelDeltaESingleSensitiveDetector::ProcessHits_constStep(const G4Step * aStep,
		G4TouchableHistory* ROHist) {
	// only primary particle hits are considered (no secondaries)
	if(aStep->GetTrack()->GetParentID() != 0 || aStep->GetTotalEnergyDeposit() < 1.*eV) {
		return false;
	}

	TRexHit *hit = new TRexHit(aStep, ROHist);
	fHitCollection->insert(hit);
	//TRexHit hit(aStep, ROHist);
	//fHitCollection->insert(&hit);

	return true;
}

// write into root file
void TRexBarrelDeltaESingleSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
	// clear old event
	fBarrelDeltaESingle->ClearParticleMC();

	if(GetTotalEnergyDeposition() > 0) {
		fBarrelDeltaESingle->ID(fID);

		//for(int i = 0; i < fHitCollection->entries(); i++) {
		//	G4ThreeVector pos = (*fHitCollection)[i]->GetHitPosition();
		//	histoXvsY->Fill(pos.x() / mm, pos.z() / mm);
		//	histoZ->Fill(pos.y() / mm);
		//}

		double resEnergy;
		//std::cout << "nbOfHits = " << fHitCollection->entries() << std::endl;

		// initialize first and second strips
		int firstStripNb = -99;
		G4double firstStripEnergy = 0. * keV;
		int firstStripA, firstStripZ;
		int firstStripTrackID;
		G4double firstStripTime;
		int firstStripStopped;

		int secondStripNb = -99;
		G4double secondStripEnergy = 0. * keV;
		int secondStripA, secondStripZ;
		int secondStripTrackID;
		G4double secondStripTime;
		int secondStripStopped;

		int currentStripNb;
		double posAlongStrip;

		for(int i = 0; i < fHitCollection->entries(); i++) {
			currentStripNb = GetStripNumber((*fHitCollection)[i]->GetLocalHitPosition());

			// if(fDirection == "forward") {
			// 	// attention .y() due to rotated coordinate system !! (.x() is the thickness of the detector)
			// 	posAlongStrip = ((*fHitCollection)[i]->GetLocalHitPosition().y() + fLengthX / 2.) / fLengthX;
			// } else if(fDirection == "middle") {
			// 	// attention .y() due to rotated coordinate system !! (.x() is the thickness of the detector)
			// 	posAlongStrip = ((*fHitCollection)[i]->GetLocalHitPosition().y() + fLengthX / 2.) / fLengthX;
			// } else {
			posAlongStrip = ((*fHitCollection)[i]->GetLocalHitPosition().y() + fLengthX / 2.) / fLengthX;
			//}

			//std::cout << "PosAlongStrip = " << posAlongStrip << std::endl;

			if(firstStripNb == -99 || firstStripNb == currentStripNb) {
				// check if the first strip is hit (for the first time or more than once)
				firstStripNb = currentStripNb;
				firstStripEnergy += (*fHitCollection)[i]->GetEnergyDeposition() * posAlongStrip;
				firstStripA = (*fHitCollection)[i]->GetParticleA();
				firstStripZ = (*fHitCollection)[i]->GetParticleZ();
				firstStripTrackID = (*fHitCollection)[i]->GetTrackID();
				firstStripTime = (*fHitCollection)[i]->GetTime();
				firstStripStopped = IsStopped(i, resEnergy);
			} else if(secondStripNb == -99 || secondStripNb == currentStripNb) {
				// check if the second strip is hit (for the first time or more than once)
				secondStripNb = currentStripNb;
				secondStripEnergy += (*fHitCollection)[i]->GetEnergyDeposition() * posAlongStrip;
				secondStripA = (*fHitCollection)[i]->GetParticleA();
				secondStripZ = (*fHitCollection)[i]->GetParticleZ();
				secondStripTrackID = (*fHitCollection)[i]->GetTrackID();
				secondStripTime = (*fHitCollection)[i]->GetTime();
				secondStripStopped = IsStopped(i, resEnergy);
			} else {
				// more than two different strips have been hit
				std::cout << "There are more than two different hit strips in the BarrelDeltaE detector." << std::endl;
			}
		}

		if(firstStripNb != -99 && secondStripNb == -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fBarrelDeltaESingle->SetStrip(firstStripNb, firstStripEnergy / GetTotalEnergyDeposition(), firstStripA, firstStripZ,
					firstStripTrackID, firstStripTime / ns, firstStripStopped);

			fBarrelDeltaESingle->SetMult(1);

			// if(firstStripNb < 0 || firstStripNb > (int)(TRexSettings::Get()->GetBBarrelDeltaESingleLengthY() / TRexSettings::Get()->GetBBarrelDeltaESingleStripWidth() + 1.e-5)) {
			//   std::cout << "firstStripNb = " << firstStripNb << std::endl;
			// }
		} else if(firstStripNb != -99 && secondStripNb != -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
				secondStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fBarrelDeltaESingle->Set2Strips(firstStripNb, firstStripEnergy / GetTotalEnergyDeposition(), firstStripA, firstStripZ,
					firstStripTrackID, firstStripTime / ns, firstStripStopped,
					secondStripNb, secondStripEnergy / GetTotalEnergyDeposition(), secondStripA, secondStripZ,
					secondStripTrackID, secondStripTime / ns, secondStripStopped);

			fBarrelDeltaESingle->SetMult(2);

			// if(firstStripNb < 0 || firstStripNb > (int)(TRexSettings::Get()->GetBBarrelDeltaESingleLengthY() / TRexSettings::Get()->GetBBarrelDeltaESingleStripWidth() + 1.e-5)) {
			// 	std::cout << "firstStripNb = " << firstStripNb << std::endl;
			// }
			// if(secondStripNb < 0 || secondStripNb > (int)(TRexSettings::Get()->GetBBarrelDeltaESingleLengthY() / TRexSettings::Get()->GetBBarrelDeltaESingleStripWidth() + 1.e-5)) {
			// 	std::cout << "secondStripNb = " << secondStripNb << std::endl;
			// }
		}

		if(fHitCollection->entries() > 0) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				fBarrelDeltaESingle->SetRear((GetTotalEnergyDeposition() + CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV) / keV);
			} else {
				fBarrelDeltaESingle->SetRear(GetTotalEnergyDeposition() / keV);
			}
		}
		//fBarrelDeltaESingle->SetRear(posAlongStrip);
	}
}

G4double TRexBarrelDeltaESingleSensitiveDetector::GetTotalEnergyDeposition() {
	G4double totalEnergy = 0.;

	// loop over all hits
	for(G4int i = 0; i < fHitCollection->entries(); i++) {
		totalEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
	}

	return totalEnergy;
}

int TRexBarrelDeltaESingleSensitiveDetector::GetStripNumber(G4ThreeVector localPos) {
	G4double z;
	int stripNb = -1;

	// if(fDirection == "forward") {
	// 	z = localPos.z() + TRexSettings::Get()->GetFBarrelDeltaESingleLengthY() / 2.;
	// 	stripNb =  (int)((z / TRexSettings::Get()->GetFBarrelDeltaESingleStripWidth()) - 1.e-5);
	// 	//std::cout << "fID = " << fID << " , localZ = " << z << " , stripNb = " << stripNb << std::endl;
	// }
	// else {
	// 	z = localPos.z() - TRexSettings::Get()->GetBBarrelDeltaESingleLengthY() / 2.;
	// 	stripNb =  (int)((fabs(z) / TRexSettings::Get()->GetBBarrelDeltaESingleStripWidth()) - 1.e-5);
	// }
	// if(fDirection == "forward") {
	//   z = localPos.z() + fLengthY / 2.;
	//   stripNb =  (int)((z / fStripWidth) - 1.e-5);

	//   if(stripNb > (int)(fLengthY / fStripWidth + 1.e-5) || stripNb < 0) {
	//     std::cout << "Problem: fID = " << fID << " , localZ = " << z << " , stripNb = " << stripNb << std::endl;
	//     return -1;
	//   }
	// }
	// else if(fDirection == "middle") {
	//   z = localPos.z() - fLengthY / 2.;
	//   stripNb =  (int)((fabs(z) / fStripWdith) - 1.e-5);

	//   if(stripNb > (int)(fLengthY / fStripWidth + 1.e-5) || stripNb < 0) {
	//     std::cout << "Problem: fID = " << fID << " , localZ = " << z << " , stripNb = " << stripNb << std::endl;
	//     return -1;
	//   }
	// }
	// else {
	//   z = localPos.z() - fLengthY / 2.;
	//   stripNb =  (int)((fabs(z) / fStripWdith) - 1.e-5);

	//   if(stripNb > (int)(fLengthY / fStripWidth + 1.e-5) || stripNb < 0) {
	//     std::cout << "Problem: fID = " << fID << " , localZ = " << z << " , stripNb = " << stripNb << std::endl;
	//     return -1;
	//   }
	// }

	if(fDirection == "forward") {
		z = localPos.z() + fLengthY / 2.;
		stripNb =  (int)((z / fStripWidth) - 1.e-5);
	} else if(fDirection == "middle") {
		z = localPos.z() - fLengthY / 2.;
	} else {
		z = localPos.z() - fLengthY / 2.;
	}

	stripNb =  (int)((fabs(z) / fStripWidth) - 1.e-5);

	if(stripNb > (int)(fLengthY / fStripWidth + 1.e-5) || stripNb < 0) {
		std::cout << "Problem: fID = " << fID << " , localZ = " << z << " , stripNb = " << stripNb << std::endl;
		return -1;
	}

	return stripNb ;
}

int TRexBarrelDeltaESingleSensitiveDetector::IsStopped(int hitIndex, double &resKinEnergy) {
	// set default value resKinEnergy (residual energy of punch through particles)
	resKinEnergy = -100.;

	// check if particle  is primary
	if((*fHitCollection)[hitIndex]->GetParentID() != 0)
		return -3;

	// check if the hitIndex is the last particle hit
	bool isLastHit;
	if(hitIndex == fHitCollection->entries() - 1) {
		isLastHit = true;
	} else if(fabs((*fHitCollection)[hitIndex]->GetVertexKineticEnergy() - (*fHitCollection)[hitIndex + 1]->GetVertexKineticEnergy()) < 0.001*eV ) { // check if it is the same particle
		isLastHit = false;
	} else {
		isLastHit = true;
	}

	if(isLastHit == false)
		return -2;

	resKinEnergy = (*fHitCollection)[hitIndex]->GetKineticEnergy() / keV;

	// check if particle is stopped
	if(fabs((*fHitCollection)[hitIndex]->GetKineticEnergy()) < 0.001*eV) {
		// stopped
		return 1;
	} else {
		// not stopped
		return 0;
	}
}
