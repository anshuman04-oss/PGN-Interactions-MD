#ifndef CONFIG_H
#define CONFIG_H

struct SystemConfig {
    double coreDiameter = 10.0;
    double monomerDiameter = 1.0;
    int chainLength = 30;
    double graftingDensity = 0.03;
    
    // Default parameters
    double maxBondAngle = 0.785398;
    double bondLength = 0.0;
};

struct AtomData {
    int id;
    int molecule;
    int type;
    double x, y, z;
};

struct BondData {
    int id;
    int type;
    int atom1, atom2;
};

#endif