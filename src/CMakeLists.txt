set(BINARY ${PROJECT_NAME}_run)

set(SOURCES
    "main.cxx"
    "Shader.h"
    "Shader.cxx"
    "GLRect.h"
    "GLRect.cxx"
    "Debug.h"
    "Debug.cpp"
)

add_executable(${BINARY} ${SOURCES})

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glfw)
find_package(glad CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glad::glad)
find_package(glm CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glm)
find_package(freetype CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE freetype)

configure_file("Rect.vert" "${CMAKE_CURRENT_BINARY_DIR}/Rect.vert" COPYONLY)
configure_file("Rect.frag" "${CMAKE_CURRENT_BINARY_DIR}/Rect.frag" COPYONLY)