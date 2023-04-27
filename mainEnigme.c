#include "enigmeFichier.h"

int main()
{

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    if (TTF_Init() == -1)
    {
        printf("TTf init failed %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    enigmeFichier e;
    choixPlayer(&e, screen);
    choixController(&e, screen);
    genererEnigmeFichier("questions.txt", &e);

    SDL_Event event;

    int continuer = 1;
    int mx;
    int my;
    SDL_Rect perso1;
    perso1.x = 0;
    perso1.y = 400;
    perso1.w = 100;
    perso1.h = 100;
    SDL_Rect perso2;
    perso2.x = 0;
    perso2.y = 600;
    perso2.w = 100;
    perso2.h = 100;

    while (continuer)
    {
        afficherBackground(e, screen);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEMOTION:
                mx = event.motion.x;
                my = event.motion.y;
                if (mx > e.posChoix1.x && mx < e.posChoix1.x + 300 && my > e.posChoix1.y && my < e.posChoix1.y + 200)
                {
                    e.mouse = 1;
                }
                else if (mx > e.posChoix2.x && mx < e.posChoix2.x + 300 && my > e.posChoix2.y && my < e.posChoix2.y + 200)
                {
                    e.mouse = 2;
                }
                else if (mx > e.posChoix3.x && mx < e.posChoix3.x + 300 && my > e.posChoix3.y && my < e.posChoix3.y + 200)
                {
                    e.mouse = 3;
                }
                else
                {
                    e.mouse = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (e.mouse)
                {
                case 1:
                    e.choix = 1;
                    break;
                case 2:
                    e.choix = 2;

                    break;
                case 3:
                    e.choix = 3;

                    break;
                }
                break;
//////////////////////////////
            case SDL_KEYDOWN:
                if (e.choixPlayer == 1)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        perso1.y -= 15;
                        break;
                    case SDLK_RIGHT:
                        perso1.x += 15;
                        break;
                    case SDLK_LEFT:
                        perso1.x -= 15;
                        break;
                    }
                }
                else
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        perso1.y -= 15;
                        break;
                    case SDLK_RIGHT:
                        perso1.x += 15;
                        break;
                    case SDLK_LEFT:
                        perso1.x -= 15;
                        break;
                    case SDLK_a:
                        perso2.x -= 15;
                        break;
                    case SDLK_z:
                        perso2.y -= 15;
                        break;
                    case SDLK_e:
                        perso2.x += 15;
                        break;
                    }
///////////////////////////////////////////
                }
            }
        }

        if (e.choix != -1)
        {

            if (e.choix == e.reponse)
            {
                e.SurfaceResultat = TTF_RenderText_Blended(e.font, " VOUS AVEZ GAGNE ", e.color2);
                printf("win");
                afficherResultatwin(e, screen);
                continuer = 0;
            }
            else
            {
                e.SurfaceResultat = TTF_RenderText_Blended(e.font, " VOUS AVEZ PERDU ", e.color2);
                printf("lose");
                afficherResultatlose(e, screen);
                continuer = 0;
            }
        }
        else
        {
            afficherEnigmeFichier(e, screen);
        }
//////////////////////////////////////////
        SDL_Surface *controllerChoix = NULL;

        SDL_Rect controllerChoixPos;
        controllerChoixPos.x = 0;
        controllerChoixPos.y = 0;
        if (e.choixController == 1)
        {
            controllerChoix = TTF_RenderText_Blended(e.font, "Controller: Keyboard", e.color2);
        }
        else
        {

            controllerChoix = TTF_RenderText_Blended(e.font, "Controller: Manette", e.color2);
        }
        SDL_BlitSurface(controllerChoix, NULL, screen, &controllerChoixPos);

        SDL_Surface *choixPlayer = NULL;
        SDL_Rect choixPlayerPos;
        choixPlayerPos.x = 0;
        choixPlayerPos.y = 50;
        if (e.choixPlayer == 1)
        {
            choixPlayer = TTF_RenderText_Blended(e.font, "Mode: Single player", e.color2);
            SDL_FillRect(screen, &perso1, 0xfcba03);
        }
        else
        {

            choixPlayer = TTF_RenderText_Blended(e.font, "Mode: Multi Player", e.color2);
           ///////////////////
 SDL_FillRect(screen, &perso1, 0xfcba03); 
            SDL_FillRect(screen, &perso2, 0xfcba03);
        }
        SDL_BlitSurface(choixPlayer, NULL, screen, &choixPlayerPos);
        SDL_Flip(screen);

        SDL_FreeSurface(controllerChoix);
        SDL_FreeSurface(choixPlayer);
    }
}
