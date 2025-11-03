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

    // Energia depositada por ionização (em MeV)
    G4double totalE = aStep->GetTotalEnergyDeposit();
    G4double nonIonE = aStep->GetNonIonizingEnergyDeposit();
    G4double ionizingE = totalE - nonIonE;

    G4int nElectrons = static_cast<G4int>(ionizingE / config::Wvalue);

    if(nElectrons <= 0){
        return false;
    }

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4ThreeVector posElectron = preStepPoint->GetPosition();
    G4double fGlobalTime = preStepPoint->GetGlobalTime();

    G4double xElectron = posElectron[0];
    G4double yElectron = posElectron[1];
    G4double zElectron = posElectron[2];

    G4double zDistance = (0.5 * config::widthDet) - zElectron;

    // Cálculo de avalanche (Townsend)

    G4double avalancheGain = exp(config::alpha * zDistance);

    // Cálculo de sinal induzido (Ramo)

    G4double iFraction = zDistance / config::widthDet;

    // Carga total induzida

    G4double nElectrons_ind = nElectrons * avalancheGain * iFraction;

    // Simulação de precisão do detector
    
    G4int nX = config::nCols;
    G4int nY = config::nRows;

    G4double maxX = config::lengthDet;
    G4double maxY = config::lengthDet;

    G4int channelX = static_cast<G4int>((0.5 * maxX - xElectron) * nX / maxX);
    G4int channelY = static_cast<G4int>((0.5 * maxY + yElectron) * nY / maxY);

    G4double detX = (channelX + 0.5) * maxX / nX;
    G4double detY = (channelY + 0.5) * maxY / nY;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posElectron[0]);
    man->FillNtupleDColumn(2, posElectron[1]);
    man->FillNtupleDColumn(3, posElectron[2]);
    man->FillNtupleDColumn(4, detX);
    man->FillNtupleDColumn(5, detY);
    man->FillNtupleDColumn(6, nElectrons);
    man->FillNtupleDColumn(7, nElectrons_ind);
    man->FillNtupleDColumn(8, fGlobalTime);
    man->AddNtupleRow(0);

    return true;
}