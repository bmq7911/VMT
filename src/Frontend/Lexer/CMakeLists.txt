
file(GLOB_RECURSE project_headers *.h *.hpp *.inl *.def)
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)


include_directories( ${CMAKE_SOURCE_DIR}/src )
if (MSVC)
add_compile_options("/std:c++17")
else()
add_compile_options("-std=c++17")
endif()
add_library( "libLexer" STATIC ${all_files}  )
set_property(TARGET "libLexer" PROPERTY FOLDER "Frontend")
target_link_libraries("libLexer" libADT )


