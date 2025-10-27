#include <iostream>

#include <G4RunManager.hh>
#include <G4MTRunManager.hh>
#include <G4UImanager.hh>
#include <G4VisManager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>

#include <G4GeometryManager.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4SolidStore.hh>

#include "MyPhysicsList.hh"
#include "MyDetectorConstruction.hh"
#include "MyActionInitialization.hh"

int main(int argc, char** argv){

    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager;
    #else
        G4RunManager *runManager = new G4RunManager;
    #endif

    // Physics List
    runManager->SetUserInitialization(new MyPhysicsList());

    // Detector Construction
    runManager->SetUserInitialization(new MyDetectorConstruction());

    // Action Initialization
    runManager->SetUserInitialization(new MyActionInitialization());

    G4UIExecutive *ui = 0;

    if(argc == 1){
        ui = new G4UIExecutive(argc, argv);
    }

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if(ui){
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    } else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    // LIMPEZA ANTES DE DELETAR (resolve o erro de segmentação)
    delete ui;
    delete visManager;
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
    delete runManager;

    return 0;
}
