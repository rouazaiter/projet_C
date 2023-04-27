#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include <time.h>
typedef struct
{
    char question[256], choix1[256], choix2[256], choix3[256];
    int reponse;

    SDL_Surface *background;
    SDL_Surface *Choixbackground;
    SDL_Surface *ChoixbackgroundSelected;

    SDL_Surface *SurfaceQuestion;
    SDL_Surface *SurfaceChoix1;
    SDL_Surface *SurfaceChoix2;
    SDL_Surface *SurfaceChoix3;
    SDL_Surface *SurfaceResultat;

    SDL_Rect posQuestion, posChoix1, posChoix2, posChoix3, posBackground, posbutton1, posbutton2, posbutton3, posResultat;
    TTF_Font *font;
    SDL_Color color1;
    SDL_Color color2;
    int mouse;
    int choix;

    int choixPlayer;
    int choixController;

} enigmeFichier;

void genererEnigmeFichier(char *NomFichier, enigmeFichier *e);
void afficherBackground(enigmeFichier e, SDL_Surface *screen);
int afficherResultatwin(enigmeFichier e, SDL_Surface *screen);
int afficherResultatlose(enigmeFichier e, SDL_Surface *screen);
void afficherEnigmeFichier(enigmeFichier e, SDL_Surface *screen);

///////////////////////////////////////////////////////////////////////////////


void choixPlayer(enigmeFichier *e, SDL_Surface *screen);
void choixController(enigmeFichier *e, SDL_Surface *screen);
