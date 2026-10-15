#ifndef NANOPARTICLE_H
#define NANOPARTICLE_H

#include<vector>
#include <cmath>

class Nanoparticle {
    private:
        std::vector<double> coordCent;
        double rad;
        int numSites;
        std::vector<std::vector<double>> siteCoords;
        
    public:
        // Constructor
        Nanoparticle::Nanoparticle(std::vector<double> center, int r, int nSites) 
            : coordCent(center), rad(r), numSites(nSites) {}

        // Getters and setters
        void setCoordCent(double x, double y, double z) {
            coordCent[0] = x;
            coordCent[1] = y;
            coordCent[2] = z;
        }
        std::vector<double> getCoordCent() {
            return coordCent;
        }
        void setRad(double r) {
            rad = r;
        }
        double getRad() {
            return rad;
        }
        void setNumSites(int n) {
            numSites = n;
        }
        int getNumSites() {
            return numSites;
        }
        void setSiteCoords(std::vector<std::vector<double>> coord) {
            siteCoords = coord;
        }
        std::vector<std::vector<double>> getSiteCoords() {
            return siteCoords;
        }
        
        // Generate the coordinates of the grafting sites
        void generateSites() {
            double phi = M_PI * (3.0 - sqrt(5.0));
            double step = (2.0 * rad) / ((double) numSites - 1.0);
            double y = rad;
            for(int i = 0; i < numSites; i++) {
                double r = sqrt(rad * rad - y * y);
                double rotAng = phi * i;
                double X = r * cos(rotAng), Y = r * sin(rotAng);
                siteCoords.push_back({X, Y, y});
                y -= step;
            }
        }
};

#endif