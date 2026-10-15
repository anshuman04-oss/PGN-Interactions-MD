#ifndef POLYMERCHAIN_H
#define POLYMERCHAIN_H

#include "Nanoparticle.h"
#include<vector>
#include<random>
#include<cmath>

class PolymerChain {
    private:
        int nMonomers;
        double rad;
        double maxBondAngle;
        double bondLength;
        Nanoparticle core;

    public:
        // Constructor
        PolymerChain(int n, double r, double maxAngle, double bLength, const Nanoparticle& coreObject)
            : nMonomers(n), rad(r), maxBondAngle(maxAngle), bondLength(bLength), core(coreObject) {}
        
        // Create a single polymer chain from the coordinate of every site
        std::vector<std::vector<double>> PolymerChain::generatePolymer(std::vector<double>& initCoord) {
        std::vector<std::vector<double>> ans;

        // FIX 1: Correct indices
        double x = initCoord[0];
        double y = initCoord[1];
        double z = initCoord[2];

        // First monomer is exactly on the grafting site
        ans.push_back({x, y, z});
        std::vector<double> prev1 = {x, y, z};

        // FIX 2: Calculate the Normal Vector for the first bond
        double cx = core.getCoordCent()[0];
        double cy = core.getCoordCent()[1];
        double cz = core.getCoordCent()[2];
        
        // Normal vector = (Site - Center) / Core Radius
        double nx = (x - cx) / core.getRad();
        double ny = (y - cy) / core.getRad();
        double nz = (z - cz) / core.getRad();

        // Move outward by exactly one bond length
        x += nx * bondLength;
        y += ny * bondLength;
        z += nz * bondLength;

        ans.push_back({x, y, z});
        std::vector<double> prev2 = {x, y, z};

        // Setup standard C++ Random Number Generators
        std::random_device rd;
        std::mt19937 gen(rd());
        // z_local ensures points stay inside the cone (Spherical Cap sampling)
        std::uniform_real_distribution<double> distZ(cos(maxBondAngle), 1.0); 
        std::uniform_real_distribution<double> distPhi(0.0, 2.0 * M_PI);

        for(int i = 2; i < nMonomers; i++) {
            // FIX 3: Calculate proper magnitude with sqrt
            double mag = 0;
            for(int j = 0; j < 3; j++) {
                mag += (prev2[j] - prev1[j]) * (prev2[j] - prev1[j]);
            }
            mag = sqrt(mag);
            
            // 1. The "Forward" Vector (Our custom Z-axis)
            std::vector<double> v_forward = {
                (prev2[0] - prev1[0]) / mag,
                (prev2[1] - prev1[1]) / mag,
                (prev2[2] - prev1[2]) / mag
            };
            
            // 2. Pick a temporary "Up" vector to help us calculate the Cross Product
            std::vector<double> temp_up = {1.0, 0.0, 0.0};
            if (std::abs(v_forward[0]) > 0.9) { 
                temp_up = {0.0, 1.0, 0.0}; // Prevent math errors if chain points straight down the X-axis
            }
            
            // 3. The "Right" Vector (Cross product of Forward and Temp Up)
            std::vector<double> v_right = {
                v_forward[1] * temp_up[2] - v_forward[2] * temp_up[1],
                v_forward[2] * temp_up[0] - v_forward[0] * temp_up[2],
                v_forward[0] * temp_up[1] - v_forward[1] * temp_up[0]
            };
            
            // Normalize the Right Vector
            double mag_r = sqrt(v_right[0]*v_right[0] + v_right[1]*v_right[1] + v_right[2]*v_right[2]);
            v_right[0] /= mag_r; v_right[1] /= mag_r; v_right[2] /= mag_r;
            
            // 4. The true "Up" Vector (Cross product of Right and Forward)
            std::vector<double> v_up = {
                v_right[1] * v_forward[2] - v_right[2] * v_forward[1],
                v_right[2] * v_forward[0] - v_right[0] * v_forward[2],
                v_right[0] * v_forward[1] - v_right[1] * v_forward[0]
            };
            
            // 5. Generate Random Local Coordinates inside the Cone
            double z_local = distZ(gen);
            double rho = sqrt(1.0 - z_local * z_local);
            double phi = distPhi(gen);
            
            double x_local = rho * cos(phi);
            double y_local = rho * sin(phi);
            
            // 6. Convert Local to Global by multiplying by our custom axes
            double new_x = prev2[0] + bondLength * (x_local * v_right[0] + y_local * v_up[0] + z_local * v_forward[0]);
            double new_y = prev2[1] + bondLength * (x_local * v_right[1] + y_local * v_up[1] + z_local * v_forward[1]);
            double new_z = prev2[2] + bondLength * (x_local * v_right[2] + y_local * v_up[2] + z_local * v_forward[2]);
            
            // Check for Steric Clash here before accepting! 
            // (If inside core, recalculate. Omitting loop for simplicity).

            // Shift the previous points forward for the next loop
            prev1 = prev2;
            prev2 = {new_x, new_y, new_z};
            
            ans.push_back(prev2);
        }
        
        return ans;
    }
};

#endif