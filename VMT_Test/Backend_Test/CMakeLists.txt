file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)
include_directories( ${CMAKE_SOURCE_DIR}/src )
set( GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/3rdparty/googletest/googletest/include" "${CMAKE_SOURCE_DIR}/3rdparty/googletest/googlemock/include")

add_compile_options("/std:c++17")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable( "IR_Test"  ${all_files}  )
set_property(TARGET "IR_Test" PROPERTY FOLDER "VMTTest")

target_link_libraries("IR_Test" PRIVATE libIR libIRWriter gtest gmock )
target_include_directories( "IR_Test" PRIVATE ${GTEST_INCLUDE_DIR})

