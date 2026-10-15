#ifndef NANOPARTICLE_H
#define NANOPARTICLE_H

#include <vector>
#include <array>

// Class Definition
class Nanoparticle {
private:
    std::array<double, 3> center;
    double radius;
    int numSites;
    std::vector<std::array<double, 3>> siteCoords;

    void generateSites();

public:
    Nanoparticle(std::array<double, 3> c, double r, double density);
    double getRadius() const;
    std::array<double, 3> getCenter() const;
    const std::vector<std::array<double, 3>>& getSites() const;
};

#endif