#ifndef SYSTEMBUILDER_H
#define SYSTEMBUILDER_H

#include "Config.h"
#include "IOutputWriter.h"
#include "Nanoparticle.h"

#include <memory>
#include <string>
#include <vector>

class SystemBuilder {
private:
    SystemConfig config;
    Nanoparticle core;
    std::unique_ptr<IOutputWriter> writer;
    std::vector<AtomData> allAtoms;
    std::vector<BondData> allBonds;

public:
    SystemBuilder(const SystemConfig& cfg, std::unique_ptr<IOutputWriter> outWriter);

    void buildSystem();
    void exportData(const std::string& filename);

    const std::vector<AtomData>& getAtoms() const { return allAtoms; }
    const std::vector<BondData>& getBonds() const { return allBonds; }
};

#endif
