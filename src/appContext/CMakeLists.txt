add_library(appContext STATIC appContext.cpp)
target_link_libraries(appContext
    PRIVATE glfw
    PRIVATE glbinding::glbinding
    PRIVATE glbinding::glbinding-aux
    PRIVATE stb
    PRIVATE imgui
)