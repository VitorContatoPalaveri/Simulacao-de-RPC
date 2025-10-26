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

#include "MySensitiveDetector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction{

public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

private:
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
};

#endif