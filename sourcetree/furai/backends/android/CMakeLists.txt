########
# Android Backend Root CMake File
########

project(furai_backend_android)

add_module(core)

set(LIBRARY_DEPS
        log
        android
        EGL
        GLESv1_CM
        stdc++
        c
        m)

#add_library(furai_backend_android SHARED ${SRCS})
add_library(furai_backend_android SHARED core/jniglue/furai_android_native_app_glue.cpp core/AndroidApplication.cpp core/jniglue/android_main.cpp)
target_link_libraries(furai_backend_android ${LIBRARY_DEPS})

