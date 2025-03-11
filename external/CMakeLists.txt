# glBinding configuration options to suppress dev warnings
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON CACHE BOOL "Suppress developer warnings" FORCE)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "Warn about deprecated features" FORCE)
set(CMAKE_MODULES ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(glfw)
add_subdirectory(glbinding)

include(${CMAKE_MODULES}/add_stb_image.cmake)
include(${CMAKE_MODULES}/add_imgui.cmake)