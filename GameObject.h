#pragma once

#include "Textured2D.h"
#include "SpriteRenderer.h"

enum piece
{
    r = -1, R = 1,
    n = -2, N = 2,
    b = -3, B = 3,
    k = -4, K = 4,
    q = -5, Q = 5,
    p = -6, P = 6
};

class GameObject
{
public:
    // Object state
    glm::vec2   Position, Size, Velocity;
    glm::vec4   Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    // Render state
    Textured2D   Sprite;
    // Constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Textured2D sprite, 
        glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // Draw sprite
    virtual void Draw(SpriteRenderer& renderer);
    piece pieceRef; // piece reference by enum
};

