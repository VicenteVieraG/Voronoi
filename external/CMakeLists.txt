# glBinding configuration options to suppress dev warnings
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON CACHE BOOL "Suppress developer warnings" FORCE)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "Warn about deprecated features" FORCE)

add_subdirectory(glfw)
add_subdirectory(glbinding)

include(${CMAKE_SOURCE_DIR}/cmake/add_stb_image.cmake)