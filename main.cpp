#include "Player.h"
#include "DeckBuilder.h"
#include <iostream>
#include <vector>  // the general-purpose vector container
#include <algorithm>  // remove and remove_if
#include "TypeConverter.hpp"
using namespace std;
TypeConverter Convert;

void Phase1(Player &J){
  cout<<"Player: "<<J.getname()<<endl;
  int i=0;
  J.gethand()->push_back(GreenCard::Draw(J.getgreen()));
  J.increasecards();

  J.getstrong()->changetap(0);

  for (i = 0; i < 4; i++) {
    J.getprov()[i]->Reveal();
  }

  if (J.getboardHol()->size()!=0){
    for (i = 0; i < J.getboardHol()->size(); i++) {
  		 J.getboardHol()->at(i)->changetap(0);
    }
  }

  if (J.getboardPer()->size()!=0){
    for (i = 0; i < J.getboardPer()->size(); i++) {
  		 J.getboardPer()->at(i)->changetap(0);
    }
  }
	for (i = 0; i < J.gethand()->size(); i++) {
		 J.gethand()->at(i)->Reveal();
  }
}

void Phase2(Player &J){
  int i;
  int strongnum;
  int money=0;
  int intinput;
  int intinput2;
  string strinput;
  string strinput2;
  Follower* f;
  Item* it;
  Follower** follow=&f;
  Item** item=&it;
  GreenCard* getridof;
  std::cout << J.getname()<<" is playing" << '\n';
  std::vector<GreenCard*>* v=J.gethand();
  if (J.getboardPer()->size()!=0){
    std::cout << "Your army:" << '\n';
    for (i = 0; i < J.getboardPer()->size(); i++) {
  		 J.getboardPer()->at(i)->Reveal();
    }
    std::cout << "\n \n \nYour hand:" << '\n';
    for (i = 0; i < J.gethand()->size(); i++) {
  	    J.gethand()->at(i)->Reveal();
    }
    std::cout << "Your untapped Holdings:" << '\n';
    for (i = 0; i < J.getboardHol()->size(); i++) {
      if(J.getboardHol()->at(i)->getisTapped() == 0){
        cout<<i<<". \n";
        J.getboardHol()->at(i)->Reveal();
        std::cout  << '\n';
      }
    }
    if (J.getstrong()->getisTapped()==0) {
      strongnum=i;
      std::cout <<strongnum<< ". \n";
      J.getstrong()->Reveal();
    }
    while (strinput!="No") {
    std::cout << "Skip Round? Yes/No" << '\n';
    std::cin >> strinput;
    if (strinput=="No"){
      do{
        std::cout << "Tap a Holding(-1 to skip)" << '\n';
        std::cin >> intinput;
        if(intinput==strongnum){
          if (J.getstrong()->getisTapped()==0) {
            J.getstrong()->changetap(1);
            money=money+J.getstrong()->getharv();
          }
        }
        else if(intinput>=0 && intinput<J.getboardHol()->size()){
          if(J.getboardHol()->at(intinput)->getisTapped() == 0){
            J.getboardHol()->at(intinput)->changetap(1);
            money=money+J.getboardHol()->at(intinput)->getharv();
          }
        }
        std::cout << "Your untapped Holdings:" << '\n';
        for (i = 0; i < J.getboardHol()->size(); i++) {
          if(J.getboardHol()->at(i)->getisTapped() == 0){
            cout<<i<<". \n";
            J.getboardHol()->at(i)->Reveal();
            std::cout  << '\n';
          }
        }

        if (J.getstrong()->getisTapped()==0) {
          strongnum=i;
          std::cout <<strongnum<< ". \n";
          J.getstrong()->Reveal();
        }
        std::cout << "\n \n \nYour hand:" << '\n';
        for (i = 0; i < J.gethand()->size(); i++) {
      	    J.gethand()->at(i)->Reveal();
        }
        std::cout << "Your money: " <<money<< '\n';
        std::cout << "Would you like to tap again?Yes/No" << '\n';
        std::cin >> strinput;
        if(strinput=="Yes"){
        for (i = 0; i < J.getboardHol()->size(); i++) {
          if(J.getboardHol()->at(i)->getisTapped() == 0){
            cout<<i<<". \n";
            J.getboardHol()->at(i)->Reveal();
            std::cout  << '\n';
          }
        }
        if (J.getstrong()->getisTapped()==0) {
          strongnum=i;
          std::cout <<strongnum<< ". \n";
          J.getstrong()->Reveal();
        }
      }
      }while(strinput!="No");
      std::cout << "\n \n \nYour hand:" << '\n';
      for (i = 0; i < J.gethand()->size(); i++) {
    	    J.gethand()->at(i)->Reveal();
      }
      std::cout << "Your money: " <<money<< '\n';
      std::cout << "Would you like to buy?Yes/No" << '\n';
      std::cin >> strinput;
      if (strinput=="Yes"){
      while(strinput=="Yes"){
        std::cout << "Your money: " <<money<< '\n';
        std::cout << "Your army:" << '\n';
        for (i = 0; i < J.getboardPer()->size(); i++) {
      		 J.getboardPer()->at(i)->Reveal();
        }
        std::cout << "\n \n \nYour hand:" << '\n';
        for (i = 0; i < J.gethand()->size(); i++) {
            std::cout << i<<"." << '\n';
      	    J.gethand()->at(i)->Reveal();
        }
        std::cout << "Choose what to buy" << '\n';
        std::cin >> intinput;
        if (intinput>=0 && intinput<J.gethand()->size()) {
          std::cout << "Would you like to pay " <<J.gethand()->at(intinput)->EffectCostget()<<" to gain "<<J.gethand()->at(intinput)->DefenceBonusget()<<" defence and attack "<<  '\n'<<"Yes/No"<<endl;
          std::cin >>strinput2;
          if (strinput2=="Yes") {
            J.gethand()->at(intinput)->bonusactivate();
          }
          if (J.gethand()->at(intinput)->getcost()<=money) {
            std::cout << "Choose a Personality\n" << '\n';
            for (i = 0; i < J.getboardPer()->size(); i++) {
               std::cout <<i << ". \n" ;
          		 J.getboardPer()->at(i)->Reveal();
            }
            std::cin >> intinput2;
            if (J.getboardPer()->at(intinput2)->gethonor()>=J.gethand()->at(intinput)->getminimhonor()){

              money=money-J.gethand()->at(intinput)->getcost();
              Convert.getCorrectType(J.gethand()->at(intinput),follow,item);
              if (*follow){
                J.getboardPer()->at(intinput2)->addcard(*follow);
              }
              else{
                J.getboardPer()->at(intinput2)->addcard(*item);
              }
              if (J.gethand()->at(intinput)){
                J.gethand()->erase(J.gethand()->begin()+intinput);
              }
            }
            else{
              std::cout << "Not enough honor!" << '\n';
            }
          }
          else{
            if(strinput2=="Yes"){
              J.gethand()->at(intinput)->hebrokenvm();
            }
            std::cout << "Not enough money!" << '\n';
          }
        }
        std::cout << "Would you like to buy again?Yes/No" << '\n';
        std::cin >> strinput;
      }
    }
  }
    std::cout << "Type Yes if you want to tap and buy, type No otherwise" << '\n';
    std::cin >> strinput;

  }
}
  else{
     std::cout << "You have no army" << '\n';
  }
}

