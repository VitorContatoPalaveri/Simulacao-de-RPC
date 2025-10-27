#ifndef MYPHYSICSLIST_HH
#define MYPHYSICSLIST_HH

#include <G4VModularPhysicsList.hh>
#include <G4EmStandardPhysics.hh>           //Lista de física de interações eletromagnética padrão
#include <G4HadronPhysicsQGSP_BERT.hh>      //Lista de física hadronica
#include <G4DecayPhysics.hh>               //Lista de física de decaimento
#include <G4IonElasticPhysics.hh>          //Lista de física para simulação de interações de íons

class MyPhysicsList : public G4VModularPhysicsList {

public:
    MyPhysicsList();
    ~MyPhysicsList();

private:
    //Módulos das listas
    G4VPhysicsConstructor* emPhysics;       
    G4VPhysicsConstructor* hadronPhysics;   
    G4VPhysicsConstructor* decayPhysics;    
    G4VPhysicsConstructor* ionElasticPhysics; 
};

#endif
