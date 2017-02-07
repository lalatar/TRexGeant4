#include "TRexMaterials.hh"
#include "MiniBallMaterial.hh"
#include "TRexSettings.hh"

#include <string>
#include <iomanip>
#include <ios>

TRexMaterials* TRexMaterials::materials = NULL;

TRexMaterials* TRexMaterials::Get(void)
{
	if (materials == NULL) {
		materials = new TRexMaterials();
	}
	return materials;
}

TRexMaterials::TRexMaterials(void)
{
	DefineIndex();

	fManager = G4NistManager::Instance();
	elH = fManager->FindOrBuildElement("H");
	elC = fManager->FindOrBuildElement("C");
	elN = fManager->FindOrBuildElement("N");
	elO = fManager->FindOrBuildElement("O");
	elF = fManager->FindOrBuildElement("F");
	elFe = fManager->FindOrBuildElement("Fe");
	elRb = fManager->FindOrBuildElement("Rb");
	elMo = fManager->FindOrBuildElement("Mo");
	elSb = fManager->FindOrBuildElement("Sb");
	elCs = fManager->FindOrBuildElement("Cs");
	elNi = fManager->FindOrBuildElement("Ni");
	elCr = fManager->FindOrBuildElement("Cr");
	elCu = fManager->FindOrBuildElement("Cu");

	iso_H2 = new G4Isotope("H2",1,2,2.014*CLHEP::g/CLHEP::mole);

	BuildAir();
	BuildBc408();
	BuildBc408_noOptical();
	BuildPlexiglass();
	BuildGlass();
	BuildAluminium();
	BuildBialkali();
	BuildC4F10();
	BuildC4F10_noOptical();
	BuildDeuterium();
	BuildDeuteratedPE();
	BuildSolidDeuterium();

	c2h6 = new G4Material("c2h6", 1.290 * CLHEP::mg / CLHEP::cm3, 2);
	c2h6->AddElement(elC, 0.25);
	c2h6->AddElement(elH, 0.75);

	neon = fManager->FindOrBuildMaterial("G4_Ne");
	neon->SetName("neon");

	borosilicate = fManager->FindOrBuildMaterial("G4_Pyrex_Glass");
	borosilicate->SetName("borosilicate");

	plasticFoam = new G4Material("PlasticFoam", 0.15 * CLHEP::g / CLHEP::cm3, 3);
	plasticFoam->AddElement(elC, 2);
	plasticFoam->AddElement(elH, 2);
	plasticFoam->AddElement(elO, 1);

	carbonFibre = new G4Material("CarbonFibre", 1.8 * CLHEP::g / CLHEP::cm3, 2);
	carbonFibre->AddElement(elC, 10);
	carbonFibre->AddElement(elN, 1);

	carbonLH2 = new G4Material("carbonLH2", 2.073 * CLHEP::g / CLHEP::cm3, 2);
	carbonLH2->AddElement(elC, 10);
	carbonLH2->AddElement(elN, 1);

	epoxy = new G4Material("epoxy", 1.2 * CLHEP::g / CLHEP::cm3, 3);
	epoxy->AddElement(elC, 21);
	epoxy->AddElement(elH, 25);
	epoxy->AddElement(elO, 5);

	concrete = fManager->FindOrBuildMaterial("G4_CONCRETE");
	concrete->SetName("concrete");

	beryllium = fManager->FindOrBuildMaterial("G4_Be");
	beryllium->SetName("beryllium");

	lh2 = fManager->FindOrBuildMaterial("G4_lH2");
	lh2->SetName("LH2");

	mylar = fManager->FindOrBuildMaterial("G4_MYLAR");
	mylar->SetName("mylar");

	stainlessSteel = new G4Material("Stainless Steel",
			7.9 * CLHEP::g / CLHEP::cm3, 3, kStateSolid, 50.0 * CLHEP::kelvin,
			1.0 * CLHEP::atmosphere);
	stainlessSteel->AddElement(elC, 1);
	stainlessSteel->AddElement(elFe, 10);
	stainlessSteel->AddElement(elMo, 1);

	polyethylene = fManager->FindOrBuildMaterial("G4_POLYETHYLENE");
	polyethylene->SetName("polyethylene");

	polypropylene = fManager->FindOrBuildMaterial("G4_POLYPROPYLENE");
	polypropylene->SetName("polypropylene");

	polystyrene = fManager->FindOrBuildMaterial("G4_POLYSTYRENE");
	polystyrene->SetName("polystyrene");

	airexC70 = fManager->BuildMaterialWithNewDensity("airexC70", "G4_POLYVINYL_CHLORIDE", 40 * CLHEP::kg / CLHEP::m3);

	bgo = fManager->FindOrBuildMaterial("G4_BGO");
	bgo->SetName("BGO");

	iron = fManager->FindOrBuildMaterial("G4_Fe");
	iron->SetName("iron");

	silver = fManager->FindOrBuildMaterial("G4_Ag");
	silver->SetName("silver");

	helium = fManager->FindOrBuildMaterial("G4_He");
	helium->SetName("helium");

	argon = fManager->FindOrBuildMaterial("G4_Ar");
	argon->SetName("argon");

	co2 = fManager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
	co2->SetName("CO2");

	copper = fManager->FindOrBuildMaterial("G4_Cu");
	copper->SetName("copper");

	gold = fManager->FindOrBuildMaterial("G4_Au");
	gold->SetName("gold");

	lead = fManager->FindOrBuildMaterial("G4_Pb");
	lead->SetName("lead");

	ethan = fManager->FindOrBuildMaterial("G4_ETHANE");
	ethan->SetName("ethan");

	cf4 = new G4Material("CF4", 3.72 * CLHEP::mg / CLHEP::cm3, 2);
	cf4->AddElement(elC, 1);
	cf4->AddElement(elF, 4);

	g11 = new G4Material("G11", 1.9 * CLHEP::g / CLHEP::cm3, 3);
	g11->AddElement(elC, 5);
	g11->AddElement(elH, 8);
	g11->AddElement(elO, 2);

	dc4gas = new G4Material("dc4gas", 1.65 * CLHEP::mg / CLHEP::cm3, 3); // density = 1.37 * density_air
	dc4gas->AddMaterial(argon, 0.45);
	dc4gas->AddMaterial(ethan, 0.45);
	dc4gas->AddMaterial(cf4, 0.1);

	strawGas = new G4Material("strawGas", 2.08 * CLHEP::mg / CLHEP::cm3, 3);
	strawGas->AddMaterial(argon, 0.74);
	strawGas->AddMaterial(co2, 0.06);
	strawGas->AddMaterial(cf4, 0.20);

	w45Gas = new G4Material("w45Gas", 1.88 * CLHEP::mg / CLHEP::cm3, 3);
	w45Gas->AddMaterial(argon, 0.85);
	w45Gas->AddMaterial(co2, 0.05);
	w45Gas->AddMaterial(cf4, 0.10);

	mw1Gas = new G4Material("mw1Gas", 1.716 * CLHEP::mg / CLHEP::cm3, 2);
	mw1Gas->AddMaterial(argon, 0.7);
	mw1Gas->AddMaterial(co2, 0.3);

	mw2Gas = new G4Material("mw2Gas", 1.41 * CLHEP::mg / CLHEP::cm3, 2); // density = 1.17 * density_air
	mw2Gas->AddMaterial(argon, 0.75);
	mw2Gas->AddMaterial(ethan, 0.25);

	ecalShashlik = new G4Material("ecalShashlik", 4.639 * CLHEP::g / CLHEP::cm3,
			2);
	ecalShashlik->AddMaterial(lead, 0.348);
	ecalShashlik->AddMaterial(polystyrene, 0.652);

	ecalMainz = new G4Material("ecalMainz", 5.176 * CLHEP::g / CLHEP::cm3, 2);
	ecalMainz->AddMaterial(lead, 0.4);
	ecalMainz->AddMaterial(polystyrene, 0.6);

	ecalOlga = new G4Material("ecalOlga", 4.49 * CLHEP::g / CLHEP::cm3, 2);
	ecalOlga->AddMaterial(lead, 0.33);
	ecalOlga->AddMaterial(polystyrene, 0.67);

	hcal1Material = new G4Material("hcal1Material", 6.51 * CLHEP::g / CLHEP::cm3,
			2);
	hcal1Material->AddMaterial(iron, 0.8);
	hcal1Material->AddMaterial(polystyrene, 0.2);

	hcal2Material = new G4Material("hcal2Material", 10.25 * CLHEP::g / CLHEP::cm3,
			2);
	hcal2Material->AddMaterial(lead, 0.893);
	hcal2Material->AddMaterial(polystyrene, 0.107);

	kapton = new G4Material("Kapton", 1.42 * CLHEP::g / CLHEP::cm3, 4);
	kapton->AddElement(elH, 0.0273);
	kapton->AddElement(elC, 0.7213);
	kapton->AddElement(elN, 0.0765);
	kapton->AddElement(elO, 0.1749);

	plastic = fManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	plastic->SetName("plastic");

	rohacell = new G4Material("rohacell", 51.3 * CLHEP::kg / CLHEP::m3, 4); // C9 H13 N O2  0.0513 g/cc
	rohacell->AddElement(elC, 9);
	rohacell->AddElement(elH, 13);
	rohacell->AddElement(elN, 1);
	rohacell->AddElement(elO, 2);

	innox = new G4Material("innox", 7.90 * CLHEP::g / CLHEP::cm3, 3);
	innox->AddElement(elC, 0.002737583);
	innox->AddElement(elCr, 0.664841611);
	innox->AddElement(elNi, 0.332420806);

	silicon = fManager->FindOrBuildMaterial("G4_Si");
	silicon->SetName("silicon");

	siliconMaterial = fManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
	siliconMaterial->SetName("silicondioxide");

	gemMaterial = new G4Material("gem-material", 4.49 * CLHEP::g / CLHEP::cm3, 2);
	gemMaterial->AddMaterial(kapton, 0.91);
	gemMaterial->AddMaterial(copper, 0.09);

	mwpcGas = new G4Material("mwpcGas", 2.08 * CLHEP::mg / CLHEP::cm3, 3);
	mwpcGas->AddMaterial(argon, 0.74);
	mwpcGas->AddMaterial(co2, 0.06);
	mwpcGas->AddMaterial(cf4, 0.20);
	mwpcMaterial = new G4Material("mwpc-material", 4.49 * CLHEP::g / CLHEP::cm3,
			2);
	mwpcMaterial->AddMaterial(mwpcGas, 0.893);
	mwpcMaterial->AddMaterial(polystyrene, 0.107);

	micromegasGas = new G4Material("micromegasGas", 0.95 * CLHEP::mg / CLHEP::cm3,
			3);
	micromegasGas->AddMaterial(neon, 0.80);
	micromegasGas->AddMaterial(c2h6, 0.1);
	micromegasGas->AddMaterial(cf4, 0.1);
	micromegasMaterial = new G4Material("micromega-material",
			4.49 * CLHEP::g / CLHEP::cm3, 4);
	micromegasMaterial->AddMaterial(micromegasGas, 0.893);
	micromegasMaterial->AddMaterial(polystyrene, 0.047);
	micromegasMaterial->AddMaterial(plastic, 0.05);
	micromegasMaterial->AddMaterial(aluminium, 0.01);

	pixelGEMMaterial = new G4Material("pgem-material",
			4.49 * CLHEP::g / CLHEP::cm3, 2);
	pixelGEMMaterial->AddMaterial(kapton, 0.91);
	pixelGEMMaterial->AddMaterial(copper, 0.09);

	richwallGas = new G4Material("w45Gas", 2.08 * CLHEP::mg / CLHEP::cm3, 3);
	richwallGas->AddMaterial(argon, 0.74);
	richwallGas->AddMaterial(co2, 0.06);
	richwallGas->AddMaterial(cf4, 0.20);
	richWallMaterial = new G4Material("richwall-material",
			4.49 * CLHEP::g / CLHEP::cm3, 3);
	richWallMaterial->AddMaterial(aluminium, 0.044);
	richWallMaterial->AddMaterial(stainlessSteel, 0.015);
	richWallMaterial->AddMaterial(richwallGas, 0.941);

	fiberGlass = new G4Material("fiberGlass", 2.5 * CLHEP::g / CLHEP::cm3, 5);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE"),  0.54);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_BORON_OXIDE"), 0.10);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_CALCIUM_OXIDE"), 0.175);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_ALUMINUM_OXIDE"), 0.14);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_MAGNESIUM_OXIDE"), 0.045);

	pcb = new G4Material("pcb", 1.8 * CLHEP::g / CLHEP::cm3, 3);
	pcb->AddMaterial(fiberGlass, 0.70);
	pcb->AddMaterial(epoxy, 0.25);
	pcb->AddElement(elCu, 0.05);

	BuildSurfaceBc408Air();
	BuildSurfaceAirBc408();
	BuildSurfaceBc408Plexiglass();
	BuildSurfacePlexiglassGlass();
	BuildSurfacePlexiglassAir();
	BuildSurfaceAirPlexiglass();
	BuildSurfaceGlassVacuum();
	BuildSurfaceVacuumBialkali();
	BuildSurfaceAluminium();
	BuildSurfaceMirror();

	//build target material
	if(TRexSettings::Get()->GetGasTargetLength() > 0.) {
		fManager->ConstructNewGasMaterial("target", TRexSettings::Get()->GetTargetMaterialName(), STP_Temperature, TRexSettings::Get()->GetTargetPressure());
	} else {
		G4Material* material = GetMaterial(TRexSettings::Get()->GetTargetMaterialName());
		G4Material* target = new G4Material("target", material->GetDensity(), material->GetNumberOfElements());
		for(size_t i = 0; i < material->GetNumberOfElements(); ++i) {
			target->AddElement(material->GetElementVector()->at(i), material->GetFractionVector()[i]);
		}
	}

	//build chamber gas material
	fManager->ConstructNewGasMaterial("chamberGas", TRexSettings::Get()->GetVacuumChamberGas(), STP_Temperature, TRexSettings::Get()->GetVacuumChamberGasPressure());
}

