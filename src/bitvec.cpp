#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <openbabel/bitvec.h>

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;


void wrap_bitvec(py::module &m) {

    m.def("Tanimoto", &OB::Tanimoto);

    py::class_< OB::OBBitVec >(m, "OBBitVec")
            .def(py::init<>())
            .def(py::init<unsigned>(), py::arg("size_in_bits"))
            .def(py::init< const OB::OBBitVec & >(), py::arg("bv"))
            .def("SetBitOn", &OB::OBBitVec::SetBitOn)
            .def("SetBitOff", &OB::OBBitVec::SetBitOff)
            .def("SetRangeOn", &OB::OBBitVec::SetRangeOn)
            .def("SetRangeOff", &OB::OBBitVec::SetRangeOff)
            .def("Fold", &OB::OBBitVec::Fold)
            .def("FirstBit", &OB::OBBitVec::FirstBit)
            .def("NextBit", &OB::OBBitVec::NextBit)
            .def("EndBit", &OB::OBBitVec::EndBit)
            .def("GetSize", &OB::OBBitVec::GetSize)
            .def("CountBits", &OB::OBBitVec::CountBits)
            .def("IsEmpty", &OB::OBBitVec::IsEmpty)
            .def("Resize", &OB::OBBitVec::Resize)
            .def("ResizeWords", &OB::OBBitVec::ResizeWords)
            .def("BitIsOn", &OB::OBBitVec::BitIsOn)
            .def("FromVecInt", &OB::OBBitVec::FromVecInt)
            .def("FromString", &OB::OBBitVec::FromString)
            .def("Clear", &OB::OBBitVec::Clear)
            .def("Negate", &OB::OBBitVec::Negate)
            .def("__getitem__", &OB::OBBitVec::operator[])
            .def(py::self &= py::self)
            .def(py::self |= py::self)
            .def(py::self |= int())
            .def(py::self ^= py::self)
            .def(py::self -= py::self)
            .def(py::self += py::self)
            .def(py::self | py::self)
            .def(py::self & py::self)
            .def(py::self - py::self)
            .def(py::self == py::self)
            .def(py::self < py::self)


            ;
}
