#ifndef FOLLOWER_H
#define FOLLOWER_H
#include <iostream>
#include "Card.h"

using namespace std;


class Follower : public GreenCard{
public:
  Follower(int Att,int Def,int Min,string txt,int EffB,int EffC,string nam,int isT,int cos)
  :GreenCard(Att,Def,Min,txt,EffB,EffC,nam,isT,cos)
  {
    //cout << "Follower constructor"<<endl;
  }
  int getType(){
    return 3;
    }
  Follower(Follower& F)
  :GreenCard(F)
  {
    std::cout << "Follower copy" << '\n';
  }
  virtual ~Follower(){
    //cout << "Follower destructor"<<endl;
  }
  void Reveal(){
    GreenCard::Reveal();
    cout<<endl;
  }
};

class Footsoldier : public Follower{
public:
  Footsoldier(string name2)
  :Follower(2,0,1,"A good ol Footsoldier",1,2,name2,0,0)
  {
    //cout << "Footsoldier constructor" << '\n';
  }
};

class Archer : public Follower{
public:
  Archer(string name2)
  :Follower(0,2,1,"A good ol Archer",1,2,name2,0,0)
  {
    //cout << "Archer constructor" << '\n';
  }
};

class Sieger : public Follower{
public:
  Sieger(string name2)
  :Follower(3,3,2,"A good ol Sieger",2,3,name2,0,5)
  {
    //cout << "Sieger constructor" << '\n';
  }
};

class Cavalry : public Follower{
public:
  Cavalry(string name2)
  :Follower(4,2,3,"A good ol Cavalry",3,4,name2,0,3)
  {
    //cout << "Cavalry constructor" << '\n';
  }
};

class Atakebune : public Follower{
public:
  Atakebune(string name2)
  :Follower(2,4,3,"A good ol Atakebune",3,4,name2,0,3)
  {
    //cout << "Atakebune constructor" << '\n';
  }
};

class Bushido : public Follower{
public:
  Bushido(string name2)
  :Follower(8,8,6,"A good ol Bushido",3,8,name2,0,8)
  {
    //cout << "Bushido constructor" << '\n';
  }
};


#endif
