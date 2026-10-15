#ifndef IOUTPUTWRITER_H
#define IOUTPUTWRITER_H

#include "Config.h"
#include <vector>
#include <string>

class IOutputWriter {
public:
    virtual ~IOutputWriter() = default;
    virtual void write(const std::string& filename, const std::vector<AtomData>& atoms, const std::vector<BondData>& bonds) = 0;
};

#endif