cmake_minimum_required(VERSION 2.8)

project(furai)

SET(CMAKE_BUILD_TYPE Debug CACHE STRING "default to debug" FORCE)


#############
# Boost thing :)
# I'm assuming you got the Furai project from the git repo
#############
if (ANDROID)
	set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/../external/boost/boost-1_49_0_android/build" CACHE PATH "Root directory of the patched Boost library")
elseif (WIN32)
	set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/../external/boost/boost-1_49_0_windows" CACHE PATH "Root directory of the Boost library")
endif (ANDROID)

if(NOT EXISTS ${BOOST_ROOT})
    message(ERROR " BOOST_ROOT_DIR NOT SET")
endif(NOT EXISTS ${BOOST_ROOT})

set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_MULTITHREAD ON)
set(Boost_INCLUDE_DIR "${BOOST_ROOT}/build/include/boost-1_49")
set(Boost_LIBRARY_DIR "${BOOST_ROOT}/build/include/lib")
find_package(Boost 1.49.0 COMPONENTS date_time filesystem system)
include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})


############
# Furai Include!
############
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(furai)
