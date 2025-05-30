cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME "Engine")

file(GLOB_RECURSE src src/*.cpp src/*.c src/*.hpp src/*.h )
add_library(${ENGINE_PROJECT_NAME} STATIC ${src} )

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(external/Math ${CMAKE_CURRENT_BINARY_DIR}/Math)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE Math)

add_subdirectory(external/stb ${CMAKE_CURRENT_BINARY_DIR}/STB)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE STB)