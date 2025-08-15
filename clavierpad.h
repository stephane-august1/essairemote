#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>  
#include "player.h"

class Clavierpad : public player
{

public:
    
   

    Clavierpad();
    void update() override;
   void InputHandler(Event &event, RenderWindow& app);

};