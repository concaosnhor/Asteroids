#include "Bullet.h"
#include <cmath>

bullet::bullet() {
    name = "bullet";
    lifeTime = 60;
}

void bullet::update() {
    dx = cos(angle * 3.14159f / 180.f) * 10.f;
    dy = sin(angle * 3.14159f / 180.f) * 10.f;
    x += dx;
    y += dy;

    if (x < 0 || x > W || y < 0 || y > H)
        life = false;

    lifeTime--;
    if (lifeTime <= 0) life = false;
}

void bullet::settings(Animation& a, float X, float Y, float Angle, float radius) {
    Entity::settings(a, X, Y, Angle, radius);
    dx = cos(angle * 3.14159f / 180.f) * 15.f;
    dy = sin(angle * 3.14159f / 180.f) * 15.f;
    life = true;
    lifeTime = 60;
}