void Phase3C(Player &Player1){
  int i=0,att=-1;
    std::cout << "Your army ready to attack/block:" << '\n';
    for (i = 0; i < Player1.getboardPer()->size(); i++) {
      if(Player1.getboardPer()->at(i)->getisTapped() == 0){
        cout<<i<<". ";
        Player1.getboardPer()->at(i)->Reveal();
        cout<<endl;
      }
    }
    do{
      cout<<"Select the Personalities you want to attack/block(-1 to stop): ";
      cin >> att;
      if(att == -1)
        break;
      if(att<-1||att>=Player1.getboardPer()->size()){
        continue;
      }
      if(Player1.getboardPer()->at(att)->getisTapped() == 0){
        Player1.getboardPer()->at(att)->changeReady(1);
        cout<<Player1.getboardPer()->at(att)->getname()<<" is ready to attack or block!"<<endl;
      }
    }while(att>=0&&att<Player1.getboardPer()->size());
}


void Phase3B(Player &Player1,Player &Player2){
  int i=0,pro=-1,totaldmg=0,totaldef=0,j=0;
  if(Player1.getboardPer()->size()!=0){
    cout<<"Alive enemy provinces:"<<endl;
    for (i = 0; i < 4; i++) {
      if(Player2.getprov()[i]->getDead()==0){
        cout<<i<<". ";
        Player2.getprov()[i]->Reveal();
      }
    }
    do{
      cout<<"Select the enemy Province that you want to attack('-1' if you want to pass): ";
      cin >> pro;
      if(pro==-1)
        return;
      if(pro<-1||pro>3){
        cout<<"wrong input"<<endl;
        break;
      }
    }while(Player2.getprov()[pro]->getDead()!=0);
    if(pro<-1||pro>3){
      Phase3B(Player1,Player2);
    }

      Phase3C(Player1);
      cout<<"Player: "<<Player2.getname()<<" blocks!"<<endl;
      Phase3C(Player2);

      for (i = 0; i < Player1.getboardPer()->size(); i++) {
        if(Player1.getboardPer()->at(i)->getReady() == 1){
          totaldmg = totaldmg + Player1.getboardPer()->at(i)->getAttack();
        }
      }
      for (i = 0; i < Player2.getboardPer()->size(); i++) {
        if(Player2.getboardPer()->at(i)->getReady() == 1){
          totaldef = totaldef + Player2.getboardPer()->at(i)->getDefence();
        }
      }


      if(totaldmg > totaldef && totaldmg-totaldef > Player2.getprov()[pro]->getDefence()){
        cout<<"Player: "<<Player1.getname()<< " won the battle and destroyed the enemy province!!"<<endl;
        Player2.getprov()[pro]->changeDead();
        //delete all enemy army
        for (i = 0; i < Player2.getboardPer()->size(); i++) {
          if(Player2.getboardPer()->at(i)->getReady() == 1){
            Player2.getboardPer()->erase(Player2.getboardPer()->begin()+i);
            i--;
          }
        }
      }
      else if(totaldmg > totaldef){
        cout<<"Player: "<<Player1.getname()<<" won the battle but didnt destroy the enemy province!"<<endl;
        //delete all enemy army that is ready
        for(i=0;i<Player2.getboardPer()->size(); i++){
          if(Player2.getboardPer()->at(i)->getReady()==1){
            Player2.getboardPer()->erase(Player2.getboardPer()->begin()+i);
            i--;
          }
        }
        //vgale kati dika soy thast ready
        for(i=0;i<Player1.getboardPer()->size(); i++){
          if(Player1.getboardPer()->at(i)->getReady()==1){
            if(Player1.getboardPer()->at(i)->getAttack()>= totaldmg-totaldef){
              Player1.getboardPer()->erase(Player1.getboardPer()->begin()+i);
              i--;
            }
          }
        }

        for(i=0;i<Player1.getboardPer()->size(); i++){
          if(Player1.getboardPer()->at(i)->getReady()==1){
            Player1.getboardPer()->at(i)->changehonor();//einai honor-2 otan feygei kapoios
            //durability sta opla --
            for(j=0;j<Player1.getboardPer()->at(i)->getitems()->size();j++){
              Player1.getboardPer()->at(i)->getitems()->at(j)->changeDurability();
              if(Player1.getboardPer()->at(i)->getitems()->at(j)->getDurability()==0){
                Player1.getboardPer()->at(i)->getitems()->erase(Player1.getboardPer()->at(i)->getitems()->begin()+j);
                j--;
              }
            }
            if(Player1.getboardPer()->at(i)->gethonor() == 0){
              cout<<"Honor equals to zero!"<<endl;
              Player1.getboardPer()->erase(Player1.getboardPer()->begin()+i);
              i--;
            }
          }
        }
      }
      else if(totaldmg == totaldef){
        cout<<"Both players tied!!"<<endl;
        //delete all enemy army thats ready
        for(i=0;i<Player2.getboardPer()->size(); i++){
          if(Player2.getboardPer()->at(i)->getReady()==1){
            Player2.getboardPer()->erase(Player2.getboardPer()->begin()+i);
            i--;
          }
        }
        //delete all friendly artmy thats ready
        for(i=0;i<Player1.getboardPer()->size(); i++){
          if(Player1.getboardPer()->at(i)->getReady()==1){
            Player1.getboardPer()->erase(Player1.getboardPer()->begin()+i);
            i--;
          }
        }
      }
      else{
        cout<<"Player: "<<Player1.getname()<<" lost the battle!!"<<endl;
        //delete all friendly army
        for(i=0;i<Player1.getboardPer()->size(); i++){
          if(Player1.getboardPer()->at(i)->getReady()==1){
            Player1.getboardPer()->erase(Player1.getboardPer()->begin()+i);
            i--;
          }
        }
        //delete kati enemy army
        for(i=0;i<Player2.getboardPer()->size(); i++){
          if(Player2.getboardPer()->at(i)->getReady()==1){
            if(Player2.getboardPer()->at(i)->getAttack()>= totaldef-totaldmg){
              Player2.getboardPer()->erase(Player2.getboardPer()->begin()+i);
              i--;
            }
          }
        }
        for(i=0;i<Player2.getboardPer()->size(); i++){
          if(Player2.getboardPer()->at(i)->getReady()==1){
            Player2.getboardPer()->at(i)->changehonor();
            //durability sto item --
            for(j=0;j<Player2.getboardPer()->at(i)->getitems()->size();j++){
              Player2.getboardPer()->at(i)->getitems()->at(j)->changeDurability();
              if(Player2.getboardPer()->at(i)->getitems()->at(j)->getDurability()==0){
                Player2.getboardPer()->at(i)->getitems()->erase(Player2.getboardPer()->at(i)->getitems()->begin()+j);
                j--;
              }
            }
            if(Player2.getboardPer()->at(i)->gethonor() == 0){
              Player2.getboardPer()->erase(Player2.getboardPer()->begin()+i);
              i--;
            }
          }
        }
      }
      for (i = 0; i < Player1.getboardPer()->size(); i++) {
        if(Player1.getboardPer()->at(i)->getReady()==1){
          Player1.getboardPer()->at(i)->changetap(1);
          Player1.getboardPer()->at(i)->changeReady(0);
        }
      }
      for (i = 0; i < Player2.getboardPer()->size(); i++) {
        if(Player2.getboardPer()->at(i)->getReady()==1){
          Player2.getboardPer()->at(i)->changetap(1);
          Player2.getboardPer()->at(i)->changeReady(0);
        }
      }
    }
  else{
    cout<<"No army to attack!"<<endl;
  }
}

