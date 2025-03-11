if(NOT TARGET glfw)
    message(FATAL_ERROR "GLFW not found")
else()
    message(STATUS "GLFW found")
endif()

set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMBUI_BACKEND_PATH ${IMGUI_PATH}/backends)

# Add imgui sources
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp)
set(IMGUI_BACKEND_SOURCES
    ${IMBUI_BACKEND_PATH}/imgui_impl_glfw.cpp
    ${IMBUI_BACKEND_PATH}/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_BACKEND_SOURCES}
)
target_link_libraries(imgui PRIVATE glfw)
target_include_directories(imgui PUBLIC
    ${IMGUI_PATH}
    ${IMBUI_BACKEND_PATH}
)