#ifndef MYSENSITIVEDETECTOR_HH
#define MYSENSITIVEDETECTOR_HH

#include <G4VSensitiveDetector.hh>

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

class MySensitiveDetector : public G4VSensitiveDetector{

public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();

private:
    G4double fTotalEnergyDeposited;

    virtual void Initialize(G4HCofThisEvent *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;

    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif