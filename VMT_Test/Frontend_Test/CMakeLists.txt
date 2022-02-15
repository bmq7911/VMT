



file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)


include_directories( ${CMAKE_SOURCE_DIR}/src )



add_compile_options("/std:c++17")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
#add_executable( "LearnGL"   ${PRIVATE} ${PUBLIC} ${SHADERS} ${GL_PUBLIC} ${GL_PRIVATE} )

add_executable( "FrontendTest"  ${all_files}  )
set_property(TARGET "FrontendTest" PROPERTY FOLDER "VMTTest")
target_link_libraries("FrontendTest" libAST libLexer libParser libSymbols)


