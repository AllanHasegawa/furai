########
# NaCl Backend Root CMake File
########

project(furai_backend_nacl)

include_directories("${CMAKE_SOURCE_DIR}/../external/nacl")
add_sources("../../../../external/nacl/opengl_context/opengl_context.cc")


add_subdirectory(exe)
add_subdirectory(core)
add_subdirectory(storage)
add_subdirectory(graphics)

set(LIBRARY_DEPS
    ppapi_cpp
    ppapi
    ppapi_gles2
    )

add_executable(furai_backend_nacl ${SRCS})
target_link_libraries(furai_backend_nacl ${LIBRARY_DEPS})

