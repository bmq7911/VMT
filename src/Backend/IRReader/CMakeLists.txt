file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})
set(PROJECT_NAME "libIRReader")

source_group_by_dir(all_files)
add_library( ${PROJECT_NAME} STATIC ${all_files} )
target_link_libraries( ${PROJECT_NAME} PRIVATE libIR )
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Backend")