void TRexMaterials::DefineIndex(void)
{
	bc408Index = 1.58;
	bc408AbsorptionLength = 3.80 * CLHEP::m; // bulk light attenuation length
	bc408Yield = 0.64 * 2 / (100 * CLHEP::eV); // 64% anthracene
	plexiglassIndex = 1.49;
	plexiglassAbsLength = 10.0 * CLHEP::m;
	glassIndex = 1.474;
	aluminiumReflectivity = 0.97;

	specularLobe[0] = 1.0;
	specularLobe[1] = 1.0;
	specularSpike[0] = 0.0;
	specularSpike[1] = 0.0;
	backScatter[0] = 0.0;
	backScatter[1] = 0.0;

	photonEnergyShort[0] = 2.0 * CLHEP::eV; // 619.92 nm
	photonEnergyShort[1] = 7.14 * CLHEP::eV; // 173.65 nm
	photonEnergyLong[0] = 2.08 * CLHEP::eV; // 596.08 nm
	photonEnergyLong[1] = 2.38 * CLHEP::eV; // 520.94 nm
	photonEnergyLong[2] = 2.58 * CLHEP::eV; // 480.56 nm
	photonEnergyLong[3] = 2.70 * CLHEP::eV; // 459.20 nm
	photonEnergyLong[4] = 2.76 * CLHEP::eV; // 449.22 nm
	photonEnergyLong[5] = 2.82 * CLHEP::eV; // 439.66 nm
	photonEnergyLong[6] = 2.92 * CLHEP::eV; // 424.60 nm
	photonEnergyLong[7] = 2.95 * CLHEP::eV; // 420.29 nm
	photonEnergyLong[8] = 3.02 * CLHEP::eV; // 410.54 nm
	photonEnergyLong[9] = 3.10 * CLHEP::eV; // 399.95 nm
	photonEnergyLong[10] = 3.26 * CLHEP::eV; // 380.32 nm
	photonEnergyLong[11] = 3.44 * CLHEP::eV; // 360.42 nm

	airRefractiveIndex[0] = 1.0;
	airRefractiveIndex[1] = 1.0;
	airAbsorpiton[0] = 10.0 * CLHEP::m;
	airAbsorpiton[1] = 10.0 * CLHEP::m;
	plexiglassRefractiveIndex[0] = plexiglassIndex;
	plexiglassRefractiveIndex[1] = plexiglassIndex;
	plexiglassAbsorpiton[0] = plexiglassAbsLength;
	plexiglassAbsorpiton[1] = plexiglassAbsLength;
	glassRefractiveIndex[0] = glassIndex;
	glassRefractiveIndex[1] = glassIndex;
	bc408RefractiveIndex[0] = bc408Index;
	bc408RefractiveIndex[1] = bc408Index;
}



