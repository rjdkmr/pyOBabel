#include <pybind11/pybind11.h>

#include <openbabel/atom.h>
#include <openbabel/bond.h>
#include <openbabel/mol.h>
#include <openbabel/residue.h>

#include "pyOBabel.h"

namespace py = pybind11;
namespace OB = OpenBabel;

OB::vector3* GetNewBondVector(OB::OBAtom *atom, double length){
    OB::vector3 *out = new OB::vector3();

    if(atom->GetNewBondVector(*out, length))    {
        return out;
    }
    else{
        std::cout<<"Runtime Warning: Cannot create new bond vector.";
        return nullptr;
    }
}

void wrap_atom(py::module &m) {

    void (OB::OBAtom::*SetTypeOne)(const std::string &) = &OB::OBAtom::SetType;
    void (OB::OBAtom::*SetVectorOne)(const OB::vector3 &) = &OB::OBAtom::SetVector;
    void (OB::OBAtom::*SetVectorTwo)(const double x,const double y,const double z) = &OB::OBAtom::SetVector;
    const OB::vector3& (OB::OBAtom::*GetVectorOne)() const = &OB::OBAtom::GetVector;

    double (OB::OBAtom::*GetDistanceFromIndex)(int index) = &OB::OBAtom::GetDistance;
    double (OB::OBAtom::*GetDistanceFromAtom)(OB::OBAtom*) = &OB::OBAtom::GetDistance;
    double (OB::OBAtom::*GetDistanceFromVector)(OB::vector3* v) = &OB::OBAtom::GetDistance;
    double (OB::OBAtom::*GetAngleBetweenAtoms)(OB::OBAtom *b, OB::OBAtom *c) = &OB::OBAtom::GetAngle;

    double (OB::OBAtom::*GetAngle)(OB::OBAtom *b, OB::OBAtom *c) = &OB::OBAtom::GetAngle;

py::class_< OB::OBAtom, OB::OBBase >(m, "OBAtom")
        .def(py::init())
        .def("Duplicate", &OB::OBAtom::Duplicate)
        .def("Clear", &OB::OBAtom::Clear)
        .def("SetIdx", &OB::OBAtom::SetIdx)
        .def("SetId", &OB::OBAtom::SetId)
        .def("SetHyb", &OB::OBAtom::SetHyb)
        .def("SetAtomicNum", &OB::OBAtom::SetAtomicNum)
        .def("SetIsotope", &OB::OBAtom::SetIsotope)
        .def("SetImplicitHCount", &OB::OBAtom::SetImplicitHCount)
        .def("SetFormalCharge", &OB::OBAtom::SetFormalCharge)
        .def("SetSpinMultiplicity", &OB::OBAtom::SetSpinMultiplicity)
        .def("SetType", SetTypeOne)  //modified
        .def("SetPartialCharge", &OB::OBAtom::SetPartialCharge)
        .def("SetVector", SetVectorOne, py::return_value_policy::reference, py::keep_alive<1, 2>()) //modified
        .def("SetVector", SetVectorTwo) //modified
        .def("SetResidue", &OB::OBAtom::SetResidue, py::return_value_policy::reference, py::keep_alive<1, 2>())
        .def("SetParent", &OB::OBAtom::SetParent, py::return_value_policy::reference, py::keep_alive<2, 1>())
        .def("SetAromatic", &OB::OBAtom::SetAromatic)
        .def("UnsetAromatic", &OB::OBAtom::UnsetAromatic)
        .def("SetClockwiseStereo", &OB::OBAtom::SetClockwiseStereo)
        .def("SetAntiClockwiseStereo", &OB::OBAtom::SetAntiClockwiseStereo)
        .def("SetPositiveStereo",&OB::OBAtom::SetPositiveStereo)
        .def("SetNegativeStereo", &OB::OBAtom::SetNegativeStereo)
        .def("UnsetStereo", &OB::OBAtom::UnsetStereo)
        .def("SetInRing", &OB::OBAtom::SetInRing)
        .def("SetChiral", &OB::OBAtom::SetChiral)

        .def("GetFormalCharge", &OB::OBAtom::GetFormalCharge)
        .def("GetAtomicNum", &OB::OBAtom::GetAtomicNum)
        .def("GetIsotope", &OB::OBAtom::GetIsotope)
        .def("GetSpinMultiplicity", &OB::OBAtom::GetSpinMultiplicity)
        .def("GetAtomicMass", &OB::OBAtom::GetAtomicMass)
        .def("GetExactMass", &OB::OBAtom::GetExactMass)
        .def("GetIdx", &OB::OBAtom::GetIdx)
        .def("GetIndex", &OB::OBAtom::GetIndex)
        .def("GetId", &OB::OBAtom::GetId)
         //.def("GetCoordinateIdx", GetCoordinateIdx)
        .def("GetValence", &OB::OBAtom::GetValence)
        .def("GetHyb", &OB::OBAtom::GetHyb)
        .def("GetImplicitHCount", &OB::OBAtom::GetImplicitHCount)
        .def("GetHvyValence", &OB::OBAtom::GetHvyValence)
        .def("GetHeteroValence", &OB::OBAtom::GetHeteroValence)
        .def("GetType", &OB::OBAtom::GetType)
        .def("GetX", &OB::OBAtom::GetX)
        .def("GetY", &OB::OBAtom::GetY)
        .def("GetZ", &OB::OBAtom::GetZ)
        .def("GetVector", GetVectorOne, py::return_value_policy::reference, py::keep_alive<1, 0>()) //modified
        .def("GetPartialCharge", &OB::OBAtom::GetPartialCharge)
        .def("GetResidue", &OB::OBAtom::GetResidue, py::return_value_policy::reference, py::keep_alive<1, 0>()) //modified
        .def("GetParent", &OB::OBAtom::GetParent, py::return_value_policy::reference_internal, py::keep_alive<0, 1>())
        .def("GetNewBondVector", &GetNewBondVector) //modified
        .def("GetBond", &OB::OBAtom::GetBond, py::return_value_policy::reference, py::keep_alive<1, 0>())
        .def("GetNextAtom", &OB::OBAtom::GetNextAtom, py::return_value_policy::reference, py::keep_alive<1, 0>())

        .def("GetDistanceFromIndex", GetDistanceFromIndex) //modified GetDistance
        .def("GetDistanceFromAtom", GetDistanceFromAtom) //modified GetDistance
        .def("GetDistanceFromVector", GetDistanceFromVector) //modified GetDistance
        .def("GetAngleBetweenAtoms", GetAngleBetweenAtoms) //modified GetDistance
        .def("GetAngle", GetAngle)

        .def("NewResidue", &OB::OBAtom::NewResidue)
        .def("AddResidue", &OB::OBAtom::AddResidue)
        .def("DeleteResidue", &OB::OBAtom::DeleteResidue)
        .def("AddBond", &OB::OBAtom::AddBond, py::return_value_policy::reference, py::keep_alive<1, 2>())
        //.def("InsertBond", &OB::OBAtom::InsertBond)
        //.def("DeleteBond", &OB::OBAtom::DeleteBond)
        .def("ClearBond", &OB::OBAtom::ClearBond)

        .def("HtoMethyl", &OB::OBAtom::HtoMethyl)
        .def("SetHybAndGeom", &OB::OBAtom::SetHybAndGeom)


        .def("CountFreeOxygens", &OB::OBAtom::CountFreeOxygens)
        .def("CountFreeSulfurs", &OB::OBAtom::CountFreeSulfurs)
        .def("ExplicitHydrogenCount", &OB::OBAtom::ExplicitHydrogenCount)
        .def("MemberOfRingCount", &OB::OBAtom::MemberOfRingCount)
        .def("MemberOfRingSize", &OB::OBAtom::MemberOfRingSize)
        .def("CountRingBonds", &OB::OBAtom::CountRingBonds)
        .def("SmallestBondAngle", &OB::OBAtom::SmallestBondAngle)
        .def("AverageBondAngle", &OB::OBAtom::AverageBondAngle)
        .def("BOSum", &OB::OBAtom::BOSum)
        .def("LewisAcidBaseCounts", &OB::OBAtom::LewisAcidBaseCounts)
        .def("HasResidue", &OB::OBAtom::HasResidue)
        .def("IsHetAtom", &OB::OBAtom::IsHetAtom)
        .def("IsAromatic", &OB::OBAtom::IsAromatic)
        .def("IsInRing", &OB::OBAtom::IsInRing)
        .def("IsInRingSize", &OB::OBAtom::IsInRingSize)
        .def("IsHeteroatom", &OB::OBAtom::IsHeteroatom)
        .def("IsConnected", &OB::OBAtom::IsConnected)
        .def("IsOneThree", &OB::OBAtom::IsOneThree)
        .def("IsOneFour", &OB::OBAtom::IsOneFour)
        .def("IsCarboxylOxygen", &OB::OBAtom::IsCarboxylOxygen)
        .def("IsPhosphateOxygen", &OB::OBAtom::IsPhosphateOxygen)
        .def("IsSulfateOxygen", &OB::OBAtom::IsSulfateOxygen)
        .def("IsNitroOxygen", &OB::OBAtom::IsNitroOxygen)
        .def("IsAmideNitrogen", &OB::OBAtom::IsAmideNitrogen)
        .def("IsPolarHydrogen", &OB::OBAtom::IsPolarHydrogen)
        .def("IsNonPolarHydrogen", &OB::OBAtom::IsNonPolarHydrogen)
        .def("IsAromaticNOxide", &OB::OBAtom::IsAromaticNOxide)
        .def("IsChiral", &OB::OBAtom::IsChiral)
        .def("IsAxial", &OB::OBAtom::IsAxial)
        .def("IsClockwise", &OB::OBAtom::IsClockwise)
        .def("IsAntiClockwise", &OB::OBAtom::IsAntiClockwise)
        .def("IsPositiveStereo", &OB::OBAtom::IsPositiveStereo)
        .def("IsNegativeStereo", &OB::OBAtom::IsNegativeStereo)
        .def("HasChiralitySpecified", &OB::OBAtom::HasChiralitySpecified)
        .def("HasChiralVolume", &OB::OBAtom::HasChiralVolume)
        .def("IsHbondAcceptor", &OB::OBAtom::IsHbondAcceptor)
        .def("IsHbondAcceptorSimple", &OB::OBAtom::IsHbondAcceptorSimple)
        .def("IsHbondDonor", &OB::OBAtom::IsHbondDonor)
        .def("IsHbondDonorH", &OB::OBAtom::IsHbondDonorH)
        .def("HasAlphaBetaUnsat", &OB::OBAtom::HasAlphaBetaUnsat)
        .def("HasBondOfOrder", &OB::OBAtom::HasBondOfOrder)
        .def("CountBondsOfOrder", &OB::OBAtom::CountBondsOfOrder)
        .def("HighestBondOrder", &OB::OBAtom::HighestBondOrder)
        .def("HasNonSingleBond", &OB::OBAtom::HasNonSingleBond)
        .def("HasSingleBond", &OB::OBAtom::HasSingleBond)
        .def("HasDoubleBond", &OB::OBAtom::HasDoubleBond)
        .def("HasAromaticBond", &OB::OBAtom::HasAromaticBond)
        .def("MatchesSMARTS", &OB::OBAtom::MatchesSMARTS)
    ;
}
