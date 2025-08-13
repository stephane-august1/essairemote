
#include <SFML/Graphics.hpp>
#include <time.h>
#include "math.h"
#include <list>
#include <SFML/System.hpp>
#include <iostream>

#include <cstdlib>
#include <string>
#include "vector"






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

//Variable globale
Font font;
string police = "coding/font/arial.ttf";
using namespace sf;

//prototype de la fonction InputHandler
void InputHandler(Event event, RenderWindow& app);

 Text txt1;
 Text txt3;
 
 Text txt8;
 Color couleur1;
  Color couleur;
   Color choixcouleur;
   int pos_text1_X= 10;
   int pos_text1_Y=10;
   int size1=52;
 string nouveautext="Player1:";
 int compteurscore=0000;
 string compteur="compteur:" +compteurscore;
 int size2=123;
 Color couleurcompteur;
    string valeur,lapolice;
    int size, posX,posY;
   Text txt;


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
class Rectangle{
  public:
    std::string name;
     float x,y,dx,dy,R,angle;
   bool life;
   
   //Animation anim;
   RectangleShape rectangle;
//constructeur
Rectangle(){}
Rectangle(string namerectangle,int X,int Y,float Angle=0,int radius=1){   
     life=1;
     this->name=namerectangle;
    //this->rectangle=rectangle;
     this->R=radius;
     
    // RectangleShape rectangle;
    rectangle.setOrigin(-R,R*3);
    rectangle.setSize(sf::Vector2f(R*3, R*3));
    rectangle.setFillColor(Color(0,255,0,80));}
    void AfficherRectangle(RenderWindow &app){
app.draw(rectangle);  }

};
/*class Information
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;
   Animation anim;
   RectangleShape rectangle;

   Information(string namerectangle,RectangleShape &rectangle)
   {
     life=1;
     this->name=namerectangle;
     this->rectangle=rectangle;
     RectangleShape rectangle ;
       rectangle.setOrigin(-R,R*3);
    rectangle.setSize(sf::Vector2f(R*3, R*3));
    rectangle.setFillColor(Color(0,255,0,80));
   }

   void settings(Animation &a,int X,int Y,float Angle=0,int radius=1)
   {
     anim = a;
     x=X; y=Y;
     angle = Angle;
     R = radius;
     
   }

   virtual void update(){};

   void draw(RenderWindow &app,RectangleShape rectangle)
   {
      
  
    // anim.rectangle.setPosition(x,y);
   //  anim.rectangle.setRotation(angle+90);
    // anim.sprite.setRotation(angle+30);   
   //  app.draw(anim.rectangle);
     app.draw(rectangle);
/*
     CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,80));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     app.draw(circle);
   }

   virtual ~Information(){};
};*/
class Entity 
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;
   Animation anim;
   Rectangle lerectangle;

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

    RectangleShape rectangle;
   
    rectangle.setSize(sf::Vector2f(R*2.5, R*2.5));     
    rectangle.setOrigin(-R,R*3);
    rectangle.setPosition(x,y);
     
     if(!enable_tracker){
     /* //Shape Line   = sf::Shape::Line(X1, Y1, X2, Y2, Epaisseur, Couleur, [Bordure], [CouleurBordure]);*/
    //rectangle.setSize(sf::Vector2f(R*2.5, R*2.5)); 
    rectangle.setSize(sf::Vector2f(R*5.0, R*5.0));     
    rectangle.setOrigin(-R*1.3,R*3);
    rectangle.setPosition(x,y);
    rectangle.setFillColor(Color(0,255,0,80));
     // Ligne diagonale du coin inférieur gauche au coin supérieur droit
    sf::VertexArray diagonale(sf::Lines, 2);
    diagonale[0].position = sf::Vector2f(rectangle.getPosition().x+R, rectangle.getPosition().y-R ); // coin inférieur gauche
    diagonale[0].color = sf::Color::Red;
    //diagonale[1].position = sf::Vector2f(rectangle.getPosition().x + rectangle.getSize().x, rectangle.getPosition().y); // coin supérieur droit
   // diagonale[1].color = sf::Color::Red;
    diagonale[1].position = sf::Vector2f(rectangle.getPosition().x +R/2, rectangle.getPosition().y -R/2);
    diagonale[1].color = sf::Color::Red;

 app.draw(rectangle);
 app.draw(diagonale);
   
     
     }else cout << "notracking" << endl;
