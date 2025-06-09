#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    float Frame, speed;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;

    Animation() {}

    Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed);

    void update();
    bool isEnd();
};

#endif
