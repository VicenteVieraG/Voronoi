add_library(components STATIC sidebar.cpp)
target_link_libraries(components
    PRIVATE glfw
    PRIVATE glbinding::glbinding
    PRIVATE imgui
    PRIVATE appContext
)