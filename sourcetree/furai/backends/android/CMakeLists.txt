project(furai_backend_android)

add_subdirectory(jniglue)
add_subdirectory(core)

#add_library(android_main SHARED main.cpp)
#target_link_libraries(android_main "furai_backend_android_jniglue" log android EGL GLESv1_CM stdc++ c m)