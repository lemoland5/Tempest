#pragma once

#include "Shapes.h"
#include <SDL.h>
#include <stack>
#include <string>

enum Type {
    TYPE_PLAYER = 0,
    TYPE_ENEMY = 1,
    TYPE_BULLET = 2
};

class Actor {
public:
    Actor() {};
    Actor(int x, int y, int width, int height, std::string id);
//    Actor(Point* point, int width, int height): m_MapPosition(point), m_Width(width), m_Height(height), m_MarkedForDeletion(false){};

    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void handleCollisions() = 0;
    virtual Type getType() = 0;

    [[nodiscard]] bool isMarkedForDeletion() const {return m_MarkedForDeletion;};
    [[nodiscard]] Point* getMapPosition() const {return m_MapPosition;};

    void moveX(int x);
    void moveY(int y);
    void addCollision(Type type);

protected:
    Point* m_Position;
    Point* m_MapPosition;
    float m_Anchor = 0.5f;
    int m_Width;
    int m_Height;
    std::string m_TextureId;
    bool m_MarkedForDeletion;
    std::stack<Type> m_CollisionStack;
};