file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})

source_group_by_dir(all_files)
include_directories( ${CMAKE_SOURCE_DIR}/src )
if(MSVC)
add_compile_options("/std:c++17")
else()
add_compile_options("-std=c++17")
endif()
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
#add_executable( "LearnGL"   ${PRIVATE} ${PUBLIC} ${SHADERS} ${GL_PUBLIC} ${GL_PRIVATE} )
add_executable( "Lexer_Test"  ${all_files}  )
set_property(TARGET "Lexer_Test" PROPERTY FOLDER "VMTTest")
target_link_libraries("Lexer_Test" libLexer libParser libSymbols libAST )


