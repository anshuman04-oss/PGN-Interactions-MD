#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include "Config.h"
#include <string>

class ConfigParser {
public:
    static SystemConfig parseCLI(int argc, char* argv[]);
    static void printUsage(const std::string& programName);
};

#endif