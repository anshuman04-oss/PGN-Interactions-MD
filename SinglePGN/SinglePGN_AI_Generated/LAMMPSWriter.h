#ifndef LAMMPSWRITER_H
#define LAMMPSWRITER_H

#include "IOutputWriter.h"

class LAMMPSWriter : public IOutputWriter {
public:
    void write(const std::string& filename, const std::vector<AtomData>& atoms, const std::vector<BondData>& bonds) override;
};

#endif