void TRexMaterials::BuildAir(void)
{
	air = fManager->FindOrBuildMaterial("G4_AIR");
	air->SetName("air");
	// G4Material(name, density, nComponents or nAtoms)
	vacuum = new G4Material("Vacuum", 1.0e-5 * 1.290 * CLHEP::mg / CLHEP::cm3, 2);
	vacuum->AddElement(elN, 0.7);
	vacuum->AddElement(elO, 0.3);

	air_noOptical = new G4Material("Air_noOptical",
			1.290 * CLHEP::mg / CLHEP::cm3, 2);
	air_noOptical->AddElement(elN, 0.7);
	air_noOptical->AddElement(elO, 0.3);

	G4MaterialPropertiesTable *airMaterialProperties =
		new G4MaterialPropertiesTable();
	airMaterialProperties->AddProperty("RINDEX", photonEnergyShort,
			airRefractiveIndex, nEntryShort);
	airMaterialProperties->AddProperty("ABSLENGTH", photonEnergyShort,
			airAbsorpiton, nEntryShort);
	air->SetMaterialPropertiesTable(airMaterialProperties);
	vacuum->SetMaterialPropertiesTable(airMaterialProperties);
}

void TRexMaterials::BuildBc408(void)
{
	G4double lessOpticalFactor = 1;
	// todo implement this into interface and check for output.

	bc408 = new G4Material("Scintillator", 1.032 * CLHEP::g / CLHEP::cm3, 2);
	bc408->AddElement(elC, 9);
	bc408->AddElement(elH, 10);

	G4double bc408RefractiveIndex[nEntryLong];
	G4double bc408Absorpiton[nEntryLong];
	for (G4int i = 0; i < nEntryLong; i++) {
		bc408RefractiveIndex[i] = bc408Index;
		bc408Absorpiton[i] = bc408AbsorptionLength;
	}
	G4double bc408Scintillation[nEntryLong] = { 0.01, 0.03, 0.17, 0.40, 0.55,
		0.83, 1.00, 0.84, 0.49, 0.20, 0.07, 0.04 };

	G4MaterialPropertiesTable *bc408MaterialProperties =
		new G4MaterialPropertiesTable();
	bc408MaterialProperties->AddProperty("RINDEX", photonEnergyLong,
			bc408RefractiveIndex, nEntryLong);
	bc408MaterialProperties->AddProperty("ABSLENGTH", photonEnergyLong,
			bc408Absorpiton, nEntryLong);
	bc408MaterialProperties->AddProperty("FASTCOMPONENT", photonEnergyLong,
			bc408Scintillation, nEntryLong);
	bc408MaterialProperties->AddConstProperty("SCINTILLATIONYIELD",
			bc408Yield / lessOpticalFactor);
	bc408MaterialProperties->AddConstProperty("RESOLUTIONSCALE", 1.0);
	bc408MaterialProperties->AddConstProperty("FASTTIMECONSTANT",
			0.9 * CLHEP::ns); // rise time
	bc408MaterialProperties->AddConstProperty("SLOWTIMECONSTANT",
			2.1 * CLHEP::ns); // decay time
	bc408MaterialProperties->AddConstProperty("YIELDRATIO", 0.27);

	bc408->SetMaterialPropertiesTable(bc408MaterialProperties);
	bc408->GetIonisation()->SetBirksConstant(0.126 * CLHEP::mm / CLHEP::MeV);
}

