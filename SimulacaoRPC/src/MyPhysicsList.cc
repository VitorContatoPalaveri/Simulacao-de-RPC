#include "MyPhysicsList.hh"

MyPhysicsList::MyPhysicsList() {
    //Inicializa os módulos de física
    // emPhysics = new G4EmStandardPhysics();             //Lista de física de interações eletromagnética padrão
    emPhysics = new G4EmStandardPhysics_option4();     //Lista de física de interações eletromagnética padrão otimizada para baixas energias
    hadronPhysics = new G4HadronPhysicsQGSP_BERT();    //Lista de física hadronica
    decayPhysics = new G4DecayPhysics();               //Lista de física de decaimento
    ionElasticPhysics = new G4IonElasticPhysics();     //Lista de física para simulação de interações de íons

    //Registra os módulos de física
    RegisterPhysics(emPhysics);
    RegisterPhysics(hadronPhysics);
    RegisterPhysics(decayPhysics);
    RegisterPhysics(ionElasticPhysics);

    // Diminuir threshold de produção de elétrons delta
    SetDefaultCutValue(1. * um);  // Corte padrão
    
    // Habilitar parâmetros EM para melhor ionização
    G4EmParameters* emParams = G4EmParameters::Instance();
    
    // CRÍTICO: Habilitar produção de elétrons de baixa energia
    emParams->SetFluo(true);                    // Fluorescência
    emParams->SetAuger(true);                   // Elétrons Auger
    emParams->SetPixe(true);                    // PIXE
    emParams->SetDeexcitationIgnoreCut(true);   // Ignorar cortes para de-excitação
    
    // Diminuir threshold de produção de secundários
    emParams->SetLowestElectronEnergy(1. * eV);   // Energia mínima de elétrons
    emParams->SetLowestMuHadEnergy(1. * eV);      // Energia mínima de partículas
    
    // Melhorar precisão de ionização
    emParams->SetStepFunction(0.1, 0.001 * mm);  // Passos muito pequenos
    emParams->SetMscRangeFactor(0.01);

    // Linear loss limit (importante para elétrons lentos)
    emParams->SetLinearLossLimit(0.01);
    
    // Habilitar perda de energia sub-threshold
    emParams->SetApplyCuts(false);  // Não aplicar cortes rigidamente

    G4cout << "=== PhysicsList configurada para elétrons de baixa energia ===" << G4endl;
}

MyPhysicsList::~MyPhysicsList() {}
