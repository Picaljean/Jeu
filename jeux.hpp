#ifndef JEUX_HPP
#define JEUX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <SDL/SDL.h>
#include <string>

using namespace std;

class ecran{
    SDL_Surface *ecr;
    SDL_Surface *background;SDL_Rect positionBackground;
    int width;
    int height;


    public:
    //!Constructeur
    ecran(int w, int h):width(w),height(h){ // h hauteur l largeur
    //!Chargement de la video (avec test)
        if(SDL_Init(SDL_INIT_VIDEO)==-1){
            fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
            exit(EXIT_FAILURE);//On quitte le programme
        }
        //!SDL_SetVideoMode(largeur,hauteur,nbcouleurs,avec la carte 3D)
        ecr = SDL_SetVideoMode(width,height,32,SDL_HWSURFACE);
        //!On verifie si l'ouverture d'ectan a marche
        if(!ecr){
            fprintf(stderr,"Impossible de charger le mode video : %s\n",SDL_GetError());
            exit(EXIT_FAILURE);
        }

        SDL_WM_SetCaption("Jeu", NULL);
        //charger l'image bitmap de fond
	// background = SDL_LoadBMP("image.bmp");
	// positionBackground.x=0;positionBackground.y=0;
        //positionBackground.w=LARGEUR;positionBackground.h=HAUTEUR;

        //SDL_BlitSurface(background,NULL,ecr,&positionBackground);//Collage de la surface sur l'ecran

        //Ajouter le background dans l'ecran
        //SDL_UpdateRect(ecr, 0, 0, 0, 0);
    }
    void peindre(int x, int y, int l, int h, int r,int g,int b) {
      SDL_Rect border;
      border.x = x;
      border.y = y;
      border.w = l;
      border.h = h;
      SDL_FillRect(ecr, &border, SDL_MapRGB(ecr->format, 0, 0, 0));
      SDL_Rect rectangle;
      rectangle.x = x+1;
      rectangle.y = y+1;
      rectangle.w = l-2;
      rectangle.h = h-2;
      SDL_FillRect(ecr, &rectangle, SDL_MapRGB(ecr->format, r, g, b));
    }
    //! rafraichir l'ecran
    void vider() {
        //On affiche un rectangle blanc, puis directement l'arriere plan
        SDL_FillRect(ecr, NULL, SDL_MapRGB(ecr->format, 255, 255, 255));
        //SDL_BlitSurface(background, NULL, ecr, NULL);
    }
    // permuter deux ecrans (courant et l'invisible)
    void flip() {SDL_Flip(ecr);}
    // destructeur ferme le mode graphique
    ~ecran(){SDL_Quit();}

    //retourner les valeurs
    int getWidth()const{return width;}
    int getHeight()const{return height;}
    SDL_Surface* get_ecr()const{return ecr;}
};

class Jeu{
private :
  int taille;
  vector<int> plateau;
  vector<pair<int,int> > swaps;
public:
  Jeu(string,int);
  ~Jeu();
  int getTaille();
  void afficher(ecran *)const;
  void swap(int,int);
  bool is_chain(int);
  void valid_swaps();
  int cell_selected(int,int);
  bool pair_exist(int,int);
  void print_swaps();
  friend ecran & operator<<(ecran &,const Jeu &);
};
#endif
