#ifndef SYSTEMBUILDER_H
#define SYSTEMBUILDER_H

/*
    For building a single PGN, we need
    1. Nanoparticle:
        centre coordinates : INPUT
        radius : INPUT
        number of grafting sites : INPUT
        coordinates of the grafting sites : GENERATED
    2. Polymer Chain:
        radius of monomer : INPUT
        chain length : INPUT
        radius : INPUT
        bond length : INPUT set to DEFAULT equal to diameter
        max bond angle : INPUT set to DEFAULT 45 degrees
    3. Serial numbers and coordinates
*/

#include "Nanoparticle.h"
#include "PolymerChain.h"
#include<vector>
#include <array>
#include <cmath>

const double piOverFour = M_PI / 4.0;

struct AtomData {
    int id;
    int molecule;
    int type;
    double x, y, z;
};

struct BondData {
    int id;
    int type;
    double atom1, atom2;
};

class SystemBuilder {
    private:
        Nanoparticle core;
        std::vector<PolymerChain> graftedPolymers;
        double graftingDensity;
        double defBondLength;
        double defBondAngle;
        std::vector<AtomData> allAtoms;
        std::vector<BondData> allBonds;
        
    public:
        SystemBuilder(double gd, double dBL, double dBA, std::vector<double> c, double radius, int numSites) :
            core(c, radius, numSites),
            graftingDensity(gd),
            defBondLength(),
            defBondAngle(piOverFour) {}
};

#endif