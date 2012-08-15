set(TMP "furai_backends_android_jniglue")

#set(LIBRARY_DEPS log)

set(${TMP}_SRCS furai_android_native_app_glue.cpp)

add_library(${TMP} STATIC ${${TMP}_SRCS})

#target_link_libraries(${TMP} ${LIBRARY_DEPS})