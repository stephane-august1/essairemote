#pragma once
#include <vector>
#include "entity.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include <SFML/Graphics.hpp>

extern int W;
extern int H;

class CollisionManager {
public:
   

 static bool isCollide(Entity *a, Entity *b);
   

  static  void handleCollisions(std::vector<Entity *> &entities, player *p, Animation &sExplosion, Animation &sExplosion_ship, Animation &sRock_small, int &Countscore);

    static void handleRebond(
        std::vector<Entity *> &entities,
        player *p,
        Animation &sRock,
        Animation &sRock_small,
        int &Countscore);
};