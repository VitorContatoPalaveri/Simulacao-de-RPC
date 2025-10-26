#include "MyPhysicsList.hh"

MyPhysicsList::MyPhysicsList(){

    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics());
}

MyPhysicsList::~MyPhysicsList(){}