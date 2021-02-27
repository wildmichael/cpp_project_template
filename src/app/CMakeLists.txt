# add an executable target
add_executable(app${PROJECT_NAME} main.cpp)

set_target_properties(app${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME})

# link the executable against the library
target_link_libraries(app${PROJECT_NAME}
    PRIVATE
        ${PROJECT_NAME}
    )

# install the executable target
install(TARGETS
    app${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT bin
    )
