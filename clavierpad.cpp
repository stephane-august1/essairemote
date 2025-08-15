#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdlib>
#include "bullet.h"
#include "clavierpad.h"
#include "player.h"
#include <iostream>

using namespace sf;


extern int W;
extern int H;
extern Clock bulletClock;
extern float bulletDelay;
extern int hitCount;
extern float DEGTORAD;
extern std::vector<Entity*> entities;
extern Animation sBullet;
extern player* p;



    

    Clavierpad::Clavierpad() {}

   
void Clavierpad::update() {
    // Gestion du thrust
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        thrust = true;
    } else {
        thrust = false;
    }
    // Gestion de la rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        angle -= 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        angle += 3;
    }
    // Appelle la physique de base du player
    player::update();
}
 void Clavierpad::InputHandler(Event &event, RenderWindow& app)
{
  if (event.type == Event::KeyPressed){
         if (event.key.code == Keyboard::Space)
              {

                if (bulletClock.getElapsedTime().asSeconds() > bulletDelay) // Ajout du délai
                {  std::cout << "TIR !" << std::endl;
                    bullet *b = new bullet();
                    b->settings(sBullet,x,y,angle,10);
                    entities.push_back(b);
                    bulletClock.restart();
                    hitCount++; // Incrémente le compteur de tirs
                }
              
              }
             
          
              //fermeture de la fenetre par echape ou par croix
             if (event.key.code == Keyboard::Escape)  
              {
                app.close();
              }
                if((event.type == Event::Closed))
              {
                app.close();
              }
}}

