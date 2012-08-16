cmake_minimum_required(VERSION 2.8)

#set(SRCS "" CACHE INTERNAL "")
########
# Macro add_module(<module>)
########
macro (add_module)
       
    file(GLOB _tSrcs "${ARGV0}/*.cpp")
    
    message(STATUS "${ARGV0} Sources:")
    foreach(_tSrc ${_tSrcs})
        message(STATUS "   -> ${_tSrc};")
    endforeach()
    list(APPEND SRCS ${_tSrcs})
    
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0}/CMakeLists.txt")
        add_subdirectory(${ARGV0})
    else()
        message(STATUS "        * ${ARGV0} dont have submodules...")
    endif()
endmacro()

############
# Macro "add_sources(<src1> <src2> ...)"
############
macro (add_sources)
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach(_src ${ARGN})
        if (_relPath)
            list (APPEND SRCS "${_relPath}/${_src}")
        else()
            list (APPEND SRCS "${_src}")
        endif()
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()

#########
# Init project Furai!
#########

project(furai)

SET(CMAKE_BUILD_TYPE Debug CACHE STRING "default to debug" FORCE)


#############
# Boost thing :)
# I'm assuming you got the Furai project from the git repo
#############
if(NOT EXISTS ${BOOST_ROOT})
    message(ERROR " BOOST_ROOT_DIR NOT SET")
    if(ANDROID)
	    set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/../external/boost/boost-1_49_0_android" CACHE PATH "Root directory of the patched Boost library")
    elseif(WIN32)
	    set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/../external/boost/boost-1_49_0_windows" CACHE PATH "Root directory of the Boost library")
    endif()
endif()


set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_MULTITHREAD ON)
set(Boost_INCLUDE_DIR "${BOOST_ROOT}/build/include/boost-1_49")
set(Boost_LIBRARY_DIR "${BOOST_ROOT}/build/include/lib")

#find_package(Boost 1.49.0 COMPONENTS date_time filesystem system)
include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIR})
link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIR})

############
# Furai Include!
############
include_directories(${INCLUDE_DIRECTORIES} ${CMAKE_SOURCE_DIR})

add_subdirectory(furai)


