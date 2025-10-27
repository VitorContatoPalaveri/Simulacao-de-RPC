#include "MyRunAction.hh"

MyRunAction::MyRunAction(){}

MyRunAction::~MyRunAction(){}

void MyRunAction::BeginOfRunAction(const G4Run*){

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->OpenFile("output.root");

    // OBS: Para abrir, escrever no terminal
    //      root output.root
    // No terminal do root, escrever
    //      new TBrowser
    // para visualizar os dados e
    //      Hits->Draw("fX:fY", "", "colz")
    // para plotar.

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*){

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile("output.root");
}