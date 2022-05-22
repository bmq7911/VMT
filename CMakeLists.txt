# 学习cmake 就是阅读别人的cmake
cmake_minimum_required (VERSION 3.0)
cmake_policy(VERSION 3.0 )
project (VMT)

#1. first to set the required cxx standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)


IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)


if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
	add_compile_options("/wd4267")
	add_compile_options("/wd4819")
	add_compile_options("/MP")
	add_compile_options("/EHsc")
endif(WIN32)

link_directories(${CMAKE_SOURCE_DIR}/libs  ${CMAKE_SOURCE_DIR}/bin )


if(WIN32)
  add_definitions( -D _DEBUG_PERFORMANCE)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set(LIBS ${CMAKE_SOURCE_DIR}/libs/gmock_maind.lib ${CMAKE_SOURCE_DIR}/libs/gmockd.lib ${CMAKE_SOURCE_DIR}/libs/gtest_maind.lib ${CMAKE_SOURCE_DIR}/libs/gtestd.lib  )
#set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Development)
endif(WIN32)

option( UNIT_TEST "Open the vmt unit test" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)    

include_directories( ${CMAKE_SOURCE_DIR}/src )

macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
			#message( STATUS "file" = ${sgbd_file} )
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
			if( ${sgbd_file} MATCHES ".+(.h|.hpp|.inl)$"  )
				source_group(${sgbd_group_name}\\public FILES ${sgbd_file})
			elseif( ${sgbd_file} MATCHES ".+(.c|.cpp)" )
				source_group(${sgbd_group_name}\\private FILES ${sgbd_file})
			else()
				source_group(${sgbd_group_name}\\resource FILES ${sgbd_file})
			endif(${sgbd_file} MATCHES ".+(.h|.hpp|.inl)$" )
			
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

macro(source_group_export_header_to_public header_dir header_files)
    if(MSVC)
        set(sgbd_cur_dir ${header_dir} )
        foreach(sgbd_file ${${header_files}})
			#message( STATUS "file" = ${sgbd_file} )
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
			if( ${sgbd_file} MATCHES ".+(.h|.hpp|.inl)$"  )
				source_group(${sgbd_group_name}\\public FILES ${sgbd_file})
			endif(${sgbd_file} MATCHES ".+(.h|.hpp|.inl)$" )
			
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_export_header_to_public)

add_subdirectory( 3rdpart/googletest )
add_subdirectory( src )
add_subdirectory( VMT_Test )



