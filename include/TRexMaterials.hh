#ifndef TREXMATERIALS_HH_
#define TREXMATERIALS_HH_

#include "CLHEP/Units/SystemOfUnits.h"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"
#include "G4MaterialTable.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4NistManager.hh"
#include "G4LogicalBorderSurface.hh"

class TRexMaterials
{
  public:
    static TRexMaterials* Get(void);
    ~TRexMaterials(void) {};
	 G4Material* GetMaterial(std::string name);//, double pressure = 0.);

	 G4NistManager* GetNistManager() { return fManager; }

  private:
	 G4Element* elH;
	 G4Element* elC;
	 G4Element* elN;
	 G4Element* elO;
	 G4Element* elF;
	 G4Element* elFe;
	 G4Element* elRb;
	 G4Element* elMo;
	 G4Element* elSb;
	 G4Element* elCs;
	 G4Element* elCr;
	 G4Element* elNi;
	 G4Element* elCu;
	 G4Isotope* iso_H2;
	 G4Element* ele_D;

	 G4Material* air;
	 G4Material* neon;
	 G4Material* air_noOptical;
	 G4Material* vacuum;
	 G4Material* bc408;
	 G4Material* bc408_noOptical;
	 G4Material* plexiglass;
	 G4Material* glass;
	 G4Material* borosilicate;
	 G4Material* aluminium;
	 G4Material* bialkali;
	 G4Material* plasticFoam;
	 G4Material* carbonFibre;
	 G4Material* carbonLH2;
	 G4Material* epoxy;
	 G4Material* concrete;
	 G4Material* beryllium;
	 G4Material* lh2;
	 G4Material* mylar;
	 G4Material* stainlessSteel;
	 G4Material* polyethylene;
	 G4Material* polypropylene;
	 G4Material* polystyrene;
	 G4Material* airexC70;
	 G4Material* bgo;
	 G4Material* iron;
	 G4Material* silver;
	 G4Material* helium;
	 G4Material* argon;
	 G4Material* co2;
	 G4Material* copper;
	 G4Material* gold;
	 G4Material* lead;
	 G4Material* ethan;
	 G4Material* cf4;
	 G4Material* c4f10;
	 G4Material* c4f10_noOptical;
	 G4Material* g11;
	 G4Material* dc4gas;
	 G4Material* strawGas;
	 G4Material* w45Gas;
	 G4Material* mwpcGas;
	 G4Material* micromegasGas;
	 G4Material* mw1Gas;
	 G4Material* mw2Gas;
	 G4Material* ecalShashlik;
	 G4Material* ecalMainz;
	 G4Material* ecalOlga;
	 G4Material* hcal1Material;
	 G4Material* hcal2Material;
	 G4Material* kapton;
	 G4Material* plastic;
	 G4Material* rohacell;
	 G4Material* innox;
	 G4Material* silicon;
	 G4Material* siliconMaterial;
	 G4Material* gemMaterial;
	 G4Material* mwpcMaterial;
	 G4Material* micromegasMaterial;
	 G4Material* pixelGEMMaterial;
	 G4Material* richWallMaterial;
	 G4Material* richwallGas;
	 G4Material* c2h6;
	 G4Material* fiberGlass;
	 G4Material* pcb;
	 G4Material* deuteriumGas;
	 G4Material* deuteratedPE;
	 G4Material* solidDeuterium;

	 G4OpticalSurface* surfaceBc408Air;
	 G4OpticalSurface* surfaceAirBc408;
	 G4OpticalSurface* surfaceBc408Plexiglass;
	 G4OpticalSurface* surfacePlexiglassGlass;
	 G4OpticalSurface* surfacePlexiglassAir;
	 G4OpticalSurface* surfaceAirPlexiglass;
	 G4OpticalSurface* surfaceGlassVacuum;
	 G4OpticalSurface* surfaceVacuumBialkali;
	 G4OpticalSurface* surfaceAluminium;
	 G4OpticalSurface* surfaceMirror;

	 TRexMaterials(void);
	 static TRexMaterials* materials;

	 void DefineIndex(void);
	 void BuildAir(void);
	 void BuildBc408(void);
	 void BuildBc408_noOptical(void);
	 void BuildPlexiglass(void);
	 void BuildGlass(void);
	 void BuildAluminium(void);
	 void BuildBialkali(void);
	 void BuildC4F10(void);
	 void BuildC4F10_noOptical(void);
	 void BuildDeuterium(void);
	 void BuildDeuteratedPE(void);
	 void BuildSolidDeuterium(void);

	 void BuildSurfaceBc408Air(void);
	 void BuildSurfaceAirBc408(void);
	 void BuildSurfaceBc408Plexiglass(void);
	 void BuildSurfacePlexiglassGlass(void);
	 void BuildSurfacePlexiglassAir(void);
	 void BuildSurfaceAirPlexiglass(void);
	 void BuildSurfaceGlassVacuum(void);
	 void BuildSurfaceVacuumBialkali(void);
	 void BuildSurfaceAluminium(void);
	 void BuildSurfaceMirror(void);

	 G4NistManager* fManager;
	 static const G4int nEntryLong = 12;
	 static const G4int nEntryShort = 2;
	 G4double bc408Index;
	 G4double bc408AbsorptionLength;
	 G4double bc408Yield;
	 G4double plexiglassIndex;
	 G4double plexiglassAbsLength;
	 G4double glassIndex;
	 G4double aluminiumReflectivity;

	 G4double specularLobe[nEntryShort];
	 G4double specularSpike[nEntryShort];
	 G4double backScatter[nEntryShort];

	 G4double photonEnergyShort[nEntryShort];
	 G4double photonEnergyLong[nEntryLong];

	 G4double airRefractiveIndex[nEntryShort];
	 G4double airAbsorpiton[nEntryShort];
	 G4double plexiglassRefractiveIndex[nEntryShort];
	 G4double plexiglassAbsorpiton[nEntryShort];
	 G4double glassRefractiveIndex[nEntryShort];
	 G4double bc408RefractiveIndex[nEntryShort];
};

#endif /* TREXMATERIALS_HH_ */
