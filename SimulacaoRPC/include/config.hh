#ifndef CONFIG_HH
#define CONFIG_HH

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

namespace config{

    // GEOMETRY DIMENTIONS

    // Gas Chamber
    const G4double lengthDet = 5. * cm;
    const G4double widthDet = 2. * mm;

    // HPL (brakelite)
    const G4double widthHPL = 2. * mm;

    // Graphite
	const G4double widthGraphite = .3 * mm;

    // Insulator (polyethylene)
	const G4double widthIns = .3 * mm;

    // Readout strip (copper)
	const G4double widthCopper = .04 * mm;
    const G4int nRows = 128;
    const G4int nCols = 128;

    // GAS FRACTIONS

    const G4double C2H2F4_fraction = 95.2 * perCent;
    const G4double isobutane_fraction = 4.5 * perCent;
    const G4double SF6_fraction = 0.3 * perCent;
    const G4double CO2_fraction = 0. * perCent;

    // ELECTRIC FIELD

    const G4double voltage = 10. * kilovolt;

    // PARTICLE GUN

    const G4String particleName = "mu+";
    const G4double particleEnergy = 1. * GeV;
    const G4double theta = 20. * degree;
};

#endif