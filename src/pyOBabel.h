#ifndef pyOBabel_H
#define pyOBabel_H

#include <string>
#include <iostream>
#include <sstream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

// #define return_existing_1_0 (py::return_value_policy<py::reference_existing_object, py::with_custodian_and_ward_postcall< 1, 0 >>())
// #define return_existing_0_1 (py::return_value_policy<py::reference_existing_object, py::with_custodian_and_ward_postcall< 0, 1 >>())
// #define return_existing_1_2 (py::return_value_policy<py::reference_existing_object, py::with_custodian_and_ward_postcall< 1, 2 >>())
// #define return_existing_2_1 (py::return_value_policy<py::reference_existing_object, py::with_custodian_and_ward_postcall< 2, 1 >>())


template<typename T>
std::string cppAddress(T *t) {
    std::stringstream address;
    address<<reinterpret_cast<void*>(t);
    return address.str();
}


void wrap_vector3(py::module &);
void wrap_base(py::module &);
void wrap_mol(py::module &);
void wrap_atom(py::module &);
void wrap_bond(py::module &);
void wrap_residue(py::module &);
void wrap_obconversion(py::module &);
void wrap_plugin(py::module &);
void wrap_bitvec(py::module &);
void wrap_builder(py::module &);
void wrap_forcefield(py::module &);
void wrap_oberror(py::module &);

#endif