void Phase3A(Player &Player1,Player &Player2){
  if(Player1.getstrong()->gethonor()>=Player2.getstrong()->gethonor()){
    cout<<"Player: "<<Player1.getname()<<" attacks first!"<<endl<<endl;
    Phase3B(Player1,Player2);
    cout<<"Player: "<<Player2.getname()<<" attacks!"<<endl<<endl;
    Phase3B(Player2,Player1);
  }
  else{
    cout<<"Player: "<<Player2.getname()<<" attacks first!"<<endl<<endl;
    Phase3A(Player2,Player1);
    cout<<"Player: "<<Player1.getname()<<" attacks!"<<endl<<endl;
    Phase3A(Player1,Player2);
  }
}


void Phase4(Player& J){
int hidden[4]={0,0,0,0};
int intinput;
int strongnum;
string strinput;
int money=0;
Personality* p;
Personality** per=&p;
Holding* h;
Holding** hol=&h;
int i;
cout<<"Player's: "<<J.getname()<<" turn!"<<endl;
do{
for (i = 0; i < 4; i++) {
  J.getprov()[i]->PrintProv();
}
std::cout << "Your untapped Holdings" << '\n';
for (i = 0; i < J.getboardHol()->size(); i++) {
  if(J.getboardHol()->at(i)->getisTapped() == 0){
    cout<<i<<". \n";
    J.getboardHol()->at(i)->Reveal();
    std::cout  << '\n';
  }
}
if (J.getstrong()->getisTapped()==0) {
  strongnum=i;
  std::cout <<strongnum<< ". \n";
  J.getstrong()->Reveal();
}
std::cout << "Skip round? Yes/No" << '\n';
std::cin >> strinput;
if (strinput!="Yes") {
  do{
    std::cout << "Tap a Holding(-1 to skip)" << '\n';
    std::cin >> intinput;
    if(intinput==strongnum){
      if (J.getstrong()->getisTapped()==0) {
        J.getstrong()->changetap(1);
        money=money+J.getstrong()->getharv();
      }
    }
    else if(intinput>=0 && intinput<J.getboardHol()->size()){
      if(J.getboardHol()->at(intinput)->getisTapped() == 0){
        J.getboardHol()->at(intinput)->changetap(1);
        money=money+J.getboardHol()->at(intinput)->getharv();
      }
    }
    std::cout << "Your untapped Holdings:" << '\n';
    for (i = 0; i < J.getboardHol()->size(); i++) {
      if(J.getboardHol()->at(i)->getisTapped() == 0){
        cout<<i<<". \n";
        J.getboardHol()->at(i)->Reveal();
        std::cout  << '\n';
      }
    }

    if (J.getstrong()->getisTapped()==0) {
      strongnum=i;
      std::cout <<strongnum<< ". \n";
      J.getstrong()->Reveal();
    }
    std::cout << "\n \n \nAvailable BlackCards for purchase:" << '\n';
    for (i = 0; i < 4; i++) {
      if(hidden[i]==0){
        std::cout <<i<< ". " << '\n';
        J.getprov()[i]->PrintProv();
      }
      else{
        std::cout << "Card hidden" << '\n';
      }
    }
    std::cout << "Your money: " <<money<< '\n';
    std::cout << "Would you like to tap again?Yes/No" << '\n';
    std::cin >> strinput;
    if(strinput=="Yes"){
    for (i = 0; i < J.getboardHol()->size(); i++) {
      if(J.getboardHol()->at(i)->getisTapped() == 0){
        cout<<i<<". \n";
        J.getboardHol()->at(i)->Reveal();
        std::cout  << '\n';
      }
    }
    if (J.getstrong()->getisTapped()==0) {
      strongnum=i;
      std::cout <<strongnum<< ". \n";
      J.getstrong()->Reveal();
    }
  }
  }while(strinput!="No");
  std::cout << "\n \n \nAvailable BlackCards for purchase:" << '\n';
  for (i = 0; i < 4; i++) {
    if(hidden[i]==0){
      std::cout <<i<< ". " << '\n';
      J.getprov()[i]->PrintProv();
    }
    else{
      std::cout << "Card hidden" << '\n';
    }
  }
  cout<< "Would you like to buy something?Yes/No"<<endl;
  std::cin >> strinput;
  if (strinput=="Yes") {
    std::cout << "Choose what you want to buy" << '\n';
    std::cin >> intinput;
      if(J.getprov()[intinput]->getblack()->getcost()>money){
        std::cout << "Not enough money!" << '\n';
      }
      else if(hidden[i]==1){
        std::cout << "Can't buy hidden card" << '\n';
      }
      else {
        std::cout << "Buying..." << '\n';
        money=money-J.getprov()[intinput]->getblack()->getcost();
        Convert.getCorrectType(J.getprov()[intinput]->getblack(),per,hol);
          if (*per){
          J.addPersonality(*per);
          hidden[intinput]=1; //draw kai bazei thn mayrh karta apo
          J.getprov()[intinput]->Setblack(BlackCard::Draw(J.getblack()));
          }
        else if(*hol){
          J.addHold(*hol);
          hidden[intinput]=1; // kai edw
          J.getprov()[intinput]->Setblack(BlackCard::Draw(J.getblack()));
        }
        }
      }
  }
  std::cout << "Would you like to repeat the buying phase?Yes/No" << '\n';
  std::cin >> strinput;
  }while (strinput!="No");
}

