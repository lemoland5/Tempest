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
        Source/MapLoader.cpp
        Header/MapLoader.h
        Source/Game.cpp
        Header/Game.h
        Source/Actor.cpp
        Header/Actor.h
        Source/TextureManager.cpp
        Header/TextureManager.h
        Source/EventHandler.cpp
        Header/EventHandler.h
        Header/Player.h
        Source/Player.cpp)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)
cmake_minimum_required(VERSION 3.26)