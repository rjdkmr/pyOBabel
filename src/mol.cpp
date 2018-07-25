#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <openbabel/mol.h>
#include <openbabel/atom.h>
#include <openbabel/bond.h>
#include <openbabel/residue.h>

#include "pyOBabel.h"
#include "mol_docs.h"

namespace py = pybind11;
namespace OB = OpenBabel;

/* Not Implemented
 * FindChildren
 */

// Get python-list of all bonds, added as a OBMol property
py::list getBonds(OB::OBMol *mol){
    py::list list;
    for(OB::OBBondIterator at = mol->BeginBonds(); at != mol->EndBonds(); ++at) {
        list.append(*at);
    }
    return list;
}

// Get python-list of all atoms, added as a OBMol property
py::list getAtoms(OB::OBMol *mol){
    py::list list;
    for(OB::OBAtomIterator at = mol->BeginAtoms(); at != mol->EndAtoms(); ++at) {
        list.append(*at);
    }
    return list;
}

// Get python-list of all residues, added as a OBMol property
py::list getResidues(OB::OBMol *mol){
    py::list list;
    for(OB::OBResidueIterator at = mol->BeginResidues(); at != mol->EndResidues(); ++at) {
        list.append(*at);
    }
    return list;
}

// GetCoordinates as a 2D list
py::list GetCoordinates(OB::OBMol *mol) {
    py::list OuterList;
    double *c = mol->GetCoordinates();
    int n = mol->NumAtoms()*3, i=0;
    while(i<n){
        py::list InnerList;
        for(int j=0; j<3; j++) {
            InnerList.append(c[i+j]);
        }
        OuterList.append(InnerList);
        i = i+3;
    }
    return OuterList;
}

// SetCoordinates by a 2D list
void SetCoordinates(OB::OBMol *mol, py::list coords) {
    // First check if the argument is of desried class
    if(!py::isinstance(coords, py::module::import("builtins").attr("list")))   {
        py::print("WARNING: Failed to set the coords. coords is not a python list.");
        return;
    }

    double *c = new double[mol->NumAtoms()*3];

    std::cout<<coords.size()<<"\n";
    if (coords.size() != mol->NumAtoms()) {
        std::cout<<"SetCoordinates: Number of atoms does not match /"
                   "with number of coordinates\n";
        delete c;
        return;
    }

    for(int i=0; i<coords.size(); i++) {
        py::list InnerList = coords[i];
        for(int j=0; j<3; j++) {
            c[(i*3)+j] = py::float_(InnerList[j]);
        }

    }
    mol->SetCoordinates(c);
}

// Set Several conformer coordinates by a 3D list[nconf][natoms][3]
void SetConformers(OB::OBMol *mol, py::list confsCoords) {
    // First check if the argument is of desried class
    if(!py::isinstance(confsCoords, py::module::import("builtins").attr("list")))   {
        py::print("WARNING: Failed to set the confsCoords. confsCoords is not a python list.");
        return;
    }

    std::vector<double*> v;
    int n = mol->NumAtoms()*3;

    for(size_t conf=0; conf<confsCoords.size(); conf++)   {
        double *c = new double[mol->NumAtoms()*3];
        py::list coords = confsCoords[conf];
        int i = 0;

        if (coords.size() != mol->NumAtoms()) {
            std::cout<<"SetConformers: Number of atoms does not match /"
                       "with number of coordinates\n";
            delete c;
            return;
        }

        for(int i=0; i<coords.size(); i++) {
            py::list InnerList = coords[i];
            for(int j=0; j<3; j++) {
                c[(i*3)+j] = py::float_(InnerList[j]);
            }
        }
        v.push_back(c);
    }
    mol->SetConformers(v);
}

// Set Several conformer coordinates by a 3D list[nconf][natoms][3]
py::list GetConformers(OB::OBMol *mol) {
    std::vector<double*> v = mol->GetConformers();
    int n = mol->NumAtoms()*3;
    py::list confsCoords;

    for(int conf=0; conf<(int)v.size(); conf++)   {
        double *c = v[conf];
        py::list coords;
        int i = 0;

        while(i<n){
            py::list InnerList;
            for(int j=0; j<3; j++) {
                InnerList.append(c[i+j]);
            }
            i = i+3;
            coords.append(InnerList);
        }
        confsCoords.append(coords);
    }
    return confsCoords;
}

