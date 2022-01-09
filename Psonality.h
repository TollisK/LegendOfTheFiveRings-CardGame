#ifndef PSONALITY_H
#define PSONALITY_H
#include <iostream>
#include "Follower.h"
#include "Item.h"
#include "Card.h"
#include <vector>
using namespace std;


class Personality : public BlackCard{
protected:
  int Attack;
  int Defence;
  int Honor;
  int isDead;
  int Ready;
  std::vector<Follower*>* myfollowers;
  std::vector<Item*>* myitems;
public:
  void changehonor(){
    Honor--;
  }
  int getReady(){
    return Ready;
  }
  int getType(){
    return 1;
  }
  int getAttack(){
    return Attack;
  }
  int getDefence(){
    return Defence;
  }
  vector<Item*>* getitems(){
    return myitems;
  }
  vector<Follower*>* getfollowers(){
    return myfollowers;
  }
  int gethonor(){
    return Honor;
  }
  void changeReady(int i){
    Ready = i;
  }
  void addcard(Follower* F){
    myfollowers->push_back(F);
    Attack=Attack+F->AttackBonusget();
    Defence=Defence+F->DefenceBonusget();
  }
  void addcard(Item* F){
    myitems->push_back(F);
    Attack=Attack+F->AttackBonusget();
    Defence=Defence+F->DefenceBonusget();
  }
  Personality(int At,int Def,int Ho,int Is,string nam,int isT,int cos)
  :Attack(At),Defence(Def),Honor(Ho),isDead(Is),BlackCard(nam,isT,cos),Ready(0)
  {
    myfollowers=new vector<Follower*>;
    myitems=new vector<Item*>;
  }
  virtual ~Personality(){
    //cout << "Personality destructor"<<endl;
  }
  void Reveal(){
    BlackCard::Reveal();
    cout<<"Attack: "<<Attack<<"\nDefence: "<<Defence<<endl<<"Honor: "<<Honor<<endl<<"isDead: "<<isDead<<endl;
  }

};

class Attacker : public Personality{
public:
  Attacker(string name2)
  :Personality(3,2,2,0,name2,0,5)
  {
    //std:://cout << "Attacker constructor" << '\n';
  }

};

class Defender : public Personality{
public:
  Defender(string name2)
  :Personality(2,3,2,0,name2,0,5)
  {
    //std:://cout << "Defender constructor" << '\n';
  }

};

class Shogun : public Personality{
public:
  Shogun(string name2)
  :Personality(10,5,8,0,name2,0,15)
  {
    //std:://cout << "Shogun constructor" << '\n';
  }

};

class Chancellor : public Personality{
public:
  Chancellor(string name2)
  :Personality(5,10,8,0,name2,0,15)
  {
  //  std:://cout << "Chancellor constructor" << '\n';
  }

};

class Champion : public Personality{
public:
  Champion(string name2)
  :Personality(20,20,12,0,name2,0,30)
  {
  //  std:://cout << "Champion constructor" << '\n';
  }

};
#endif
