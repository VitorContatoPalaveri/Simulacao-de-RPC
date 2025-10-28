#include "MyPrimaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator(){

    fParticleGun = new G4ParticleGun(1);

    // Particle position
    G4double x = 0. * mm;
    G4double z = -(config::widthDet/2 + config::widthHPL + config::widthGraphite + config::widthIns + config::widthCopper + 2 * mm);
    G4double y = z * std::tan(config::theta);

    G4ThreeVector pos(x, y, z);

    // Particle direction
    G4double px = 0.;
    G4double py = std::sin(config::theta);
    G4double pz = std::cos(config::theta);

    G4ThreeVector mom(px, py, pz);

    // Particle type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle(config::particleName);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(config::particleEnergy);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator(){

    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){

    // Create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}