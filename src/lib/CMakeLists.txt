# add a library target
add_library(${PROJECT_NAME} SHARED)

# create the DLL export header for the library target
set_target_properties(${PROJECT_NAME} PROPERTIES
    DEFINE_SYMBOL ${PROJECT_NAME_SAN}_EXPORTS)
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    BASE_NAME ${PROJECT_NAME}
    EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}_export.hpp
    )

# headers to be installed
set(PUBLIC_HEADERS
    ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/hello.hpp
    ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}/config.hpp
    ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}_export.hpp
    )

# create a pre-compiled header with commonly used headers that will be
# force-injected into this libraries sources. Other shared library targets can
# reuse this pre-compiled header without rebuilding their own by using
# target_precompiled_headers(otherlib REUSE_FROM ${PROJECT_NAME}).
# do not mark these as INTERFACE or PUBLIC, you don't want to force
# downstream targets (even third-party ones!) to build a precompiled header with
# the headers you thought were useful :-)
target_precompile_headers(${PROJECT_NAME}
    PRIVATE
        "<fmt/format.h>"
        "<iostream>"
        "<ostream>"
        "<sstream>"
        "<string>"
        "<vector>"
    )

# add sources to the library target
target_sources(${PROJECT_NAME}
    PRIVATE
        hello.cpp

        ${PUBLIC_HEADERS}
    )

# mark the public headers for installation
set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS}")

# configure the include paths for the library target
target_include_directories(${PROJECT_NAME}
    # these are only private to this library
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}
    # these will be used by this library and its dependents, however the ones
    # with $<BUILD_INTERFACE:...> are only used during this build and the one
    # with $<INSTALL_INTERFACE:...> will be used once this library is installed.
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

# link the library against its dependencies which will also take care of
# include paths and defines
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        fmt::fmt
        )

# install the library target
install(TARGETS
    ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT dev
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT bin
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT bin
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}" COMPONENT dev
    )