void Phase5(Player& J){
  int i=0,input;
  cout<<endl<<"Player: "<<J.getname()<<endl;
  if(J.gethand()->size() > MAXHANDSIZE){
    cout<<"Remove one (1) from your hand because you overdrew"<<endl;
    cout<<"Your available cards:"<<endl;
    for (i = 0; i < J.gethand()->size(); i++) {
      cout<<i<<".";
  		 J.gethand()->at(i)->Reveal();
    }
    do{
      cout<<"Choose which card you want to remove! ";
      cin >> input;
    }while(input<0 || input >= J.gethand()->size());
    J.gethand()->erase(J.gethand()->begin()+input);
  }
  cout<<endl<<endl<<"Your hand:"<<endl;
  for (i = 0; i < J.gethand()->size(); i++) {
    cout<<i<<".";
     J.gethand()->at(i)->Reveal();
  }
  cout<<"Your provinces!: "<<endl;
  for (i = 0; i < 4; i++) {
    J.getprov()[i]->Reveal();
    cout<<endl;
  }
  cout<<"Your Army!: "<<endl;
  for(i=0;i<J.getboardPer()->size();i++){
    J.getboardPer()->at(i)->Reveal();
    cout<<endl;
  }
  cout<<"Your Holdings!: "<<endl;
  for(i=0;i<J.getboardHol()->size();i++){
    J.getboardHol()->at(i)->Reveal();
    cout<<endl;
  }
}

int checkend(Player& J){
  if(J.getprov()[0]->getDead()==1 && J.getprov()[1]->getDead()==1 && J.getprov()[2]->getDead()==1 && J.getprov()[3]->getDead()==1){
    cout<<"Player: "<<J.getname()<<" LOST!!!"<<endl;
    return 1;
  }
  return 0;
}


int main(){
  DeckBuilder bobby;
  DeckBuilder bobby2;
  list<GreenCard*>* green=bobby.createFateDeck();
  list<BlackCard*>* black=bobby.createDynastyDeck();
  list<BlackCard*>* black2=bobby2.createDynastyDeck();
  list<GreenCard*>* green2=bobby2.createFateDeck();
  bobby.deckShuffler(green);
  bobby.deckShuffler(black);
  bobby2.deckShuffler(green2);
  bobby2.deckShuffler(black2);
  Player John("John",green,black);
  Player Joe("Joe",green2,black2);
  while(!checkend(John)&&!checkend(Joe)){
    Phase1(John);
    Phase1(Joe);
    Phase2(John);
    Phase2(Joe);
    Phase3A(John,Joe);
    Phase4(John);
    Phase4(Joe);
    Phase5(John);
    Phase5(Joe);
  }
}
