#include "Player.h"
#include <cmath>
#include <SFML/Window/Keyboard.hpp>

player::player() {
    name = "player";
    thrust = false;
}

void player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        dx += cos(angle * 3.14159f / 180.f) * 0.1f;
        dy += sin(angle * 3.14159f / 180.f) * 0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        dx -= cos(angle * 3.14159f / 180.f) * 0.1f;
        dy -= sin(angle * 3.14159f / 180.f) * 0.1f;
    }

    dx *= 0.98f;
    dy *= 0.98f;

    float maxSpeed = 7.f;
    float speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed) {
        dx = dx / speed * maxSpeed;
        dy = dy / speed * maxSpeed;
    }

    Entity::update();
}

void player::draw(sf::RenderWindow& app) {
    anim.sprite.setPosition(x, y);
    anim.sprite.setRotation(angle + 90.f);
    app.draw(anim.sprite);
}
