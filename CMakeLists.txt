cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# load project info from vcpkg.json
file(READ vcpkg.json VCPKG_CONFIG_JSON)
string(JSON VCPKG_PROJECT_NAME GET "${VCPKG_CONFIG_JSON}" name)
string(JSON VCPKG_PROJECT_VERSION GET "${VCPKG_CONFIG_JSON}" version-string)
string(JSON VCPKG_PROJECT_DESCRIPTION GET "${VCPKG_CONFIG_JSON}" description)

# configure project
project("${VCPKG_PROJECT_NAME}"
    VERSION "${VCPKG_PROJECT_VERSION}"
    DESCRIPTION "${VCPKG_PROJECT_DESCRIPTION}"
    LANGUAGES CXX
    )

# installation directories
set(CMAKE_INSTALL_DATADIR "share/${PROJECT_NAME}")
include(GNUInstallDirs)

# configure testing
include(CTest)

# find required library dependencies
find_package(fmt CONFIG REQUIRED)
if (BUILD_TESTING)
  find_package(Catch2 CONFIG REQUIRED)
endif ()

# find Doxygen (if availalbe)
find_package(Doxygen)

# set the required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# make sure that symbols are not exported by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# make sure that all runtime files are written to a common bin/ directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# deal with Windows idiosyncracies
if (MSVC)
  set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif ()
if (WIN32)
  # on Windows the min() and max() macros ususally get in the way
  add_compile_definitions(NOMINMAX)
endif ()

# create config.hpp
include(cmake/utils.cmake)
string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_SAN)
string(REGEX REPLACE "[^0-9A-Z]" "_" PROJECT_NAME_SAN "${PROJECT_NAME_SAN}")
make_hex_version(
    PROJECT_VERSION_HEX
    ${CMAKE_PROJECT_VERSION_MAJOR}
    ${CMAKE_PROJECT_VERSION_MINOR}
    ${CMAKE_PROJECT_VERSION_PATCH})
configure_file(include/myproject/config.hpp.in include/myproject/config.hpp @ONLY)

# build the source
add_subdirectory(src)

# build the tests
if (BUILD_TESTING)
  add_subdirectory(test)
endif ()

# configure the docs
if (DOXYGEN_FOUND)
  set(DOXYGEN_EXTRACT_PRIVATE NO)
  set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
  set(DOXYGEN_FULL_PATH_NAMES YES)
  set(DOXYGEN_STRIP_FROM_PATH
    "${CMAKE_BINARY_DIR}/include"
    "${CMAKE_SOURCE_DIR}/include")
  doxygen_add_docs(doc
      "${CMAKE_BINARY_DIR}/include"
      "${CMAKE_SOURCE_DIR}/include"
      "${CMAKE_SOURCE_DIR}/src"
      ALL
      )
  install(DIRECTORY
    "${CMAKE_BINARY_DIR}/html"
    TYPE DOC
    COMPONENT doc
    EXCLUDE_FROM_ALL)
endif ()

# create package configuration
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/package-config.cmake.in "${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}"
  PATH_VARS
    CMAKE_INSTALL_INCLUDEDIR
    CMAKE_INSTALL_LIBDIR
  )

write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY SameMajorVersion)

# install package configuration
install(FILES
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    TYPE DATA
    COMPONENT dev
    )

# install exported targets
install(EXPORT ${PROJECT_NAME}-targets
    DESTINATION "${CMAKE_INSTALL_DATADIR}"
    NAMESPACE ${PROJECT_NAME_SAN}::
    COMPONENT dev)
