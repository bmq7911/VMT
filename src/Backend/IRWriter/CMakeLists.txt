file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)
add_library( "libIRWriter" STATIC ${all_files} )
target_link_libraries( "libIRWriter" PRIVATE libIR )
set_property(TARGET "libIRWriter" PROPERTY FOLDER "Backend")


