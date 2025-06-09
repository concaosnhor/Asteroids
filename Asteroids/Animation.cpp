#include "Animation.h"

Animation::Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed) {
    Frame = 0;
    speed = Speed;

    for (int i = 0; i < count; i++)
        frames.push_back(sf::IntRect(x + i * w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(w / 2.f, h / 2.f);
    sprite.setTextureRect(frames[0]);
}

void Animation::update() {
    Frame += speed;
    int n = static_cast<int>(frames.size());
    if (Frame >= n) Frame -= n;
    sprite.setTextureRect(frames[(int)Frame]);
}

bool Animation::isEnd() {
    return Frame + speed >= frames.size();
}
