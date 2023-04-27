#include "enigmeFichier.h"

void genererEnigmeFichier(char *NomFichier, enigmeFichier *e)
{

    int compteur_ligne = 1;
    int test = 0;

    srand(time(NULL));
    int question_random_number = (rand() % 2) + 1;

    printf("Random number: %d\n", question_random_number);

    FILE *fp = fopen(NomFichier, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
    }
    else
    {
        printf("opened \n");

        while (test == 0)
        {

            fscanf(fp, "%[^?]? %d \n", e->question, &(e->reponse));

            if (compteur_ligne == question_random_number)
            {
                test = 1;
            }
            else
            {
                compteur_ligne++;
            }
        }

        fclose(fp);
    }
    printf("Question: %s\n", e->question);
    printf("Reponse: %d\n", e->reponse);

    strcat(e->question, "?");

    e->font = TTF_OpenFont("angelina.TTF", 40);
    if (e->font == NULL)
    {
        printf("Can't open font:  %s\n", SDL_GetError());
    }
    e->color1.r = 255;
    e->color1.g = 0;
    e->color1.b = 0;

    e->color2.r = 255;
    e->color2.g = 255;
    e->color2.b = 255;

    e->SurfaceQuestion = TTF_RenderText_Solid(e->font, e->question, e->color2);

    char num_quest_char[255];
    sprintf(num_quest_char, "%d", question_random_number);
    char path1[255];
    strcpy(path1, num_quest_char);
    strcat(path1, "/choix1.png");
    char path2[255];
    strcpy(path2, num_quest_char);
    strcat(path2, "/choix2.png");
    char path3[255];
    strcpy(path3, num_quest_char);
    strcat(path3, "/choix3.png");

    e->SurfaceChoix1 = IMG_Load(path1);
    if (e->SurfaceChoix1 == NULL)
    {
        printf("Can't open choix1:  %s\n", SDL_GetError());
    }
    e->SurfaceChoix2 = IMG_Load(path2);
    if (e->SurfaceChoix2 == NULL)
    {
        printf("Can't open choix2:  %s\n", SDL_GetError());
    }
    e->SurfaceChoix3 = IMG_Load(path3);

    e->background = IMG_Load("QuizBg.png");
    e->Choixbackground = IMG_Load("buttonoff.png");
    e->ChoixbackgroundSelected = IMG_Load("buttonOn.png");

    e->posBackground.x = 0;
    e->posBackground.y = 0;

    e->posQuestion.x = 1920 / 2 - 400;
    e->posQuestion.y = 1080 / 2;

    e->posChoix1.x = 1920 / 3 + 170 - 200;
    e->posChoix1.y = 1080 / 2 + 125;
    e->posbutton1.x = 1920 / 3 - 200;
    e->posbutton1.y = 1080 / 2 + 100;

    e->posChoix2.x = 1920 * 2 / 3 + 170 - 200;
    e->posChoix2.y = 1080 / 2 + 125;
    e->posbutton2.x = 1920 * 2 / 3 - 200;
    e->posbutton2.y = 1080 / 2 + 100;

    e->posChoix3.x = 1920 / 2 + 170 - 200;
    e->posChoix3.y = 1080 / 2 + 225;
    e->posbutton3.x = 1920 / 2 - 200;
    e->posbutton3.y = 1080 / 2 + 200;

    e->mouse = 0;
    e->choix = -1;
    e->posResultat.x = 1920 / 2 - 200;
    e->posResultat.y = 1080 / 2 + 100;
}

void afficherBackground(enigmeFichier e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.background, NULL, screen, &e.posBackground);
}

int afficherResultatwin(enigmeFichier e, SDL_Surface *screen)
{

    SDL_Surface *originalSurface = e.SurfaceResultat;
    SDL_Rect pos = e.posResultat;

    double maxZoom = 5.0;

    Uint32 start = SDL_GetTicks();
    while (SDL_GetTicks() - start < 5000)
    {
        double zoom = (SDL_GetTicks() - start) / 1000.0 * maxZoom / 5.0;
        if (zoom > maxZoom / 2.0)
        {
            zoom = maxZoom / 2.0;
        }
        SDL_Surface *zoomedSurface = rotozoomSurface(originalSurface, 0, zoom, 0);

        SDL_Rect posZoomed = {(screen->w - zoomedSurface->w) / 2, (screen->h - zoomedSurface->h) / 2, 0, 0};

        SDL_BlitSurface(e.background, NULL, screen, &e.posBackground);
        SDL_BlitSurface(zoomedSurface, NULL, screen, &posZoomed);

        SDL_FreeSurface(zoomedSurface);

        SDL_Flip(screen);

        SDL_Delay(10);
    }

    double zoom = maxZoom / 2.0;
    SDL_Surface *zoomedSurface = rotozoomSurface(originalSurface, 0, zoom, 0);

    SDL_Rect posZoomed = {(screen->w - zoomedSurface->w) / 2, (screen->h - zoomedSurface->h) / 2, 0, 0};

    SDL_BlitSurface(e.background, NULL, screen, &e.posBackground);
    SDL_BlitSurface(zoomedSurface, NULL, screen, &posZoomed);

    SDL_FreeSurface(zoomedSurface);
    SDL_Flip(screen);

    SDL_Delay(5000);
}