// Add conformer coordinates as a 2D list[natoms][3]
void AddConformer(OB::OBMol *mol, py::list coords) {
    // First check if the argument is of desried class
    if(!py::isinstance(coords, py::module::import("builtins").attr("list")))   {
        py::print("WARNING: Failed to set the coords. coords is not a python list.");
        return;
    }

    double *c = new double[mol->NumAtoms()*3];

    if (coords.size() != mol->NumAtoms()) {
        std::cout<<"AddConformer: Number of atoms does not match /"
                   "with number of coordinates\n";
        delete c;
        return;
    }

    for(int i=0; i<coords.size(); i++) {
        py::list InnerList = coords[i];
        for(int j=0; j<3; j++) {
            c[(i*3)+j] = py::float_(InnerList[j]);
        }
    }
    mol->AddConformer(c);
}

// Get conformer coordinates as a 2D list[natoms][3]
py::list GetConformer(OB::OBMol *mol, int nconf) {
    py::list OuterList;
    double *c = mol->GetConformer(nconf);
    int n = mol->NumAtoms()*3, i=0;
    while(i<n){
        py::list InnerList;
        for(int j=0; j<3; j++) {
            InnerList.append(c[i+j]);
        }
        OuterList.append(InnerList);
        i = i+3;
    }
    return OuterList;
}

// Get current conformer number
int GetConformerNumber(OB::OBMol *mol) {
    std::vector<double*> v = mol->GetConformers();
    double *c = mol->GetCoordinates(); // Get current coordinates
    int conformerNumber;
    for(int a = 0; a < v.size(); a++){
        if (v.at(a) == c){
            conformerNumber = a;
            break;
        }
    }
    return conformerNumber;
}



//
OB::OBMol* copy(OB::OBMol *mol) {
    OB::OBMol *newMol = new OB::OBMol(*mol);
    return newMol;
}


// Wrapper class for virtual functions
class pyOBMol : public OB::OBMol
{

public:

    using OB::OBMol::OBMol;

    void BeginModify() {
        PYBIND11_OVERLOAD( void, OBMol, BeginModify);
    }

    void EndModify() {
        PYBIND11_OVERLOAD( void, OBMol, EndModify);
    }

};


