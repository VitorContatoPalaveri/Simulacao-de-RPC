#ifndef MYDETECTORCONSTRUCTION_HH
#define MYDETECTORCONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>

#include <G4Box.hh>
#include <G4Sphere.hh>

#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Material.hh>

#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

#include <G4VisAttributes.hh>
#include <G4Color.hh>
#include <G4SDManager.hh>

#include <G4UniformElectricField.hh>
#include <G4FieldManager.hh>
#include <G4EqMagElectricField.hh>
#include <G4MagIntegratorStepper.hh>
#include <G4ChordFinder.hh>
#include <G4ClassicalRK4.hh>
#include <G4MagIntegratorDriver.hh>
#include <G4TransportationManager.hh>

#include <G4ProductionCuts.hh>
#include <G4UserLimits.hh>

#include "MySensitiveDetector.hh"
#include "config.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction{

public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

private:
	G4LogicalVolume *logicWorld;
	G4VPhysicalVolume *physWorld;

	G4LogicalVolume *logicDetector;
	G4VPhysicalVolume *physDetector;

	G4LogicalVolume *logicHPL;
	G4VPhysicalVolume *physHPL;

	G4LogicalVolume *logicGraphite;
	G4VPhysicalVolume *physGraphite;

    G4LogicalVolume *logicInsulator;
	G4VPhysicalVolume *physInsulator;

	G4LogicalVolume *logicCopper;
	G4VPhysicalVolume *physCopper;

    virtual void ConstructSDandField();

	// Campo elétrico
    G4UniformElectricField* fElectricField;
    G4FieldManager* fFieldManager;
    G4EqMagElectricField* fEquation;
    G4MagIntegratorStepper* fStepper;
	G4MagInt_Driver* fIntDriver;
    G4ChordFinder* fChordFinder;

	virtual void ConstructElectricField();
	virtual void CreateChordFinder(G4FieldManager*, G4ElectricField*);
};

#endif