void TRexMaterials::BuildBc408_noOptical(void)
{
	bc408_noOptical = new G4Material("Scintillator_noOptical",
			1.032 * CLHEP::g / CLHEP::cm3, 2);
	bc408_noOptical->AddElement(elC, 9);
	bc408_noOptical->AddElement(elH, 10);
}

void TRexMaterials::BuildPlexiglass(void)
{
	plexiglass = fManager->FindOrBuildMaterial("G4_PLEXIGLASS");
	plexiglass->SetName("plexiglass");

	G4double plexiglassEnergy[nEntryShort] = { 7.14 * CLHEP::eV, 2.0 * CLHEP::eV };
	G4MaterialPropertiesTable* plexiglassMaterialProperties =
		new G4MaterialPropertiesTable();
	plexiglassMaterialProperties->AddProperty("RINDEX", plexiglassEnergy,
			plexiglassRefractiveIndex, nEntryShort);
	plexiglassMaterialProperties->AddProperty("ABSLENGTH", plexiglassEnergy,
			plexiglassAbsorpiton, nEntryShort);
	plexiglass->SetMaterialPropertiesTable(plexiglassMaterialProperties);
}

void TRexMaterials::BuildGlass(void)
{
	glass = fManager->FindOrBuildMaterial("G4_GLASS_PLATE");
	glass->SetName("glass");

	G4MaterialPropertiesTable* glassMaterialProperties =
		new G4MaterialPropertiesTable();
	glassMaterialProperties->AddProperty("RINDEX", photonEnergyShort,
			glassRefractiveIndex, nEntryShort);
	glass->SetMaterialPropertiesTable(glassMaterialProperties);
}

