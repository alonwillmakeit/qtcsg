function(qtcsg_check_float_support)
    try_run(
        QTCSG_FLOAT_SUPPORT_RESULT
        QTCSG_FLOAT_SUPPORT_COMPILES
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}/cmake/checkfloatsupport.cpp
        LINK_LIBRARIES Qt::Gui)

    if (NOT QTCSG_FLOAT_SUPPORT_COMPILES)
        message(FATAL_ERROR "Could not compile floating point test")
    endif()

    math(EXPR failed "${QTCSG_FLOAT_SUPPORT_RESULT} & 1")

    if (failed)
        message(FATAL_ERROR "Bad floating point support: Can't calculate vector lengths")
    endif()

    if (QTCSG_FLOAT_SUPPORT_RESULT EQUAL 0)
        add_compile_definitions(QTCSG_USE_QVECTOR3D_NORMALIZED)
    endif()
endfunction()

qtcsg_check_float_support()
