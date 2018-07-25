#ifndef MOL_DOCS_H
#define MOL_DOCS_H


const char* molDoc = R"f(Molecule Class

The most important class in Open Babel is OBMol, or the molecule class.
The OBMol class is designed to store all the basic information
associated with a molecule, to make manipulations on the connection
table of a molecule facile, and to provide member functions which
automatically perceive information about a molecule. A guided tour
of the OBMol class is a good place to start.

Example
-------

::

    import pyOBabel as ob

    # An OBMol class can be instantiated by
    mol = OBMol()

    conv = ob.OBConversion()
    conv.SetInFormat("MOL2")
    conv.ReadFile(mol, filename)

    # Print index and atomic number
    for atom in mol.atoms:
        print(atom.GetIndex(), atom.GetAtomicNum())

    # Print bond order, first atom index and second atom index
    for bond in mol.bonds:
        print(bond.GetBondOrder(), bond.GetBeginAtom().GetIndex(),
            bond.GetEndAtom().GetIndex())

)f";


const char* propAtomsDoc = R"f(List of the atoms : :class:`OBAtom`.
It yields a read-only list.

Example
-------

::

    # Print index and atomic number
    for atom in mol.atoms:
        print(atom.GetIndex(), atom.GetAtomicNum())


)f";

const char* propBondsDoc = R"f(List of the bonds : :class:`OBBond`.
It yields a read-only list.

Example
-------

::

    # Print bond order, first atom index and second atom index
    for bond in mol.bonds:
        print(bond.GetBondOrder(), bond.GetBeginAtom().GetIndex(),
                bond.GetEndAtom().GetIndex())


)f";

const char* propResiduesDoc = R"f(List of the residues - :class:`OBResidue`.

Example
-------

::

    # Print Residue name
    for residue in mol.residues:
        print(residue.GetName())

)f";

#endif // MOL_DOCS_H
