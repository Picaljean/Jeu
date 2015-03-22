#include <iostream>
#define SIZE_CELL 50
#include "jeux.hpp"


bool play(string levelname,int plat){
  SDL_Event event,event2;
  bool continuer = true;
  int tempsPrecedent = 0, tempsActuel = 0;
  int intervalle = 10;
  int cellfocused=0,cell2=0;

  Jeu j(levelname,plat);

  ecran zone_affichage(SIZE_CELL*j.getTaille(),SIZE_CELL*j.getTaille());
 
  j.valid_swaps();

  while (continuer)
    {
      while(SDL_PollEvent(&event)){
	switch(event.type)
	  {
	  case SDL_QUIT:
	    return false;
	  case SDL_KEYDOWN:
	    switch(event.key.keysym.sym){
	    case SDLK_ESCAPE:
	      return false;
	    }
	  case SDL_MOUSEBUTTONDOWN:
	    switch(event.button.button){
	    case SDL_BUTTON_LEFT:
	      cellfocused=j.cell_selected(event.button.x,event.button.y);
	      do{
		SDL_WaitEvent(&event2);
	      }while(event2.type != SDL_MOUSEBUTTONDOWN);
	      switch(event2.button.button){
	      case SDL_BUTTON_LEFT:
		cell2=j.cell_selected(event2.button.x,event2.button.y);
		if(j.pair_exist(cellfocused,cell2)){// cell2 is near of cell1, swap it
		  j.swap(cellfocused,cell2);
		}
	      }	    
	      break;
	    }
	    break;
	  }
      }    
      zone_affichage<<j;
      zone_affichage.flip();

      tempsActuel = SDL_GetTicks();

      if (tempsActuel - tempsPrecedent < intervalle){
	SDL_Delay(intervalle - (tempsActuel - tempsPrecedent));
      }
      tempsPrecedent = tempsActuel;
    }
  return EXIT_SUCCESS;
}

int main(){
  int choice=0,plat=0;
  string levelname;

  cout<<"Menu :"<<endl<<"Pour choisir un niveau pré-enregistré, tapez (0)"<<endl<<"Pour choisir de générer aléatoirement un niveau, tapez (1)"<<endl;
  cin>>choice;
  if(!choice){
    cout<<"Nom du niveau :"<<endl;
    cin>>levelname;
  }else{
    cout<<"Entrez la taille du plateau :"<<endl;
    cin>>plat;  
  }
  srand(time(NULL));
  play(levelname,plat);
  return 0;
}
