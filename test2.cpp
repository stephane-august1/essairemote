#include <SFML/Graphics.hpp>
#include <time.h>
#include "math.h"
#include <list>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include "vector"
#include <cstdlib>
#include "sstream"
#include "animation.h"
#include "entity.h"
#include "asteroid.h"
#include "clavierpad.h"
#include "bullet.h"
#include "player.h"
#include "debug.h"
using namespace sf;
using namespace std;

//taille de la fenetre
int W = 1300;
int H = 850;
//position fenetre
const int poswindowX=43;
const int poswindowY=60;
bool enable_tracker=0;
bool enable_tracker_player=0;
float DEGTORAD = 0.017453f;

bool DebugMode_player=true;
bool DebugMode_bullet=true;
bool DebugMode_asteroid=false;
Font debugFont;
Clock bulletClock; // Ajouté pour gérer le délai entre tirs
float bulletDelay = 0.40f; // Délai en secondes entre deux tirs
int tirCount = 0; // Compteur de tirs
int hitCount = 0; // Compteur de touches
int Countasteroid = 0; // Compteur de touches
int Countscore=0; // Compteur de score
std::vector<Entity*> entities;
Animation sBullet;
player* p = nullptr;
//prototype de la fonction 
//void InputHandler(Event event, RenderWindow& app);
bool    isCollide(Entity *a,Entity *b);

bool isCollide(Entity *a,Entity *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}



int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);
 if (!debugFont.loadFromFile("./src/fonts/arial.ttf")) {
        cout<< "Erreur chargement police debug !" << endl;
        
    }
    Texture t1,t2,t3,t4,t5,t6,t7;
    t1.loadFromFile("./src/images/spaceship.png");
    t2.loadFromFile("./src/images/background.jpg");
    t3.loadFromFile("./src/images/explosions/type_C.png");
    t4.loadFromFile("./src/images/rock.png");
    t5.loadFromFile("./src/images/fire_blue.png");
    t6.loadFromFile("./src/images/rock_small.png");
    t7.loadFromFile("./src/images/explosions/type_B.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite background(t2);

    Animation sExplosion(t3, 0,0,256,256, 48, 0.5);
    Animation sRock(t4, 0,0,64,64, 16, 0.2);
    Animation sRock_small(t6, 0,0,64,64, 16, 0.2);
   // Animation sBullet(t5, 0,0,32,64, 16, 0.8);
   sBullet = Animation(t5, 0,0,32,64, 16, 0.8);
   Animation sPlayer(t1, 40,0,40,40, 1, 0);
  
  Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sExplosion_ship(t7, 0,0,192,192, 64, 0.5);


   // std::list<Entity*> entities;

    for(int i=0;i<25;i++)
    {
      asteroid *a = new asteroid();
      a->settings(sRock, rand()%W, rand()%(H/2), rand()%360, 25);
      entities.push_back(a);
    }

    //player *p = new player();
    player *p = new Clavierpad();
    p->settings(sPlayer,W/2,+770,-90,20);
 
    entities.push_back(p);

    /////main loop/////
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
 p->InputHandler(event, app);
  
        }

    
              

             
/********** gestion du rebond entre 2 asteroid*****************************/
  /* 
   for (auto itA = entities.begin(); itA != entities.end(); ++itA)
{
    auto itB = itA;
    ++itB; // Commence à l'élément suivant pour éviter les doublons et auto-collisions

    for (; itB != entities.end(); ++itB)
    {
        Entity* a = *itA;
        Entity* b = *itB;

        if (a->name == "asteroid" && b->name == "asteroid")
        {
            if (isCollide(a, b))
            {
                a->dx *= -1;
                a->dy *= -1;
                b->dx *= -1;
                b->dy *= -1;
            }
        }
    }
}
*/
/********** find de gestion du rebond asteroid*****************************/
 
std::vector<Entity*> toAdd; // Pour stocker les nouvelles entités à ajouter après la boucle

