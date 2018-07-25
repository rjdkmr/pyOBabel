macro(make_python_extension)
  PARSE_ARGUMENTS(OBPY
    "LINK_LIBRARIES;DEPENDS;DEST"
    ""
    ${ARGN})
CAR(OBPY_NAME ${OBPY_DEFAULT_ARGS})
CDR(OBPY_SOURCES ${OBPY_DEFAULT_ARGS})

    PYTHON_ADD_MODULE(${OBPY_NAME} ${OBPY_SOURCES})
    set_target_properties(${OBPY_NAME} PROPERTIES PREFIX "")
if(WIN32)
    set_target_properties(${OBPY_NAME} PROPERTIES SUFFIX ".pyd"
                          LIBRARY_OUTPUT_DIRECTORY
                          ${OBABEL_PYTHON_OUTPUT_DIRECTORY}/${OBPY_DEST})
else(WIN32)
    set_target_properties(${OBPY_NAME} PROPERTIES
                          LIBRARY_OUTPUT_DIRECTORY
                          ${OBABEL_PYTHON_OUTPUT_DIRECTORY}/${OBPY_DEST})
endif(WIN32)
    target_link_libraries(${OBPY_NAME} ${OBPY_LINK_LIBRARIES}
                          ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} )

    INSTALL(TARGETS ${OBPY_NAME}
            LIBRARY DESTINATION ${OBabel_PythonDir}/${OBPY_DEST} COMPONENT python)

endmacro(make_python_extension)

