########
# Android Backend Root CMake File
########

project(furai_backend_android)

include_directories(${CMAKE_SOURCE_DIR}/../external/android)

add_subdirectory(core)

set(LIBRARY_DEPS
        log
        android
        EGL
        GLESv1_CM
        stdc++
        c
        m)

add_library(furai_backend_android STATIC ${SRCS})
target_link_libraries(furai_backend_android ${LIBRARY_DEPS})

