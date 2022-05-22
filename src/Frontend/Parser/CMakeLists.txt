

file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)

include_directories( ${CMAKE_SOURCE_DIR}/src )

add_library( "libParser" STATIC ${all_files} )
target_link_libraries( "libParser" PRIVATE libSymbols libDiagnose )
set_property(TARGET "libParser" PROPERTY FOLDER "Frontend")


