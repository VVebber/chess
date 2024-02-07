cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(Chess src/main.cpp src/GameLogic.h src/Functions.h
               src/Logic.h src/Logic.cpp
               src/Figures/Figure.h src/Figures/Figure.cpp
               src/Windows/MainMenu.h src/Windows/MainMenu.cpp
               src/Windows/PlayMenu.h src/Windows/PlayMenu.cpp
               src/Windows/Setting.h src/Windows/Setting.cpp
               src/Windows/TypeGame.h src/Windows/TypeGame.cpp)

# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(Chess ${OPENGL_LIBRARIES})
# Find SFML
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Chess sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
# Find GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Chess glfw)
