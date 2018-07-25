#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <openbabel/builder.h>
#include <openbabel/mol.h>
#include <openbabel/atom.h>
#include <openbabel/math/vector3.h>

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

void wrap_builder(py::module &m) {


    py::class_< OB::OBBuilder >(m, "OBBuilder")
            .def(py::init())
            .def("Build", &OB::OBBuilder::Build, py::arg("mol"), py::arg("stereoWarnings")=true)
            .def("SetKeepRings", &OB::OBBuilder::SetKeepRings)
            .def("UnsetKeepRings", &OB::OBBuilder::UnsetKeepRings)
            .def("LoadFragments", &OB::OBBuilder::LoadFragments)
            .def_static("GetNewBondVector", (OB::vector3 (*)(OB::OBAtom*)) &OB::OBBuilder::GetNewBondVector,
                        py::arg("atom"))
            .def_static("GetNewBondVector", (OB::vector3 (*)(OB::OBAtom*, double)) &OB::OBBuilder::GetNewBondVector,
                 py::arg("atom"), py::arg("length"))
            .def_static("Connect", (bool (*)(OB::OBMol &,int,int,OB::vector3 &,int)) &OB::OBBuilder::Connect,
                 py::arg("mol"), py::arg("a"), py::arg("b"), py::arg("newpos"), py::arg("bondOrder") = 1)
            .def_static("Connect",  (bool (*)(OB::OBMol &,int,int,int)) &OB::OBBuilder::Connect,
                 py::arg("mol"), py::arg("a"), py::arg("b"), py::arg("bondOrder") = 1)
            .def_static("Swap", &OB::OBBuilder::Swap,
                        py::arg("mol"), py::arg("a"), py::arg("b"), py::arg("c"), py::arg("d"))
            .def_static("CorrectStereoAtoms", (bool (*)(OB::OBMol &)) &OB::OBBuilder::CorrectStereoAtoms,
                        py::arg("mol"))
            .def_static("CorrectStereoAtoms", (bool (*)(OB::OBMol &,bool)) &OB::OBBuilder::CorrectStereoAtoms,
                        py::arg("mol"), py::arg("warn")=true)
            .def_static("IsSpiroAtom", &OB::OBBuilder::IsSpiroAtom,
                        py::arg("atomId"), py::arg("mol"))
            .def_static("GetFragment", &OB::OBBuilder::GetFragment,
                        py::arg("atom"))
            .def_static("AddNbrs", &OB::OBBuilder::AddNbrs,
                        py::arg("fragment"), py::arg("atom"))

            ;
}
