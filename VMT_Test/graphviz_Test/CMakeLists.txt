file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})
set(ITERM_NAME "graphviz_Test")
source_group_by_dir(all_files)
include_directories( ${CMAKE_SOURCE_DIR}/src )

add_compile_options("/std:c++17")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable( ${ITERM_NAME}  ${all_files}  )
target_include_directories(${ITERM_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/3rdparty/graphviz-2.50.0/include" )
set( graphviz_lib_path "${CMAKE_SOURCE_DIR}/3rdparty/graphviz-2.50.0/lib")
set( graphviz_lib ${graphviz_lib_path}/cdt.lib 
                  ${graphviz_lib_path}/cgraph.lib 
				  ${graphviz_lib_path}/cgraph++.lib 
				  ${graphviz_lib_path}/gvc.lib 
				  ${graphviz_lib_path}/gvc++.lib 
				  ${graphviz_lib_path}/gvplugin_core.lib 
				  ${graphviz_lib_path}/gvplugin_dot_layout.lib 
				  ${graphviz_lib_path}/gvplugin_gdiplus.lib 
				  ${graphviz_lib_path}/gvplugin_neato_layout.lib 
				  ${graphviz_lib_path}/gvplugin_pango.lib 
				  ${graphviz_lib_path}/pathplan.lib 
				  ${graphviz_lib_path}/xdot.lib )
set_property(TARGET ${ITERM_NAME} PROPERTY FOLDER "VMTTest")
target_link_libraries( ${ITERM_NAME} PRIVATE ${graphviz_lib})


