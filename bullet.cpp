#include "bullet.h"
#include<string>
#include <cmath>
#include <sstream>
#include <cstdlib>

using namespace sf; 
using namespace std;

// Variables externes pour les dimensions de la fenêtre
extern int W;
extern int H;
extern bool DebugMode_bullet;
extern int tirCount; // si tu utilises tirCount dans le debug
extern Clock bulletClock; // Ajouté pour gérer le délai entre tirs
extern float bulletDelay; // Délai en secondes entre deux tirs  
extern float DEGTORAD;

 

  bullet:: bullet()
   { name="bullet";}

   void bullet::update()
   {
     dx=cos(angle*DEGTORAD)*6;
     dy=sin(angle*DEGTORAD)*6;
     angle+=rand()%7-3;  /*try this*/
     x+=dx;
     y+=dy;

     if (x>W || x<0 || y>H || y<0) life=0;
   }
    void bullet::Drawhitbullet(sf::RenderWindow &app){
   if(DebugMode_bullet){

   //Entity::draw(app); // Dessine le sprite normalement
      // 🔲 Hitbox (rectangle semi-transparent)
   /*RectangleShape hitboxplayer;
    hitboxplayer.setSize(Vector2f(R * 4, R * 4));
    hitboxplayer.setOrigin(R/2, R);
    hitboxplayer.setPosition(x, y);
    hitboxplayer.setFillColor(Color(255, 0, 0, 100)); // rouge transparent
    app.draw(hitboxplayer);*/
    // 🧠 Infos de debug spécifiques au joueur
    extern Font debugFont;
    Text debugText;
    debugText.setFont(debugFont);        
    debugText.setCharacterSize(24);
    debugText.setFillColor(Color::Green);

    std::ostringstream ss;
    ss << "BULLET DEBUG\n";
    ss << "Pos: x,y:(" << int(x) << "," << int(y) << ")\n";
    ss << "Speed: dx,dy (" << dx << ", " << dy << ")\n";
    ss << "Angle: R: " << int(angle);
    ss << " tirCount : " << tirCount << "\n";
    debugText.setString(ss.str());
   // debugText.setPosition(x + R + 10, y - R - 20);
    debugText.setPosition(x + R + 5, y - R);
    app.draw(debugText);

   }}



