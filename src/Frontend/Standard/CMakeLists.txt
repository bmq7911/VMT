
file(GLOB_RECURSE project_headers *.h *.hpp *.inl *.def)
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)


include_directories( ${CMAKE_SOURCE_DIR}/src )


add_library( "libStandard" STATIC ${all_files}  )
set_property(TARGET "libStandard" PROPERTY FOLDER "Frontend")
target_link_libraries("libStandard" libADT )


