#include "Config.h"
#include "ConfigParser.h"
#include "SystemBuilder.h"
#include "LAMMPSWriter.h"
#include <memory>

int main(int argc, char* argv[]) {
    SystemConfig config = ConfigParser::parseCLI(argc, argv);

    SystemBuilder builder(config, std::make_unique<LAMMPSWriter>());
    builder.buildSystem();
    builder.exportData("data.lammps");

    return 0;
}