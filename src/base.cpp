#include <pybind11/pybind11.h>

#include <openbabel/base.h>

// #include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

// redefined here as it was un-named enum under the OBGenericDataType namespace
enum OBGenericDataType {
    //! Unknown data type (default)
    UndefinedData =  OB::OBGenericDataType::UndefinedData,

    //! Arbitrary key/value data, i.e., OBPairData
    PairData = OB::OBGenericDataType::PairData,

    //! Energetics data (e.g., total energy, heat of formation, etc.;
     EnergyData = OB::OBGenericDataType::EnergyData,

    //! Storing text comments (one per molecule, atom, bond, etc.) (for other data, e.g., author, keyword, ... use OBPairData)
     CommentData = OB::OBGenericDataType::CommentData,

    //! Arbitrary information about conformers, i.e., OBConformerData
     ConformerData = OB::OBGenericDataType::ConformerData,

    //! Bond data external to OpenBabel, i.e., OBExternalBond, OBExternalBondData
     ExternalBondData = OB::OBGenericDataType::ExternalBondData,

    //! Information for generating & manipulating rotamers, i.e. OBRotamerList
     RotamerList = OB::OBGenericDataType::RotamerList,

    //! Info. for storing bonds to atoms yet to be added, i.e. OBVirtualBond
     VirtualBondData = OB::OBGenericDataType::VirtualBondData,

    //! Information on rings in a molecule, i.e., OBRingData
     RingData = OB::OBGenericDataType::RingData,

    //! Information about torsion/dihedral angles, i.e., OBTorsionData and OBTorsion
     TorsionData = OB::OBGenericDataType::TorsionData,

    //! Bond angles in a molecule, i.e., OBAngle, OBAngleData
     AngleData = OB::OBGenericDataType::AngleData,

    //! Residue serial numbers
     SerialNums = OB::OBGenericDataType::SerialNums,

    //! Crystallographic unit cell data, i.e., OBUnitCell
     UnitCell = OB::OBGenericDataType::UnitCell,

    //! Spin data, including NMR, atomic and molecular spin, etc.
     SpinData = OB::OBGenericDataType::SpinData,

    //! Arbitrary partial and total charges, dipole moments, etc.
     ChargeData = OB::OBGenericDataType::ChargeData,

    //! Symmetry data -- po and space groups, transforms, etc. i.e., OBSymmetryData
     SymmetryData = OB::OBGenericDataType::SymmetryData,

    //! Arbitrary chiral information (atom, bond, molecule, etc.) i.e., OBChiralData
     ChiralData = OB::OBGenericDataType::ChiralData,

    //! Atomic and molecular occupation data (e.g., for crystal structures)
     OccupationData = OB::OBGenericDataType::OccupationData,

    //! Density (cube) data and surfaces
     DensityData = OB::OBGenericDataType::DensityData,

    //! Electronic levels, redox states, orbitals, etc.
     ElectronicData = OB::OBGenericDataType::ElectronicData,

    //! Vibrational modes, frequencies, etc.
     VibrationData = OB::OBGenericDataType::VibrationData,

    //! Rotational energy information
     RotationData = OB::OBGenericDataType::RotationData,

    //! Nuclear transitions (e.g., decay, capture, fission, fusion;
     NuclearData = OB::OBGenericDataType::NuclearData,

    //! Set Data (a set of OBGenericData)
     SetData = OB::OBGenericDataType::SetData,

    //! Grid Data (e.g., 3D grids of data a.k.a. cubes)
     GridData = OB::OBGenericDataType::GridData,

    //! Vector Data (i.e., one vector like a dipole moment)
     VectorData = OB::OBGenericDataType::VectorData,

    //! Matrix data (i.e., a 3x3 matrix like a rotation or quadrupole moment)
     MatrixData = OB::OBGenericDataType::MatrixData,

    //! Stereochemistry data (see OBStereoBase)
     StereoData = OB::OBGenericDataType::StereoData,

    //! Density of States data (fermi energy and energy vs. density data)
     DOSData = OB::OBGenericDataType::DOSData,

