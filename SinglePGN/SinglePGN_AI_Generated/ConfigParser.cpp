#include "ConfigParser.h"
#include <iostream>
#include <cstdlib>

void ConfigParser::printUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " [options]\n"
              << "Options:\n"
              << "  -c <coreDiameter>       (default: 10.0)\n"
              << "  -m <monomerDiameter>    (default: 1.0)\n"
              << "  -l <chainLength>        (default: 30)\n"
              << "  -g <graftingDensity>    (default: 0.03)\n"
              << "  -a <maxBondAngle>       (default: 0.785398)\n"
              << "  -b <bondLength>         (default: 1.0)\n";
}

SystemConfig ConfigParser::parseCLI(int argc, char* argv[]) {
    SystemConfig config; 

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (i + 1 < argc) {
            if (arg == "-c") config.coreDiameter = std::stod(argv[++i]);
            else if (arg == "-m") config.monomerDiameter = std::stod(argv[++i]);
            else if (arg == "-l") config.chainLength = std::stoi(argv[++i]);
            else if (arg == "-g") config.graftingDensity = std::stod(argv[++i]);
            else if (arg == "-a") config.maxBondAngle = std::stod(argv[++i]);
            else if (arg == "-b") config.bondLength = std::stod(argv[++i]);
            else {
                std::cerr << "Unknown option: " << arg << "\n";
                printUsage(argv[0]);
                exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "Missing value for option: " << arg << "\n";
            printUsage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    return config;
}