file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})
set(ITERM_NAME "graphviz_Test")
source_group_by_dir(all_files)
include_directories( ${CMAKE_SOURCE_DIR}/src )

add_compile_options("/std:c++17")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable( ${ITERM_NAME}  ${all_files}  )

set_property(TARGET ${ITERM_NAME} PROPERTY FOLDER "VMTTest")
target_link_libraries( ${ITERM_NAME} PRIVATE ${graphviz_lib} gtest )


