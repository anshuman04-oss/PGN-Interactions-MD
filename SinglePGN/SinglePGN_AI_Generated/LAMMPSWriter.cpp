#include "LAMMPSWriter.h"
#include <fstream>

void LAMMPSWriter::write(const std::string& filename, const std::vector<AtomData>& atoms, const std::vector<BondData>& bonds) {
    std::ofstream out(filename);
    if (!out) return;

    out << "LAMMPS Data File # atom_style molecular\n\n";
    out << atoms.size() << " atoms\n";
    out << bonds.size() << " bonds\n";
    out << "0 angles\n0 dihedrals\n0 impropers\n\n";
    out << "2 atom types\n1 bond types\n\n";
    
    out << "-500.0 500.0 xlo xhi\n-500.0 500.0 ylo yhi\n-500.0 500.0 zlo zhi\n\n";
    
    out << "Masses\n\n1 50.0\n2 1.0\n\n";
    out << "Atoms\n\n";
    
    for (const auto& a : atoms) {
        out << a.id << " " << a.molecule << " " << a.type << " " << a.x << " " << a.y << " " << a.z << "\n";
    }
    
    if (!bonds.empty()) {
        out << "\nBonds\n\n";
        for (const auto& b : bonds) {
            out << b.id << " " << b.type << " " << b.atom1 << " " << b.atom2 << "\n";
        }
    }
}