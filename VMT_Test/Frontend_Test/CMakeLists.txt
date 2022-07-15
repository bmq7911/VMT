file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)
include_directories( ${CMAKE_SOURCE_DIR}/src )

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable( "FrontendTest"  ${all_files}  )
set_property(TARGET "FrontendTest" PROPERTY FOLDER "VMTTest")
target_compile_features("FrontendTest" PUBLIC cxx_std_17 )
target_link_libraries("FrontendTest" libDiagnose libAST libParser  libLexer libAST libIR libIRWriter )


