#ifndef HOLDING_H
#define HOLDING_H
#include <iostream>
#include "Card.h"
#define INDEF       5
#define HARVARD  5
#define STRHONOR  5
#define MINEVALUE 3
#define GOLDMINEVALUE 5
#define CRYSTALMINEVALUE 6
using namespace std;

class Mine;
class GoldMine;
class CrystalMine;


class Holding : public BlackCard{
protected:
  int HarvestValue;
public:
  int getType(){
    return 2;
  }
  Holding(int Harv,string nam,int isT,int cos2)
  :HarvestValue(Harv),BlackCard(nam,isT,cos2)
  {
    //cout << "Holding constructor"<<endl;
  }
  int getharv()const{
    return HarvestValue;
  }
  virtual ~Holding(){
    //cout << "Holding destructor"<<endl;
  }
  void Reveal(){
    BlackCard::Reveal();
    cout<<"Harvest Value:"<<HarvestValue<<endl;
  }
  void Print() {
    BlackCard::Print();
    cout<<"Harvest Value:"<<HarvestValue<<endl;
  }
  virtual int ismine(){
    return 0;
  }
  virtual void connect(Holding*H){
    std::cout << "NOT THIS ONE" << '\n';
  }

  virtual void connect(Holding* H,int i){
        std::cout << "NOT THIS ONE" << '\n';
  }
  static void getMine(Holding* hold,Mine** mine){
    if(hold->ismine()==1){
      (*mine)=(Mine *)hold;
    }
    else{
    std::cout << "Not a mine" << '\n';
    (*mine)= NULL;
    }
  }

  static void getGoldMine(Holding* hold,GoldMine** mine){
    if(hold->ismine()==2){
      (*mine)=(GoldMine *)hold;
    }
    else{
    std::cout << "Not a Goldmine" << '\n';
    (*mine)= NULL;
    }
  }

  static void getCrystalMine(Holding* hold,CrystalMine** mine){
    if(hold->ismine()==3){
      (*mine)=(CrystalMine *)hold;
    }
    else{
    std::cout << "Not a CrystalMine" << '\n';
    (*mine)= NULL;
    }
  }
};



class GiftsandFavour:public Holding{
public:
GiftsandFavour(string name2)
:Holding(2,name2,0,2)
{
  //cout:://cout << "GiftsandFavour constructor" << '\n';
}
};

class Plain:public Holding{
public:
Plain(string name2)
:Holding(2,name2,0,2)
{
  //cout:://cout << "Plain constructor" << '\n';
}
};

class Farmland:public Holding{
public:
Farmland(string name2)
:Holding(4,name2,0,3)
{
  //cout:://cout << "Farmland constructor" << '\n';
}
};

class Mine:public Holding{
private:
  GoldMine* upperholding;
public:
Mine(string name2)
:Holding(MINEVALUE,name2,0,5),upperholding(NULL)
{
  //cout:://cout << "Mine constructor" << '\n';
}
virtual int ismine(){
  return 1;
}

void connect(Holding* Get);


};

class GoldMine:public Holding{
private:
  Mine* subholding;
  CrystalMine* upperholding;
public:
GoldMine(string name2)
:Holding(GOLDMINEVALUE,name2,0,7),upperholding(NULL),subholding(NULL)
{
  //cout:://cout << "GoldMine constructor" << '\n';
}

void connect(Holding*);




virtual int ismine(){
  return 2;
}
};

class CrystalMine:public Holding{
private:
  GoldMine* subholding;
public:
CrystalMine(string name2)
:Holding(CRYSTALMINEVALUE,name2,0,12),subholding(NULL)
{

}

void connect(Holding* G,int i);

virtual int ismine(){
  return 3;
}
};

class Stronghold : public Holding{
private:
  int indef;
  int starthonor;
public:
  int getdef()const{
    return indef;
  }
  int gethonor()const{
    return starthonor;
  }
  Stronghold(string name2)
:indef(INDEF),starthonor(STRHONOR),Holding(HARVARD,name2,0,0)
  {
    //cout:://cout << "Create Stronghold" << '\n';
  }

};






#endif
