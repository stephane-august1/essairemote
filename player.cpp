#include "player.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <sstream>


// Variables externes pour les dimensions de la fenêtre
extern int W;
extern int H;
extern bool DebugMode_player;
extern int tirCount; // si tu utilises tirCount dans le debug
extern float bulletDelay; // Délai en secondes entre deux tirs  
extern float DEGTORAD;
extern sf::Font debugFont;

player::player()
{
    thrust = false;
    name = "player";
}

void player::update()
{
    if (thrust)
    {
        dx += std::cos(angle * 0.017453f) * 0.2f;
        dy += std::sin(angle * 0.017453f) * 0.2f;
    }
    else
    {
        dx *= 0.99f;
        dy *= 0.99f;
    }

    float speed = std::sqrt(dx * dx + dy * dy);
    if (speed > 15)
    {
        dx *= 15 / speed;
        dy *= 15 / speed;
    }

    x += dx;
    y += dy;

    if (x > W) x = 0; if (x < 0) x = W;
    if (y > H) y = 0; if (y < 0) y = H;
}

void player::Drawhitplayer(sf::RenderWindow &app)
{
    
   if(DebugMode_player){

   Entity::draw(app); // Dessine le sprite normalement
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
    ss << "PLAYER DEBUG\n";
    ss << "Pos: x,y:(" << int(x) << "," << int(y) << ")\n";
    ss << "Speed: dx,dy (" << dx << ", " << dy << ")\n";
    ss << "Angle: R: " << int(angle);

    debugText.setString(ss.str());
   // debugText.setPosition(x + R + 10, y - R - 20);
    debugText.setPosition(x + R + 5, y - R);
    app.draw(debugText);
   }
}