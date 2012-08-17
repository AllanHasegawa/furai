cmake_minimum_required(VERSION 2.8)

project(furai-hellotriangle)

###
# Using precompiled furai_backend_android library!
###
add_library(furai_backend_android STATIC IMPORTED)
set_property(TARGET furai_backend_android PROPERTY
	IMPORTED_LOCATION
	${CMAKE_BINARY_DIR}/libs/armeabi/libfurai_backend_android.a
	)


set(JNIGLUE_ROOT "${CMAKE_SOURCE_DIR}/../../../external/android/native_app_glue")

include_directories(
    ${INCLUDE_DIRECTORIES}
    ${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/../../../sourcetree
	${CMAKE_SOURCE_DIR}/../../../external/boost/boost-1_49_0_android/build/include/boost-1_49
	${JNIGLUE_ROOT}
	)

set(SRCS
	android_main.cpp
	${JNIGLUE_ROOT}/android_native_app_glue.c
	)

set(LIBRARY_DEPS
        log
        android
        EGL
        GLESv1_CM
        stdc++
        m
        furai_backend_android
        )

add_library(furai_sample SHARED ${SRCS})
target_link_libraries(
	furai_sample
	${LIBRARY_DEPS}
	)
