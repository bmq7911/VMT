file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})


source_group_by_dir(all_files)
add_library( "libIR" STATIC ${all_files} )
set_property(TARGET "libIR" PROPERTY FOLDER "Backend")


