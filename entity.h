#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "animation.h"

class Entity {
public:
    float x, y, dx, dy, R, angle;
    bool life;
    std::string name;
    Animation anim;

    Entity();
    virtual void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1);
    virtual void update();
    virtual void draw(sf::RenderWindow &app);
    virtual ~Entity();
};