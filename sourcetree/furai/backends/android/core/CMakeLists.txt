set(TMP "furai_backend_android_core")

set(LIBRARY_DEPS "furai_backends_android_jniglue")

set(${TMP}_SRCS AndroidApplication.cpp)

add_library(${TMP} SHARED ${${TMP}_SRCS})

target_link_libraries(${TMP} ${LIBRARY_DEPS})