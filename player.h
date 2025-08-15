#pragma once
#include "entity.h"

class player : public Entity
{
public:
    bool thrust;
    player();
    void update() override;
    void Drawhitplayer(sf::RenderWindow &app);
};
