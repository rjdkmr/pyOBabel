#include <pybind11/pybind11.h>
#include <openbabel/bond.h>
#include <openbabel/mol.h>

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

void wrap_bond(py::module &m) {

    void (OB::OBBond::*SetLengthOne)(OB::OBAtom *fixed,double length) = &OB::OBBond::SetLength;
    void (OB::OBBond::*SetLengthTwo)(double length) = &OB::OBBond::SetLength;

    OB::OBAtom* (OB::OBBond::*GetBeginAtom)() = &OB::OBBond::GetBeginAtom;
    OB::OBAtom* (OB::OBBond::*GetEndAtom)() = &OB::OBBond::GetEndAtom;

    py::class_< OB::OBBond, OB::OBBase >(m, "OBBond")
            .def("SetId", &OB::OBBond::SetId)
            .def("SetBO", &OB::OBBond::SetBO)
            .def("SetBondOrder", &OB::OBBond::SetBondOrder)
            .def("SetBegin", &OB::OBBond::SetBegin)
            .def("SetEnd", &OB::OBBond::SetEnd)
            .def("SetParent", &OB::OBBond::SetParent, py::return_value_policy::reference, py::keep_alive<2, 1>())
            .def("SetLength", SetLengthOne)
            .def("SetLength", SetLengthTwo)
            .def("SetAromatic", &OB::OBBond::SetAromatic)
            .def("SetWedge", &OB::OBBond::SetWedge)
            .def("SetHash", &OB::OBBond::SetHash)
            .def("SetWedgeOrHash", &OB::OBBond::SetWedgeOrHash)
            .def("SetUp", &OB::OBBond::SetUp)
            .def("SetDown", &OB::OBBond::SetDown)
            .def("SetInRing", &OB::OBBond::SetInRing)
            .def("SetClosure", &OB::OBBond::SetClosure)
            .def("UnsetHash", &OB::OBBond::UnsetHash)
            .def("UnsetWedge", &OB::OBBond::UnsetWedge)
            .def("UnsetUp", &OB::OBBond::UnsetUp)
            .def("UnsetDown", &OB::OBBond::UnsetDown)
            .def("UnsetAromatic", &OB::OBBond::UnsetAromatic)

            .def("GetIdx", &OB::OBBond::GetIdx)
            .def("GetId", &OB::OBBond::GetId)
            .def("GetBO", &OB::OBBond::GetBO)
            .def("GetBondOrder", &OB::OBBond::GetBondOrder)
            .def("GetFlags", &OB::OBBond::GetFlags)
            .def("GetBeginAtomIdx", &OB::OBBond::GetBeginAtomIdx)
            .def("GetEndAtomIdx", &OB::OBBond::GetEndAtomIdx)
            .def("GetBeginAtom", GetBeginAtom, py::return_value_policy::reference, py::keep_alive<1, 0>())
            .def("GetEndAtom", GetEndAtom, py::return_value_policy::reference, py::keep_alive<1, 0>())
            .def("GetNbrAtom", &OB::OBBond::GetNbrAtom, py::return_value_policy::reference, py::keep_alive<1, 0>())
            .def("GetParent", &OB::OBBond::GetParent, py::return_value_policy::reference, py::keep_alive<0, 1>())
            .def("GetEquibLength", &OB::OBBond::GetEquibLength)
            .def("GetLength", &OB::OBBond::GetLength)
            .def("GetNbrAtomIdx", &OB::OBBond::GetNbrAtomIdx)
            //.def("FindSmallestRing", &OB::OBBond::FindSmallestRing)
            .def("IsAromatic", &OB::OBBond::IsAromatic)
            .def("IsInRing", &OB::OBBond::IsInRing)
            .def("IsRotor", &OB::OBBond::IsRotor)
            .def("IsAmide", &OB::OBBond::IsAmide)
            .def("IsPrimaryAmide", &OB::OBBond::IsPrimaryAmide)
            .def("IsSecondaryAmide", &OB::OBBond::IsSecondaryAmide)
            .def("IsTertiaryAmide", &OB::OBBond::IsTertiaryAmide)
            .def("IsEster", &OB::OBBond::IsEster)
            .def("IsCarbonyl", &OB::OBBond::IsCarbonyl)
            .def("IsClosure", &OB::OBBond::IsClosure)
            .def("IsUp", &OB::OBBond::IsUp)
            .def("IsDown", &OB::OBBond::IsDown)
            .def("IsWedge", &OB::OBBond::IsWedge)
            .def("IsHash", &OB::OBBond::IsHash)
            .def("IsWedgeOrHash", &OB::OBBond::IsWedgeOrHash)
            .def("IsCisOrTrans", &OB::OBBond::IsCisOrTrans)
            .def("IsDoubleBondGeometry", &OB::OBBond::IsDoubleBondGeometry)
        ;
}
