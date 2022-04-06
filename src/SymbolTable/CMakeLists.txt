file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)
if(MSVC)
add_compile_options("/std:c++17")
else()
add_compile_options("-std=c++17")
endif() #end if(MSVC)
add_library( "libSymbols" STATIC ${all_files} )
set_property(TARGET "libSymbols" PROPERTY FOLDER "SymbolTable")


