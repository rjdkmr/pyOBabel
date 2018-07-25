#include "pyOBabel.h"

PYBIND11_MODULE(pyOBabel, m) 
{
    wrap_vector3(m);
    wrap_base(m);
    wrap_mol(m);
    wrap_atom(m);
    wrap_bond(m);
    wrap_residue(m);
    wrap_obconversion(m);
    wrap_plugin(m);
    wrap_bitvec(m);
    wrap_builder(m);
    wrap_forcefield(m);
    wrap_oberror(m);
}
