cmake_minimum_required(VERSION 3.15)

project(NovaBullet)

add_subdirectory("Engine")

file(GLOB_RECURSE src src/*.cpp src/*.c src/*.hpp src/*.h )
add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} "Engine" Math glad STB -static gcc stdc++ winpthread -dynamic)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20 )

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Release)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)