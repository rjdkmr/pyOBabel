#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <openbabel/math/vector3.h>

#include "pyOBabel.h"
#include "vector3.h"

namespace py = pybind11;
namespace OB = OpenBabel;

// Get coordinate as a py list ( ~ Get(const double *c))
py::list Get_Wrapped(OB::vector3*v){
    py::list list;
    list.append(v->GetX());
    list.append(v->GetY());
    list.append(v->GetZ());
    return list;
}

OB::vector3* initByList(py::list list) {
    return new OB::vector3(py::float_(list[0]), py::float_(list[1]), py::float_(list[2]));
}

// Copy a vector
OB::vector3* copy(OB::vector3 *v){
    return new OB::vector3(*v);
}

// Create orthogonal vector.In OB::vector3::createOrthoVector, argument is output
// Therefore it is wrapped such that returned is output.
OB::vector3* createOrthoVector(OB::vector3 *v){
    OB::vector3 *out = new OB::vector3();

    if(v->createOrthoVector(*out))    {
        return out;
    }
    else{
        return nullptr;
    }
}

void wrap_vector3(py::module &m) {

    void (OB::vector3::*SetOne)(const double inX, const double inY, const double inZ) = &OB::vector3::Set;

    py::class_< OB::vector3 >(m, "vector3", vector3Doc)
            .def(py::init< const double, const double, const double >(),
                 py::arg("inX") = 0.0, py::arg("inY")= 0.0, py::arg("inZ")=0.0)
            .def(py::init([](py::list list){return initByList(list);}))
            .def("Set",  SetOne, py::arg("inX"), py::arg("inY"), py::arg("inZ"), Set1Doc)
            .def("SetX", &OB::vector3::SetX, py::arg("inX"), SetXDoc)
            .def("SetY", &OB::vector3::SetY, py::arg("inY"), SetYDoc)
            .def("SetZ", &OB::vector3::SetZ, py::arg("inZ"), SetZDoc)
            .def("GetX", &OB::vector3::GetX, GetXDoc)
            .def("GetY", &OB::vector3::GetY, GetYDoc)
            .def("GetZ", &OB::vector3::GetZ, GetZDoc)
            .def("Get",  &Get_Wrapped, GetDoc)
            .def("copy", &copy, copyDoc)
            .def("__getitem__", &OB::vector3::operator[])
            .def(py::self += py::self)
            .def(py::self += double())
            .def(py::self -= py::self)
            .def(py::self -= double())
            .def(py::self *= double())
            .def(py::self /= double())
            .def(py::self == py::self)
            .def(py::self != py::self)
             //ToDo: .def("randomUnitVector", &OB::vector3::randomUnitVector, randomUnitVectorDoc)
            .def("normalize", &OB::vector3::normalize, normalizeDoc)
            .def("CanBeNormalized", &OB::vector3::CanBeNormalized, CanBeNormalizedDoc)
            .def("length_2", &OB::vector3::length_2, length2Doc)
            .def("length", &OB::vector3::length, lengthDoc)
            .def("IsApprox", &OB::vector3::IsApprox, IsApproxDoc)
            .def("distSq", &OB::vector3::distSq, py::arg("v"), distSqDoc)
            .def("createOrthoVector", &createOrthoVector, createOrthoVectorDoc )
            .def(py::self + py::self)
            .def(py::self - py::self)
            .def(-py::self)
            .def(py::self * double())
            .def(double() * py::self)
            .def(py::self / double())
            ;

    m.def("dot", &OB::dot, py::arg("v1"), py::arg("v2"), dotDoc);
    m.def("cross", &OB::cross, py::arg("v1"), py::arg("v2"), crossDoc);
    m.def("vectorAngle", &OB::vectorAngle, py::arg("v1"), py::arg("v2"), vectorAngleDoc);
    m.def("CalcTorsionAngle", &OB::CalcTorsionAngle,
          py::arg("a"), py::arg("b"), py::arg("c"), py::arg("d"),
          CalcTorsionAngleDoc);
    m.def("Point2PlaneSigned", &OB::Point2PlaneSigned,
          py::arg("a"), py::arg("b"), py::arg("c"), py::arg("d"),
          Point2PlaneSignedDoc);
    m.def("Point2Plane", &OB::Point2Plane,
          py::arg("a"), py::arg("b"), py::arg("c"), py::arg("d"),
          Point2PlaneDoc);
    m.def("Point2PlaneAngle", &OB::Point2PlaneAngle,
          py::arg("a"), py::arg("b"), py::arg("c"), py::arg("d"),
          Point2PlaneAngleDoc);
    m.def("Point2Line", &OB::Point2Line,
          py::arg("a"), py::arg("b"), py::arg("c"),
          Point2LineDoc);


}
