#include "Asteroid.h"

asteroid::asteroid() {
    name = "asteroid";
}

void asteroid::update() {
    angle += 1.5f;
    Entity::update();
}
