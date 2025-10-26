#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction(){}

MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume *MyDetectorConstruction::Construct(){
    
    G4bool checkOverlaps = true;

    G4NistManager *nist  = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material* insulatorMat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
	G4Material* graphiteMat = nist->FindOrBuildMaterial("G4_GRAPHITE");
	G4Material* HPLmat = nist->FindOrBuildMaterial("G4_BAKELITE");
	G4Material* copperMat = nist->FindOrBuildMaterial("G4_Cu");

    // === CRIAÇÃO DA MISTURA GASOSA DA RPC ===
    
    // Definir elementos
    G4Element *elC = nist->FindOrBuildElement("C");
    G4Element *elH = nist->FindOrBuildElement("H");
    G4Element *elF = nist->FindOrBuildElement("F");
    G4Element *elS = nist->FindOrBuildElement("S");
    
    // Criar os gases componentes
    
    // C2H2F4 (Tetrafluoroetano, HFC-134a)
    G4Material *C2H2F4 = new G4Material("C2H2F4", 4.25*kg/m3, 3, kStateGas, 293.15*kelvin, 1*atmosphere);
    C2H2F4->AddElement(elC, 2);
    C2H2F4->AddElement(elH, 2);
    C2H2F4->AddElement(elF, 4);
    
    // i-C4H10 (Isobutano)
    G4Material *isobutane = new G4Material("isobutane", 2.51*kg/m3, 2, kStateGas, 293.15*kelvin, 1*atmosphere);
    isobutane->AddElement(elC, 4);
    isobutane->AddElement(elH, 10);
    
    // SF6 (Hexafluoreto de enxofre)
    G4Material *SF6 = new G4Material("SF6", 6.17*kg/m3, 2, kStateGas, 293.15*kelvin, 1*atmosphere);
    SF6->AddElement(elS, 1);
    SF6->AddElement(elF, 6);
    
    // Criar a mistura (RPC gas mixture)
    G4double density_mixture = 0.952*4.25 + 0.045*2.51 + 0.003*6.17; // densidade ponderada em kg/m3
    G4Material *rpcGas = new G4Material("RPCGas", density_mixture*kg/m3, 3, kStateGas, 293.15*kelvin, 1*atmosphere);
    rpcGas->AddMaterial(C2H2F4, 95.2*perCent);
    rpcGas->AddMaterial(isobutane, 4.5*perCent);
    rpcGas->AddMaterial(SF6, 0.3*perCent);
    
    // === FIM DA CRIAÇÃO DA MISTURA ===

	// World

    G4double rWorld = 5. * cm;

    G4Sphere *solidWorld = new G4Sphere("solidWorld", 0.0, rWorld, 0.0, 360. * deg, 0.0, 180. * deg);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

	// Gas Chamber

    G4double lengthDet = 5. * cm;
    G4double widthDet = 2. * mm;

    G4Box *solidDetector = new G4Box("solidDetector", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthDet);
    logicDetector = new G4LogicalVolume(solidDetector, rpcGas, "logicDetector");
    physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicDetector, "physDetector", logicWorld, false, checkOverlaps);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(0., 0., 1., 0.1));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

	// HPL (brakelite)

	G4double widthHPL = 1. * mm;
    G4double zHPLpos = widthDet/2 + widthHPL/2;

	G4Box *solidHPL = new G4Box("solidHPL", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthHPL);
    logicHPL = new G4LogicalVolume(solidHPL, HPLmat, "logicHPL");
    physHPL = new G4PVPlacement(0, G4ThreeVector(0., 0., -zHPLpos), logicHPL, "physHPL", logicWorld, false, checkOverlaps);
    physHPL = new G4PVPlacement(0, G4ThreeVector(0., 0., zHPLpos), logicHPL, "physHPL", logicWorld, false, checkOverlaps);

    G4VisAttributes *HPLvisAtt = new G4VisAttributes(G4Color(1., .75, .18, 1.));
    HPLvisAtt->SetForceSolid(true);
    logicHPL->SetVisAttributes(HPLvisAtt);

	// Graphite

	G4double widthGraphite = .1 * mm;
    G4double zGraphitePos = widthDet/2 + widthHPL + widthGraphite/2;

	G4Box *solidGraphite = new G4Box("solidGraphite", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthGraphite);
    logicGraphite = new G4LogicalVolume(solidGraphite, graphiteMat, "logicGraphite");
    physGraphite = new G4PVPlacement(0, G4ThreeVector(0., 0., -zGraphitePos), logicGraphite, "physGraphite", logicWorld, false, checkOverlaps);
    physGraphite = new G4PVPlacement(0, G4ThreeVector(0., 0., zGraphitePos), logicGraphite, "physGraphite", logicWorld, false, checkOverlaps);

    G4VisAttributes *graVisAtt = new G4VisAttributes(G4Color(.22, .28, .31, 1.));
    graVisAtt->SetForceSolid(true);
    logicGraphite->SetVisAttributes(graVisAtt);

	// Insulator

	G4double widthIns = .1 * mm;
    G4double zInsPos = widthDet/2 + widthHPL + widthGraphite + widthIns/2;

	G4Box *solidInsulator = new G4Box("solidInsulator", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthIns);
    logicInsulator = new G4LogicalVolume(solidInsulator, insulatorMat, "logicInsulator");
    physInsulator = new G4PVPlacement(0, G4ThreeVector(0., 0., -zInsPos), logicInsulator, "physInsulator", logicWorld, false, checkOverlaps);
    physInsulator = new G4PVPlacement(0, G4ThreeVector(0., 0., zInsPos), logicInsulator, "physInsulator", logicWorld, false, checkOverlaps);

    G4VisAttributes *insVisAtt = new G4VisAttributes(G4Color(.6, .6, .6, 1.));
    insVisAtt->SetForceSolid(true);
    logicInsulator->SetVisAttributes(insVisAtt);

	// Readout strip (copper)

	G4double widthCopper = .02 * mm;
    G4double zCopperPos = widthDet/2 + widthHPL + widthGraphite + widthIns + widthCopper/2;

	G4Box *solidCopper = new G4Box("solidCopper", 0.5 * lengthDet, 0.5 * lengthDet, 0.5 * widthCopper);
    logicCopper = new G4LogicalVolume(solidCopper, copperMat, "logicCopper");
    physCopper = new G4PVPlacement(0, G4ThreeVector(0., 0., zCopperPos), logicCopper, "physCopper", logicWorld, false, checkOverlaps);

    G4VisAttributes *copVisAtt = new G4VisAttributes(G4Color(.9, .29, .01, 1.));
    copVisAtt->SetForceSolid(true);
    logicCopper->SetVisAttributes(copVisAtt);

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField(){

    // MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    // logicDetector->SetSensitiveDetector(sensDet);
    // G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}