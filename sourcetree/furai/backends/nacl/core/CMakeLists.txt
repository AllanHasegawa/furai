###
# furai/backends/nacl/core
###

add_subdirectory(mainthreadcalls)

add_sources(
    NaClApplication.cpp
    NaClModule.cpp
    NaClWindow.cpp
    NaClClock.cpp
    NaClLogJSConsole.cpp
    NaClLogEnvVars.cpp
    )