void wrap_mol(py::module &m) {

    py::enum_<OB::HydrogenType>(m, "HydrogenType")
            .value("AllHydrogen", OB::HydrogenType::AllHydrogen)
            .value("PolarHydrogen", OB::HydrogenType::PolarHydrogen)
            .value("NonPolarHydrogen", OB::HydrogenType::NonPolarHydrogen)
    ;

    bool (OB::OBMol::*AddBondBetweenAtoms)(int,int,int,int,int) = &OB::OBMol::AddBond;
    bool (OB::OBMol::*AddBond)(OB::OBBond&) = &OB::OBMol::AddBond;

    OB::OBAtom* (OB::OBMol::*NewAtom)() = &OB::OBMol::NewAtom;
    OB::OBAtom* (OB::OBMol::*NewAtomById)(unsigned long) = &OB::OBMol::NewAtom;

    OB::OBBond* (OB::OBMol::*NewBond)() = &OB::OBMol::NewBond;
    OB::OBBond* (OB::OBMol::*NewBondById)(unsigned long) = &OB::OBMol::NewBond;

    double (OB::OBMol::*GetTorsionByIndex)(int,int,int,int) = &OB::OBMol::GetTorsion;
    double (OB::OBMol::*GetTorsionByAtoms)(OB::OBAtom*, OB::OBAtom*,OB::OBAtom*,OB::OBAtom*) = &OB::OBMol::GetTorsion;

    void (OB::OBMol::*RenumberAtomsByAtoms)(std::vector<OB::OBAtom*>&) = &OB::OBMol::RenumberAtoms;
    void (OB::OBMol::*RenumberAtomsByIndex)(std::vector<int>) = &OB::OBMol::RenumberAtoms;

    py::class_<OB::OBMol, pyOBMol, OB::OBBase >(m, "OBMol", molDoc)
            .def(py::init())
            .def("copy", &copy) // only default virtual function might work

            // Some properties added for convinence
            .def_property_readonly("atoms", &getAtoms, propAtomsDoc)
            .def_property_readonly("bonds", &getBonds, propBondsDoc)
            .def_property_readonly("residues", &getResidues, propResiduesDoc)
            .def_property("coordinates", &GetCoordinates, &SetCoordinates)
            .def_property("conformer", &GetConformerNumber, &OB::OBMol::SetConformer)

            .def("ReserveAtoms", &OB::OBMol::ReserveAtoms)
            .def("AddAtom", &OB::OBMol::AddAtom,
                 py::arg("atom"), py::arg("forceNewId")=false)
            .def("InsertAtom", &OB::OBMol::InsertAtom)
            .def("AddBondBetweenAtoms", AddBondBetweenAtoms,
                  py::arg("beginIdx"), py::arg("endIdx"), py::arg("order"),
                  py::arg("flags")=0, py::arg("insertpos")=-1
                 )
            .def("AddBond", AddBond)
            .def("AddResidue", &OB::OBMol::AddResidue)
            .def("NewAtom", NewAtom, py::return_value_policy::reference, py::keep_alive<1, 0>())
            .def("NewAtomById", NewAtomById, py::return_value_policy::reference, py::keep_alive<1, 0>())
            .def("NewBond",NewBond, py::return_value_policy::reference, py::keep_alive<1, 0>())
            .def("NewBondById", NewBondById, py::return_value_policy::reference, py::keep_alive<1, 0>())
            .def("NewResidue", &OB::OBMol::NewResidue, py::return_value_policy::reference, py::keep_alive<1, 0>())
            .def("DeleteAtom", &OB::OBMol::DeleteAtom,
                 py::arg("atom"), py::arg("destroyAtom")=false )
            .def("DeleteBond", &OB::OBMol::DeleteBond,
                 py::arg("bond"), py::arg("destroyBond")=false)
            .def("DeleteResidue", &OB::OBMol::DeleteResidue,
                 py::arg("residue"), py::arg("destroyResidue")=false)

             //Molecule modification methods
            .def("BeginModify", &OB::OBMol::BeginModify)
            .def("EndModify", &OB::OBMol::EndModify, py::arg("nukePerceivedData")=true)

             //Data retrieval methods
            .def("GetTitle", &OB::OBMol::GetTitle, py::arg("replaceNewlines") = true)
            .def("NumAtoms", &OB::OBMol::NumAtoms)
            .def("NumBonds", &OB::OBMol::NumBonds)
            .def("NumHvyAtoms", &OB::OBMol::NumHvyAtoms)
            .def("NumResidues", &OB::OBMol::NumResidues)
            .def("NumRotors", &OB::OBMol::NumRotors, py::arg("sampleRingBonds") = false)
            .def("GetTorsionByIndex", GetTorsionByIndex)
            .def("GetTorsionByAtoms", GetTorsionByAtoms)
            .def("GetAngle", &OB::OBMol::GetAngle)
            .def("AreInSameRing", &OB::OBMol::AreInSameRing)
            .def("GetFormula", &OB::OBMol::GetFormula)
            .def("GetSpacedFormula", &OB::OBMol::GetSpacedFormula, py::arg("ones")=0, py::arg("sp")=" ", py::arg("implicitH") = true)
            .def("GetHeatFormation", (double (OB::OBMol::*)()const) &OB::OBMol::GetEnergy) // GetEnergy()
            .def("GetMolWt", &OB::OBMol::GetMolWt, py::arg("implicitH")=true)
            .def("GetExactMass", &OB::OBMol::GetExactMass)
            .def("GetTotalCharge", &OB::OBMol::GetTotalCharge)
            .def("GetTotalSpinMultiplicity", &OB::OBMol::GetTotalSpinMultiplicity)
            .def("GetDimension", &OB::OBMol::GetDimension)
            .def("GetCoordinates", &GetCoordinates) //modified above
             // Need OBRing .def("GetSSSR", &OB::OBMol::GetSSSR)
             // NEED OBRing .def("GetLSSR", &OB::OBMol::GetLSSR)
            .def("AutomaticFormalCharge", &OB::OBMol::AutomaticFormalCharge)
            .def("AutomaticPartialCharge", &OB::OBMol::AutomaticPartialCharge)

            //Data modification methods
            .def("SetTitle", (void (OB::OBMol::*)(std::string &)) &OB::OBMol::SetTitle)
            .def("SetFormula", &OB::OBMol::SetFormula)
            .def("SetHeatFormation", &OB::OBMol::SetEnergy)
            .def("SetDimension", &OB::OBMol::SetDimension)
            .def("SetTotalCharge", &OB::OBMol::SetTotalCharge)
            .def("SetTotalSpinMultiplicity", &OB::OBMol::SetTotalSpinMultiplicity)
            //NEED OBInternalCoord .def("SetInternalCoord", &OB::OBMol::SetInternalCoord)
            .def("SetAutomaticFormalCharge", &OB::OBMol::SetAutomaticFormalCharge)
            .def("SetAutomaticPartialCharge", &OB::OBMol::SetAutomaticPartialCharge)

            .def("SetAromaticPerceived", &OB::OBMol::SetAromaticPerceived)
            .def("SetSSSRPerceived", &OB::OBMol::SetSSSRPerceived)
            .def("SetLSSRPerceived", &OB::OBMol::SetLSSRPerceived)
            .def("SetRingAtomsAndBondsPerceived", &OB::OBMol::SetRingAtomsAndBondsPerceived)
            .def("SetAtomTypesPerceived", &OB::OBMol::SetAtomTypesPerceived)
            .def("SetRingTypesPerceived", &OB::OBMol::SetRingTypesPerceived)
            .def("SetChainsPerceived", &OB::OBMol::SetChainsPerceived)
            .def("SetChiralityPerceived", &OB::OBMol::SetChiralityPerceived)
            .def("SetPartialChargesPerceived", &OB::OBMol::SetPartialChargesPerceived)
            .def("SetHybridizationPerceived", &OB::OBMol::SetHybridizationPerceived)
            .def("SetClosureBondsPerceived", &OB::OBMol::SetClosureBondsPerceived)
            .def("SetHydrogensAdded", &OB::OBMol::SetHydrogensAdded)
            .def("SetCorrectedForPH", &OB::OBMol::SetCorrectedForPH)
            .def("SetSpinMultiplicityAssigned", &OB::OBMol::SetSpinMultiplicityAssigned)
            .def("SetFlags", &OB::OBMol::SetFlags)

            .def("UnsetAromaticPerceived", &OB::OBMol::UnsetAromaticPerceived)
            .def("UnsetSSSRPerceived", &OB::OBMol::UnsetSSSRPerceived)
            .def("UnsetLSSRPerceived", &OB::OBMol::UnsetLSSRPerceived)
            .def("UnsetRingTypesPerceived", &OB::OBMol::UnsetRingTypesPerceived)
            .def("UnsetPartialChargesPerceived", &OB::OBMol::UnsetPartialChargesPerceived)
            .def("UnsetHydrogensAdded", &OB::OBMol::UnsetHydrogensAdded)
            .def("UnsetFlag", &OB::OBMol::UnsetFlag)

             //Molecule modification methods
            .def("Clear", &OB::OBMol::Clear)
            .def("RenumberAtomsByAtoms", RenumberAtomsByAtoms)
            .def("RenumberAtomsByIndex", RenumberAtomsByIndex)
            .def("SetCoordinates", &SetCoordinates)  //modified above
            .def("ToInertialFrameForOneConformer", (void (OB::OBMol::*)(int,double*)) &OB::OBMol::ToInertialFrame)
            .def("ToInertialFrameForAllConformers", (void (OB::OBMol::*)()) &OB::OBMol::ToInertialFrame)
            .def("TranslateAllConformers", (void (OB::OBMol::*)(const OB::vector3 &)) &OB::OBMol::Translate)
            .def("TranslateOneConformer", (void (OB::OBMol::*)(const OB::vector3 &, int)) &OB::OBMol::Translate)
             //.def("Rotate", &OB::OBMol::Rotate)
             //.def("Rotate", &OB::OBMol::Rotate)
             //.def("Rotate", &OB::OBMol::Rotate)
            .def("Center", (void (OB::OBMol::*)()) &OB::OBMol::Center)
            .def("DeleteHydrogensAll", (bool (OB::OBMol::*)()) &OB::OBMol::DeleteHydrogens)
            .def("DeleteHydrogensFromAtom", (bool (OB::OBMol::*)(OB::OBAtom*)) &OB::OBMol::DeleteHydrogens)
            .def("DeletePolarHydrogens", &OB::OBMol::DeletePolarHydrogens)
            .def("DeleteNonPolarHydrogens", &OB::OBMol::DeleteNonPolarHydrogens)
            .def("DeleteHydrogen", &OB::OBMol::DeleteHydrogen)
            .def("AddHydrogens", (bool (OB::OBMol::*)(bool,bool,double)) &OB::OBMol::AddHydrogens,
                 py::arg("polaronly")=false,py::arg("correctForPH")=false, py::arg("pH")=7.4)
            .def("AddHydrogens", (bool (OB::OBMol::*)(OB::OBAtom*)) &OB::OBMol::AddHydrogens)
            .def("AddPolarHydrogens", &OB::OBMol::AddPolarHydrogens)
            .def("AddNonPolarHydrogens", &OB::OBMol::AddNonPolarHydrogens)
            .def("AddNewHydrogens", &OB::OBMol::AddNewHydrogens,
                 py::arg("whichHydrogen"), py::arg("correctForPH")=false, py::arg("pH")=7.4)
            .def("StripSalts", &OB::OBMol::StripSalts, py::arg("threshold")=0)
            .def("Separate", &OB::OBMol::Separate, py::arg("StartIndex")=1)
            .def("ConvertDativeBonds", &OB::OBMol::ConvertDativeBonds)
            .def("MakeDativeBonds", &OB::OBMol::MakeDativeBonds)
            .def("ConvertZeroBonds", &OB::OBMol::ConvertZeroBonds)
            .def("CorrectForPH", &OB::OBMol::CorrectForPH, py::arg("pH")=7.4)
            .def("AssignSpinMultiplicity", &OB::OBMol::AssignSpinMultiplicity,
                 py::arg("NoImplicitH")=false)
            .def("AssignTotalChargeToAtoms", &OB::OBMol::AssignTotalChargeToAtoms)
            .def("SetIsPatternStructure", &OB::OBMol::SetIsPatternStructure)
            .def("CenterOfConformer", (OB::vector3 (OB::OBMol::*)(int)) &OB::OBMol::Center)
            .def("SetTorsion", &OB::OBMol::SetTorsion)
            .def("FindSSSR", &OB::OBMol::FindSSSR)
            .def("FindLSSR", &OB::OBMol::FindLSSR)
            .def("FindRingAtomsAndBonds", &OB::OBMol::FindRingAtomsAndBonds)
            .def("FindChiralCenters", &OB::OBMol::FindChiralCenters)
            // NEED OBBitVec .def("FindLargestFragment", &OB::OBMol::FindLargestFragment)
            .def("ContigFragList", &OB::OBMol::ContigFragList)
            .def("Align", &OB::OBMol::Align)
            .def("ConnectTheDots", &OB::OBMol::ConnectTheDots)
            .def("PerceiveBondOrders", &OB::OBMol::PerceiveBondOrders)
            .def("FindAngles", &OB::OBMol::FindAngles)
            .def("FindTorsions", &OB::OBMol::FindTorsions)
             // Result by argument .def("GetGTDVector", &OB::OBMol::GetGTDVector)
             // Result by argument .def("GetGIVector", &OB::OBMol::GetGIVector)
             // Result by argument .def("GetGIDVector", &OB::OBMol::GetGIDVector)

            // Methods to check for existence of properties
            .def("Has2D", &OB::OBMol::Has2D, py::arg("Not3D")=false)
            .def("Has3D", &OB::OBMol::Has3D)
            .def("HasNonZeroCoords", &OB::OBMol::HasNonZeroCoords)
            .def("HasAromaticPerceived", &OB::OBMol::HasAromaticPerceived)
            .def("HasSSSRPerceived", &OB::OBMol::HasSSSRPerceived)
            .def("HasLSSRPerceived", &OB::OBMol::HasLSSRPerceived)
            .def("HasRingAtomsAndBondsPerceived", &OB::OBMol::HasRingAtomsAndBondsPerceived)
            .def("HasAtomTypesPerceived", &OB::OBMol::HasAtomTypesPerceived)
            .def("HasRingTypesPerceived", &OB::OBMol::HasRingTypesPerceived)
            .def("HasChiralityPerceived", &OB::OBMol::HasChiralityPerceived)
            .def("HasPartialChargesPerceived", &OB::OBMol::HasPartialChargesPerceived)
            .def("HasHybridizationPerceived", &OB::OBMol::HasHybridizationPerceived)
            .def("HasClosureBondsPerceived", &OB::OBMol::HasClosureBondsPerceived)
            .def("HasChainsPerceived", &OB::OBMol::HasChainsPerceived)
            .def("HasHydrogensAdded", &OB::OBMol::HasHydrogensAdded)
            .def("IsCorrectedForPH", &OB::OBMol::IsCorrectedForPH)
            .def("HasSpinMultiplicityAssigned", &OB::OBMol::HasSpinMultiplicityAssigned)
            .def("IsChiral", &OB::OBMol::IsChiral)
            .def("Empty", &OB::OBMol::Empty)

            // Multiple conformer member functions
            .def("NumConformers", &OB::OBMol::NumConformers)
            .def("SetConformersCoords", &SetConformers) //modified above
            .def("AddConformerCoords", &AddConformer) //modified above
            .def("SetConformerByIndex", &OB::OBMol::SetConformer)
            // argument is a double array .def("CopyConformer", &OB::OBMol::CopyConformer)
            .def("DeleteConformerByIndex", &OB::OBMol::DeleteConformer)
            .def("GetConformerCoordsByIndex", &GetConformer) //modified above
            .def("SetConformerEnergies", &OB::OBMol::SetEnergies)
            .def("GetConformerEnergies", &OB::OBMol::GetEnergies)
            .def("GetConformerEnergy", (double (OB::OBMol::*)(int)) &OB::OBMol::GetEnergy)
            .def("GetConformersAllCoords", &GetConformers);
    ;
}
