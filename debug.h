#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
#include "bullet.h"
#include "asteroid.h"
#include "player.h"

class Debug {
public:
    static void DrawBullets(const std::vector<Entity*>& entities, sf::RenderWindow& app);
    static void DrawAsteroids(const std::vector<Entity*>& entities, sf::RenderWindow& app);
    static void DrawPlayer(player* p, sf::RenderWindow& app);
};