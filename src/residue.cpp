#include <pybind11/pybind11.h>

#include <openbabel/residue.h>

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

void wrap_residue(py::module &m) {

    py::class_< OB::OBResidue, OB::OBBase >(m, "OBResidue")
            //.def("cppAddress", &cppAddress<OB::OBResidue>)
            .def("SetName", &OB::OBResidue::SetName)
            .def("GetName", &OB::OBResidue::GetName)
        ;
}
