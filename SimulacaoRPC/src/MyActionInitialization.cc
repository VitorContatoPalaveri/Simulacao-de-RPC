#include "MyActionInitialization.hh"

MyActionInitialization::MyActionInitialization(){}

MyActionInitialization::~MyActionInitialization(){}

void MyActionInitialization::BuildForMaster() const{}

void MyActionInitialization::Build() const{

    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);
}