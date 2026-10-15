#include "Nanoparticle.h"
#include <cmath>

namespace {
constexpr double kPi = 3.14159265358979323846;
}

Nanoparticle::Nanoparticle(std::array<double, 3> c, double r, double density) : center(c), radius(r) {
    numSites = static_cast<int>(std::round(4.0 * kPi * r * r * density));
    generateSites();
}

void Nanoparticle::generateSites() {
    siteCoords.clear();

    if (numSites <= 0) {
        return;
    }

    if (numSites == 1) {
        siteCoords.push_back({center[0], center[1] + radius, center[2]});
        return;
    }

    double phi = kPi * (3.0 - std::sqrt(5.0));
    for (int i = 0; i < numSites; i++) {
        double y = 1.0 - (i / double(numSites - 1)) * 2.0;
        double radiusAtY = std::sqrt(1.0 - y * y);
        double theta = phi * i;
        double x = std::cos(theta) * radiusAtY;
        double z = std::sin(theta) * radiusAtY;
        siteCoords.push_back({center[0] + x * radius, center[1] + y * radius, center[2] + z * radius});
    }
}

double Nanoparticle::getRadius() const { 
    return radius; 
}

std::array<double, 3> Nanoparticle::getCenter() const { 
    return center; 
}

const std::vector<std::array<double, 3>>& Nanoparticle::getSites() const { 
    return siteCoords; 
}
