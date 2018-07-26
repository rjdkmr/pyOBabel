

add_library(pyOBabel MODULE 
	                   pyOBabel.cpp
                           base.cpp
                           vector3.cpp vector3.h
                           atom.cpp
                           bond.cpp
                           mol.cpp mol_docs.h
                           residue.cpp
                           obconversion.cpp
                           plugin.cpp
                           bitvec.cpp
                           builder.cpp
                           forcefield.cpp
                           oberror.cpp
           )


target_link_libraries(pyOBabel PUBLIC ${OPENBABEL2_LIBRARIES} PRIVATE pybind11::module)
#set_target_properties(pyOBabel PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
#                                          SUFFIX "${PYTHON_MODULE_EXTENSION}"
#                                          LIBRARY_OUTPUT_DIRECTORY ${OBABEL_PYTHON_OUTPUT_DIRECTORY}
#                     )

set_target_properties(pyOBabel LIBRARY_OUTPUT_DIRECTORY ${OBABEL_PYTHON_OUTPUT_DIRECTORY} )


INSTALL(TARGETS pyOBabel
        LIBRARY DESTINATION ${OBabel_PythonDir}
        COMPONENT python
       )

