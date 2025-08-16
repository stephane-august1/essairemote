#include "collision.h"
#include <cstdlib>

bool CollisionManager::isCollide(Entity *a, Entity *b)
{
    return (b->x - a->x)*(b->x - a->x) +
           (b->y - a->y)*(b->y - a->y) <
           (a->R + b->R)*(a->R + b->R);
}

void CollisionManager::handleCollisions(
    std::vector<Entity*>& entities,
    player* p,
    Animation& sExplosion,
    Animation& sExplosion_ship,
    Animation& sRock_small,
    int& Countscore
) {
    std::vector<Entity*> toAdd;

    for (auto a : entities) {
        for (auto b : entities) {
            if (a->name == "asteroid" && b->name == "bullet" && a->life && b->life) {
                if (CollisionManager::isCollide(a, b)) {
                    a->life = false;
                    b->life = false;

                    Entity* e = new Entity();
                    e->settings(sExplosion, a->x, a->y);
                    e->name = "explosion";
                    toAdd.push_back(e);
                    Countscore++;
                    for (int i = 0; i < 2; i++) {
                        if (a->R == 15) continue;
                        Entity* e = new asteroid();
                        e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                        toAdd.push_back(e);
                    }
                }
            }

            if (a->name == "player" && b->name == "asteroid" && a->life && b->life) {
                if (isCollide(a, b)) {
                    b->life = false;
                    Countscore += 1;
                    Entity* e = new Entity();
                    e->settings(sExplosion_ship, a->x, a->y);
                    e->name = "explosion";
                    toAdd.push_back(e);

                    p->settings(p->anim, W / 2, 770, -90, 20);
                    p->dx = 0; p->dy = 0;
                }
            }
        }
    }

    // Ajoute les nouvelles entités après la détection de collision
    for (auto e : toAdd) entities.push_back(e);
}
void CollisionManager::handleRebond(
    std::vector<Entity*>& entities,
    player* /*p*/,
    Animation& /*sRock*/,
    Animation& /*sRock_small*/,
    int& /*Countscore*/
) {
    for (auto itA = entities.begin(); itA != entities.end(); ++itA) {
        auto itB = itA;
        ++itB; // Commence à l'élément suivant pour éviter les doublons et auto-collisions

        for (; itB != entities.end(); ++itB) {
            Entity* a = *itA;
            Entity* b = *itB;

            if (a->name == "asteroid" && b->name == "asteroid") {
                if (CollisionManager::isCollide(a, b)) {
                    a->dx *= -1;
                    a->dy *= -1;
                    b->dx *= -1;
                    b->dy *= -1;
                }
            }
        }
    }
}