int afficherResultatlose(enigmeFichier e, SDL_Surface *screen)
{
    SDL_Surface *originalSurface = e.SurfaceResultat;
    SDL_Rect pos = e.posResultat;

    double maxAngle = 360.0;

    Uint32 start = SDL_GetTicks();
    while (SDL_GetTicks() - start < 5000)
    {
        double angle = (SDL_GetTicks() - start) / 5000.0 * maxAngle;
        SDL_Surface *rotatedSurface = rotozoomSurface(originalSurface, angle, 1.0, 0);

        SDL_Rect posRotated = {(screen->w - rotatedSurface->w) / 2, (screen->h - rotatedSurface->h) / 2, 0, 0};

        SDL_BlitSurface(e.background, NULL, screen, &e.posBackground);
        SDL_BlitSurface(rotatedSurface, NULL, screen, &posRotated);

        SDL_FreeSurface(rotatedSurface);

        SDL_Flip(screen);

        SDL_Delay(10);
    }

    SDL_Surface *rotatedSurface = rotozoomSurface(originalSurface, maxAngle, 1.0, 0);

    SDL_Rect posRotated = {(screen->w - rotatedSurface->w) / 2, (screen->h - rotatedSurface->h) / 2, 0, 0};

    SDL_BlitSurface(e.background, NULL, screen, &e.posBackground);
    SDL_BlitSurface(rotatedSurface, NULL, screen, &posRotated);

    SDL_FreeSurface(rotatedSurface);

    SDL_Flip(screen);

    SDL_Delay(5000);
}

void afficherEnigmeFichier(enigmeFichier e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.SurfaceQuestion, NULL, screen, &e.posQuestion);

    ;

    SDL_BlitSurface(e.SurfaceChoix1, NULL, screen, &e.posChoix1);

    SDL_BlitSurface(e.SurfaceChoix2, NULL, screen, &e.posChoix2);

    SDL_BlitSurface(e.SurfaceChoix3, NULL, screen, &e.posChoix3);
}


////////////////////////////////////////////
void choixPlayer(enigmeFichier *e, SDL_Surface *screen)
{
    SDL_Surface *multiPlayer = IMG_Load("choix/multiplayer.png");
    SDL_Surface *singlePlayer = IMG_Load("choix/singelPlayer.png");

    SDL_Rect multiPos;
    multiPos.w = 400;
    multiPos.h = 400;
    multiPos.y = 200;
    multiPos.x = 200;

    SDL_Rect singlePos;
    singlePos.w = 400;
    singlePos.h = 400;
    singlePos.y = 200;
    singlePos.x = 600;

    SDL_BlitSurface(multiPlayer, NULL, screen, &multiPos);
    SDL_BlitSurface(singlePlayer, NULL, screen, &singlePos);
    SDL_Flip(screen);
    int loop = 1;
    SDL_Event event;

    while (loop)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop = 0;

                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.motion.x >= multiPos.x &&
                    event.motion.x <= multiPos.w + multiPos.x &&
                    event.motion.y >= multiPos.y &&
                    event.motion.y <= multiPos.y + multiPos.h)
                {
                    e->choixPlayer = 2;
                    loop = 0;
                }
                if (event.motion.x >= singlePos.x &&
                    event.motion.x <= singlePos.w + singlePos.x &&
                    event.motion.y >= singlePos.y &&
                    event.motion.y <= singlePos.y + singlePos.h)
                {
                    e->choixPlayer = 1;
                    loop = 0;
                }
                break;
            }
        }
    }
    SDL_FreeSurface(multiPlayer);
    SDL_FreeSurface(singlePlayer);
}


void choixController(enigmeFichier *e, SDL_Surface *screen)
{
    SDL_Surface *keyboard = IMG_Load("choix/keyboard.png");
    SDL_Surface *manette = IMG_Load("choix/manette.png");

    SDL_Rect keyPos;
    keyPos.w = 400;
    keyPos.h = 400;
    keyPos.y = 200;
    keyPos.x = 200;
    SDL_Rect manettePos;
    manettePos.w = 400;
    manettePos.h = 400;
    manettePos.y = 200;
    manettePos.x = 600;

    SDL_BlitSurface(keyboard, NULL, screen, &keyPos);
    SDL_BlitSurface(manette, NULL, screen, &manettePos);
    SDL_Flip(screen);
    int loop = 1;
    SDL_Event event;

    while (loop)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop = 0;

                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.motion.x >= manettePos.x &&
                    event.motion.x <= manettePos.w + manettePos.x &&
                    event.motion.y >= manettePos.y &&
                    event.motion.y <= manettePos.y + manettePos.h)
                {
                    e->choixController = 2;
                    loop = 0;
                }
                if (event.motion.x >= keyPos.x &&
                    event.motion.x <= keyPos.w + keyPos.x &&
                    event.motion.y >= keyPos.y &&
                    event.motion.y <= keyPos.y + keyPos.h)
                {
                    e->choixController = 1;
                    loop = 0;
                }
                break;
            }
        }
    }
    SDL_FreeSurface(keyboard);
    SDL_FreeSurface(manette);
}
