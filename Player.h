#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include "Card.h"
#include "Psonality.h"
#include "Holding.h"
#include "Follower.h"
#include "Item.h"
#define MAXHANDSIZE 6
#define STARTHAND 4

using namespace std;


class Province{
private:
  BlackCard* mycard;
  int defense;
  int isRevealed;
  int isDead;
public:
  Province(BlackCard* bobby,int def)
  :mycard(bobby),defense(def),isRevealed(0),isDead(0)
  {
    //std::cout << "Province constructor" << '\n';
  }
  void Reveal(){
    isRevealed = 1;
    mycard->Reveal();
    std::cout << "Province defense: " <<defense<<endl<<endl;
  }
  int getDead()const{
    return isDead;
  }
  void changeDead(){
    isDead = 1;
  }
  int getDefence(){
    return defense;
  }

  void PrintProv(){
  if (isDead==0) {
    if (isRevealed==0) {
      std::cout << "Card is hidden until start of round!" << '\n';
    }
    else{
      Reveal();
    }
  }
}
BlackCard* getblack(){
  return mycard;
}
void Setblack(BlackCard* black){
  mycard = black;
}

};

class Player{
protected:
  string name;
  list<GreenCard*>* green;
  list<BlackCard*>* black;
  Stronghold* mystronghold;
  Province** provinces;
  vector<GreenCard*>* hand;
  int cardsinhand;
  vector<Personality*>* boardPersonalities;
  vector<Holding*>* boardHoldings;
public:
  Stronghold* getstrong(){
    return mystronghold;
  }
  Province** getprov(){
    return provinces;
  }
  vector<GreenCard*>* gethand(){
    return hand;
  }
  int getcards(){
    return cardsinhand;
  }
  vector<Personality*>* getboardPer(){
    return boardPersonalities;
  }
  vector<Holding*>* getboardHol(){
    return boardHoldings;
  }
  list<GreenCard*>* getgreen(){
    return green;
  }
  list<BlackCard*>* getblack(){
    return black;
  }
  void increasecards(){
    cardsinhand++;
  }
  string getname(){
    return name;
  }

  Player(string nam,list<GreenCard*>* grn,list<BlackCard*>* blk)
  :green(grn),black(blk),name(nam),boardHoldings(NULL),boardPersonalities(NULL),cardsinhand(4)
  {
    boardHoldings = new vector<Holding*>;
    boardPersonalities = new vector<Personality*>;
    hand = new vector<GreenCard*>;
    provinces = new Province* [4];
    mystronghold=new Stronghold("A good ol Stronghold");
    for (size_t i = 0; i < 4; i++){
      provinces[i]=new Province(BlackCard::Draw(black),mystronghold->getdef());
    }
    for (size_t i = 0; i < STARTHAND; i++){
      hand->push_back(GreenCard::Draw(green));
    }
  }


  ~Player(){
    delete mystronghold;
    boardHoldings->clear();
    boardPersonalities->clear();
    hand->clear();
    for(int i=0;i<4;i++){
      delete provinces[i];
    }
    delete[] provinces;

    list<GreenCard *>::iterator it;
    list<BlackCard *>::iterator it2;

    if (green){
      for (it = green->begin(); it != green->end(); it++){
        green->remove((*it));
        delete *it;
        it = green->begin();
      }
    }
    if (black){
      for (it2 = black->begin(); it2 != black->end(); it++){
        black->remove((*it2));
        delete *it2;
        it2 = black->begin();
      }
    }


  /*list<Personality *>::iterator it;
	list<Holding *>::iterator it2;

  if (boardPersonalities){
	for (it = boardPersonalities->begin(); it != boardPersonalities->end(); it++)
	{
		boardPersonalities->remove((*it));
		delete *it;
		it = boardPersonalities->begin();
	}
}
if (boardHoldings){
	for (it2 = boardHoldings->begin(); it2 != boardHoldings->end(); it++)
	{
		boardHoldings->remove((*it2));
		delete *it2;
		it2 = boardHoldings->begin();
	}
}
  if (boardPersonalities)
	delete boardPersonalities;
  if (boardHoldings)
	delete boardHoldings;
  for (size_t i = 0; i < 4; i++) {
    if (provinces[i]!=NULL)
    delete provinces[i];
  }
  delete[] provinces;
  for (size_t i = 0; i < MAXHANDSIZE; i++) {
    if (hand[i]!=NULL)
    delete hand[i];
  }
  delete[] hand;
  delete mystronghold;*/
}

void addPersonality(Personality* P){
  boardPersonalities->push_back(P);
}
void addHold(Holding* H){
  int i;
  int type=H->ismine();
  if (type==1) {
    for (int i = 0; i <boardHoldings->size() ; i++) {
      if(boardHoldings->at(i)->ismine()==2){
        boardHoldings->at(i)->connect(H);
      }
    }
  }
  else if (type==2) {
    for(i=0;i<boardHoldings->size();i++) {
      if(boardHoldings->at(i)->ismine()==1){
        boardHoldings->at(i)->connect(H);
      }
    }
    for(i=0;i<boardHoldings->size();i++){
      if(boardHoldings->at(i)->ismine()==3){
        boardHoldings->at(i)->connect(H);
      }
    }
  }
  else if(type==3){
    for(i=0;i<boardHoldings->size();i++){
      if(boardHoldings->at(i)->ismine()==2){
        boardHoldings->at(i)->connect(H);
      }
    }
  }
  boardHoldings->push_back(H);

}
};

#endif