    //! Electronic transition data (e.g., UV/Vis, excitation energies, etc.)
     ElectronicTransitionData = OB::OBGenericDataType::ElectronicTransitionData,

    // space for up to 2^14 more entries...

    //! Custom (user-defined data)
     CustomData0 = OB::OBGenericDataType::CustomData0,
     CustomData1 = OB::OBGenericDataType::CustomData1,
     CustomData2 = OB::OBGenericDataType::CustomData2,
     CustomData3 = OB::OBGenericDataType::CustomData3,
     CustomData4 = OB::OBGenericDataType::CustomData4,
     CustomData5 = OB::OBGenericDataType::CustomData5,
     CustomData6 = OB::OBGenericDataType::CustomData6,
     CustomData7 = OB::OBGenericDataType::CustomData7,
     CustomData8 = OB::OBGenericDataType::CustomData8,
     CustomData9 = OB::OBGenericDataType::CustomData9,
     CustomData10 = OB::OBGenericDataType::CustomData10,
     CustomData11 = OB::OBGenericDataType::CustomData11,
     CustomData12 = OB::OBGenericDataType::CustomData12,
     CustomData13 = OB::OBGenericDataType::CustomData13,
     CustomData14 = OB::OBGenericDataType::CustomData14,
     CustomData15 = OB::OBGenericDataType::CustomData15,
};


class pyOBGenericData : public OB::OBGenericData
{

public:

    using OB::OBGenericData::OBGenericData;
    //pyOBGenericData(const std::string attr, const unsigned int type, const OB::DataOrigin source) : OB::OBGenericData(attr,type,source){}

    const std::string GetAttribute() {
        PYBIND11_OVERLOAD(const std::string, OBGenericData, GetAttribute);
    }

    const std::string GetValue() {
        PYBIND11_OVERLOAD(const std::string, OBGenericData, GetValue);
    }

    OB::DataOrigin GetOrigin() {
        PYBIND11_OVERLOAD(OB::DataOrigin, OBGenericData, GetOrigin);
    }
};