for (auto a : entities) {
    for (auto b : entities) {
        if (a->name == "asteroid" && b->name == "bullet" && a->life && b->life) {
            if (isCollide(a, b)) {
                a->life = false;
                b->life = false;

                Entity *e = new Entity();
                e->settings(sExplosion, a->x, a->y);
                e->name = "explosion";
                toAdd.push_back(e);
Countscore++;
                for (int i = 0; i < 2; i++) {
                    if (a->R == 15) continue;
                    Entity *e = new asteroid();
                    e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                    toAdd.push_back(e);
                }
            }
        }

        if (a->name == "player" && b->name == "asteroid" && a->life && b->life) {
            if (isCollide(a, b)) {
                b->life = false;
                Countscore += 1;
                Entity *e = new Entity();
                e->settings(sExplosion_ship, a->x, a->y);
                e->name = "explosion";
                toAdd.push_back(e);

                        p->settings(sPlayer, W / 2, +770, -90, 20);
                p->dx = 0; p->dy = 0;
            }
        }
    }
}

// Ajoute les nouvelles entités après la détection de collision
for (auto e : toAdd) entities.push_back(e);

    if (p->thrust) { p->anim = sPlayer_go;}
    else   p->anim = sPlayer;


    for(auto e:entities)
     if (e->name=="explosion")
      if (e->anim.isEnd()) e->life=0;

    if (rand()%150==0)
     {
       asteroid *a = new asteroid();
       a->settings(sRock, 0,rand()%(H/2), rand()%360, 25);
       entities.push_back(a);
       
     }

    for(auto i=entities.begin();i!=entities.end();)
    {
      Entity *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entities.erase(i); delete e;}
      else i++;
    }

   //////draw//////
   app.draw(background);
   //dessine le debugplayer si bool DebugMode_player=true
   //p->Drawhitplayer(app);
   if (DebugMode_player)
    Debug::DrawPlayer(p, app);
  
   // Ajoute ce bloc pour dessiner la hitbox des bullets
/*   if(DebugMode_bullet){
   for (auto e : entities)
   {
       if (e->name == "bullet" && e->life)
       {
           bullet* b = dynamic_cast<bullet*>(e);
           if (b) b->Drawhitbullet(app);
       }
   }}*/
  if (DebugMode_bullet)
    Debug::DrawBullets(entities, app);

    // Ajoute ce bloc pour dessiner la hitbox des asteroids
  
if (DebugMode_asteroid)
    Debug::DrawAsteroids(entities, app);
/*    if(DebugMode_asteroid){
   for (auto e : entities)
   {
       if (e->name == "asteroid")
       {
           asteroid* b = dynamic_cast<asteroid*>(e);
           if (b) b->Drawhasteroid(app);
       }
   }}*/
   //dessine toutes les entitées debug et DebugMode_all_entity=true
   for(auto i:entities) i->draw(app);
   //compte les asteroid
  /* for (auto e : entities) {
    if (e->name == "asteroid" && e->life)
        Countasteroid++;
}*/
   //affiche le score:

    Text scoreText;
    scoreText.setFont(debugFont);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    std::ostringstream ss;
    ss << "Score: " << Countscore << "\n";
    ss << "Tir Count: " << hitCount << "\n";
    ss << "Hit Count: " << Countscore << "\n";
    ss << "Asteroid Count: " << Countasteroid << "\n";
    scoreText.setString(ss.str());
    scoreText.setPosition(10, 10);
    app.draw(scoreText);

  
   
    
   app.display();
    }

   
    return 0;
}

 //Fonction fermeture fenetre
void InputHandler(Event event, RenderWindow& app)
{
  if (event.type == Event::KeyPressed)
           
          
              //fermeture de la fenetre par echape ou par croix
              if((Keyboard::isKeyPressed(Keyboard::Escape)))
               
              {
                app.close();
              }
                if((event.type == Event::Closed))
              {
                app.close();
              }
}
