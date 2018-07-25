#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <openbabel/obconversion.h>
#include <openbabel/mol.h>
#include <openbabel/atom.h>
#include <openbabel/bond.h>
#include <openbabel/residue.h>

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

py::dict fileFormatDictionary(std::vector<std::string> formats) {
    py::dict formattedDict;
    for(int i=0; i<formats.size(); i++) {
        py::object string = py::str(formats.at(i));
        py::object split = py::module::import("re").attr("split");
        py::list temp = split("\\s+--\\s+", string);
        if(temp.size()>0)
            formattedDict[py::str(temp[0])] = py::str(temp[1]);
        else
            formattedDict[py::str(temp[0])] = " ";
    }
    return formattedDict;
}

py::dict GetInputFormats() {
    OB::OBConversion obconv = OB::OBConversion();
    std::vector<std::string> formats = obconv.GetSupportedInputFormat();
    return fileFormatDictionary(formats);
}

py::dict GetOutputFormats() {
    OB::OBConversion obconv = OB::OBConversion();
    std::vector<std::string> formats = obconv.GetSupportedOutputFormat();
    return fileFormatDictionary(formats);
}

bool Read(OB::OBConversion *conv, OB::OBBase *pOB) {
    return conv->Read(pOB);
}

bool Write(OB::OBConversion *conv, OB::OBBase *pOB) {
    return conv->Write(pOB);
}

void wrap_obconversion(py::module &m){

    m.attr("inputFormats") = GetInputFormats();
    m.attr("outputFormats") = GetOutputFormats();


    py::class_<OB::OBConversion> conversion (m, "OBConversion");

    py::enum_<OB::OBConversion::Option_type>(conversion, "Option_type")
            .value("INOPTIONS", OB::OBConversion::Option_type::INOPTIONS)
            .value("OUTOPTIONS", OB::OBConversion::Option_type::OUTOPTIONS)
            .value("GENOPTIONS", OB::OBConversion::Option_type::GENOPTIONS)
            .value("ALL", OB::OBConversion::Option_type::ALL)
            .export_values();


    conversion.def(py::init<>())
            .def(py::init<std::string, std::string>())
            .def("GetSupportedInputFormat", &OB::OBConversion::GetSupportedInputFormat)
            .def("GetSupportedOutputFormat", &OB::OBConversion::GetSupportedOutputFormat)
            .def("SetInAndOutFormats", (void (OB::OBConversion::*)(const char*,const char*,bool,bool)) &OB::OBConversion::GetSupportedInputFormat,
                 py::arg("inID"), py::arg("outID"), py::arg("ingzip")=false, py::arg("outgzip")=false)
            .def("SetInFormat", (bool (OB::OBConversion::*)(const char*,bool)) &OB::OBConversion::SetInFormat,
                 py::arg("inID"), py::arg("isgzip")=false)
            .def("SetOutFormat", (bool (OB::OBConversion::*)(const char*,bool)) &OB::OBConversion::SetOutFormat,
                 py::arg("inID"), py::arg("isgzip")=false)
            .def("IsOption", &OB::OBConversion::IsOption, py::arg("opt"), py::arg("opttyp")=OB::OBConversion::Option_type::OUTOPTIONS)
            .def("GetOptions", &OB::OBConversion::GetOptions)
            .def("AddOption", &OB::OBConversion::AddOption, py::arg("opt"), py::arg("opttyp")=OB::OBConversion::Option_type::OUTOPTIONS, py::arg("txt")=NULL)
            .def("RemoveOption", &OB::OBConversion::RemoveOption)
            .def("SetOptions", &OB::OBConversion::SetOptions)
            .def("Convert", (int (OB::OBConversion::*)()) &OB::OBConversion::Convert )
            .def("FullConvert", &OB::OBConversion::FullConvert )
            .def("AddChemObject", &OB::OBConversion::AddChemObject)
            .def("GetChemObject", &OB::OBConversion::GetChemObject)
            .def("IsLast", &OB::OBConversion::IsLast)
            .def("IsFirstInput", &OB::OBConversion::IsFirstInput)
            .def("SetFirstInput", &OB::OBConversion::SetFirstInput)
            .def("GetOutputIndex", &OB::OBConversion::GetOutputIndex)
            .def("SetOutputIndex", &OB::OBConversion::SetOutputIndex)
            .def("SetMoreFilesToCome", &OB::OBConversion::SetMoreFilesToCome)
            .def("SetOneObjectOnly", &OB::OBConversion::SetOneObjectOnly)
            .def("SetLast", &OB::OBConversion::SetLast)
            .def("IsLastFile", &OB::OBConversion::IsLastFile)
            .def("GetCount", &OB::OBConversion::GetCount)
            .def("Write", &Write) // modified above, std::istream not yet supported in pybind11
            .def("WriteString", &OB::OBConversion::WriteString,
                 py::arg("obmol"), py::arg("trimWhitespace")=false)
            .def("WriteFile", &OB::OBConversion::WriteFile)
            .def("CloseOutFile", &OB::OBConversion::CloseOutFile)
            .def("Read", &Read) // modified above, std::istream not yet supported in pybind11
            .def("ReadString", &OB::OBConversion::ReadString)
            .def("ReadFile", &OB::OBConversion::ReadFile)
            .def("OpenInAndOutFiles", &OB::OBConversion::OpenInAndOutFiles)
            ;



}
