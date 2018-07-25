#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

#include <openbabel/oberror.h>

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

// Set Python stream as a dynamic attribute __outstream__
void SetOutputStream(OB::OBMessageHandler *msgHandle, py::object pyStream) {

    // First check if the argument is of desried class
    if(!py::isinstance(pyStream, py::module::import("io").attr("IOBase")))   {
        py::print("WARNING: Failed to set the stream. Stream is not instance of io.IOBase or its derived class.");
        return;
    }

    py::detail::pythonbuf buffer(pyStream);
    std::ostream cppStream(nullptr);
    cppStream.rdbuf(&buffer);
    msgHandle->SetOutputStream(&cppStream);
    py::object pMsgHandle = py::cast(msgHandle);
    pMsgHandle.attr("__outstream__") = pyStream;

}

// Get Python stream
py::object GetOutputStream(OB::OBMessageHandler *msgHandle) {
    py::object pMsgHandle = py::cast(msgHandle);
    return pMsgHandle.attr("__outstream__");
}


void wrap_oberror(py::module &m) {

    py::enum_<OB::obMessageLevel>(m, "obMessageLevel")
            .value("obError", OB::obMessageLevel::obError)
            .value("obWarning", OB::obMessageLevel::obWarning)
            .value("obInfo", OB::obMessageLevel::obInfo)
            .value("obAuditMsg", OB::obMessageLevel::obAuditMsg)
            .value("obDebug", OB::obMessageLevel::obDebug)
    ;

    py::enum_<OB::errorQualifier>(m, "errorQualifier")
            .value("always", OB::errorQualifier::always)
            .value("onceOnly", OB::errorQualifier::onceOnly)
    ;

    py::class_<OB::OBError>(m, "OBError")
            .def(py::init<const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const OB::obMessageLevel>(),
                 py::arg("method")="", py::arg("errorMsg")="" ,py::arg("explanation")="", py::arg("possibleCause")="",
                 py::arg("suggestedRemedy")="", py::arg("obMessageLevel")= OB::obDebug)
            .def("message", &OB::OBError::message)
            .def("GetMethod", &OB::OBError::GetMethod)
            .def("GetError", &OB::OBError::GetError)
            .def("GetExplanation", &OB::OBError::GetExplanation)
            .def("GetPossibleCause", &OB::OBError::GetPossibleCause)
            .def("GetSuggestedRemedy", &OB::OBError::GetSuggestedRemedy)
            .def("GetLevel", &OB::OBError::GetLevel)
            ;

    py::class_<OB::OBMessageHandler>(m, "OBMessageHandler", py::dynamic_attr())
            .def(py::init())
            .def_property("stream", &GetOutputStream, &SetOutputStream)

            .def("ThrowErrorByOBError", (void (OB::OBMessageHandler::*)(OB::OBError, OB::errorQualifier)) &OB::OBMessageHandler::ThrowError,
                 py::arg("err"), py::arg("qqualifier") = OB::errorQualifier::always)
            .def("ThrowErrorByMessage", (void (OB::OBMessageHandler::*)(const std::string &,
                                                               const std::string &,
                                                               OB::obMessageLevel,
                                                               OB::errorQualifier)) &OB::OBMessageHandler::ThrowError,
                 py::arg("method"),
                 py::arg("errorMsg"),
                 py::arg("level") = OB::obMessageLevel::obDebug,
                 py::arg("qualifier") = OB::errorQualifier::always)
            .def("GetMessagesOfLevel", &OB::OBMessageHandler::GetMessagesOfLevel)
            .def("StartLogging", &OB::OBMessageHandler::StartLogging)
            .def("SetMaxLogEntries", &OB::OBMessageHandler::SetMaxLogEntries)
            .def("GetMaxLogEntries", &OB::OBMessageHandler::GetMaxLogEntries)
            .def("ClearLog", &OB::OBMessageHandler::ClearLog)
            .def("SetOutputLevel", &OB::OBMessageHandler::SetOutputLevel)
            .def("GetOutputLevel", &OB::OBMessageHandler::GetOutputLevel)
            .def("SetOutputStream", &SetOutputStream)
            .def("GetOutputStream", &GetOutputStream)
            .def("StopErrorWrap", &OB::OBMessageHandler::StopErrorWrap)

            .def("GetErrorMessageCount", &OB::OBMessageHandler::GetErrorMessageCount)
            .def("GetWarningMessageCount", &OB::OBMessageHandler::GetWarningMessageCount)
            .def("GetInfoMessageCount", &OB::OBMessageHandler::GetInfoMessageCount)
            .def("GetAuditMessageCount", &OB::OBMessageHandler::GetAuditMessageCount)
            .def("GetDebugMessageCount", &OB::OBMessageHandler::GetDebugMessageCount)
            .def("GetMessageSummary", &OB::OBMessageHandler::GetMessageSummary)
            ;

    m.attr("obErrorLog") = py::cast(&OB::obErrorLog);
    SetOutputStream(&OB::obErrorLog, py::module::import("sys").attr("stderr"));

}
