#include "debug.h"
#include "player.h"

void Debug::DrawBullets(const std::vector<Entity*>& entities, sf::RenderWindow& app) {
    for (auto e : entities) {
        if (e->name == "bullet" && e->life) {
            bullet* b = dynamic_cast<bullet*>(e);
            if (b) b->Drawhitbullet(app);
        }
    }
}

void Debug::DrawAsteroids(const std::vector<Entity*>& entities, sf::RenderWindow& app) {
    for (auto e : entities) {
        if (e->name == "asteroid") {
            asteroid* a = dynamic_cast<asteroid*>(e);
            if (a) a->Drawhasteroid(app);
        }
    }
}

void Debug::DrawPlayer(player* p, sf::RenderWindow& app) {
    if (p) p->Drawhitplayer(app);
}