cmake_minimum_required(VERSION 2.8.8)


###
# Setting up NACL_PATH variable
###
set(NACL_PATH "$ENV{NACL_SDK_ROOT}" CACHE PATH "Native Client SDK Bundle Path")
if(NACL_PATH STREQUAL "")
	message(ERROR "ENVVAR NACL_SDK_ROOT not found")
endif()
file(TO_CMAKE_PATH "${NACL_PATH}" NACL_PATH)


set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)

###
# Setting up the instruction target
###
set(NACL_TARGET "x86_64" CACHE STRING "Target: x86_64 | x86_32")
if(NACL_TARGET STREQUAL "x86_32")
	set(NACL_TARGET_FLAG "-m32")
else()
	set(NACL_TARGET_FLAG "-m64")
endif()

# expand to support others hosts
set(NACL_TOOLCHAIN win_x86_newlib)

if(CMAKE_HOST_WIN32)
	set(NACL_C_COMPILER_SUFFIX .exe)
endif()

###
# Setting up the compiler executable...
###
set(NACL_C_COMPILER "i686-nacl-gcc${NACL_C_COMPILER_SUFFIX}")
set(NACL_CXX_COMPILER "i686-nacl-g++${NACL_C_COMPILER_SUFFIX}")

set(CMAKE_C_COMPILER "${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/bin/${NACL_C_COMPILER}" CACHE PATH "gcc")
set(CMAKE_CXX_COMPILER "${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/bin/${NACL_CXX_COMPILER}" CACHE PATH "g++")

###
# Default Flags.
# From:
#   https://developers.google.com/native-client/devguide/devcycle/building
###
set(NACL_WARNING_FLAGS "-Wno-long-long -Wall -Wswitch-enum -Werror -pedantic")
# Debug
set(CMAKE_CXX_FLAGS_DEBUG "${NACL_TARGET_FLAG} -O0 -g -pthread -std=gnu++98 ${NACL_WARNING_FLAGS}")
# Profile
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${NACL_TARGET_FLAG} -g -O2 -pthread -std=gnu++98 -msse -mfpmath=sse -ffast-math -fomit-frame-pointer ${NACL_WARNING_FLAGS}")
# Deploy
set(CMAKE_CXX_FLAGS_RELEASE "${NACL_TARGET_FLAG} -s -O3 -pthread -std=gnu++98 -msse -mfpmath=sse -ffast-math -fomit-frame-pointer ${NACL_WARNING_FLAGS}")
# Default == Debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")

###
# Default Linker Flags
###
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -W1 -as-needed")

###
# Include directories used by the IDE
###
set(NACL_TOOLCHAIN_VERSION "x86_64-nacl")

include_directories("${NACL_PATH}/src")
include_directories("${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/${NACL_TOOLCHAIN_VERSION}/include")
include_directories("${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/lib/gcc/${NACL_TOOLCHAIN_VERSION}/4.4.3/include")
include_directories("${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/${NACL_TOOLCHAIN_VERSION}/include/c++/4.4.3")
include_directories("${NACL_PATH}/toolchain/${NACL_TOOLCHAIN}/${NACL_TOOLCHAIN_VERSION}/include/c++/4.4.3/${NACL_TOOLCHAIN_VERSION}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

###
# Output configuration. Default to "out of sourcetree" binaries.
###
set(NACL_OUTPUT_ROOT "${CMAKE_BINARY_DIR}" CACHE PATH
	"Directory to place output files. Default to CMAKE_BINARY_DIR.")

set(EXECUTABLE_OUTPUT_PATH "${NACL_OUTPUT_ROOT}/libs/nacl-${NACL_TARGET}" CACHE PATH "Directory to place output files")

###
# Info variables.
###
set(NACL True)

