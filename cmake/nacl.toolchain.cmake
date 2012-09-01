cmake_minimum_required(VERSION 2.8.8)

set(NACL_PATH "$ENV{NACL_SDK_ROOT}" CACHE PATH "Native Client SDK Bundle Path")

if(NACL_PATH STREQUAL "")
	message(ERROR "ENVVAR NACL_SDK_ROOT not found")
endif()

file(TO_CMAKE_PATH "${NACL_PATH}" NACL_PATH)

set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_SYSTEM_VERSION 1)

set(NACL_TARGET x86_64-nacl)

# expand to support others hosts
set(NACL_TOOLCHAIN win_x86_newlib)

if(CMAKE_HOST_WIN32)
	set(NACL_C_COMPILER_SUFFIX .exe)
	set(NACL_TOOLCHAIN_64 "x86_64-nacl/")
endif()

set(CMAKE_C_COMPILER "${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/bin/${NACL_TARGET}-gcc${NACL_C_COMPILER_SUFFIX}" CACHE PATH "gcc")
set(CMAKE_CXX_COMPILER "${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/bin/${NACL_TARGET}-g++${NACL_C_COMPILER_SUFFIX}" CACHE PATH "g++")

set(CMAKE_CXX_FLAGS "-O0 -g -pthread -std=gnu++98 -Wno-long-long -Wall -Wswitch-enum -Werror -pedantic")

include_directories("${NACL_PATH}/src")
include_directories("${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/${NACL_TOOLCHAIN_64}/include")
include_directories("${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/lib/gcc/${NACL_TARGET}/4.4.3/include")
include_directories("${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/${NACL_TARGET}/include/c++/4.4.3")
include_directories("${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/${NACL_TARGET}/include/c++/4.4.3/${NACL_TARGET}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(NACL_OUTPUT_ROOT "${CMAKE_BINARY_DIR}" CACHE PATH
	"Directory to place output files. Default to CMAKE_BINARY_DIR.")

set(EXECUTABLE_OUTPUT_PATH "${NACL_OUTPUT_ROOT}/libs/${NACL_TARGET}" CACHE PATH "Directory to place output files")

set(NACL True)

