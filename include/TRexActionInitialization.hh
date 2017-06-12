#ifndef TRexActionInitialization_h 
#define TRexActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

#include "TRexDetectorConstruction.hh"
#include "TRexData.hh"
#include "MiniBallHistoManager.hh"

class TRexActionInitialization : public G4VUserActionInitialization
{
    public:
        TRexActionInitialization(TRexDetectorConstruction*, TRexData* data, MiniBallHistoManager*);
        ~TRexActionInitialization();

        virtual void BuildForMaster() const;
        virtual void Build() const;

    private:
        TRexDetectorConstruction* fDetConst;
        TRexData* fData;
	MiniBallHistoManager* fHistoMan;
};

#endif
