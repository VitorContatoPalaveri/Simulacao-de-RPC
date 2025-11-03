#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction(){}

MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume *MyDetectorConstruction::Construct(){
    
    G4bool checkOverlaps = true;

    G4NistManager *nist  = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material* insulator = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
	G4Material* graphite = nist->FindOrBuildMaterial("G4_GRAPHITE");
	G4Material* HPLmat = nist->FindOrBuildMaterial("G4_BAKELITE");
	G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");
	G4Material* CO2 = nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE");

    // === CRIAÇÃO DA MISTURA GASOSA DA RPC ===

    G4double C2H2F4_fraction = config::C2H2F4_fraction;
    G4double isobutane_fraction = config::isobutane_fraction;
    G4double SF6_fraction = config::SF6_fraction;
    G4double CO2_fraction = config::CO2_fraction;
    
    // Definir elementos
    G4Element *elC = nist->FindOrBuildElement("C");
    G4Element *elH = nist->FindOrBuildElement("H");
    G4Element *elF = nist->FindOrBuildElement("F");
    G4Element *elS = nist->FindOrBuildElement("S");
    
    // Criar os gases componentes

    G4double pressure = config::pressure;
    G4double temp = config::temp;
    
    // C2H2F4 (Tetrafluoroetano, HFC-134a)
    G4Material *C2H2F4 = new G4Material("C2H2F4", 4.25*kg/m3, 3, kStateGas, temp, pressure);
    C2H2F4->AddElement(elC, 2);
    C2H2F4->AddElement(elH, 2);
    C2H2F4->AddElement(elF, 4);
    
    // i-C4H10 (Isobutano)
    G4Material *isobutane = new G4Material("isobutane", 2.51*kg/m3, 2, kStateGas, temp, pressure);
    isobutane->AddElement(elC, 4);
    isobutane->AddElement(elH, 10);
    
    // SF6 (Hexafluoreto de enxofre)
    G4Material *SF6 = new G4Material("SF6", 6.17*kg/m3, 2, kStateGas, temp, pressure);
    SF6->AddElement(elS, 1);
    SF6->AddElement(elF, 6);
    
    // Criar a mistura (RPC gas mixture)
    G4double density_mixture = C2H2F4_fraction*4.25 + isobutane_fraction*2.51 + SF6_fraction*6.17 + CO2_fraction*1.84; // densidade ponderada em kg/m3
    G4Material *rpcGas = new G4Material("RPCGas", density_mixture*kg/m3, 4, kStateGas, 293.15*kelvin, 1*atmosphere);
    rpcGas->AddMaterial(C2H2F4, C2H2F4_fraction);
    rpcGas->AddMaterial(isobutane, isobutane_fraction);
    rpcGas->AddMaterial(SF6, SF6_fraction);
    rpcGas->AddMaterial(CO2, CO2_fraction);
    
    // === FIM DA CRIAÇÃO DA MISTURA ===

	// World

    G4double rWorld = config::lengthDet * std::sqrt(2);

    G4Sphere *solidWorld = new G4Sphere("solidWorld", 0.0, rWorld, 0.0, 360. * deg, 0.0, 180. * deg);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());  // Makes invisible (Duran Duran)

	// Gas Chamber

    G4double lengthDet = config::lengthDet;
    G4double widthDet = config::widthDet;

    G4Box *solidDetector = new G4Box("solidDetector", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthDet);
    logicDetector = new G4LogicalVolume(solidDetector, rpcGas, "logicDetector");
    physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicDetector, "physDetector", logicWorld, false, checkOverlaps);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(0., 0., 1., 0.1));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

	// HPL (brakelite)

	G4double widthHPL = config::widthHPL;
    G4double zHPLpos = widthDet/2 + widthHPL/2;

	G4Box *solidHPL = new G4Box("solidHPL", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthHPL);
    logicHPL = new G4LogicalVolume(solidHPL, HPLmat, "logicHPL");
    physHPL = new G4PVPlacement(0, G4ThreeVector(0., 0., -zHPLpos), logicHPL, "physHPL", logicWorld, false, checkOverlaps);
    physHPL = new G4PVPlacement(0, G4ThreeVector(0., 0., zHPLpos), logicHPL, "physHPL", logicWorld, false, checkOverlaps);

    G4VisAttributes *HPLvisAtt = new G4VisAttributes(G4Color(1., .75, .18, 1.));
    HPLvisAtt->SetForceSolid(true);
    logicHPL->SetVisAttributes(HPLvisAtt);

	// Graphite

	G4double widthGraphite = config::widthGraphite;
    G4double zGraphitePos = widthDet/2 + widthHPL + widthGraphite/2;

	G4Box *solidGraphite = new G4Box("solidGraphite", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthGraphite);
    logicGraphite = new G4LogicalVolume(solidGraphite, graphite, "logicGraphite");
    physGraphite = new G4PVPlacement(0, G4ThreeVector(0., 0., -zGraphitePos), logicGraphite, "physGraphite", logicWorld, false, checkOverlaps);
    physGraphite = new G4PVPlacement(0, G4ThreeVector(0., 0., zGraphitePos), logicGraphite, "physGraphite", logicWorld, false, checkOverlaps);

    G4VisAttributes *graVisAtt = new G4VisAttributes(G4Color(.22, .28, .31, 1.));
    graVisAtt->SetForceSolid(true);
    logicGraphite->SetVisAttributes(graVisAtt);

	// Insulator (polyehylene)

	G4double widthIns = config::widthIns;
    G4double zInsPos = widthDet/2 + widthHPL + widthGraphite + widthIns/2;

	G4Box *solidInsulator = new G4Box("solidInsulator", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthIns);
    logicInsulator = new G4LogicalVolume(solidInsulator, insulator, "logicInsulator");
    physInsulator = new G4PVPlacement(0, G4ThreeVector(0., 0., -zInsPos), logicInsulator, "physInsulator", logicWorld, false, checkOverlaps);
    physInsulator = new G4PVPlacement(0, G4ThreeVector(0., 0., zInsPos), logicInsulator, "physInsulator", logicWorld, false, checkOverlaps);

    G4VisAttributes *insVisAtt = new G4VisAttributes(G4Color(.6, .6, .6, 1.));
    insVisAtt->SetForceSolid(true);
    logicInsulator->SetVisAttributes(insVisAtt);

    // Readout strip (copper)

    G4double widthCopper = config::widthCopper;
    G4double zCopperPos = widthDet/2 + widthHPL + widthGraphite + widthIns + widthCopper/2;

    G4Box *solidCopper = new G4Box("solidCopper", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthCopper);
    logicCopper = new G4LogicalVolume(solidCopper, copper, "logicCopper");
    physCopper = new G4PVPlacement(0, G4ThreeVector(0., 0., zCopperPos), logicCopper, "physCopper", logicWorld, false, checkOverlaps);

    G4VisAttributes *copVisAtt = new G4VisAttributes(G4Color(.9, .29, .01, 1.));
    copVisAtt->SetForceSolid(true);
    logicCopper->SetVisAttributes(copVisAtt);

    // === CORTES DE PRODUÇÃO ESPECÍFICOS PARA O GÁS ===
    // G4Region* gasRegion = new G4Region("GasRegion");
    // gasRegion->AddRootLogicalVolume(logicDetector);
    // G4ProductionCuts* gasCuts = new G4ProductionCuts();
    // gasCuts->SetProductionCut(0.01 * mm);
    // gasRegion->SetProductionCuts(gasCuts);

    // G4ProductionCuts* fineCuts = new G4ProductionCuts();
    // fineCuts->SetProductionCut(0.001 * mm);

    // G4Region* detectorRegion = new G4Region("DetectorRegion");
    // detectorRegion->AddRootLogicalVolume(logicHPL);
    // detectorRegion->AddRootLogicalVolume(logicGraphite);
    // detectorRegion->AddRootLogicalVolume(logicInsulator);
    // detectorRegion->SetProductionCuts(fineCuts);

    // logicHPL->SetUserLimits(new G4UserLimits(0.1 * widthHPL));
    // logicGraphite->SetUserLimits(new G4UserLimits(0.1 * widthGraphite));
    // logicInsulator->SetUserLimits(new G4UserLimits(0.1 * widthIns));

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField(){

    ConstructElectricField();

    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
}

