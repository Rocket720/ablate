add_executable(libraryTests "")
target_link_libraries(libraryTests PUBLIC GTest::gtest GTest::gmock ablateLibrary testingResources CHREST::cppParserTestLibrary)

target_sources(libraryTests
        PRIVATE
        main.cpp
        )

add_subdirectory(parameters)
add_subdirectory(parser)
add_subdirectory(mathFunctions)
add_subdirectory(environment)
add_subdirectory(finiteVolume)
add_subdirectory(finiteElement)
add_subdirectory(particles)
add_subdirectory(eos)
add_subdirectory(domain)
add_subdirectory(utilities)
add_subdirectory(monitors)
add_subdirectory(io)
add_subdirectory(boundarySolver)
add_subdirectory(chemistry)
add_subdirectory(radiation)

gtest_discover_tests(libraryTests
        # set a working directory so your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
        )

# Allow public access to the header files in the directory
target_include_directories(libraryTests PUBLIC ${CMAKE_CURRENT_LIST_DIR})

## Copy all input/output files needed for testing
copy_to_test_directory(${CMAKE_CURRENT_SOURCE_DIR}/outputs)
copy_to_test_directory(${CMAKE_CURRENT_SOURCE_DIR}/inputs)