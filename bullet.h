
#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include <string>
#include "string"


class bullet: public Entity
{
   public:
    std::string name;
    bool life;
    bullet();   
    void  update() override;
    void Drawhitbullet(RenderWindow &app);

};

#endif // PLAYER_H