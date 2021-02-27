# list of tests
set(TEST_NAMES
    hello_test
    )

# configure Catch2 output format
set(CATCH2_REPORTER_NAME console CACHE STRING "The Catch2 reporter name.")
set_property(CACHE CATCH2_REPORTER_NAME PROPERTY STRINGS compact console junit xml)
if (CATCH2_REPORTER_NAME STREQUAL junit OR CATCH2_REPORTER_NAME STREQUAL xml)
    set(CATCH2_OUTFILE_SUFFIX .xml)
else ()
    set(CATCH2_OUTFILE_SUFFIX .txt)
endif ()

# configure whether to redirect Catch2 output to a file
option(CATCH2_REDIRECT_OUTPUT "Whether to redirect test output to files" OFF)
if (CATCH2_REDIRECT_OUTPUT)
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/out")
endif ()

# build and add tests
foreach (tn IN LISTS TEST_NAMES)
    # build the test
    add_executable(${tn} ${tn}.cpp)
    target_compile_definitions(${tn} PRIVATE -DCATCH_CONFIG_MAIN)
    target_link_libraries(${tn}
        PRIVATE
            ${PROJECT_NAME}
            Catch2::Catch2
        )

    # assemble command line options for the test runner
    set(CATCH2_OPTIONS -r ${CATCH2_REPORTER_NAME})
    if (CATCH2_REDIRECT_OUTPUT)
        list(APPEND CATCH2_OPTIONS -o "${CMAKE_CURRENT_BINARY_DIR}/out/${tn}${CATCH2_OUTFILE_SUFFIX}")
    endif ()

    # add the test
    add_test(NAME ${tn} COMMAND ${tn} ${CATCH2_OPTIONS})
endforeach ()