void TRexMaterials::BuildAluminium(void)
{
	aluminium = fManager->FindOrBuildMaterial("G4_Al");
	aluminium->SetName("aluminium");

	G4double aluminiumEnergy[nEntryShort] = { 2.0 * CLHEP::eV, 3.5 * CLHEP::eV };
	G4double aluminiumRefractiveIndex[nEntryShort] = { 1.51, 1.61 };
	G4double aluminiumAbsorpiton[nEntryShort] = { 1.0e-20 * CLHEP::m, 1.0e-20
		* CLHEP::m };
	G4MaterialPropertiesTable* aluminiumMaterialProperties =
		new G4MaterialPropertiesTable();
	aluminiumMaterialProperties->AddProperty("RINDEX", aluminiumEnergy,
			aluminiumRefractiveIndex, nEntryShort);
	aluminiumMaterialProperties->AddProperty("ABSLENGTH", aluminiumEnergy,
			aluminiumAbsorpiton, nEntryShort);
	aluminium->SetMaterialPropertiesTable(aluminiumMaterialProperties);
}

void TRexMaterials::BuildBialkali(void)
{
	bialkali = new G4Material("bialkali", 3 * CLHEP::g / CLHEP::cm3, 3,
			kStateSolid);
	bialkali->AddElement(elSb, 1);
	bialkali->AddElement(elRb, 1);
	bialkali->AddElement(elCs, 1);
	G4MaterialPropertiesTable* bialkaliProperties =
		new G4MaterialPropertiesTable();
	G4double bialkaliAbsorption[nEntryShort] = { 1.0e-6 * CLHEP::mm, 1.0e-6
		* CLHEP::mm };
	bialkaliProperties->AddProperty("ABSLENGTH", photonEnergyShort,
			bialkaliAbsorption, nEntryShort);
	bialkaliProperties->AddProperty("RINDEX", photonEnergyShort,
			glassRefractiveIndex, nEntryShort);
	bialkali->SetMaterialPropertiesTable(bialkaliProperties);
}