/**
 * Extracted from https://github.com/allanjales/RPCSimulation.
 */
void MyDetectorConstruction::ConstructElectricField(){

    // Parâmetros do campo
    G4double voltage = config::voltage;
    G4double gap = config::widthDet;
    G4double electricFieldStrength = voltage / gap;

	// Set local eletric field
	fElectricField = new G4UniformElectricField(G4ThreeVector(0., 0., -electricFieldStrength));
	fFieldManager = new G4FieldManager();
	fFieldManager->SetDetectorField(fElectricField);
	CreateChordFinder(fFieldManager, fElectricField);

	// Set which parts will have eletric field
	logicDetector->SetFieldManager(fFieldManager, true);

    // Ajustar precisão
    fFieldManager->SetDeltaOneStep(0.01 * mm);
    fFieldManager->SetDeltaIntersection(0.001 * mm);
    
    G4cout << "Campo elétrico: " << electricFieldStrength/(kilovolt/mm) << " kV/mm" << G4endl;
    G4cout << "Gap total: " << gap/mm << " mm" << G4endl;
}

/**
 * Extracted from https://github.com/allanjales/RPCSimulation.
 */
void MyDetectorConstruction::CreateChordFinder(G4FieldManager* fFieldManager, G4ElectricField* fElectricField){

	fEquation = new G4EqMagElectricField(fElectricField);

	fStepper = new G4ClassicalRK4(fEquation, 8);
	G4cout << "G4ClassicalRK4 (default) is called" << G4endl;

	G4double minStep  = 0.02 * um;
	G4cout << "The minimal step in integral is equal to " << G4BestUnit(minStep, "Length") << G4endl;

	fIntDriver = new G4MagInt_Driver(minStep, fStepper, fStepper->GetNumberOfVariables());
	fChordFinder = new G4ChordFinder(fIntDriver);
	fChordFinder->SetDeltaChord(minStep);
	fFieldManager->SetChordFinder(fChordFinder);
}