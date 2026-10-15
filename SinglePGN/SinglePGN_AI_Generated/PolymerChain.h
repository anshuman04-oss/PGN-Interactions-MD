#ifndef POLYMERCHAIN_H
#define POLYMERCHAIN_H

#include <vector>
#include <array>
#include "Nanoparticle.h"

class PolymerChain {
private:
    int nMonomers;
    double maxBondAngle;
    double bondLength;
    const Nanoparticle& core;

public:
    PolymerChain(int n, double maxAngle, double bLength, const Nanoparticle& c);
    std::vector<std::array<double, 3>> generate(const std::array<double, 3>& siteCoord) const;
};

#endif