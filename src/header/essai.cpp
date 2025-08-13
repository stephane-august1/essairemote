#include <time.h>
#include <list>
#include "math.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <array>
#include <sstream>
#include <array>


using namespace std;


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

int main()
{

    //  cout << "entrer le nombre d'objet point voulu" << endl;
    int nbrObjet=0;
  // cin >> nbrObjet ;
  const int nbrcase=3;
  // cout << "entrer le nombre de case par objet voulu" << endl;
 //  cin >> nbrcase;

  Point *p = new Point("pointp",1,4);
  Point *p1 = new Point("pointp1",13,4);

//p->Afficherpoint();

   /* vector<Point *> v;
for(auto e: v){
   cout << e->name << endl;
   e->Afficherpoint();}*/
   Point *p3 = new Point("point3t",4,6);
   p->Afficherpoint();
     
      // Basic 10-element integer array.
   //vec[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

constexpr size_t size = 4;
   
    vector<string> v={"traits_p","ddede","dede"};;
//Auto[size];
auto d = int{10};
string lenom =p->name;
int positiondex =p->positionx;
    // Assign a new value to the first element
   /* numbers[0]->name =p[0].name;
     numbers[1]->positionx= p[1].positionx;
      numbers[2]->positiony= p[2].positiony;
      cout << numbers[0] << "\n" <<endl;
      cout << numbers[1] <<"\n" << endl;
      cout << "la"<<numbers[2] << "\n" <<endl;*/
      // numbers[0]=(Point *) p;
     //  numbers[1]= (Point *) p3;
      // numbers[2]= (Point *) &p;
       //numbers[1]=p->name;
     // numbers[3].push_back(Point p4 = new Point);
    // monvector.push_back(new Point ("fff",4,8));
    // monvector.push_back(p);
    // monvector.push_back(p3);
      // Declare an array of doubles to be allocated on the stack
    string numbers[] {};
   // string  val=p;
     string valeur=p->name;
      string valeur2 =(p3->name);
     // (*numbers).push_back(&p);
      std::list<Point*> points;
     points.push_back(p);
    // numbers[0]->name=p.name;
     //  cout <<"adresse denumbers[0] : " << numbers[0]  <<endl;
     //  cout <<"adresse p sur numbers[1] : " << numbers[1] <<endl;
     //cout <<"adresse p sur numbers[2] : " << points << "\n" <<endl;
      // cout << "adresse monvector = "<<monvector[2] <<endl;
     //   cout << "adresse p = "<<&p  <<endl;
     //  cout << "vect = "<<vect[1] << "\n" <<endl;
    
   /*    cout << "number[1]"<<numbers[1] <<"\n" << endl;
       for(auto& y: v ) { // Access by value using a copy declared as a specific type.
           int i=0;
           i=i+1;            // Not preferred.
        cout << "i= "<< v << "numbers: " << y << " ";
    }
    cout << endl;*/
    int i=0;
    for(auto p: points){
        
            p->Afficherpoint();
              p1->Afficherpoint();
                p3->Afficherpoint();
    }    
    std::cout << endl;
//moddifi p name
p->name="point1";p1->name="point2";p3->name="point3";
        for(auto p: points){
         p->Afficherpoint();
              p1->Afficherpoint();
                p3->Afficherpoint();
    }    
            

    
    std::cout << endl;
// p->Afficherpoint();
   // pointArray[nbrPoint+1]->name = p[nbrPoint+1].name;
    // Range-based for loop to iterate through the array.
 /*   for( Array y : vect ) { // Access by value using a copy declared as a specific type.
                       // Not preferred.
        cout << y << " ";
    }
    cout << endl;

    // The auto keyword causes type inference to be used. Preferred.

    for( auto y : x ) { // Copy of 'x', almost always undesirable
        cout << y << " ";
    }
    cout << endl;

    for( auto &y : x ) { // Type inference by reference.
        // Observes and/or modifies in-place. Preferred when modify is needed.
        cout << y << " ";
    }
    cout << endl;*/

   // x[]=;
   
 
   
// int tab2 []={p,p2,p3};
/*   string tab[nbrcase] ={"ddd","ccc"};
   string*pt1;
   pt1 = &tab[0];
   int*pt2;




//creation des objet Points:

   Point *p = new Point[nbrPoint];
   for(int i=0;i<=nbrPoint+1;i++){
cout << "entrer" << nbrPoint+1<< "le premier point de forme text,nbr,nbr" << endl;
cin >> p[i].name>> p[i].posx >> p[i].posy;
cout << "\n"; 

pointArray[nbrPoint+1]->name = p[nbrPoint+1].name;
 pointArray[nbrPoint+1]->posx = p[nbrPoint+1].posx;
  pointArray[nbrPoint+1]->posy = p[nbrPoint+1].posy;
 // return Point pointArray[];
   }
  for(int i=0;i<2;i++){
         nbrObjet+1;
        // cout << "nbrObjet "<<"i="<< nbrcase << " - "<< + nbrObjet << "\n" << endl;
          for(int j=0;j<=2;j++){
                nbrcase+1;
     cout << "nbrObjet "<<"i= " << i<<"-"<< "j= " << j << " - "<< nbrObjet << "\n" << endl;
              //  cout << "nbrObjet "<< nbrObjet <<"case: " << nbrcase << "\n" << endl;
    }
    
    }
   
   // Array de pointers qui pointe sur class 'Point' objects
   
   
   //Point *p = new Point{};
  for(int i=0;i<nbrObjet;i++){
    nbrObjet+1;
              Point *p= new Point{};
        
         cout << "entre le nom avec guillemets puis 2 chiffres x et y " << endl;
        cin >> p[i].name>> p[i].posx >> p[i].posy;
     for(int j=0;j<=nbrcase;j++){
      
        nbrcase+1;
       
//Point p[i][j]= new Point(p[i][j].name,p[i][j].posx ,p[i][j].posy);


       // cin >> p[i].name>> p[i].posx >> p[i].posy;
int positionduX,positionduY;
string lenom;
int u=nbrObjet;
      Point* PointArray1[i][j];
PointArray1[i][j] = new Point;

cout << "PointArray1[i] " << PointArray1[i][j]<< "i=" << i << endl;
cout << "PointArray1[i] " << PointArray1[1][j]<< "i=rang1: " << i << endl;
cout << "p[j].name" << p[j].name << endl;
cout << "p[i].name" << p[i].name << endl;
//cin >>name = p[i][j].name >> p[i][j].posx >> p[i][j].posy; 
    PointArray1[i][0]->name= p[j].name;
    PointArray1[i][1]->posx= p[j].positionx;
    PointArray1[i][2]->posy= p[j].positiony;

  cout << PointArray1[i][0] <<"\n"<< endl;
  cout << PointArray1[i][1] <<"\n"<< endl;
  cout << PointArray1[i][2] <<"\n"<< endl;
  //return Point;
// return PointArray1[i][j]->Afficherpoint();

}

}
   vector<Point *> v;
for(auto e : v){
   e->Afficherpoint();}
//cout << PointArray1[0][2] << endl;
    PointArray1[1]->name = "pointeur5";
    PointArray1[2]->posx = 33;
    PointArray1[3]->posy = 55;


pointArray2[1] = new Point;
  pointArray2[0]->name = "pointeur6";
 pointArray2[1]->posx = 33;
  pointArray2[2]->posy = 88;


pointArray3[2] = new Point;
  pointArray3[0]->name = "pointeur7";
 pointArray3[1]->posx =99;
  pointArray3[2]->posy = 47;

  // PointArray1[1][1]->Afficherpoint();
 for(int i=0;i<=nbrObjet;i++){
     for(int j=0;j<=nbrcase;j++){
        cout << "premier indice tab" << "["[i] + "]" << "["[j] +"]" << endl;
//PointArray1[i][j]->Afficherpoint();

 }}





// Display the models of each car using the show() method






// Display the models of each car using the show() method



  for(int i=0;i<=nbrPoint;i++)
{
//i+1;
cout << "resultat"<< " i: "<< i << endl;
// p[i]->Afficherpoint() ; 
 }
 
cout << "adresse de &p " << &p << " fin "<< endl;
cout << "adresse de &tab " << &tab << " fin "<< endl;
cout << "adresse de pt1 " << pt1 << " fin "<< endl;
cout << "adresse de *pt1 " << *pt1 << " fin "<< endl;
cout << "ajoute au pt1 " << *pt1+"eeee" << " fin "<< endl;
  // cout << "x est var: " << *p << " fin "<< endl;
   cout << "x est var: " << *(pt1+1) << " fin "<< endl; 
   cout << "x est var: " << *(pt1+1) << " fin "<< endl;  
   cout << "x est var: " << *pt2 << " fin "<< endl;
   
   


  // p[nbrdepoint]->Afficherpoint(); }*/
return 0;
}