void wrap_base(py::module &m)  {

    m.def("version_OB", OB::OBReleaseVersion, "Return the version of the Open Babel library for feature-detection");

    py::enum_<OBGenericDataType>(m, "OBGenericDataType")
        .value("UndefinedData",  UndefinedData)
        .value("PairData" , PairData)
        .value("EnergyData" , EnergyData)
        .value("CommentData" , CommentData)
        .value("ConformerData" , ConformerData)
        .value("ExternalBondData" , ExternalBondData)
        .value("RotamerList" , RotamerList)
        .value("VirtualBondData" , VirtualBondData)
        .value("RingData" , RingData)
        .value("TorsionData" , TorsionData)
        .value("AngleData" , AngleData)
        .value("SerialNums" , SerialNums)
        .value("UnitCell" , UnitCell)
        .value("SpinData" , SpinData)
        .value("ChargeData" , ChargeData)
        .value("SymmetryData" , SymmetryData)
        .value("ChiralData" , ChiralData)
        .value("OccupationData" , OccupationData)
        .value("DensityData" , DensityData)
        .value("ElectronicData" , ElectronicData)
        .value("VibrationData" , VibrationData)
        .value("RotationData" , RotationData)
        .value("NuclearData" , NuclearData)
        .value("SetData" , SetData)
        .value("GridData" , GridData)
        .value("VectorData" , VectorData)
        .value("MatrixData" , MatrixData)
        .value("StereoData" , StereoData)
        .value("DOSData" , DOSData)
        .value("ElectronicTransitionData" , ElectronicTransitionData)
        .value("CustomData0" , CustomData0)
        .value("CustomData1" , CustomData1)
        .value("CustomData2" , CustomData2)
        .value("CustomData3" , CustomData3)
        .value("CustomData4" , CustomData4)
        .value("CustomData5" , CustomData5)
        .value("CustomData6" , CustomData6)
        .value("CustomData7" , CustomData7)
        .value("CustomData8" , CustomData8)
        .value("CustomData9" , CustomData9)
        .value("CustomData10" , CustomData10)
        .value("CustomData11" , CustomData11)
        .value("CustomData12" , CustomData12)
        .value("CustomData13" , CustomData13)
        .value("CustomData14" , CustomData14)
        .value("CustomData15" , CustomData15)
    ;

    py::enum_<OB::DataOrigin>(m, "DataOrigin")
        .value("any", OB::any)                           //!< Undefined or unspecified (default)
        .value("fileformatInput", OB::fileformatInput)   //!< Read from an input file
        .value("userInput", OB::userInput)               //!< Added by the user
        .value("perceived", OB::perceived)               //!< Perceived by Open Babel library methods
        .value("external", OB::external)                 //!< Added by an external program
        .value("local", OB::local)                       //!< Not for routine external use (e.g. in sdf or cml properties)
     ;




    py::class_< OB::OBGenericData, pyOBGenericData >(m, "OBGenericData")
        .def(py::init< const std::string, const unsigned int, const OB::DataOrigin >(),"Doc string",
             py::arg("attr") = "undefined", py::arg("type")=UndefinedData, py::arg("source")=OB::any
             )
        .def("SetAttribute", &OB::OBGenericData::SetAttribute)
        .def("SetOrigin", &OB::OBGenericData::SetOrigin)
        .def("GetAttribute", &OB::OBGenericData::GetAttribute)
        .def("GetDataType", &OB::OBGenericData::GetDataType)
        .def("GetValue", &OB::OBGenericData::GetValue)
        .def("GetOrigin", &OB::OBGenericData::GetOrigin)
    ;


    bool (OB::OBBase::*HasDataAsName)(const std::string &) = &OB::OBBase::HasData;
    bool (OB::OBBase::*HasDataAsType)(const unsigned int) = &OB::OBBase::HasData;
    void (OB::OBBase::*DeleteDataByType)(const unsigned int) = &OB::OBBase::DeleteData;
    void (OB::OBBase::*DeleteDataByObject)(OB::OBGenericData*) = &OB::OBBase::DeleteData;
    void (OB::OBBase::*DeleteDataByObjectList)(std::vector<OB::OBGenericData*>&) = &OB::OBBase::DeleteData;
    bool (OB::OBBase::*DeleteDataByName)(const std::string &) = &OB::OBBase::DeleteData;
    OB::OBGenericData* (OB::OBBase::*GetDataByType)(const unsigned int) = &OB::OBBase::GetData;
    OB::OBGenericData* (OB::OBBase::*GetDataByName)(const std::string&) = &OB::OBBase::GetData;
    std::vector<OB::OBGenericData*> (OB::OBBase::*GetAllDataByType)(const unsigned int) = &OB::OBBase::GetAllData;
    std::vector<OB::OBGenericData*> &(OB::OBBase::*GetAllData)() = &OB::OBBase::GetData;
    std::vector<OB::OBGenericData*> (OB::OBBase::*GetAllDataByOrigin)(OB::DataOrigin) = &OB::OBBase::GetData;
    py::class_< OB::OBBase >(m, "OBBase")
            .def("HasDataAsName", HasDataAsName)
            .def("HasDataAsType", HasDataAsType)
            .def("DeleteDataByType", DeleteDataByType)
            .def("DeleteDataByObject", DeleteDataByObject)
            .def("DeleteDataByObjectList", DeleteDataByObjectList)
            .def("DeleteDataByName", DeleteDataByName)
            .def("SetData", &OB::OBBase::SetData)
            .def("CloneData", &OB::OBBase::CloneData)
            .def("DataSize", &OB::OBBase::DataSize)
            .def("DeleteDataByType", DeleteDataByType)
            .def("DeleteDataByObject", DeleteDataByObject)
            .def("DeleteDataByObjectList", DeleteDataByObjectList)
            .def("DeleteDataByName", DeleteDataByName)
            .def("GetDataByType", GetDataByType)
            .def("GetDataByName", GetDataByName)
            .def("GetAllDataByType", GetAllDataByType)
            .def("GetAllData", GetAllData)
            .def("GetAllDataByOrigin", GetAllDataByOrigin)

    ;

}
