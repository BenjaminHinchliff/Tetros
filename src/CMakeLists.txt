set(BINARY ${PROJECT_NAME}_run)

set(SOURCES
    "main.cxx"
)

add_executable(${BINARY} ${SOURCES})

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glfw)
find_package(glad CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glad::glad)
find_package(glm CONFIG REQUIRED)
target_link_libraries(${BINARY} PRIVATE glm)