#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <openbabel/plugin.h>

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

// Wrapper class for virtual functions
class pyOBPlugin : public OB::OBPlugin
{

public:

    using OB::OBPlugin::OBPlugin;

    const char* Description() {
        PYBIND11_OVERLOAD_PURE( const char*, OBPlugin, Description);
    }

    const char* TypeID() {
        PYBIND11_OVERLOAD_PURE( const char*, OBPlugin, TypeID);
    }

    bool Display(std::string&txt, const char* param, const char* ID=NULL) {
        PYBIND11_OVERLOAD_PURE( bool, OBPlugin, Display, txt, param, ID);
    }

    OBPlugin* MakeInstance(const std::vector<std::string>& desc) {
        PYBIND11_OVERLOAD_PURE( OBPlugin*, OBPlugin, MakeInstance, desc);
    }


    void Init() {
        PYBIND11_OVERLOAD_PURE( void, OBPlugin, Init);
    }
};

bool ListAsVector(const char* PluginID, const char* param,  py::list list){
    std::vector<std::string> vlist = std::vector<std::string>();
    bool result = OB::OBPlugin::ListAsVector(PluginID, param, vlist);
    list.attr("clear")();
    for (int i=0; i<vlist.size(); i++){
        list.append(vlist.at(i));
    }
    return result;
}

void wrap_plugin(py::module &m){
    py::class_< OB::OBPlugin, pyOBPlugin >(m, "OBPlugin")
            // Virtual functions
            .def("TypeID", &OB::OBPlugin::TypeID)
            .def("Display", &OB::OBPlugin::Display)
            .def("MakeInstance", &OB::OBPlugin::MakeInstance)
            .def("Init", &OB::OBPlugin::Init)

            .def("GetPlugin", &OB::OBPlugin::GetPlugin)
            .def("GetID", &OB::OBPlugin::GetID)
            .def_static("List", &ListAsVector)
             //.def("List", &OB::OBPlugin::List)
            .def_static("ListAsString", &OB::OBPlugin::ListAsString)
            .def_static("FirstLine", &OB::OBPlugin::FirstLine)
     ;

}
