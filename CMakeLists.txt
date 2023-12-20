cmake_minimum_required(VERSION 3.26)
project(Tempest)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tempest
        Source/main.cpp
        Header/Shapes.h
        Source/Node.cpp
        Header/Node.h
        Source/Map.cpp
        Header/Map.h
        Source/Game.cpp
        Header/Game.h)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)