void TRexMaterials::BuildC4F10(void)
{
	c4f10 = new G4Material("C4F10", 11.21 * CLHEP::kg / CLHEP::m3, 2, kStateGas,
			298 * CLHEP::kelvin, 1.0 * CLHEP::atmosphere);
	c4f10->AddElement(elC, 4);
	c4f10->AddElement(elF, 10);

	G4double photonEnergy[11];
	G4double c4f10RefractiveIndex[11];

	photonEnergy[0] = 1.77 * CLHEP::eV; // 700 nm
	photonEnergy[1] = 2.07 * CLHEP::eV; // 600 nm
	photonEnergy[2] = 2.25 * CLHEP::eV; // 550 nm
	photonEnergy[3] = 2.48 * CLHEP::eV; // 500 nm
	photonEnergy[4] = 2.76 * CLHEP::eV; // 450 nm
	photonEnergy[5] = 3.10 * CLHEP::eV; // 400 nm
	photonEnergy[6] = 3.54 * CLHEP::eV; // 350 nm
	photonEnergy[7] = 4.13 * CLHEP::eV; // 300 nm
	photonEnergy[8] = 4.96 * CLHEP::eV; // 250 nm
	photonEnergy[9] = 6.20 * CLHEP::eV; // 200 nm
	photonEnergy[10] = 10.0 * CLHEP::eV; // 123.98 nm

	c4f10RefractiveIndex[0] = 1.00147;
	c4f10RefractiveIndex[1] = 1.001475;
	c4f10RefractiveIndex[2] = 1.00148;
	c4f10RefractiveIndex[3] = 1.00149;
	c4f10RefractiveIndex[4] = 1.0015;
	c4f10RefractiveIndex[5] = 1.00152;
	c4f10RefractiveIndex[6] = 1.00153;
	c4f10RefractiveIndex[7] = 1.00156;
	c4f10RefractiveIndex[8] = 1.0016;
	c4f10RefractiveIndex[9] = 1.0017;
	c4f10RefractiveIndex[10] = 1.0017;

	G4double c4f10Absorpiton[nEntryLong];
	for (G4int i = 0; i < nEntryLong; i++) {
		c4f10Absorpiton[i] = 10.00 * CLHEP::m; //TODO
	}

	G4MaterialPropertiesTable *c4f10MaterialProperties =
		new G4MaterialPropertiesTable();
	c4f10MaterialProperties->AddProperty("RINDEX", photonEnergy,
			c4f10RefractiveIndex, 11);
	c4f10MaterialProperties->AddProperty("ABSLENGTH", photonEnergyLong,
			c4f10Absorpiton, nEntryLong);
	c4f10MaterialProperties->AddConstProperty("SCINTILLATIONYIELD",
			100.0 / CLHEP::MeV);

	c4f10->SetMaterialPropertiesTable(c4f10MaterialProperties);
}

void TRexMaterials::BuildC4F10_noOptical(void)
{
	c4f10_noOptical = new G4Material("C4F10_noOptical",
			11.21 * CLHEP::kg / CLHEP::m3, 2, kStateGas, 298 * CLHEP::kelvin,
			1.0 * CLHEP::atmosphere);
	c4f10_noOptical->AddElement(elC, 4);
	c4f10_noOptical->AddElement(elF, 10);
}

