message(STATUS "-- Adding STB Image library")

set(STB stb)
set(STB_SOURCE ${CMAKE_SOURCE_DIR}/external/stb/.)

add_library(${STB} INTERFACE)
target_include_directories(${STB} INTERFACE ${STB_SOURCE})