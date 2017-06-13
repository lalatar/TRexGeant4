#include "TRexStackingAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4IonTable.hh"

TRexStackingAction::TRexStackingAction(){
	particleTable = G4ParticleTable::GetParticleTable();
	
	electronDef = nullptr;
}

TRexStackingAction::~TRexStackingAction()
{}

G4ClassificationOfNewTrack TRexStackingAction::ClassifyNewTrack(const G4Track* track){
	if (electronDef == nullptr){
		electronDef = particleTable->FindParticle("e-");
	}
    G4ClassificationOfNewTrack classification;
    
    classification = fUrgent;
    
    //do not simulate electrons, to speed up simulation
    if(track->GetParticleDefinition() == electronDef){
        classification = fKill;
    }
    
    return classification;
}

void TRexStackingAction::NewStage()
{}

void TRexStackingAction::PrepareNewEvent()
{}

