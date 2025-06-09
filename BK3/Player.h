#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

class player : public Entity {
public:
    bool thrust;
    Animation anim_go;

    player();
    void update() override;
    void draw(sf::RenderWindow& app) override;
};

#endif
