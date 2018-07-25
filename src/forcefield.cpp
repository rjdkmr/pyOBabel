#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <openbabel/forcefield.h>
//#include "forcefieldgaff.h"

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

/* Not Implemented
 *
 * Vector analysis
 *
 */

py::dict getForceFieldNames(){
    std::vector<std::string> vlist = std::vector<std::string>();
    py::list temp;
    py::dict names;
    py::object split = py::module::import("re").attr("split");
    py::str desc, name;


    bool result = OB::OBPlugin::ListAsVector("forcefields", NULL, vlist);

    if(!result){
        return py::none();
    }
    for (int i=0; i<vlist.size(); i++){
        desc = py::str(vlist.at(i));
        temp = split("\\s+", desc);
        name = py::str(temp[0]);
        py::slice d = py::slice(py::len(name), py::len(desc), 1);
        names[name] = desc[d].attr("lstrip")();
    }

    return names;
}


// Wrapper class for virtual functions
class pyOBForceField : public OB::OBForceField
{

public:

    using OB::OBForceField::OBForceField;

    OB::OBForceField* MakeNewInstance() {
        PYBIND11_OVERLOAD_PURE( OB::OBForceField*, OBForceField, MakeNewInstance);
    }

    std::string GetUnit() {
        PYBIND11_OVERLOAD_PURE( std::string, OBForceField, GetUnit);
    }

    bool HasAnalyticalGradients() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, HasAnalyticalGradients);
    }

    bool ParseParamFile() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, ParseParamFile);
    }

    bool SetFormalCharges() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, SetFormalCharges);
    }

    bool SetPartialCharges() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, SetPartialCharges);
    }

    bool SetupCalculations() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, SetupCalculations);
    }

    bool SetupPointers() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, SetupPointers);
    }

    bool Energy() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, Energy);
    }

    double E_Bond(bool UNUSED_gradients = true) {
        PYBIND11_OVERLOAD_PURE( double, OBForceField, E_Bond, UNUSED_gradients);
    }

    double E_Angle(bool UNUSED_gradients = true) {
        PYBIND11_OVERLOAD_PURE( double, OBForceField, E_Angle, UNUSED_gradients);
    }

    double E_StrBnd(bool UNUSED_gradients = true) {
        PYBIND11_OVERLOAD_PURE( double, OBForceField, E_StrBnd, UNUSED_gradients);
    }

    double E_Torsion(bool UNUSED_gradients = true) {
        PYBIND11_OVERLOAD_PURE( double, OBForceField, E_Torsion, UNUSED_gradients);
    }

    double E_OOP(bool UNUSED_gradients = true) {
        PYBIND11_OVERLOAD_PURE( double, OBForceField, E_OOP, UNUSED_gradients);
    }

    double E_VDW(bool UNUSED_gradients = true) {
        PYBIND11_OVERLOAD_PURE( double, OBForceField, E_VDW, UNUSED_gradients);
    }

    double E_Electrostatic(bool UNUSED_gradients = true) {
        PYBIND11_OVERLOAD_PURE( double, OBForceField, E_Electrostatic, UNUSED_gradients);
    }

    bool Validate() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, Validate);
    }

    bool ValidateGradients() {
        PYBIND11_OVERLOAD_PURE( bool, OBForceField, ValidateGradients);
    }

};

