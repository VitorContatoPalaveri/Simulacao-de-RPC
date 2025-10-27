#include "MyPhysicsList.hh"

MyPhysicsList::MyPhysicsList() {
    //Inicializa os módulos de física
    emPhysics = new G4EmStandardPhysics();             //Lista de física de interações eletromagnética padrão
    hadronPhysics = new G4HadronPhysicsQGSP_BERT();    //Lista de física hadronica
    decayPhysics = new G4DecayPhysics();               //Lista de física de decaimento
    ionElasticPhysics = new G4IonElasticPhysics();     //Lista de física para simulação de interações de íons

    //Registra os módulos de física
    RegisterPhysics(emPhysics);
    RegisterPhysics(hadronPhysics);
    RegisterPhysics(decayPhysics);
    RegisterPhysics(ionElasticPhysics);
}

MyPhysicsList::~MyPhysicsList() {}
