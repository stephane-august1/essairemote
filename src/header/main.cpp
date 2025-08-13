#include <time.h>
#include <list>
#include "math.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>


using namespace std;
using namespace sf;

const int W = 1200;
const int H = 800;
Font font;
Text text;
float x,y,dx,dy,R,angle;
float Angle=0;
int radius=1;
float DEGTORAD = 0.017453f;

//prototype de la fonction InputHandler
void InputHandler(Event event, RenderWindow& app);
class Point{
public:
     string name,nom;
    int positionx,positiony;
    int newx,newy;
    int posx,posy;
    //accesseurs:
    int getPositionX(){return positionx;}
    int setPositionX(int newx){positionx=newx;}
    string getName(){return name;}
    
    int getPositionY(){return positiony;}
    int setPositionY(int positiony){positiony=positiony;}
    string  setName(string nom){name=nom;}


Point( string name,int positionx,int positiony):name(name),posx(positionx),posy(positiony){
    this->positionx=positionx;
    this->positiony=positiony;
this->name=name;}
Point() : name("Unknown"), posx(0), posy(0) {} 
void Afficherpoint(){
    
cout <<"nom : " << name <<" posx,y : "<< positionx <<","<< positiony << "\n ";
}
};

class Animation
{
   public:
   float Frame, speed;
   Sprite sprite;
   RectangleShape rectangle;
   std::vector<IntRect> frames;

   Animation(){}

   Animation (RectangleShape &rectangle, int x, int y, int w, int h, int count, float Speed)
   {
    this->rectangle=rectangle;
     Frame = 0;
     speed = Speed;

     for (int i=0;i<count;i++)
      frames.push_back( IntRect(x+i*w, y, w, h)  );

     rectangle.setPosition(x,y);
     rectangle.setRotation(angle+90);
    
        rectangle.setSize(sf::Vector2f(200, 200));
        rectangle.setOrigin(R,R);
        rectangle.setPosition(100,100);
        rectangle.setFillColor(Color(0,255,0,80));
     rectangle.setOrigin(w/2,h/2);
     
   }


   void update()
   {
     Frame += speed;
     int n = frames.size();
     if (Frame >= n) Frame -= n;
     if (n>0) rectangle.setTextureRect( frames[int(Frame)] );
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
   RectangleShape rectangle;

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
     rectangle.setPosition(x,y);
     rectangle.setRotation(angle+90);
    
        rectangle.setSize(sf::Vector2f(200, 200));
        rectangle.setOrigin(R,R);
        rectangle.setPosition(100,100);
        rectangle.setFillColor(Color(0,255,0,80));
     app.draw(anim.rectangle);
    // app.draw(rectangle);
/*
     CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,80));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     app.draw(circle);*/
   }

   virtual ~Entity(){};
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

int main()
{srand(time(0));

  
        RenderWindow app(VideoMode(W, H), "Asteroids!");
        
   
           
    
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        { //fermeture de la fenetre par echape ou par croix
              //appel de la fonction InputHandler
              InputHandler(event,app);
/*****************partie point******/
        Point *p = new Point("pt1",33,44);
              p->Afficherpoint();  
        list<Point*> points;
      for(auto p: points){
                    p->Afficherpoint();            
    }    cout << endl;  
/*****************end off partie point******/
/*****************partie rectangle******/
     RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(200, 200));
        rectangle.setOrigin(R,R);
        rectangle.setPosition(100,100);
        rectangle.setFillColor(Color(233,255,0,80));
    
     
    // app.draw(rectangle);  
     /************end off partie rectangle******/
     Entity *player = new Entity();
      Animation durectangle(rectangle, 40,0,40,40, 1, 0);
     player->settings(durectangle,200,200,0,20);
    
    
        // player *player = new player();
    //player->settings(sPlayer,200,200,0,20);
   player->draw(app);
    //entities.push_back(player);
   app.display();}
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