void wrap_forcefield(pybind11::module &m){

    m.attr("forcefields") = getForceFieldNames();

    py::class_< OB::OBFFConstraints >(m, "OBFFConstraints")
            .def(py::init())
            .def("Clear", &OB::OBFFConstraints::Clear)
            .def("GetConstraintEnergy", &OB::OBFFConstraints::GetConstraintEnergy)
            .def("GetGradient", &OB::OBFFConstraints::GetGradient, py::arg("a"))
            .def("Setup", &OB::OBFFConstraints::Setup, py::arg("mol"))
            .def("SetFactor", &OB::OBFFConstraints::SetFactor, py::arg("factor"))
            .def("AddIgnore", &OB::OBFFConstraints::AddIgnore, py::arg("a"))
            .def("AddAtomConstraint", &OB::OBFFConstraints::AddAtomConstraint, py::arg("a"))
            .def("AddAtomXConstraint", &OB::OBFFConstraints::AddAtomXConstraint, py::arg("a"))
            .def("AddAtomYConstraint", &OB::OBFFConstraints::AddAtomYConstraint, py::arg("a"))
            .def("AddAtomZConstraint", &OB::OBFFConstraints::AddAtomZConstraint, py::arg("a"))
            .def("AddDistanceConstraint", &OB::OBFFConstraints::AddDistanceConstraint, py::arg("a"), py::arg("b"), py::arg("length"))
            .def("AddAngleConstraint", &OB::OBFFConstraints::AddAngleConstraint, py::arg("a"), py::arg("b"), py::arg("c"), py::arg("angle"))
            .def("AddTorsionConstraint", &OB::OBFFConstraints::AddTorsionConstraint,
                 py::arg("a"), py::arg("b"), py::arg("b"), py::arg("d"), py::arg("torsion"))
            .def("DeleteConstraint", &OB::OBFFConstraints::DeleteConstraint, py::arg("index"))
            .def("GetFactor", &OB::OBFFConstraints::GetFactor)
            .def("GetConstraintType", &OB::OBFFConstraints::GetConstraintType, py::arg("index"))
            .def("GetConstraintValue", &OB::OBFFConstraints::GetConstraintValue, py::arg("index"))
            .def("GetConstraintAtomA", &OB::OBFFConstraints::GetConstraintAtomA, py::arg("index"))
            .def("GetConstraintAtomB", &OB::OBFFConstraints::GetConstraintAtomB, py::arg("index"))
            .def("GetConstraintAtomC", &OB::OBFFConstraints::GetConstraintAtomC, py::arg("index"))
            .def("GetConstraintAtomD", &OB::OBFFConstraints::GetConstraintAtomD, py::arg("index"))
            .def("IsIgnored", &OB::OBFFConstraints::IsIgnored, py::arg("a"))
            .def("IsFixed", &OB::OBFFConstraints::IsFixed, py::arg("a"))
            .def("IsXFixed", &OB::OBFFConstraints::IsXFixed, py::arg("a"))
            .def("IsYFixed", &OB::OBFFConstraints::IsYFixed, py::arg("a"))
            .def("IsZFixed", &OB::OBFFConstraints::IsZFixed, py::arg("a"))
            .def("GetIgnoredBitVec", &OB::OBFFConstraints::GetIgnoredBitVec)
            .def("GetFixedBitVec", &OB::OBFFConstraints::GetFixedBitVec)
    ;

    py::class_< OB::OBForceField, pyOBForceField, OB::OBPlugin >(m, "OBForceField")
            //.def_static("Default", &OB::OBForceField::Default)
            .def_static("FindType", &OB::OBForceField::FindType)
            .def("MakeNewInstance", &OB::OBForceField::MakeNewInstance)
            .def_static("FindForceField", (OB::OBForceField* (*)(const std::string&)) &OB::OBForceField::FindForceField,
                        py::return_value_policy::reference)
            .def("SetParameterFile", &OB::OBForceField::SetParameterFile, py::arg("filename"))
            .def("GetUnit", &OB::OBForceField::GetUnit)
            .def("HasAnalyticalGradients", &OB::OBForceField::HasAnalyticalGradients)
            .def("Setup", (bool (OB::OBForceField::*)(OB::OBMol &)) &OB::OBForceField::Setup )
            .def("SetupWithConstraints", (bool (OB::OBForceField::*)(OB::OBMol &, OB::OBFFConstraints &)) &OB::OBForceField::Setup )
            .def("ParseParamFile", &OB::OBForceField::ParseParamFile)
            .def("SetTypes", &OB::OBForceField::SetTypes)
            .def("SetFormalCharges", &OB::OBForceField::SetFormalCharges)
            .def("SetPartialCharges", &OB::OBForceField::SetPartialCharges)
            .def("SetupCalculations", &OB::OBForceField::SetupCalculations)
            .def("SetupPointers", &OB::OBForceField::SetupPointers)
            .def("IsSetupNeeded", &OB::OBForceField::IsSetupNeeded, py::arg("mol"))
            .def("GetAtomTypes", &OB::OBForceField::GetAtomTypes, py::arg("mol"))
            .def("GetCoordinates", &OB::OBForceField::GetCoordinates, py::arg("mol"))
            .def("UpdateCoordinates", &OB::OBForceField::UpdateCoordinates, py::arg("mol"))
            .def("GetConformers", &OB::OBForceField::GetConformers, py::arg("mol"))
            .def("UpdateConformers", &OB::OBForceField::UpdateConformers, py::arg("mol"))
            .def("SetCoordinates", &OB::OBForceField::SetCoordinates, py::arg("mol"))
            .def("SetConformers", &OB::OBForceField::SetConformers, py::arg("mol"))
            // NEED OBGRID .def("OBGridData", &OB::OBForceField::OBGridData)

            //Interacting group
            .def("AddIntraGroup", &OB::OBForceField::AddIntraGroup, py::arg("group"))
            .def("AddInterGroup", &OB::OBForceField::AddInterGroup, py::arg("group"))
            .def("AddInterGroups", &OB::OBForceField::AddInterGroups, py::arg("group1"), py::arg("group2"))
            .def("ClearGroups", &OB::OBForceField::ClearGroups)
            .def("HasGroups", &OB::OBForceField::HasGroups)

            // Cut-off
            .def("EnableCutOff", &OB::OBForceField::EnableCutOff, py::arg("enable"))
            .def("IsCutOffEnabled", &OB::OBForceField::IsCutOffEnabled)
            .def("SetVDWCutOff", &OB::OBForceField::SetVDWCutOff, py::arg("r"))
            .def("GetVDWCutOff", &OB::OBForceField::GetVDWCutOff)
            .def("SetElectrostaticCutOff", &OB::OBForceField::SetElectrostaticCutOff, py::arg("r"))
            .def("GetElectrostaticCutOff", &OB::OBForceField::GetElectrostaticCutOff)
            .def("SetUpdateFrequency", &OB::OBForceField::SetUpdateFrequency, py::arg("f"))
            .def("GetUpdateFrequency", &OB::OBForceField::GetUpdateFrequency)
            .def("UpdatePairsSimple", &OB::OBForceField::UpdatePairsSimple)
            .def("GetNumPairs", &OB::OBForceField::GetNumPairs)
            .def("GetNumElectrostaticPairs", &OB::OBForceField::GetNumElectrostaticPairs)
            .def("GetNumVDWPairs", &OB::OBForceField::GetNumVDWPairs)
            .def("EnableAllPairs", &OB::OBForceField::EnableAllPairs)

            //Energy Evaluation
            .def("Energy", &OB::OBForceField::Energy)
            .def("E_Bond", &OB::OBForceField::E_Bond)
            .def("E_Angle", &OB::OBForceField::E_Angle)
            .def("E_StrBnd", &OB::OBForceField::E_StrBnd)
            .def("E_Torsion", &OB::OBForceField::E_Torsion)
            .def("E_OOP", &OB::OBForceField::E_OOP)
            .def("E_VDW", &OB::OBForceField::E_VDW)
            .def("E_Electrostatic", &OB::OBForceField::E_Electrostatic)

            // Logging
            .def("PrintTypes", &OB::OBForceField::PrintTypes)
            .def("PrintFormalCharges", &OB::OBForceField::PrintFormalCharges)
            .def("PrintPartialCharges", &OB::OBForceField::PrintPartialCharges)
            .def("PrintVelocities", &OB::OBForceField::PrintVelocities)
            //.def("SetLogFile", &OB::OBForceField::SetLogFile)
            .def("SetLogLevel", &OB::OBForceField::SetLogLevel)
            .def("GetLogLevel", &OB::OBForceField::GetLogLevel)
            .def("OBFFLog", (void (OB::OBForceField::*)(std::string)) &OB::OBForceField::OBFFLog, py::arg("msg"))

            //Structure generation
            .def("DistanceGeometry", &OB::OBForceField::DistanceGeometry)
            .def("SystematicRotorSearch", &OB::OBForceField::SystematicRotorSearch,
                 py::arg("geomSteps")=2500, py::arg("sampleRingBonds")=false)
            .def("SystematicRotorSearchInitialize", &OB::OBForceField::SystematicRotorSearchInitialize,
                 py::arg("geomSteps")=2500, py::arg("sampleRingBonds")=false)
            .def("SystematicRotorSearchNextConformer", &OB::OBForceField::SystematicRotorSearchNextConformer,
                 py::arg("geomSteps")=2500)
            .def("RandomRotorSearch", &OB::OBForceField::RandomRotorSearch,
                 py::arg("conformers"), py::arg("geomSteps")=2500, py::arg("sampleRingBonds")=false)
            .def("RandomRotorSearchInitialize", &OB::OBForceField::RandomRotorSearchInitialize,
                 py::arg("conformers"), py::arg("geomSteps")=2500, py::arg("sampleRingBonds")=false)
            .def("RandomRotorSearchNextConformer", &OB::OBForceField::RandomRotorSearchNextConformer,
                 py::arg("geomSteps")=2500)
            .def("WeightedRotorSearch", &OB::OBForceField::WeightedRotorSearch,
                 py::arg("conformers"), py::arg("geomSteps")=2500, py::arg("sampleRingBonds")=false)
            .def("FastRotorSearch", &OB::OBForceField::FastRotorSearch,
                 py::arg("permute")=true)
            .def("SetLineSearchType", &OB::OBForceField::SetLineSearchType,
                 py::arg("type"))
            .def("GetLineSearchType", &OB::OBForceField::GetLineSearchType)
            .def("LineSearch", (OB::vector3 (OB::OBForceField::*)(OB::OBAtom *, OB::vector3 &)) &OB::OBForceField::LineSearch,
                 py::arg("atom"), py::arg("direction"))
            //.def("Newton2NumLineSearch", &OB::OBForceField::Newton2NumLineSearch)
            //.def("LineSearchTakeStep", &OB::OBForceField::LineSearchTakeStep)

            .def("SteepestDescent", &OB::OBForceField::SteepestDescent,
                 py::arg("steps"), py::arg("econv") = 1e-6f, py::arg("method") = OBFF_ANALYTICAL_GRADIENT)
            .def("SteepestDescentInitialize", &OB::OBForceField::SteepestDescentInitialize,
                 py::arg("steps"), py::arg("econv") = 1e-6f, py::arg("method") = OBFF_ANALYTICAL_GRADIENT)
            .def("SteepestDescentTakeNSteps", &OB::OBForceField::SteepestDescentTakeNSteps, py::arg("n"))
            .def("ConjugateGradients", &OB::OBForceField::ConjugateGradients,
                 py::arg("steps"), py::arg("econv") = 1e-6f, py::arg("method") = OBFF_ANALYTICAL_GRADIENT)
            .def("ConjugateGradientsInitialize", &OB::OBForceField::ConjugateGradientsInitialize,
                 py::arg("steps"), py::arg("econv") = 1e-6f, py::arg("method") = OBFF_ANALYTICAL_GRADIENT)
            .def("ConjugateGradientsTakeNSteps", &OB::OBForceField::ConjugateGradientsTakeNSteps, py::arg("n"))

            // Molecular Dynamics
            .def("GenerateVelocities", &OB::OBForceField::GenerateVelocities)
            .def("CorrectVelocities", &OB::OBForceField::CorrectVelocities)
            .def("MolecularDynamicsTakeNSteps", &OB::OBForceField::MolecularDynamicsTakeNSteps,
                 py::arg("steps"), py::arg("Temperature"), py::arg("timestep") = 0.001, py::arg("method") = OBFF_ANALYTICAL_GRADIENT)
            .def("GetConstraints", &OB::OBForceField::GetConstraints)
            .def("SetConstraints", &OB::OBForceField::SetConstraints, py::arg("constraints"))
            .def("SetFixAtom", &OB::OBForceField::SetFixAtom, py::arg("index"))
            .def("UnsetFixAtom", &OB::OBForceField::UnsetFixAtom)
            .def("SetIgnoreAtom", &OB::OBForceField::SetIgnoreAtom)
            .def("UnsetIgnoreAtom", &OB::OBForceField::UnsetIgnoreAtom)

            // Validation
            .def("DetectExplosion", &OB::OBForceField::DetectExplosion)
            .def("ValidateLineSearch", &OB::OBForceField::ValidateLineSearch,
                 py::arg("atom"), py::arg("direction"))
            .def("ValidateSteepestDescent", &OB::OBForceField::ValidateSteepestDescent, py::arg("steps"))
            .def("ValidateConjugateGradients", &OB::OBForceField::ValidateConjugateGradients, py::arg("steps"))
            .def("Validate", &OB::OBForceField::Validate)
            .def("ValidateGradients", &OB::OBForceField::ValidateGradients)
            .def("ValidateGradientError", &OB::OBForceField::ValidateGradientError,
                 py::arg("numgrad"), py::arg("anagrad"))

    ;


    //py::class_< OB::OBForceFieldGaff, OB::OBForceField >(m, "OBForceFieldGaff");

}
