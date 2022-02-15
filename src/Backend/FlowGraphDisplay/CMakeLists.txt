file(GLOB_RECURSE project_headers *.h *.hpp *.inl )
file(GLOB_RECURSE project_cpps *.cpp *.c )
set(all_files ${project_headers} ${project_cpps})
set( ITERM_NAME "libFlowGraphDisplay")
source_group_by_dir(all_files)
add_compile_options("/std:c++17")
add_library( ${ITERM_NAME} STATIC ${all_files} )
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
target_link_libraries( "libFlowGraphDisplay" PRIVATE libIR ${graphviz_lib})

set_property(TARGET "libFlowGraphDisplay" PROPERTY FOLDER "Backend")