void TRexMaterials::BuildSurfaceBc408Air(void)
{
	surfaceBc408Air = new G4OpticalSurface("bc408AirSurface");
	surfaceBc408Air->SetType(dielectric_dielectric);
	surfaceBc408Air->SetModel(unified);
	surfaceBc408Air->SetFinish(ground);
	surfaceBc408Air->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", photonEnergyShort,
			airRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", photonEnergyShort,
			specularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", photonEnergyShort,
			specularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", photonEnergyShort,
			backScatter, nEntryShort);
	surfaceBc408Air->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceAirBc408(void)
{
	surfaceAirBc408 = new G4OpticalSurface("airBc408Surface");
	surfaceAirBc408->SetType(dielectric_dielectric);
	surfaceAirBc408->SetModel(unified);
	surfaceAirBc408->SetFinish(ground);
	surfaceAirBc408->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", photonEnergyShort,
			bc408RefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", photonEnergyShort,
			specularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", photonEnergyShort,
			specularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", photonEnergyShort,
			backScatter, nEntryShort);
	surfaceAirBc408->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceBc408Plexiglass(void)
{
	surfaceBc408Plexiglass = new G4OpticalSurface("bc408PlexiglassSurface");
	surfaceBc408Plexiglass->SetType(dielectric_dielectric);
	surfaceBc408Plexiglass->SetModel(unified);
	surfaceBc408Plexiglass->SetFinish(ground);
	surfaceBc408Plexiglass->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", photonEnergyShort,
			plexiglassRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", photonEnergyShort,
			specularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", photonEnergyShort,
			specularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", photonEnergyShort,
			backScatter, nEntryShort);
	surfaceBc408Plexiglass->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfacePlexiglassGlass(void)
{
	surfacePlexiglassGlass = new G4OpticalSurface("plexiglassGlassSurface");
	surfacePlexiglassGlass->SetType(dielectric_dielectric);
	surfacePlexiglassGlass->SetModel(unified);
	surfacePlexiglassGlass->SetFinish(ground);
	surfacePlexiglassGlass->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", photonEnergyShort,
			glassRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", photonEnergyShort,
			specularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", photonEnergyShort,
			specularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", photonEnergyShort,
			backScatter, nEntryShort);
	surfacePlexiglassGlass->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfacePlexiglassAir(void)
{
	surfacePlexiglassAir = new G4OpticalSurface("plexiglassAirSurface");
	surfacePlexiglassAir->SetType(dielectric_dielectric);
	surfacePlexiglassAir->SetModel(unified);
	surfacePlexiglassAir->SetFinish(ground);
	surfacePlexiglassAir->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", photonEnergyShort,
			airRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", photonEnergyShort,
			specularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", photonEnergyShort,
			specularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", photonEnergyShort,
			backScatter, nEntryShort);
	surfacePlexiglassAir->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceAirPlexiglass(void)
{
	surfaceAirPlexiglass = new G4OpticalSurface("airPlexiglassSurface");
	surfaceAirPlexiglass->SetType(dielectric_dielectric);
	surfaceAirPlexiglass->SetModel(unified);
	surfaceAirPlexiglass->SetFinish(ground);
	surfaceAirPlexiglass->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", photonEnergyShort,
			plexiglassRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", photonEnergyShort,
			specularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", photonEnergyShort,
			specularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", photonEnergyShort,
			backScatter, nEntryShort);
	surfaceAirPlexiglass->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceGlassVacuum(void)
{
	surfaceGlassVacuum = new G4OpticalSurface("glassVacuumSurface");
	surfaceGlassVacuum->SetType(dielectric_dielectric);
	surfaceGlassVacuum->SetModel(unified);
	surfaceGlassVacuum->SetFinish(ground); //groundair
	surfaceGlassVacuum->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", photonEnergyShort,
			airRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", photonEnergyShort,
			specularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", photonEnergyShort,
			specularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", photonEnergyShort,
			backScatter, nEntryShort);
	surfaceGlassVacuum->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceVacuumBialkali(void)
{
	surfaceVacuumBialkali = new G4OpticalSurface("vacuumBialkaliSurface");
	surfaceVacuumBialkali->SetType(dielectric_dielectric);
	surfaceVacuumBialkali->SetModel(unified);
	surfaceVacuumBialkali->SetFinish(ground);
	surfaceVacuumBialkali->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", photonEnergyShort,
			glassRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", photonEnergyShort,
			specularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", photonEnergyShort,
			specularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", photonEnergyShort,
			backScatter, nEntryShort);
	surfaceVacuumBialkali->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceAluminium(void)
{
	surfaceAluminium = new G4OpticalSurface("aluminiumSurface");
	surfaceAluminium->SetType(dielectric_metal);
	surfaceAluminium->SetModel(unified);
	surfaceAluminium->SetFinish(ground);
	surfaceAluminium->SetPolish(0.0);

	G4double aluminiumReflectivityShort[nEntryShort] = { aluminiumReflectivity,
		aluminiumReflectivity };
	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("REFLECTIVITY", photonEnergyShort,
			aluminiumReflectivityShort, nEntryShort);
	surfaceAluminium->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceMirror(void)
{
	surfaceMirror = new G4OpticalSurface("mirrorSurface");
	surfaceMirror->SetModel(unified);
	surfaceMirror->SetType(dielectric_dielectric);
	surfaceMirror->SetFinish(polishedfrontpainted);

	G4double aluminiumReflectivityShort[nEntryShort] = { 1.0, 1.0 };
	G4MaterialPropertiesTable* surfaceProperties =
		new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("REFLECTIVITY", photonEnergyShort,
			aluminiumReflectivityShort, nEntryShort);
	surfaceAluminium->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildDeuterium(void)
{
	ele_D = new G4Element("Deuterium Atom","D",1);
	ele_D->AddIsotope(iso_H2, 100.*perCent);

	//G4Material* Deuterium = new G4Material("DeuteriumGas", density=0.08*g/m3, ncomponents=2, kStateGas, 
	//                                       temperature=293.15*kelvin, chamberPressure=0.005*bar);
	deuteriumGas = new G4Material("2H", 0.180 * 10.0e-3 * CLHEP::kg / CLHEP::m3, 1,
			kStateGas, 298 * CLHEP::kelvin, 10.0e-3 * CLHEP::atmosphere);

	deuteriumGas->AddElement(ele_D,2);
}

void TRexMaterials::BuildDeuteratedPE(void)
{
	ele_D = new G4Element("Deuterium Atom","D",1);
	ele_D->AddIsotope(iso_H2, 100.*perCent);

	deuteratedPE = new G4Material("DeuteratedPE",
			0.92 * CLHEP::g / CLHEP::cm3, 2);
	deuteratedPE->AddElement(elC, 2);
	deuteratedPE->AddElement(ele_D, 4);
}

void TRexMaterials::BuildSolidDeuterium(void)
{
	ele_D = new G4Element("Deuterium Atom","D",1);
	ele_D->AddIsotope(iso_H2, 100.*perCent);

	//G4Material* Deuterium = new G4Material("DeuteriumGas", density=0.08*g/m3, ncomponents=2, kStateGas, 
	//                                       temperature=293.15*kelvin, chamberPressure=0.005*bar);
	solidDeuterium = new G4Material("SolidDeuterium", 196.7 * CLHEP::kg / CLHEP::m3, 1,
			kStateSolid);

	solidDeuterium->AddElement(ele_D,2);
}


G4Material* TRexMaterials::GetMaterial(std::string name) {//, double pressure) {
	//// if the pressure is non-zero, we add it (in mbar) to the name (with two digits precision)
	//if(pressure != 0.) {
	//	std::ostringstream str;
	//	str<<name<<"_"<<std::fixed<<std::setprecision(2)<<1000.*pressure/bar<<std::defaultfloat<<"mbar";
	//	name = str.str();
	//}
	G4Material* material = G4Material::GetMaterial(name);
	if(material != NULL) { 
		return material; 
	}

	if(name == "vacuum" || name == "dummy"){
		material = MiniBallMaterial::Get()->GetMaterialVacuum();
	} else if(((G4String)name).contains("PE")) {
		material = TRexMaterials::Get()->deuteratedPE;
	} else if(name == "deuteriumGas") {
		material = TRexMaterials::Get()->deuteriumGas;
	} else if(name == "solidDeuterium") {
		material = TRexMaterials::Get()->solidDeuterium;
	} else if(((G4String)name).contains("G4_")) {
		material = TRexMaterials::Get()->GetNistManager()->FindOrBuildMaterial(name);
	} else if(((G4String)name).contains("48Ti")) {
		material = TRexMaterials::Get()->GetNistManager()->FindOrBuildMaterial("G4_Ti");
	} else if(((G4String)name).contains("109Ag")) {
		material = TRexMaterials::Get()->GetNistManager()->FindOrBuildMaterial("G4_Ag");
	} else {
		G4String matName = name;
		G4int splitIndex = matName.find_first_not_of("0123456789");
		G4String massNumberString = matName.substr(0,splitIndex);
		G4String elementName = matName.substr(splitIndex,  std::string::npos);
		G4int massNumber = atoi(massNumberString);

		G4Material* bufferMaterial =  TRexMaterials::Get()->GetNistManager()->FindOrBuildMaterial("G4_"+elementName);
		G4double density = bufferMaterial->GetDensity();
		G4double molarMass = TRexMaterials::Get()->GetNistManager()->GetAtomicMass(bufferMaterial->GetZ(),massNumber)*(g/mole)/amu_c2;
		G4cout << "matName " << matName << " massNrString " << massNumber << " elementName " << elementName << " Z " << bufferMaterial->GetZ() <<" molar mass " << std::setprecision(5)<<
			molarMass/(g/mole) << " density " << density/(g/cm3)<< G4endl;
		material = new G4Material(matName,bufferMaterial->GetZ(), molarMass, density );
	}

	std::cout<<"got material "<<material->GetName()<<" from "<<name<<std::endl;

	return material;
}
