file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)
if(MSVC)
add_compile_options("/std:c++17")
ele()
add_compile_options("-std=c++17")
endif(MSCV)
add_library( "libADT" STATIC ${all_files} )
set_property(TARGET "libADT" PROPERTY FOLDER "ADT")


