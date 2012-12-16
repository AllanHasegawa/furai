cmake_minimum_required(VERSION 2.8)

#######
# SRCS is a GLOBAL variable holding a list of all sources
# to be compiled :)
#
# Since the compilation is inside each "backend" dir,
# the sources are relative to that!
#######
set(SRCS "" CACHE INTERNAL "")


########
# Macro add_module(<module>)
#
# not gonna use it =/
# the "file(GLOB" thing only works for new/deleted files
# when a CMakeLists.txt file is changed. If you dont change
# it, no new/deleted sources will be processed. Kinda annoying!
########
macro (add_module)
       
    file(GLOB _tSrcs "${ARGV0}/*.cpp")
    
    message(STATUS "${ARGV0} Sources:")
    foreach(_tSrc ${_tSrcs})
        message(STATUS "   -> ${_tSrc};")
    endforeach()
    
    list(APPEND SRCS ${_tSrcs})
    
    set(SRCS ${SRCS} CACHE INTERNAL "")
    
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0}/CMakeLists.txt")
        add_subdirectory(${ARGV0})
    else()
        message(STATUS "        * ${ARGV0} dont have submodules...")
    endif()
endmacro()

############
# Macro "add_sources(<src1> <src2> ...)"
#
# call this method inside the source directory, with it,
# relative to that directory :)
############
macro (add_sources)
    file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} _nativePath)
    
    foreach(_src ${ARGN})
        list (APPEND SRCS "${_nativePath}/${_src}")
    endforeach()
    
    set (SRCS ${SRCS} CACHE INTERNAL "")
endmacro()

#########
# Init project Furai!
#########

project(furai)

SET(CMAKE_BUILD_TYPE Debug CACHE STRING "default to Debug" FORCE)


############
# Furai Include!
############
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(furai)


