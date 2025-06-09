#include "Entity.h"
#include "globals.h"

Entity::Entity() {
    life = true;
    name = "";
    dx = dy = 0.f;
}

void Entity::settings(Animation& a, float X, float Y, float Angle, float radius) {
    anim = a;
    x = X; y = Y;
    angle = Angle;
    R = radius;
}

void Entity::update() {
    x += dx;
    y += dy;

    if (x > W) x = 0;
    if (x < 0) x = W;
    if (y > H) y = 0;
    if (y < 0) y = H;
}

void Entity::draw(sf::RenderWindow& app) {
    anim.sprite.setPosition(x, y);
    anim.sprite.setRotation(angle + 90.f);
    app.draw(anim.sprite);
}
