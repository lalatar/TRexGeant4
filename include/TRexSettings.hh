/*
 * TRexSettings.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXSETTINGS_HH_
#define TREXSETTINGS_HH_

#include "TEnv.h"

#include "G4UnitsTable.hh"
#include "globals.hh"

#include <string>

class TRexSettings {
public:
  static TRexSettings* Get();
  virtual ~TRexSettings();

  void ReadSettingsFile(std::string settingsFile);
  std::string GetSettingsFile() { return fSettingsFile; }  //GetSettingsFile
  std::string GetPrimaryGenerator() { return fPrimaryGenerator; }

  int SimulateGammas() { return fSimulateGammas; }
  int IncludeEnergyResolution() { return fIncludeEnergyResolution; }
  int IncludeVacuumChamber() { return fIncludeVacuumChamber; }
  std::string GetVacuumChamberType() { return fVacuumChamberType; }
  std::string GetVacuumChamberGas() { return fVacuumChamberGas; }
  double GetVacuumChamberGasPressure() { return fVacuumChamberGasPressure; }

  // test source parameters
  G4double GetTestSourceEnergy() { return fTestSourceEnergy; }

  // beam parameters
  G4double GetBeamEnergy() { return fBeamEnergy; }
  G4double GetBeamWidth() { return fBeamWidth; }
  G4double GetThetaCmMin() { return fThetaCmMin; }

  G4int GetProjectileZ() { return fProjectileZ; }
  G4int GetProjectileA() { return fProjectileA; }
  G4int GetTargetZ() { return fTargetZ; }
  G4int GetTargetA() { return fTargetA; }
  G4int GetEjectileZ() { return fEjectileZ; }
  G4int GetEjectileA() { return fEjectileA; }
  G4int GetRecoilZ() { return fRecoilZ; }
  G4int GetRecoilA() { return fRecoilA; }
  std::string GetProjectileName() { return fProjectileName; }
  std::string GetTargetName() { return fTargetName; }
  std::string GetEjectileName() { return fEjectileName; }
  std::string GetRecoilName() { return fRecoilName; }

  std::string GetTargetMaterialName() { return fTargetMaterialName; }
  G4double GetTargetAtomicRatio() { return fTargetAtomicRatio; }
  G4double GetTransferOrCoulexProbability() { return fTransferOrCoulexProbability; }

  std::string GetLevelFile() { return fLevelFile; }
  std::string GetAngularDistributionFile() { return fAngularDistributionFile; }
  std::string GetMassFile() { return fMassFile; }

  // alpha source  parameters
  G4double GetAlphaSourceDiameter() { return fAlphaSourceDiameter; }
  G4double GetAlphaSourceThickness() { return fAlphaSourceThickness; }

  // target dimensions (or inactive alpha source dimensions)
  G4double GetTargetDiameter() { return fTargetDiameter; }
  G4double GetTargetThickness() { return fTargetThickness; }
  G4double GetGasTargetLength() { return fGasTargetLength; }
  G4double GetTargetPressure() { return fTargetPressure; }
  // returns the target length in um
  G4double GetTargetPhysicalLength();
  //G4String GetTargetMaterial() { return fTargetMaterial; }
  G4double GetTargetMaterialDensity() { return fTargetMaterialDensity; }
  void SetTargetMaterialDensity(G4double density) { fTargetMaterialDensity = density; }
  void SetTargetThickness(G4double thickness) { fTargetThickness = thickness; }

  // visualization
  int Colours() { return fColours; }
  bool VisualizationCut() { return fVisualizationCut; }
  void VisualizationCut(bool cut) { fVisualizationCut = cut; }

  // fill always the detector tree regardless if a detector was hit or not ?
  int WriteAllEvents() { return fWriteAllEvents; }


  //////////////////
  // detectors
  //////////////////
  int ConstructPCB(){ return fConstructPCB;}

  // FCD deltaE
  int UseFCDdeltaE() { return fUseFCDdeltaE; }
  int GetNbOfFCDdeltaESingles() { return fNbOfFCDdeltaESingles; }
  std::vector<G4double> GetFCDdeltaESinglePosX() { return fFCDdeltaESinglePosX; }
  std::vector<G4double> GetFCDdeltaESinglePosY() { return fFCDdeltaESinglePosY; }
  std::vector<G4double> GetFCDdeltaESinglePosZ() { return fFCDdeltaESinglePosZ; }
  std::vector<G4double> GetFCDdeltaESingleStartAngle() { return fFCDdeltaESingleStartAngle; }
  std::vector<G4double> GetFCDdeltaESingleThickness() { return fFCDdeltaESingleThickness; }
  G4double GetFCDdeltaESingleDeadLayer() { return fFCDdeltaESingleDeadLayer; }
  G4double GetFCDdeltaESingleInnerRadius() { return fFCDdeltaESingleInnerRadius; }
  G4double GetFCDdeltaESingleOuterRadius() { return fFCDdeltaESingleOuterRadius; }
  G4double GetFCDdeltaESingleRingWidth() { return fFCDdeltaESingleRingWidth; }
  G4double GetFCDdeltaESingleSpanningAngle() { return fFCDdeltaESingleSpanningAngle; }
  G4double GetFCDdeltaESingleStripWidth() { return fFCDdeltaESingleStripWidth; }
  int FCDTransferTo16Strips() { return fFCDTransferTo16Strips; }
  G4double GetFCDdeltaESingleEnergyResolution() { return fFCDdeltaESingleEnergyResolution; }
  G4double GetFCDdeltaESingleFoilThickness() { return fFCDdeltaESingleFoilThickness; }
  // FCD Erest
  int UseFCDErest() { return fUseFCDErest; }
  int GetNbOfFCDErestSingles() { return fNbOfFCDErestSingles; }
  std::vector<G4double> GetFCDErestSinglePosX() { return fFCDErestSinglePosX; }
  std::vector<G4double> GetFCDErestSinglePosY() { return fFCDErestSinglePosY; }
  std::vector<G4double> GetFCDErestSinglePosZ() { return fFCDErestSinglePosZ; }
  std::vector<G4double> GetFCDErestSingleStartAngle() { return fFCDErestSingleStartAngle; }
  std::vector<G4double> GetFCDErestSingleThickness() { return fFCDErestSingleThickness; }
  G4double GetFCDErestSingleDeadLayer() { return fFCDErestSingleDeadLayer; }
  G4double GetFCDErestSingleInnerRadius() { return fFCDErestSingleInnerRadius; }
  G4double GetFCDErestSingleOuterRadius() { return fFCDErestSingleOuterRadius; }
  G4double GetFCDErestSingleSpanningAngle() { return fFCDErestSingleSpanningAngle; }
  G4double GetFCDErestSingleEnergyResolution() { return fFCDErestSingleEnergyResolution; }

  // BCD deltaE
  int UseBCDdeltaE() { return fUseBCDdeltaE; }
  int GetNbOfBCDdeltaESingles() { return fNbOfBCDdeltaESingles; }
  std::vector<G4double> GetBCDdeltaESinglePosX() { return fBCDdeltaESinglePosX; }
  std::vector<G4double> GetBCDdeltaESinglePosY() { return fBCDdeltaESinglePosY; }
  std::vector<G4double> GetBCDdeltaESinglePosZ() { return fBCDdeltaESinglePosZ; }
  std::vector<G4double> GetBCDdeltaESingleStartAngle() { return fBCDdeltaESingleStartAngle; }
  std::vector<G4double> GetBCDdeltaESingleThickness() { return fBCDdeltaESingleThickness; }
  G4double GetBCDdeltaESingleDeadLayer() { return fBCDdeltaESingleDeadLayer; }
  G4double GetBCDdeltaESingleInnerRadius() { return fBCDdeltaESingleInnerRadius; }
  G4double GetBCDdeltaESingleOuterRadius() { return fBCDdeltaESingleOuterRadius; }
  G4double GetBCDdeltaESingleRingWidth() { return fBCDdeltaESingleRingWidth; }
  G4double GetBCDdeltaESingleSpanningAngle() { return fBCDdeltaESingleSpanningAngle; }
  G4double GetBCDdeltaESingleStripWidth() { return fBCDdeltaESingleStripWidth; }
  int BCDTransferTo16Strips() { return fBCDTransferTo16Strips; }
  G4double GetBCDdeltaESingleEnergyResolution() { return fBCDdeltaESingleEnergyResolution; }
  G4double GetBCDdeltaESingleFoilThickness() { return fBCDdeltaESingleFoilThickness; }
  // BCD Erest
  int UseBCDErest() { return fUseBCDErest; }
  int GetNbOfBCDErestSingles() { return fNbOfBCDErestSingles; }
  std::vector<G4double> GetBCDErestSinglePosX() { return fBCDErestSinglePosX; }
  std::vector<G4double> GetBCDErestSinglePosY() { return fBCDErestSinglePosY; }
  std::vector<G4double> GetBCDErestSinglePosZ() { return fBCDErestSinglePosZ; }
  std::vector<G4double> GetBCDErestSingleStartAngle() { return fBCDErestSingleStartAngle; }
  std::vector<G4double> GetBCDErestSingleThickness() { return fBCDErestSingleThickness; }
  G4double GetBCDErestSingleDeadLayer() { return fBCDErestSingleDeadLayer; }
  G4double GetBCDErestSingleInnerRadius() { return fBCDErestSingleInnerRadius; }
  G4double GetBCDErestSingleOuterRadius() { return fBCDErestSingleOuterRadius; }
  G4double GetBCDErestSingleSpanningAngle() { return fBCDErestSingleSpanningAngle; }
  G4double GetBCDErestSingleEnergyResolution() { return fBCDErestSingleEnergyResolution; }

  // FBarrel deltaE
  int UseFBarrelDeltaE() { return fUseFBarrelDeltaE; }
  int GetNbOfFBarrelDeltaESingles() { return fNbOfFBarrelDeltaESingles; }
  //std::vector<G4double> GetFBarrelDeltaESinglePosX() { return fFBarrelDeltaESinglePosX; }
  //std::vector<G4double> GetFBarrelDeltaESinglePosY() { return fFBarrelDeltaESinglePosY; }
  std::vector<G4double> GetFBarrelDeltaESinglePosZ() { return fFBarrelDeltaESinglePosZ; }
  std::vector<G4double> GetFBarrelDeltaESingleDistanceToBeam() { return fFBarrelDeltaESingleDistanceToBeam; }
  std::vector<G4double> GetFBarrelDeltaESingleStartAngle() { return fFBarrelDeltaESingleStartAngle; }
  std::vector<G4double> GetFBarrelDeltaESingleThickness() { return fFBarrelDeltaESingleThickness; }
  G4double GetFBarrelDeltaESingleDeadLayer() { return fFBarrelDeltaESingleDeadLayer; }
  G4double GetFBarrelDeltaESingleLengthX() { return fFBarrelDeltaESingleLengthX; }
  G4double GetFBarrelDeltaESingleLengthY() { return fFBarrelDeltaESingleLengthY; }
  G4double GetFBarrelDeltaESingleStripWidth() { return fFBarrelDeltaESingleStripWidth; }
  G4double GetFBarrelDeltaESingleEnergyResolution() { return fFBarrelDeltaESingleEnergyResolution; }
  G4double GetFBarrelDeltaESingleFoilThickness() { return fFBarrelDeltaESingleFoilThickness; }
  // FBarrel Erest
  int UseFBarrelErest() { return fUseFBarrelErest; }
  int GetNbOfFBarrelErestSingles() { return fNbOfFBarrelErestSingles; }
  //std::vector<G4double> GetFBarrelErestSinglePosX() { return fFBarrelErestSinglePosX; }
  //std::vector<G4double> GetFBarrelErestSinglePosY() { return fFBarrelErestSinglePosY; }
  std::vector<G4double> GetFBarrelErestSinglePosZ() { return fFBarrelErestSinglePosZ; }
  std::vector<G4double> GetFBarrelErestSingleDistanceToBeam() { return fFBarrelErestSingleDistanceToBeam; }
  std::vector<G4double> GetFBarrelErestSingleStartAngle() { return fFBarrelErestSingleStartAngle; }
  std::vector<G4double> GetFBarrelErestSingleThickness() { return fFBarrelErestSingleThickness; }
  G4double GetFBarrelErestSingleDeadLayer() { return fFBarrelErestSingleDeadLayer; }
  G4double GetFBarrelErestSingleLengthX() { return fFBarrelErestSingleLengthX; }
  G4double GetFBarrelErestSingleLengthY() { return fFBarrelErestSingleLengthY; }
  G4double GetFBarrelErestSingleEnergyResolution() { return fFBarrelErestSingleEnergyResolution; }
  // Second FBarrel deltaE
  int UseSecondFBarrelDeltaE() { return fUseSecondFBarrelDeltaE; }
  int GetNbOfSecondFBarrelDeltaESingles() { return fNbOfSecondFBarrelDeltaESingles; }
  std::vector<G4double> GetSecondFBarrelDeltaESinglePosZ() { return fSecondFBarrelDeltaESinglePosZ; }
  std::vector<G4double> GetSecondFBarrelDeltaESingleDistanceToBeam() { return fSecondFBarrelDeltaESingleDistanceToBeam; }
  std::vector<G4double> GetSecondFBarrelDeltaESingleStartAngle() { return fSecondFBarrelDeltaESingleStartAngle; }
  std::vector<G4double> GetSecondFBarrelDeltaESingleThickness() { return fSecondFBarrelDeltaESingleThickness; }
  G4double GetSecondFBarrelDeltaESingleDeadLayer() { return fSecondFBarrelDeltaESingleDeadLayer; }
  G4double GetSecondFBarrelDeltaESingleLengthX() { return fSecondFBarrelDeltaESingleLengthX; }
  G4double GetSecondFBarrelDeltaESingleLengthY() { return fSecondFBarrelDeltaESingleLengthY; }
  G4double GetSecondFBarrelDeltaESingleStripWidth() { return fSecondFBarrelDeltaESingleStripWidth; }
  G4double GetSecondFBarrelDeltaESingleEnergyResolution() { return fSecondFBarrelDeltaESingleEnergyResolution; }
  G4double GetSecondFBarrelDeltaESingleFoilThickness() { return fSecondFBarrelDeltaESingleFoilThickness; }

  // MBarrel deltaE
  int UseMBarrelDeltaE() { return fUseMBarrelDeltaE; }
  int GetNbOfMBarrelDeltaESingles() { return fNbOfMBarrelDeltaESingles; }
  //std::vector<G4double> GetMBarrelDeltaESinglePosX() { return fMBarrelDeltaESinglePosX; }
  //std::vector<G4double> GetMBarrelDeltaESinglePosY() { return fMBarrelDeltaESinglePosY; }
  std::vector<G4double> GetMBarrelDeltaESinglePosZ() { return fMBarrelDeltaESinglePosZ; }
  std::vector<G4double> GetMBarrelDeltaESingleDistanceToBeam() { return fMBarrelDeltaESingleDistanceToBeam; }
  std::vector<G4double> GetMBarrelDeltaESingleStartAngle() { return fMBarrelDeltaESingleStartAngle; }
  std::vector<G4double> GetMBarrelDeltaESingleThickness() { return fMBarrelDeltaESingleThickness; }
  G4double GetMBarrelDeltaESingleDeadLayer() { return fMBarrelDeltaESingleDeadLayer; }
  G4double GetMBarrelDeltaESingleLengthX() { return fMBarrelDeltaESingleLengthX; }
  G4double GetMBarrelDeltaESingleLengthY() { return fMBarrelDeltaESingleLengthY; }
  G4double GetMBarrelDeltaESingleStripWidth() { return fMBarrelDeltaESingleStripWidth; }
  G4double GetMBarrelDeltaESingleEnergyResolution() { return fMBarrelDeltaESingleEnergyResolution; }
  G4double GetMBarrelDeltaESingleFoilThickness() { return fMBarrelDeltaESingleFoilThickness; }
  // MBarrel Erest
  int UseMBarrelErest() { return fUseMBarrelErest; }
  int GetNbOfMBarrelErestSingles() { return fNbOfMBarrelErestSingles; }
  //std::vector<G4double> GetMBarrelErestSinglePosX() { return fMBarrelErestSinglePosX; }
  //std::vector<G4double> GetMBarrelErestSinglePosY() { return fMBarrelErestSinglePosY; }
  std::vector<G4double> GetMBarrelErestSinglePosZ() { return fMBarrelErestSinglePosZ; }
  std::vector<G4double> GetMBarrelErestSingleDistanceToBeam() { return fMBarrelErestSingleDistanceToBeam; }
  std::vector<G4double> GetMBarrelErestSingleStartAngle() { return fMBarrelErestSingleStartAngle; }
  std::vector<G4double> GetMBarrelErestSingleThickness() { return fMBarrelErestSingleThickness; }
  G4double GetMBarrelErestSingleDeadLayer() { return fMBarrelErestSingleDeadLayer; }
  G4double GetMBarrelErestSingleLengthX() { return fMBarrelErestSingleLengthX; }
  G4double GetMBarrelErestSingleLengthY() { return fMBarrelErestSingleLengthY; }
  G4double GetMBarrelErestSingleEnergyResolution() { return fMBarrelErestSingleEnergyResolution; }

  // BBarrel deltaE
  int UseBBarrelDeltaE() { return fUseBBarrelDeltaE; }
  int GetNbOfBBarrelDeltaESingles() { return fNbOfBBarrelDeltaESingles; }
  //std::vector<G4double> GetBBarrelDeltaESinglePosX() { return fBBarrelDeltaESinglePosX; }
  //std::vector<G4double> GetBBarrelDeltaESinglePosY() { return fBBarrelDeltaESinglePosY; }
  std::vector<G4double> GetBBarrelDeltaESinglePosZ() { return fBBarrelDeltaESinglePosZ; }
  std::vector<G4double> GetBBarrelDeltaESingleDistanceToBeam() { return fBBarrelDeltaESingleDistanceToBeam; }
  std::vector<G4double> GetBBarrelDeltaESingleStartAngle() { return fBBarrelDeltaESingleStartAngle; }
  std::vector<G4double> GetBBarrelDeltaESingleThickness() { return fBBarrelDeltaESingleThickness; }
  G4double GetBBarrelDeltaESingleDeadLayer() { return fBBarrelDeltaESingleDeadLayer; }
  G4double GetBBarrelDeltaESingleLengthX() { return fBBarrelDeltaESingleLengthX; }
  G4double GetBBarrelDeltaESingleLengthY() { return fBBarrelDeltaESingleLengthY; }
  G4double GetBBarrelDeltaESingleStripWidth() { return fBBarrelDeltaESingleStripWidth; }
  G4double GetBBarrelDeltaESingleEnergyResolution() { return fBBarrelDeltaESingleEnergyResolution; }
  G4double GetBBarrelDeltaESingleFoilThickness() { return fBBarrelDeltaESingleFoilThickness; }
  // BBarrel Erest
  int UseBBarrelErest() { return fUseBBarrelErest; }
  int GetNbOfBBarrelErestSingles() { return fNbOfBBarrelErestSingles; }
  //std::vector<G4double> GetBBarrelErestSinglePosX() { return fBBarrelErestSinglePosX; }
  //std::vector<G4double> GetBBarrelErestSinglePosY() { return fBBarrelErestSinglePosY; }
  std::vector<G4double> GetBBarrelErestSinglePosZ() { return fBBarrelErestSinglePosZ; }
  std::vector<G4double> GetBBarrelErestSingleDistanceToBeam() { return fBBarrelErestSingleDistanceToBeam; }
  std::vector<G4double> GetBBarrelErestSingleStartAngle() { return fBBarrelErestSingleStartAngle; }
  std::vector<G4double> GetBBarrelErestSingleThickness() { return fBBarrelErestSingleThickness; }
  G4double GetBBarrelErestSingleDeadLayer() { return fBBarrelErestSingleDeadLayer; }
  G4double GetBBarrelErestSingleLengthX() { return fBBarrelErestSingleLengthX; }
  G4double GetBBarrelErestSingleLengthY() { return fBBarrelErestSingleLengthY; }
  G4double GetBBarrelErestSingleEnergyResolution() { return fBBarrelErestSingleEnergyResolution; }
  // Second BBarrel deltaE
  int UseSecondBBarrelDeltaE() { return fUseSecondBBarrelDeltaE; }
  int GetNbOfSecondBBarrelDeltaESingles() { return fNbOfSecondBBarrelDeltaESingles; }
  std::vector<G4double> GetSecondBBarrelDeltaESinglePosZ() { return fSecondBBarrelDeltaESinglePosZ; }
  std::vector<G4double> GetSecondBBarrelDeltaESingleDistanceToBeam() { return fSecondBBarrelDeltaESingleDistanceToBeam; }
  std::vector<G4double> GetSecondBBarrelDeltaESingleStartAngle() { return fSecondBBarrelDeltaESingleStartAngle; }
  std::vector<G4double> GetSecondBBarrelDeltaESingleThickness() { return fSecondBBarrelDeltaESingleThickness; }
  G4double GetSecondBBarrelDeltaESingleDeadLayer() { return fSecondBBarrelDeltaESingleDeadLayer; }
  G4double GetSecondBBarrelDeltaESingleLengthX() { return fSecondBBarrelDeltaESingleLengthX; }
  G4double GetSecondBBarrelDeltaESingleLengthY() { return fSecondBBarrelDeltaESingleLengthY; }
  G4double GetSecondBBarrelDeltaESingleStripWidth() { return fSecondBBarrelDeltaESingleStripWidth; }
  G4double GetSecondBBarrelDeltaESingleEnergyResolution() { return fSecondBBarrelDeltaESingleEnergyResolution; }
  G4double GetSecondBBarrelDeltaESingleFoilThickness() { return fSecondBBarrelDeltaESingleFoilThickness; }

  // Forward Trapezoid deltaE
  int UseFTrapezoidDeltaE() { return fUseFTrapezoidDeltaE; }
  int GetNbOfFTrapezoidDeltaESingles() { return fNbOfFTrapezoidDeltaESingles; }
  std::vector<G4double> GetFTrapezoidDeltaESinglePosZ() { return fFTrapezoidDeltaESinglePosZ; }
  G4double GetFTrapezoidDeltaESingleInnerRadius() { return fFTrapezoidDeltaESingleInnerRadius; }
  G4double GetFTrapezoidDeltaESingleOuterRadius() { return fFTrapezoidDeltaESingleOuterRadius; }
  G4double GetFTrapezoidDeltaESingleDeltaZ() { return fFTrapezoidDeltaESingleDeltaZ; }
  std::vector<G4double> GetFTrapezoidDeltaESingleThickness() { return fFTrapezoidDeltaESingleThickness; }
  std::vector<G4double> GetFTrapezoidDeltaESingleStartAngle() { return fFTrapezoidDeltaESingleStartAngle; }
  G4double GetFTrapezoidDeltaESingleNbOfRings() { return fFTrapezoidDeltaESingleNbOfRings; }
  G4double GetFTrapezoidDeltaESingleNbOfStrips() { return fFTrapezoidDeltaESingleNbOfStrips; }
  G4double GetFTrapezoidDeltaESingleEnergyResolution() { return fFTrapezoidDeltaESingleEnergyResolution; }
  G4double GetFTrapezoidDeltaESingleFoilThickness() { return fFTrapezoidDeltaESingleFoilThickness; }
  // Forward Trapezoid Erest
  int UseFTrapezoidErest() { return fUseFTrapezoidErest; }
  int GetNbOfFTrapezoidErestSingles() { return fNbOfFTrapezoidErestSingles; }
  std::vector<G4double> GetFTrapezoidErestSinglePosZ() { return fFTrapezoidErestSinglePosZ; }
  G4double GetFTrapezoidErestSingleInnerRadius() { return fFTrapezoidErestSingleInnerRadius; }
  G4double GetFTrapezoidErestSingleOuterRadius() { return fFTrapezoidErestSingleOuterRadius; }
  G4double GetFTrapezoidErestSingleDeltaZ() { return fFTrapezoidErestSingleDeltaZ; }
  std::vector<G4double> GetFTrapezoidErestSingleThickness() { return fFTrapezoidErestSingleThickness; }
  std::vector<G4double> GetFTrapezoidErestSingleStartAngle() { return fFTrapezoidErestSingleStartAngle; }
  G4double GetFTrapezoidErestSingleEnergyResolution() { return fFTrapezoidErestSingleEnergyResolution; }

  // Backward Trapezoid deltaE
  int UseBTrapezoidDeltaE() { return fUseBTrapezoidDeltaE; }
  int GetNbOfBTrapezoidDeltaESingles() { return fNbOfBTrapezoidDeltaESingles; }
  std::vector<G4double> GetBTrapezoidDeltaESinglePosZ() { return fBTrapezoidDeltaESinglePosZ; }
  G4double GetBTrapezoidDeltaESingleInnerRadius() { return fBTrapezoidDeltaESingleInnerRadius; }
  G4double GetBTrapezoidDeltaESingleOuterRadius() { return fBTrapezoidDeltaESingleOuterRadius; }
  G4double GetBTrapezoidDeltaESingleDeltaZ() { return fBTrapezoidDeltaESingleDeltaZ; }
  std::vector<G4double> GetBTrapezoidDeltaESingleThickness() { return fBTrapezoidDeltaESingleThickness; }
  std::vector<G4double> GetBTrapezoidDeltaESingleStartAngle() { return fBTrapezoidDeltaESingleStartAngle; }
  G4double GetBTrapezoidDeltaESingleNbOfRings() { return fBTrapezoidDeltaESingleNbOfRings; }
  G4double GetBTrapezoidDeltaESingleNbOfStrips() { return fBTrapezoidDeltaESingleNbOfStrips; }
  G4double GetBTrapezoidDeltaESingleEnergyResolution() { return fBTrapezoidDeltaESingleEnergyResolution; }
  G4double GetBTrapezoidDeltaESingleFoilThickness() { return fBTrapezoidDeltaESingleFoilThickness; }
  // Backward Trapezoid Erest
  int UseBTrapezoidErest() { return fUseBTrapezoidErest; }
  int GetNbOfBTrapezoidErestSingles() { return fNbOfBTrapezoidErestSingles; }
  std::vector<G4double> GetBTrapezoidErestSinglePosZ() { return fBTrapezoidErestSinglePosZ; }
  G4double GetBTrapezoidErestSingleInnerRadius() { return fBTrapezoidErestSingleInnerRadius; }
  G4double GetBTrapezoidErestSingleOuterRadius() { return fBTrapezoidErestSingleOuterRadius; }
  G4double GetBTrapezoidErestSingleDeltaZ() { return fBTrapezoidErestSingleDeltaZ; }
  std::vector<G4double> GetBTrapezoidErestSingleThickness() { return fBTrapezoidErestSingleThickness; }
  std::vector<G4double> GetBTrapezoidErestSingleStartAngle() { return fBTrapezoidErestSingleStartAngle; }
  G4double GetBTrapezoidErestSingleEnergyResolution() { return fBTrapezoidErestSingleEnergyResolution; }

  // Miniball
  int GetNbOfMiniballClusters() { return fNbOfMiniballClusters; }
  std::vector<G4String> GetMiniballClusterNames() { return fMiniballClusterNames; }
  std::vector<int> GetMiniballClusterTypes() { return fMiniballClusterTypes; }
  std::vector<G4double> GetMiniballClusterRho() { return fMiniballClusterRho; }
  std::vector<G4double> GetMiniballClusterTheta() { return fMiniballClusterTheta; }
  std::vector<G4double> GetMiniballClusterPhi() { return fMiniballClusterPhi; }
  std::vector<G4double> GetMiniballClusterSpin() { return fMiniballClusterSpin; }
  G4double GetMiniballEnergyResolutionCore() { return fMiniballEnergyResolutionCore; }
  G4double GetMiniballEnergyResolutionSegment() { return fMiniballEnergyResolutionSegment; }

private:
  TRexSettings();

  static TRexSettings* fSettings;

  std::string fSettingsFile;
  std::string fPrimaryGenerator;
  int fSimulateGammas;
  int fIncludeEnergyResolution;
  int fIncludeVacuumChamber;
  std::string fVacuumChamberType;
  std::string fVacuumChamberGas;
  double fVacuumChamberGasPressure;

  G4double fTestSourceEnergy;
  G4double fBeamEnergy;
  G4double fBeamWidth;
  G4double fThetaCmMin;

  G4int fProjectileZ, fProjectileA;
  G4int fTargetZ, fTargetA;
  G4int fEjectileZ, fEjectileA;
  G4int fRecoilZ, fRecoilA;
  std::string fProjectileName, fTargetName, fEjectileName, fRecoilName;

  std::string fTargetMaterialName;
  G4double fTargetAtomicRatio;
  G4double fTransferOrCoulexProbability;

  std::string fLevelFile;
  std::string fAngularDistributionFile;
  std::string fMassFile;

  G4double fAlphaSourceDiameter;
  G4double fAlphaSourceThickness;

  G4double fTargetDiameter;
  G4double fTargetThickness;
  G4double fGasTargetLength;
  G4double fTargetPressure;
  //G4String fTargetMaterial;
  G4double fTargetMaterialDensity;

  int fColours;
  int fWriteAllEvents;
  bool fVisualizationCut;

  int fConstructPCB;

  // FCD deltaE
  int fUseFCDdeltaE;
  int fNbOfFCDdeltaESingles;
  std::vector<G4double> fFCDdeltaESinglePosX;
  std::vector<G4double> fFCDdeltaESinglePosY;
  std::vector<G4double> fFCDdeltaESinglePosZ;
  std::vector<G4double> fFCDdeltaESingleStartAngle;
  std::vector<G4double> fFCDdeltaESingleThickness;
  G4double fFCDdeltaESingleDeadLayer;
  G4double fFCDdeltaESingleInnerRadius;
  G4double fFCDdeltaESingleOuterRadius;
  G4double fFCDdeltaESingleRingWidth;
  G4double fFCDdeltaESingleSpanningAngle;
  G4double fFCDdeltaESingleStripWidth;
  int fFCDTransferTo16Strips;
  G4double fFCDdeltaESingleEnergyResolution;
  G4double fFCDdeltaESingleFoilThickness;
  // FCD Erest
  int fUseFCDErest;
  int fNbOfFCDErestSingles;
  std::vector<G4double> fFCDErestSinglePosX;
  std::vector<G4double> fFCDErestSinglePosY;
  std::vector<G4double> fFCDErestSinglePosZ;
  std::vector<G4double> fFCDErestSingleStartAngle;
  std::vector<G4double> fFCDErestSingleThickness;
  G4double fFCDErestSingleDeadLayer;
  G4double fFCDErestSingleInnerRadius;
  G4double fFCDErestSingleOuterRadius;
  G4double fFCDErestSingleSpanningAngle;
  G4double fFCDErestSingleEnergyResolution;

  // BCD deltaE
  int fUseBCDdeltaE;
  int fNbOfBCDdeltaESingles;
  std::vector<G4double> fBCDdeltaESinglePosX;
  std::vector<G4double> fBCDdeltaESinglePosY;
  std::vector<G4double> fBCDdeltaESinglePosZ;
  std::vector<G4double> fBCDdeltaESingleStartAngle;
  std::vector<G4double> fBCDdeltaESingleThickness;
  G4double fBCDdeltaESingleDeadLayer;
  G4double fBCDdeltaESingleInnerRadius;
  G4double fBCDdeltaESingleOuterRadius;
  G4double fBCDdeltaESingleRingWidth;
  G4double fBCDdeltaESingleSpanningAngle;
  G4double fBCDdeltaESingleStripWidth;
  int fBCDTransferTo16Strips;
  G4double fBCDdeltaESingleEnergyResolution;
  G4double fBCDdeltaESingleFoilThickness;
  // BCD Erest
  int fUseBCDErest;
  int fNbOfBCDErestSingles;
  std::vector<G4double> fBCDErestSinglePosX;
  std::vector<G4double> fBCDErestSinglePosY;
  std::vector<G4double> fBCDErestSinglePosZ;
  std::vector<G4double> fBCDErestSingleStartAngle;
  std::vector<G4double> fBCDErestSingleThickness;
  G4double fBCDErestSingleDeadLayer;
  G4double fBCDErestSingleInnerRadius;
  G4double fBCDErestSingleOuterRadius;
  G4double fBCDErestSingleSpanningAngle;
  G4double fBCDErestSingleEnergyResolution;

  // FBarrel deltaE
  int fUseFBarrelDeltaE;
  int fNbOfFBarrelDeltaESingles;
  //std::vector<G4double> fFBarrelDeltaESinglePosX;
  //std::vector<G4double> fFBarrelDeltaESinglePosY;
  std::vector<G4double> fFBarrelDeltaESinglePosZ;
  std::vector<G4double> fFBarrelDeltaESingleDistanceToBeam;
  std::vector<G4double> fFBarrelDeltaESingleStartAngle;
  std::vector<G4double> fFBarrelDeltaESingleThickness;
  G4double fFBarrelDeltaESingleDeadLayer;
  G4double fFBarrelDeltaESingleLengthX;
  G4double fFBarrelDeltaESingleLengthY;
  G4double fFBarrelDeltaESingleStripWidth;
  G4double fFBarrelDeltaESingleEnergyResolution;
  G4double fFBarrelDeltaESingleFoilThickness;
  // FBarrel Erest
  int fUseFBarrelErest;
  int fNbOfFBarrelErestSingles;
  //std::vector<G4double> fFBarrelErestSinglePosX;
  //std::vector<G4double> fFBarrelErestSinglePosY;
  std::vector<G4double> fFBarrelErestSinglePosZ;
  std::vector<G4double> fFBarrelErestSingleDistanceToBeam;
  std::vector<G4double> fFBarrelErestSingleStartAngle;
  std::vector<G4double> fFBarrelErestSingleThickness;
  G4double fFBarrelErestSingleDeadLayer;
  G4double fFBarrelErestSingleLengthX;
  G4double fFBarrelErestSingleLengthY;
  G4double fFBarrelErestSingleEnergyResolution;
  // Second FBarrel deltaE
  int fUseSecondFBarrelDeltaE;
  int fNbOfSecondFBarrelDeltaESingles;
  std::vector<G4double> fSecondFBarrelDeltaESinglePosZ;
  std::vector<G4double> fSecondFBarrelDeltaESingleDistanceToBeam;
  std::vector<G4double> fSecondFBarrelDeltaESingleStartAngle;
  std::vector<G4double> fSecondFBarrelDeltaESingleThickness;
  G4double fSecondFBarrelDeltaESingleDeadLayer;
  G4double fSecondFBarrelDeltaESingleLengthX;
  G4double fSecondFBarrelDeltaESingleLengthY;
  G4double fSecondFBarrelDeltaESingleStripWidth;
  G4double fSecondFBarrelDeltaESingleEnergyResolution;
  G4double fSecondFBarrelDeltaESingleFoilThickness;

  // MBarrel deltaE
  int fUseMBarrelDeltaE;
  int fNbOfMBarrelDeltaESingles;
  //std::vector<G4double> fMBarrelDeltaESinglePosX;
  //std::vector<G4double> fMBarrelDeltaESinglePosY;
  std::vector<G4double> fMBarrelDeltaESinglePosZ;
  std::vector<G4double> fMBarrelDeltaESingleDistanceToBeam;
  std::vector<G4double> fMBarrelDeltaESingleStartAngle;
  std::vector<G4double> fMBarrelDeltaESingleThickness;
  G4double fMBarrelDeltaESingleDeadLayer;
  G4double fMBarrelDeltaESingleLengthX;
  G4double fMBarrelDeltaESingleLengthY;
  G4double fMBarrelDeltaESingleStripWidth;
  G4double fMBarrelDeltaESingleEnergyResolution;
  G4double fMBarrelDeltaESingleFoilThickness;
  // MBarrel Erest
  int fUseMBarrelErest;
  int fNbOfMBarrelErestSingles;
  //std::vector<G4double> fMBarrelErestSinglePosX;
  //std::vector<G4double> fMBarrelErestSinglePosY;
  std::vector<G4double> fMBarrelErestSinglePosZ;
  std::vector<G4double> fMBarrelErestSingleDistanceToBeam;
  std::vector<G4double> fMBarrelErestSingleStartAngle;
  std::vector<G4double> fMBarrelErestSingleThickness;
  G4double fMBarrelErestSingleDeadLayer;
  G4double fMBarrelErestSingleLengthX;
  G4double fMBarrelErestSingleLengthY;
  G4double fMBarrelErestSingleEnergyResolution;

  // BBarrel deltaE
  int fUseBBarrelDeltaE;
  int fNbOfBBarrelDeltaESingles;
  //std::vector<G4double> fBBarrelDeltaESinglePosX;
  //std::vector<G4double> fBBarrelDeltaESinglePosY;
  std::vector<G4double> fBBarrelDeltaESinglePosZ;
  std::vector<G4double> fBBarrelDeltaESingleDistanceToBeam;
  std::vector<G4double> fBBarrelDeltaESingleStartAngle;
  std::vector<G4double> fBBarrelDeltaESingleThickness;
  G4double fBBarrelDeltaESingleDeadLayer;
  G4double fBBarrelDeltaESingleLengthX;
  G4double fBBarrelDeltaESingleLengthY;
  G4double fBBarrelDeltaESingleStripWidth;
  G4double fBBarrelDeltaESingleEnergyResolution;
  G4double fBBarrelDeltaESingleFoilThickness;
  // BBarrel Erest
  int fUseBBarrelErest;
  int fNbOfBBarrelErestSingles;
  //std::vector<G4double> fBBarrelErestSinglePosX;
  //std::vector<G4double> fBBarrelErestSinglePosY;
  std::vector<G4double> fBBarrelErestSinglePosZ;
  std::vector<G4double> fBBarrelErestSingleDistanceToBeam;
  std::vector<G4double> fBBarrelErestSingleStartAngle;
  std::vector<G4double> fBBarrelErestSingleThickness;
  G4double fBBarrelErestSingleDeadLayer;
  G4double fBBarrelErestSingleLengthX;
  G4double fBBarrelErestSingleLengthY;
  G4double fBBarrelErestSingleEnergyResolution;
  // Second BBarrel deltaE
  int fUseSecondBBarrelDeltaE;
  int fNbOfSecondBBarrelDeltaESingles;
  std::vector<G4double> fSecondBBarrelDeltaESinglePosZ;
  std::vector<G4double> fSecondBBarrelDeltaESingleDistanceToBeam;
  std::vector<G4double> fSecondBBarrelDeltaESingleStartAngle;
  std::vector<G4double> fSecondBBarrelDeltaESingleThickness;
  G4double fSecondBBarrelDeltaESingleDeadLayer;
  G4double fSecondBBarrelDeltaESingleLengthX;
  G4double fSecondBBarrelDeltaESingleLengthY;
  G4double fSecondBBarrelDeltaESingleStripWidth;
  G4double fSecondBBarrelDeltaESingleEnergyResolution;
  G4double fSecondBBarrelDeltaESingleFoilThickness;

  // Forward Trapezoid deltaE
  int fUseFTrapezoidDeltaE;
  int fNbOfFTrapezoidDeltaESingles;
  std::vector<G4double> fFTrapezoidDeltaESinglePosZ;
  G4double fFTrapezoidDeltaESingleInnerRadius;
  G4double fFTrapezoidDeltaESingleOuterRadius;
  G4double fFTrapezoidDeltaESingleDeltaZ;
  std::vector<G4double> fFTrapezoidDeltaESingleThickness;
  std::vector<G4double> fFTrapezoidDeltaESingleStartAngle;
  int fFTrapezoidDeltaESingleNbOfRings;
  int fFTrapezoidDeltaESingleNbOfStrips;
  G4double fFTrapezoidDeltaESingleEnergyResolution;
  G4double fFTrapezoidDeltaESingleFoilThickness;
  // Forward Trapezoid Erest
  int fUseFTrapezoidErest;
  int fNbOfFTrapezoidErestSingles;
  std::vector<G4double> fFTrapezoidErestSinglePosZ;
  G4double fFTrapezoidErestSingleInnerRadius;
  G4double fFTrapezoidErestSingleOuterRadius;
  G4double fFTrapezoidErestSingleDeltaZ;
  std::vector<G4double> fFTrapezoidErestSingleThickness;
  std::vector<G4double> fFTrapezoidErestSingleStartAngle;
  G4double fFTrapezoidErestSingleEnergyResolution;

  // Backward Trapezoid deltaE
  int fUseBTrapezoidDeltaE;
  int fNbOfBTrapezoidDeltaESingles;
  std::vector<G4double> fBTrapezoidDeltaESinglePosZ;
  G4double fBTrapezoidDeltaESingleInnerRadius;
  G4double fBTrapezoidDeltaESingleOuterRadius;
  G4double fBTrapezoidDeltaESingleDeltaZ;
  std::vector<G4double> fBTrapezoidDeltaESingleThickness;
  std::vector<G4double> fBTrapezoidDeltaESingleStartAngle;
  int fBTrapezoidDeltaESingleNbOfRings;
  int fBTrapezoidDeltaESingleNbOfStrips;
  G4double fBTrapezoidDeltaESingleEnergyResolution;
  G4double fBTrapezoidDeltaESingleFoilThickness;
  // Backward Trapezoid Erest
  int fUseBTrapezoidErest;
  int fNbOfBTrapezoidErestSingles;
  std::vector<G4double> fBTrapezoidErestSinglePosZ;
  G4double fBTrapezoidErestSingleInnerRadius;
  G4double fBTrapezoidErestSingleOuterRadius;
  G4double fBTrapezoidErestSingleDeltaZ;
  std::vector<G4double> fBTrapezoidErestSingleThickness;
  std::vector<G4double> fBTrapezoidErestSingleStartAngle;
  G4double fBTrapezoidErestSingleEnergyResolution;

  // Miniball
  int fNbOfMiniballClusters;
  std::vector<G4String> fMiniballClusterNames;
  std::vector<int> fMiniballClusterTypes;
  std::vector<G4double> fMiniballClusterRho, fMiniballClusterTheta, fMiniballClusterPhi, fMiniballClusterSpin;
  G4double fMiniballEnergyResolutionCore;
  G4double fMiniballEnergyResolutionSegment;
};

#endif /* TREXSETTINGS_HH_ */
