#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Animation.h"

class Entity {
public:
    float x, y, dx, dy, R, angle;
    bool life;
    std::string name;
    Animation anim;

    Entity();
    virtual ~Entity() = default;

    virtual void update();
    virtual void draw(sf::RenderWindow& app);
    void settings(Animation& a, float X, float Y, float Angle = 0.f, float radius = 1.f);
};

#endif
