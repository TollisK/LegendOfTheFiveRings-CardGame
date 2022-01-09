#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include "Card.h"
using namespace std;


class Item : public GreenCard{
protected:
  int Durability;
public:
  Item(int Dur,int Att,int Def,int Min,string txt,int EffB,int EffC,string nam,int isT,int cos)
  :GreenCard(Att,Def,Min,txt,EffB,EffC,nam,isT,cos),Durability(Dur)
  {
    //cout << "Item constructor"<<endl;
  }
  int getType(){
    return 4;
  }
  int getDurability(){
    return Durability;
  }
  Item(Item& I)
  :GreenCard(I)
  {
    std::cout << "Item copy" << '\n';
  }
  virtual ~Item(){
    //cout << "Item destructor"<<endl;
  }
  void Reveal(){
    GreenCard::Reveal();
    cout<<"Durability:"<<Durability<<endl<<endl;
  }
  void changeDurability(){
    Durability--;
  }

};

class Katana : public Item{
public:
  Katana(string name2)
  :Item(3,2,0,1,"A good ol Katana",1,2,name2,0,0)
  {
    //cout << "Katana constructor"<<endl;
  }
};

class Spear : public Item{
public:
  Spear(string name2)
  :Item(3,0,2,1,"A good ol Spear",1,2,name2,0,0)
  {
    //cout << "Spear constructor"<<endl;
  }
};

class Bow : public Item{
public:
  Bow(string name2)
  :Item(5,2,2,2,"A good ol Bow",3,4,name2,0,2)
  {
    //cout << "Bow constructor"<<endl;
  }
};

class Ninjato : public Item{
public:
  Ninjato(string name2)
  :Item(4,3,3,3,"A good ol Ninjato",2,2,name2,0,4)
  {
    //cout << "Ninjato constructor"<<endl;
  }
};

class Wakizashi : public Item{
public:
  Wakizashi(string name2)
  :Item(8,5,5,3,"A good ol Wakizashi",3,3,name2,0,8)
  {
    //cout << "Wakizashi constructor"<<endl;
  }
};

#endif
