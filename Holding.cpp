#include "Holding.h"
#include <iostream>

using namespace std;


void Mine::connect(Holding* Get){
  GoldMine* G;
  GoldMine** point=&G;
  std::cout << "Mine connect called from number "<<Get->ismine() << '\n';
  Holding::getGoldMine(Get,point);
  if (G){
    std::cout << "Stage 1" << '\n';
    if ((G->ismine()==2)) {
      std::cout << "Stage 2" << '\n';
      if (upperholding==NULL){
        std::cout << "Stage 3" << '\n';
        upperholding=G;
        HarvestValue=MINEVALUE+2;
        G->connect(this);
      }
    }
  }
}


void GoldMine::connect(Holding* MCet){
  Mine* MC;
  Mine** point=&MC;
  CrystalMine* MCr;
  CrystalMine** pointr=&MCr;
  std::cout << "Called from a number " <<MCet->ismine()<< '\n';
  Holding::getMine(MCet,point);
  Holding::getCrystalMine(MCet,pointr);
  if(MC){
    if ((MC->ismine()==1)){
      if(subholding==NULL && upperholding==NULL){
        subholding=MC;
        HarvestValue=GOLDMINEVALUE+4;
        MC->connect(this);
      }
      else if(subholding==NULL && upperholding!=NULL){
        subholding=MC;
        HarvestValue=GOLDMINEVALUE*2;
        MC->connect(this);
        upperholding->connect(this,1);
        }
      }
    }
    else if(MCr){
       if ((MCr->ismine()==3)){
        if(subholding==NULL && upperholding==NULL){
           upperholding==MCr;
          HarvestValue=GOLDMINEVALUE+5;
          MCr->connect(this,0);
        }
        else if(subholding!=NULL && upperholding==NULL){
          upperholding==MCr;
          HarvestValue=GOLDMINEVALUE*2;
          MCr->connect(this,1);
        }
      }
    }
}


void CrystalMine::connect(Holding* Get,int i){
  GoldMine* G;
  GoldMine** point=&G;
  Holding::getGoldMine(Get,point);
  if(G){
    if (G->ismine()==2){
      if (subholding==NULL){
        std::cout << "SUB IS NULL" << '\n';
        subholding==G;
        if (i==0){
          HarvestValue=CRYSTALMINEVALUE*2;
        }
        else if(i==1){
          HarvestValue=CRYSTALMINEVALUE*4;
        }
        G->connect(this);
      }
    }
  }
}
