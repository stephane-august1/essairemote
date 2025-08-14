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

using namespace sf;
using namespace std;

//taille de la fenetre
const int W = 1300;
const int H = 850;
//position fenetre
const int poswindowX=43;
const int poswindowY=60;
bool enable_tracker=0;
bool enable_tracker_player=0;
float DEGTORAD = 0.017453f;
bool DebugMode_all_entity=false;
bool DebugMode_player=true;


class Animation
{
   public:
   float Frame, speed;
   Sprite sprite;
   std::vector<IntRect> frames;

   Animation(){}

   Animation (Texture &t, int x, int y, int w, int h, int count, float Speed)
   {
     Frame = 0;
     speed = Speed;

     for (int i=0;i<count;i++)
      frames.push_back( IntRect(x+i*w, y, w, h)  );

     sprite.setTexture(t);
     sprite.setOrigin(w/2,h/2);
     sprite.setTextureRect(frames[0]);
   }


   void update()
   {
     Frame += speed;
     int n = frames.size();
     if (Frame >= n) Frame -= n;
     if (n>0) sprite.setTextureRect( frames[int(Frame)] );
   }

   bool isEnd()
   {
     return Frame+speed>=frames.size();
   }

};


class Entity
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;
   Animation anim;

   Entity()
   {
     life=1;
   }

   void settings(Animation &a,int X,int Y,float Angle=0,int radius=1)
   {
     anim = a;
     x=X; y=Y;
     angle = Angle;
     R = radius;
   }

   virtual void update(){};

   void draw(RenderWindow &app)
   {       
     anim.sprite.setPosition(x,y);
     anim.sprite.setRotation(angle+90);
    // anim.sprite.setRotation(angle+30);
     app.draw(anim.sprite);
  if(DebugMode_all_entity){
        // 🔲 Hitbox (rectangle semi-transparent)
   RectangleShape hitbox;
    hitbox.setSize(Vector2f(R * 4, R * 4));
    hitbox.setOrigin(R/2, R);
    hitbox.setPosition(x, y);
    hitbox.setFillColor(Color(255, 0, 0, 100)); // rouge transparent
    app.draw(hitbox);

    // 📝 Texte de debug
    Font font;
    font.loadFromFile("./src/fonts/arial.ttf"); // Assure-toi que le fichier existe

    Text debugText;
    debugText.setFont(font);
    debugText.setCharacterSize(12);
    debugText.setFillColor(Color::White);

    std::ostringstream ss;
ss << "/src/fonts/arial.ttf";

    ss << "Name: " << name << "\n";
    ss << "Pos: (" << int(x) << ", " << int(y) << ")\n";
    ss << "Speed: (" << dx << ", " << dy << ")\n";
    ss << "Angle: " << int(angle);

   debugText.setString(ss.str());

    debugText.setPosition(x + R + 5, y - R);
    app.draw(debugText);
  }
   }


   virtual ~Entity(){};
};


class asteroid: public Entity
{
   public:
   asteroid()
   {
     //dx=rand()%8-4;
     //dy=rand()%8-4;
      dx=rand()%2-1;
     dy=rand()%2-1;
     name="asteroid";
   }

   void update()
   {
     x+=dx;
     y+=dy;

     if (x>W) x=0;  if (x<0) x=W;
     if (y>H) y=0;  if (y<0) y=H;
   }


};


class bullet: public Entity
{
   public:
   bullet()
   {
     name="bullet";
   }

   void  update()
   {
     dx=cos(angle*DEGTORAD)*6;
     dy=sin(angle*DEGTORAD)*6;
     // angle+=rand()%7-3;  /*try this*/
     x+=dx;
     y+=dy;

     if (x>W || x<0 || y>H || y<0) life=0;
   }

};


class player: public Entity
{
   public:
   bool thrust;

   player()
   {
     name="player";
   }

   void update()
   {
     if (thrust)
      { dx+=cos(angle*DEGTORAD)*0.2;
        dy+=sin(angle*DEGTORAD)*0.2; }
     else
      { dx*=0.99;
        dy*=0.99; }

    int maxSpeed=5;
    float speed = sqrt(dx*dx+dy*dy);
    if (speed>maxSpeed)
     { dx *= maxSpeed/speed;
       dy *= maxSpeed/speed; }

    x+=dx;
    y+=dy;

    if (x>W) x=0; if (x<0) x=W;
    if (y>H) y=0; if (y<0) y=H;
   }
   void Drawhitplayer(RenderWindow &app){
   if(DebugMode_player){

   Entity::draw(app); // Dessine le sprite normalement
      // 🔲 Hitbox (rectangle semi-transparent)
   RectangleShape hitboxplayer;
    hitboxplayer.setSize(Vector2f(R * 4, R * 4));
    hitboxplayer.setOrigin(R/2, R);
    hitboxplayer.setPosition(x, y);
    hitboxplayer.setFillColor(Color(255, 0, 0, 100)); // rouge transparent
    app.draw(hitboxplayer);
    // 🧠 Infos de debug spécifiques au joueur
    Font font;
    font.loadFromFile("./src/fonts/arial.ttf");

    Text debugText;
    debugText.setFont(font);
    debugText.setCharacterSize(24);
    debugText.setFillColor(Color::Green);

        std::ostringstream ss;
    ss << "/src/fonts/arial.ttf";
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

};


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
    Animation sBullet(t5, 0,0,32,64, 16, 0.8);
    Animation sPlayer(t1, 40,0,40,40, 1, 0);
    Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sExplosion_ship(t7, 0,0,192,192, 64, 0.5);


    std::list<Entity*> entities;

    for(int i=0;i<15;i++)
    {
      asteroid *a = new asteroid();
      a->settings(sRock, rand()%W, rand()%H, rand()%360, 25);
      entities.push_back(a);
    }

    player *p = new player();
    p->settings(sPlayer,200,200,0,20);
   
    entities.push_back(p);

    /////main loop/////
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::KeyPressed)
             if (event.key.code == Keyboard::Space)
              {
                bullet *b = new bullet();
                b->settings(sBullet,p->x,p->y,p->angle,10);
                entities.push_back(b);
              }
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=3;
    if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true;
    else p->thrust=false;


    for(auto a:entities)
     for(auto b:entities)
     {
      if (a->name=="asteroid" && b->name=="bullet")
       if ( isCollide(a,b) )
           {
            a->life=false;
            b->life=false;

            Entity *e = new Entity();
            e->settings(sExplosion,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);


            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             Entity *e = new asteroid();
             e->settings(sRock_small,a->x,a->y,rand()%360,15);
             entities.push_back(e);
            }

           }

      if (a->name=="player" && b->name=="asteroid")
       if ( isCollide(a,b) )
           {
            b->life=false;

            Entity *e = new Entity();
            e->settings(sExplosion_ship,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            p->settings(sPlayer,W/2,H/2,0,20);
            p->dx=0; p->dy=0;
           }
     }


    if (p->thrust)  p->anim = sPlayer_go;
    else   p->anim = sPlayer;


    for(auto e:entities)
     if (e->name=="explosion")
      if (e->anim.isEnd()) e->life=0;

    if (rand()%150==0)
     {
       asteroid *a = new asteroid();
       a->settings(sRock, 0,rand()%H, rand()%360, 25);
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
   p->Drawhitplayer(app);
   //dessine toutes les entitées debug si bool DebugMode_all_entity=true
   for(auto i:entities) i->draw(app);
   app.display();
    }

    return 0;
}
