#include "MySensitiveDetector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name){}

MySensitiveDetector::~MySensitiveDetector(){}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist){

    G4Track *track = aStep->GetTrack();

    G4ParticleDefinition* particle = track->GetDefinition();
    
    // Verificar se é elétron
    if(particle != G4Electron::ElectronDefinition()) {
        return false;  // Não é elétron, ignora
    }

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector[0]);
    man->FillNtupleDColumn(2, posDetector[1]);
    man->FillNtupleDColumn(3, posDetector[2]);
    man->AddNtupleRow(0);

    return true;
}