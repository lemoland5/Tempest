#pragma once

#include "Shapes.h"
#include <SDL.h>
#include <stack>
#include <string>

enum Type {
    TYPE_PLAYER = 0,
    TYPE_ENEMY = 1,
    TYPE_BULLET = 2,
    TYPE_PARTICLE = 3
};

class Actor {
public:
    Actor() = default;
    Actor(float x, float y, int width, int height, std::string id);
    virtual ~Actor();
//    Actor(Point* point, int width, int height): m_pMapPosition(point), m_Width(width), m_Height(height), m_MarkedForDeletion(false){};

    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void handleCollisions() = 0;
    virtual void kill();

    void markForDeletion() {m_MarkedForDeletion = true;};
    virtual Type getType() = 0;
    [[nodiscard]] bool isMarkedForDeletion() const {return m_MarkedForDeletion;};
    [[nodiscard]] Point* getMapPosition() const {return m_pMapPosition;};

    void moveX(int x);
    void moveXAbs(int x);
    void moveY(int y);
    void addCollision(Type type);
    void correctRotation();

protected:
    Point* m_pPosition;
    Point* m_pMapPosition;
    float m_Anchor = 0.5f;
    int m_Width;
    int m_Height;
    float m_Rotation;
    std::string m_TextureId;
    bool m_MarkedForDeletion = false;
    std::stack<Type> m_CollisionStack;
};