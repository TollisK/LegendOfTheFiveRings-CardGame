#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <list>
using namespace std;

class Card{
protected:
  string name;
  int isTapped;
  int cost;
public:
  virtual void changetap(int value){
    isTapped=value;
  }
  Card(string nam,int isT,int cos)
  :name(nam),isTapped(isT),cost(cos)
  {
    //cout << "Card constructor" << '\n';
  }
  Card(Card& C)
  :name(C.name),isTapped(C.isTapped),cost(C.cost)
  {
    std::cout << "Card copy" << '\n';
  }
  virtual ~Card(){
    //cout << "Card destructor" << '\n';
  }
  virtual void Reveal(){
    cout<<"Name: "<<name<<endl<<"isTapped: "<<isTapped<<endl<<"Cost: "<<cost<<endl;
  }
  virtual int getisTapped()const{
    return isTapped;
  }
  virtual int getcost()const{
    return cost;
  }
  string getname(){
    return name;
  }
  virtual int getType(){
    return 0;
  }


};

class GreenCard : public Card{
protected:
  int AttackBonus;
  int DefenceBonus;
  int MinimumHonor;
  string Cardtxt;
  int EffectBonus;
  int EffectCost;
public:
  GreenCard(int Att,int Def,int Min,string txt,int EffB,int EffC,string nam,int isT,int cos)
  :AttackBonus(Att),DefenceBonus(Def),MinimumHonor(Min),Cardtxt(txt),EffectBonus(EffB),EffectCost(EffC),Card(nam,isT,cos)
  {
    //cout<<"GreenCard constructor"<<endl;
  }
  GreenCard(GreenCard& G)
  :AttackBonus(G.AttackBonus),DefenceBonus(G.DefenceBonus),MinimumHonor(G.MinimumHonor),Cardtxt(G.Cardtxt),EffectCost(G.EffectCost),EffectBonus(G.EffectBonus),Card(G)
  {
    std::cout << "GreenCard copy" << '\n';
  }
  virtual ~GreenCard(){
    //cout << "GreenCard destructor"<<endl;
  }
  int getminimhonor(){
    return MinimumHonor;
  }
  int AttackBonusget(){
    return AttackBonus;
  }
  int DefenceBonusget(){
    return DefenceBonus;
  }
  int EffectBonusget(){
    return DefenceBonus;
  }
  int EffectCostget(){
    return DefenceBonus;
  }
  string getname()const{
    return name;
  }
  void bonusactivate(){
    cost=cost+EffectCost;
    AttackBonus=AttackBonus+EffectBonus;
    DefenceBonus=DefenceBonus+EffectBonus;
  }
  void hebrokenvm(){
    cost=cost-EffectCost;
    AttackBonus=AttackBonus-EffectBonus;
    DefenceBonus=DefenceBonus-EffectBonus;
  }

  static GreenCard* Draw(list<GreenCard *> *green){
    static bool firstcard=false;
     if (firstcard){
      firstcard=true;
       return green->front();
     }
    green->pop_front();
    return green->front();
  }
  void Reveal(){
    cout<<"GreenCard:"<<endl<<"AttackBonus: "<<AttackBonus<<endl<<"DefenceBonus:"<<DefenceBonus<<endl<<"MinimumHonor:"<<MinimumHonor<<endl<<"Cardtxt:"<<Cardtxt<<endl<<"EffectBonus:"<<EffectBonus<<endl<<"EffectCost:"<<EffectCost<<endl;
    Card::Reveal();
  }
};

class BlackCard : public Card{
protected:
  int isRevealed;
public:
  BlackCard(string nam,int isT,int cos)
  :isRevealed(0),Card(nam,isT,cos)
  {
    //cout<<"BlackCard constructor"<<endl;
  }
  virtual ~BlackCard(){
    //cout << "BlackCard destructor"<<endl;
  }

  string getname()const{
    return name;
  }

  static BlackCard* Draw(list<BlackCard *> *black){
    static bool firstcard2=false;
     if (firstcard2){
      firstcard2=true;
       return black->front();
     }
    black->pop_front();
    return black->front();
  }

  void Reveal(){
    isRevealed = 1;
    cout<<"BlackCard: "<<endl;
    Card::Reveal();
  }
  virtual void Print(){
    cout<<"BlackCard: "<<endl;
    Card::Reveal();
  }
};


#endif
