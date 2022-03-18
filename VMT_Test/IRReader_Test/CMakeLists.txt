file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})
set(PROJECT_NAME "test_ireader")
source_group_by_dir(all_files)


set( GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/3rdparty/googletest/googletest/include" "${CMAKE_SOURCE_DIR}/3rdparty/googletest/googlemock/include")
include_directories( ${CMAKE_SOURCE_DIR}/src )

if(MSVC)
	add_compile_options("/std:c++17")
else()
	add_compile_options("-std=c++17")
endif()
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)


add_executable( ${PROJECT_NAME}  ${all_files}  )
target_include_directories( ${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIR} )
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "VMTTest")
target_link_libraries( ${PROJECT_NAME} libIRReader gtest gmock )


