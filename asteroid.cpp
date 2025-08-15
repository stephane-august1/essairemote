#include "asteroid.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "entity.h"

// ...includes existants...
extern int W;
extern int H;
extern bool DebugMode_asteroid;
extern int tirCount; // si tu utilises tirCount dans le debug
   asteroid::asteroid()
   {
     //dx=rand()%8-4;
     //dy=rand()%8-4;
     dx=rand()%2-1;
     dy=rand()%2-1;
     name="asteroid";
     
   }

   void asteroid::update()
   {
     x+=dx;
     y+=dy;

     if (x>W) x=0;  if (x<0) x=W;
     //zone complete tout l'ecran
    // if (y>H) y=0;  if (y<0) y=H;
      // Limite la zone de rebond à la moitié supérieure
     if (y > H/2) y = 0;
     if (y < 0) y = H/1.5;
   }
  void asteroid::Drawhasteroid(sf::RenderWindow &app){
   if(DebugMode_asteroid){

   //Entity::draw(app); // Dessine le sprite normalement
      // 🔲 Hitbox (rectangle semi-transparent)
   /*RectangleShape hitboxplayer;
    hitboxplayer.setSize(Vector2f(R * 4, R * 4));
    hitboxplayer.setOrigin(R/2, R);
    hitboxplayer.setPosition(x, y);
    hitboxplayer.setFillColor(Color(255, 0, 0, 100)); // rouge transparent
    app.draw(hitboxplayer);*/
    // 🧠 Infos de debug spécifiques au joueur
    extern sf::Font debugFont;
    sf::Text debugText;
    debugText.setFont(debugFont);        
    debugText.setCharacterSize(24);
    debugText.setFillColor(sf::Color::Green);

    std::ostringstream ss;
    ss << "ASTEROID DEBUG\n";
    ss << "Pos: x,y:(" << int(x) << "," << int(y) << ")\n";
    ss << "Speed: dx,dy (" << dx << ", " << dy << ")\n";
    ss << "Angle: R: " << int(angle);
    ss << " tirCount : " << tirCount << "\n";
    debugText.setString(ss.str());
   // debugText.setPosition(x + R + 10, y - R - 20);
    debugText.setPosition(x + R + 5, y - R);
    app.draw(debugText);

   }}


