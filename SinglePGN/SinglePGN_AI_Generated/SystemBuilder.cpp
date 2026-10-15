#include "SystemBuilder.h"
#include "PolymerChain.h"

#include <cstddef>
#include <utility>

namespace {
SystemConfig normalizeConfig(SystemConfig cfg) {
    if (cfg.bondLength <= 0.0) {
        cfg.bondLength = cfg.monomerDiameter;
    }
    return cfg;
}
}

SystemBuilder::SystemBuilder(const SystemConfig& cfg, std::unique_ptr<IOutputWriter> outWriter)
    : config(normalizeConfig(cfg)),
      core(std::array<double, 3>{0.0, 0.0, 0.0}, config.coreDiameter / 2.0, config.graftingDensity),
      writer(std::move(outWriter))
{}

void SystemBuilder::buildSystem() {
    allAtoms.clear();
    allBonds.clear();

    int gAtomID = 1;
    int gMolID = 1;
    int gBondID = 1;

    std::array<double, 3> c = core.getCenter();
    allAtoms.push_back(AtomData{gAtomID++, gMolID++, 1, c[0], c[1], c[2]});

    PolymerChain chainGen(config.chainLength, config.maxBondAngle, config.bondLength, core);
    const auto& sites = core.getSites();

    for (const auto& site : sites) {
        std::vector<std::array<double, 3>> chainCoords = chainGen.generate(site);
        for (size_t i = 0; i < chainCoords.size(); i++) {
            allAtoms.push_back(AtomData{gAtomID, gMolID, 2, chainCoords[i][0], chainCoords[i][1], chainCoords[i][2]});

            if (i == 0) {
                allBonds.push_back(BondData{gBondID++, 1, 1, gAtomID});
            } else {
                allBonds.push_back(BondData{gBondID++, 1, gAtomID - 1, gAtomID});
            }
            gAtomID++;
        }
        gMolID++;
    }
}

void SystemBuilder::exportData(const std::string& filename) {
    if (writer) {
        writer->write(filename, allAtoms, allBonds);
    }
}
