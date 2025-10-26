#include "MyPrimaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator(){

    fParticleGun = new G4ParticleGun(1);

    // Particle position
    G4double x = 0. * mm;
    G4double y = 0. * mm;
    G4double z = -3. * mm;

    G4ThreeVector pos(x, y, z);

    // Particle direction
    G4double px = 0.;
    G4double py = 0.;
    G4double pz = 1.;

    G4ThreeVector mom(px, py, pz);

    // Particle type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindAntiParticle("mu-");

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentum(mom);
    fParticleGun->SetParticleEnergy(1. * GeV);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator(){

    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){

    // Create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}