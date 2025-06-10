#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "globals.h"

class bullet : public Entity {
public:
    int lifeTime;

    bullet();
    void update() override;
    void settings(Animation& a, float X, float Y, float Angle, float radius);
};

#endif
