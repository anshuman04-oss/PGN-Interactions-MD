#include "PolymerChain.h"
#include <cmath>
#include <random>

namespace {
constexpr double kPi = 3.14159265358979323846;
}

PolymerChain::PolymerChain(int n, double maxAngle, double bLength, const Nanoparticle& c)
    : nMonomers(n), maxBondAngle(maxAngle), bondLength(bLength), core(c) {}

std::vector<std::array<double, 3>> PolymerChain::generate(const std::array<double, 3>& siteCoord) const {
    std::vector<std::array<double, 3>> chain;

    if (nMonomers <= 0) {
        return chain;
    }

    chain.push_back(siteCoord);

    if (nMonomers == 1) {
        return chain;
    }

    std::array<double, 3> c = core.getCenter();
    double r = core.getRadius();

    double nx = (siteCoord[0] - c[0]) / r;
    double ny = (siteCoord[1] - c[1]) / r;
    double nz = (siteCoord[2] - c[2]) / r;

    std::array<double, 3> prev1 = siteCoord;
    std::array<double, 3> prev2 = {
        siteCoord[0] + nx * bondLength,
        siteCoord[1] + ny * bondLength,
        siteCoord[2] + nz * bondLength
    };
    chain.push_back(prev2);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distZ(std::cos(maxBondAngle), 1.0);
    std::uniform_real_distribution<double> distPhi(0.0, 2.0 * kPi);

    for(int i = 2; i < nMonomers; i++) {
        while (true) {
            double mag = std::sqrt(std::pow(prev2[0]-prev1[0], 2) + std::pow(prev2[1]-prev1[1], 2) + std::pow(prev2[2]-prev1[2], 2));
            std::array<double, 3> vf = {(prev2[0]-prev1[0])/mag, (prev2[1]-prev1[1])/mag, (prev2[2]-prev1[2])/mag};
            
            std::array<double, 3> tup = {1.0, 0.0, 0.0};
            if (std::abs(vf[0]) > 0.9) {
                tup = {0.0, 1.0, 0.0};
            }
            
            std::array<double, 3> vr = {
                vf[1]*tup[2] - vf[2]*tup[1],
                vf[2]*tup[0] - vf[0]*tup[2],
                vf[0]*tup[1] - vf[1]*tup[0]
            };
            double magR = std::sqrt(vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2]);
            vr = {vr[0]/magR, vr[1]/magR, vr[2]/magR};
            
            std::array<double, 3> vu = {
                vr[1]*vf[2] - vr[2]*vf[1],
                vr[2]*vf[0] - vr[0]*vf[2],
                vr[0]*vf[1] - vr[1]*vf[0]
            };
            
            double zl = distZ(gen);
            double rho = std::sqrt(1.0 - zl*zl);
            double phi = distPhi(gen);
            double xl = rho * std::cos(phi);
            double yl = rho * std::sin(phi);
            
            std::array<double, 3> cand = {
                prev2[0] + bondLength * (xl*vr[0] + yl*vu[0] + zl*vf[0]),
                prev2[1] + bondLength * (xl*vr[1] + yl*vu[1] + zl*vf[1]),
                prev2[2] + bondLength * (xl*vr[2] + yl*vu[2] + zl*vf[2])
            };
            
            double distToCore = std::sqrt(std::pow(cand[0]-c[0], 2) + std::pow(cand[1]-c[1], 2) + std::pow(cand[2]-c[2], 2));
            if (distToCore >= r) {
                prev1 = prev2;
                prev2 = cand;
                chain.push_back(cand);
                break;
            }
        }
    }
    return chain;
}
