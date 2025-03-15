set(GRAPHICS graphics)
add_library(${GRAPHICS} STATIC graphics.cpp)

target_link_libraries(${GRAPHICS}
    PRIVATE glbinding::glbinding
)