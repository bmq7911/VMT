file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)
if(MSVC)
add_compile_options("/std:c++17")
else()
add_compile_options("-std=c++17")
endif()
add_library( "libAST" STATIC ${all_files} )
set_property(TARGET "libAST" PROPERTY FOLDER "Frontend")


