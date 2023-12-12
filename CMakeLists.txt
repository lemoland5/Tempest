cmake_minimum_required(VERSION 3.26)
project(Tempest)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tempest
        main.cpp
        Shapes.h
        Node.cpp
        Map.cpp
        Game.cpp
        Game.h
        SDL_overload.h)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)