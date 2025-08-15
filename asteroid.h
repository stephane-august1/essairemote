#pragma once
#include "entity.h"

class asteroid : public Entity {
public:
    asteroid();
    void update() override;
    void Drawhasteroid(sf::RenderWindow &app);
};