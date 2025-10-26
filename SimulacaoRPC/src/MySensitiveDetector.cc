#include "MySensitiveDetector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name){

    fTotalEnergyDeposited = 0.;
}

MySensitiveDetector::~MySensitiveDetector(){}

void MySensitiveDetector::Initialize(G4HCofThisEvent *){

    fTotalEnergyDeposited = 0.;
}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent *){

    G4cout << "Deposited energy: " << fTotalEnergyDeposited << G4endl;
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *){

    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();

    if(fEnergyDeposited > 0){
        fTotalEnergyDeposited += fEnergyDeposited;
    }

    return true;
}