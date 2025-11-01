#ifndef MYSENSITIVEDETECTOR_HH
#define MYSENSITIVEDETECTOR_HH

#include <G4VSensitiveDetector.hh>
#include <G4RunManager.hh>
#include <G4Electron.hh>

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

#include <G4RootAnalysisManager.hh>
using G4AnalysisManager = G4RootAnalysisManager;

#include "config.hh"

class MySensitiveDetector : public G4VSensitiveDetector{

public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();

private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif