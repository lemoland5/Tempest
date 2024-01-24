cmake_minimum_required(VERSION 3.22.1)

project(Tempest)


set(CMAKE_CXX_STANDARD 17)

#include(C:/Users/Niep/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake)


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
        Source/EventHandler.cpp
        Header/EventHandler.h
        Header/Player.h
        Source/Player.cpp
        Source/Shapes.cpp
        Source/Bullet.cpp
        Header/Bullet.h
        Source/Flipper.cpp
        Header/Flipper.h
        Source/Fuseball.cpp
        Header/Fuseball.h
        Header/CollisionManager.h
        Source/Pulsar.cpp
        Header/Pulsar.h
        Source/FlipperTanker.cpp
        Header/FlipperTanker.h
        Source/HudManager.cpp
        Header/HudManager.h
        Source/Enemy.cpp
        Header/Enemy.h
        Source/Path.cpp
        Header/Path.h
        Source/PathManager.cpp
        Header/PathManager.h
)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)