set(BINARY ${PROJECT_NAME}_run)

set(SOURCES
    "main.cxx"
    "Shader.h"
    "Shader.cxx"
    "Debug.h"
    "Debug.cxx"
    "Mesh.h"
    "Mesh.cxx"
    "TexturedMesh.h"
    "TexturedMesh.cxx"
    "Square.h"
    "Square.cxx"
    "Grid.h"
    "Grid.cxx"
    "BlockTemplates.h"
    "Block.h"
    "Block.cxx"
)

add_executable(${BINARY} ${SOURCES})

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glfw)
find_package(glad CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glad::glad)
find_package(glm CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glm)

configure_file("resources/shaders/ColorAndText.vert" "${CMAKE_CURRENT_BINARY_DIR}/ColorAndText.vert" COPYONLY)
configure_file("resources/shaders/ColorAndText.frag" "${CMAKE_CURRENT_BINARY_DIR}/ColorAndText.frag" COPYONLY)

configure_file("resources/images/block.png" "${CMAKE_CURRENT_BINARY_DIR}/block.png" COPYONLY)