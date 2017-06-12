#include "TRexActionInitialization.hh"

#include "MiniBallHistoManager.hh"
#include "MiniBallHistoGenerator.hh"
#include "MiniBallRootGenerator.hh"

#include "TRexPrimaryGeneratorAction.hh"
#include "TRexRunAction.hh"
#include "TRexEventAction.hh"

TRexActionInitialization::TRexActionInitialization(TRexDetectorConstruction* detConst, TRexData* data, MiniBallHistoManager* histoMan) : G4VUserActionInitialization(), fDetConst(detConst), fData(data), fHistoMan(histoMan)
{

}

TRexActionInitialization::~TRexActionInitialization(){

}

void TRexActionInitialization::Build() const{
    // set mandatory user action class
    TRexPrimaryGeneratorAction* gen_action = new TRexPrimaryGeneratorAction();
    SetUserAction(gen_action);

    TRexEventAction* event_action = new TRexEventAction(fDetConst, fHistoMan);
    SetUserAction(event_action);

    TRexRunAction* run_action = new TRexRunAction(fData, gen_action, event_action);
    SetUserAction(run_action);
}

void TRexActionInitialization::BuildForMaster() const{
    TRexPrimaryGeneratorAction* gen_action = new TRexPrimaryGeneratorAction;

    TRexEventAction* event_action = new TRexEventAction(fDetConst, fHistoMan);

    TRexRunAction* run_action = new TRexRunAction(fData, gen_action, event_action);
    SetUserAction(run_action);
}