/*
     CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,80));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     app.draw(circle);*/
   }

   virtual ~Entity(){};
};


class asteroid: public Entity
{
   public:
   asteroid()
   {
     dx=rand()%8-4;
     dy=rand()%8-4;
     name="asteroid";
   }

   void update()
   {
       
     x+=dx/2;
     y+=dy/2;

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
   
     dx=cos(angle*DEGTORAD)*13;
     dy=sin(angle*DEGTORAD)*13;
    //  angle+=rand()%7-3;  /*try this* tir en angle*/
      //vistesse deplacement du tir
     x+=dx/2;
     y+=dy/2;
   
     if (x>W || x<0 || y>H || y<0) life=0;
   }

};


class player: public Entity
{
   public:
   bool thrust;
   bool spaceshipleft=false;

    string getplayername(){return name;}
   player()
   {
     name="player";
   }

   void update()
   {
     if (thrust)
      { dx+=cos(angle*DEGTORAD)*0.8;
        dy+=sin(angle*DEGTORAD)*0.8; }if (spaceshipleft)

        {
          dx+=0.99;
          dy=0;
        }
        

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
    //position de la fenetre;
    app.setPosition(sf::Vector2i(poswindowX,poswindowY));
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
   int var = pos_text1_X;
   string var2 = "\"la var \"+ var"  ;
   

     

    Animation sExplosion(t3, 0,0,256,256, 48, 0.5);
    Animation sRock(t4, 0,0,64,64, 16, 0.2);
    Animation sRock_small(t6, 0,0,64,64, 16, 0.2);
    Animation sBullet(t5, 0,0,32,64, 16, 0.8);
    Animation sPlayer(t1, 40,0,40,40, 1, 0);
    Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sPlayer_left(t1, 0,0,40,40, 1, 0);
    Animation sExplosion_ship(t7, 0,0,192,192,68, 0.5);
   // Animation sExplosion_ship(t7, 0,0,800,500,48, 0);

 // Load the sounds used in the game

   

    std::list<Entity*> entities;
//nbr asteroide grand
    for(int i=0;i<6;i++)
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
            
//Gestion des evenements fonction inputhandler
            if (event.type == Event::KeyPressed)
            //Gestion du tir
             if (event.key.code == Keyboard::Space)
              {
                bullet *b = new bullet();
                b->settings(sBullet,p->x,p->y,p->angle,10);
                entities.push_back(b);
              
              }
          //Gestion des evenements fonction inputhandler
              //Gestion du deplacement vaisseau
              if(event.key.code == Keyboard::Right) p->angle+=3;
              if(event.key.code == Keyboard::Left) p->angle-=3;
              
              //version avec sprite vers la gauche.
              //if((event.key.code == Keyboard::Left)&&(p->spaceshipleft=true))p->angle-=3;
              //else p->spaceshipleft=false;
              if(event.key.code == Keyboard::Up) p->thrust=true;
              else p->thrust=false;
              //fermeture de la fenetre par echape ou par croix
              //appel de la fonction InputHandler
              InputHandler(event,app);
        
           
        }

 

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
            
            //nombre de sération grand rock en small
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
           // e->settings(sExplosion,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);
            

            p->settings(sPlayer,W/2,H/2,0,20);
           // p->settings(sPlayer,W/2,-750,0,20);
            p->dx=0; p->dy=0;
           }
     }


    if (p->thrust) { p->anim = sPlayer_go;}
    else if ((p->thrust)&&(p->spaceshipleft)) { p->anim = sPlayer_left;}
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

  
   Rectangle *lerectangle= new Rectangle("nomrectangle",22,33,0,133);
//Rectangle lerectangle("nomrectangle",22,33,0,1);
      

  app.draw(background);
  
      // lerectangle.AfficherRectangle(app);
   for(auto i:entities) i->draw(app);
   lerectangle->AfficherRectangle(app);
    
   app.display();
    }

   
    return 0;
}
//Fonctions:
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
