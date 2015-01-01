#include "jeux.hpp"
#include <chrono>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>
#define SIZE_CELL 50
using namespace std;

Jeu::Jeu(string level, int l){
  if(!l){
    ifstream file(level,ios::in);
    int cell;
    int length=0;
    if(file){
      while(!file.eof()){
	file>>cell;
	length++;
	plateau.push_back(cell);
      }
      taille=sqrt(length);
      file.close();
    }else{
      cerr<<"Unable to open the file"<<endl;
      taille=9;
      for(int cpt=0;cpt<taille*taille;cpt++){
	plateau.push_back(rand()%(int)ceil((float)taille/2));
      }
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      shuffle (plateau.begin(), plateau.end(), std::default_random_engine(seed));
    }
  }else{
    taille=l;
    for(int cpt=0;cpt<l*l;cpt++){
      plateau.push_back(rand()%(int)ceil((float)taille/2));
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (plateau.begin(), plateau.end(), std::default_random_engine(seed));
  }
}

Jeu::~Jeu(){}

int Jeu::getTaille(){return taille;}

void Jeu::afficher(ecran * ecr)const{
  //copy(plateau.begin(), plateau.end(),ostream_iterator<int>(os, " "));
  auto it=plateau.begin();
  int x=0;
  int y=0;
  for(it;it!=plateau.end();it++){
    switch((*it)){
    case 0:{
      ecr->peindre(x,y,SIZE_CELL,SIZE_CELL,49,140,231);
      break;}
    case 1:{
      ecr->peindre(x,y,SIZE_CELL,SIZE_CELL,121,28,248);
      break;}
    case 2:{
      ecr->peindre(x,y,SIZE_CELL,SIZE_CELL,97,75,58);
      break;}
    case 3:{
      ecr->peindre(x,y,SIZE_CELL,SIZE_CELL,31,160,85);
      break;}
    case 4:{
      ecr->peindre(x,y,SIZE_CELL,SIZE_CELL,169,17,1);
      break;}
    default:{
      ecr->peindre(x,y,SIZE_CELL,SIZE_CELL,255,255,255);
      break;}
      }
    x+=SIZE_CELL;
    if(x==SIZE_CELL*taille){
      x=0;
      y+=SIZE_CELL;
    }
  }
}

void Jeu::swap(int x1,int x2){
  int tmp=plateau[x2];
  plateau[x2]=plateau[x1];
  plateau[x1]=tmp;
}

bool Jeu::is_chain(int x){//check after a swap if there is cells to remove
  int i=x;
  int horizontal=0;
  int vertical=0;
  while(plateau[i]==plateau[x] && x/taille==i/taille){//check left
    i--;
    horizontal++;
  }
  i=x+1;
  while(plateau[i]==plateau[x] && x/taille==i/taille){//check right
    i++;
    horizontal++;
  }
  i=x;
  while(i>=0 && plateau[i]==plateau[x]){//check up
    i-=taille;
    vertical++;
  }
  i=x+taille;
  while(i<taille*taille && plateau[i]==plateau[x]){//check down
    i+=taille;
    vertical++;
  }
  return (horizontal>=3 || vertical >=3) ? true : false;
}

void Jeu::valid_swaps(){
  for(int i=0;i<taille*taille;i++){
    if(i%taille>0){//check for a left swap
      swap(i,i-1);
      if(is_chain(i-1)){
	swaps.push_back(make_pair(i,i-1));
      }
      swap(i-1,i);
    }
    if(i%taille==taille-1){//check for a right swap
      swap(i,i+1);
      if(is_chain(i+1)){
	swaps.push_back(make_pair(i,i+1));
      }
      swap(i+1,i);
    }
    if(i/taille>0){//check for a up swap
      swap(i,i-taille);
      if(is_chain(i-taille)){
	swaps.push_back(make_pair(i,i-taille));
      }
      swap(i-taille,i);
    }
    if(i/taille==taille-1){//check for a down swap
      swap(i,i+taille);
      if(is_chain(i+taille)){
	swaps.push_back(make_pair(i,i+taille));
      }
      swap(i+taille,i);
    }
  }
}

int Jeu::cell_selected(int x,int y){
  int cellnum=0;
  while(x>SIZE_CELL){
    x-=SIZE_CELL;
    cellnum++;
  }
  while(y>SIZE_CELL){
    y-=SIZE_CELL;
    cellnum+=taille;
  }
  return cellnum;
}

bool Jeu::pair_exist(int cell1,int cell2){
  return (find(swaps.begin(),swaps.end(),make_pair(cell1,cell2))!=swaps.end() || find(swaps.begin(),swaps.end(),make_pair(cell2,cell1))!=swaps.end()) ? true : false;
}

void Jeu::print_swaps(){
  auto it = swaps.begin();
  for(it;it!=swaps.end();it++){
    cout<<"("<<(*it).first<<","<<(*it).second<<") ";
  }
  cout<<endl;
}

ecran & operator<<(ecran & ecr,const Jeu &j){
  j.afficher(&ecr);
  return ecr;
}
