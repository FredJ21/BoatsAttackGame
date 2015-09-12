#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "Battle_boats.h"
#include "level.h"
#include "anim.h"


int main( int argc, char* args[] )
{

    printf("Go ...!!!\n");

    /******************************************************************************************************************
                                                INIT SDL 2
    *******************************************************************************************************************/

    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO) != 0 ) {  printf( "SDL_Init ERREUR ! SDL_GetError: %s\n", SDL_GetError() ); return -1; }

    // Création de la fenêtre
    SDL_Window *pWindow = NULL;
    pWindow = SDL_CreateWindow( APP_TITRE , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAP_TAILLE_X, MAP_TAILLE_Y, SDL_WINDOW_SHOWN );
 //   pWindow = SDL_CreateWindow( APP_TITRE , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP );
    if(!pWindow) {                          printf( "SDL_Window ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    // Création du Renderer
    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!pRenderer) {                        printf( "SDL_Renderer ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    // permet d'obtenir les redimensionnements plus doux.
   // SDL_RenderSetLogicalSize(pRenderer, MAP_TAILLE_X, MAP_TAILLE_Y);


    // Chargement de l'image
    SDL_Surface *pSurface = SDL_LoadBMP (START_IMG);
    if(!pSurface) {                          printf( "SDL_Surface ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    // Création de la texture (texture = surface dans le GPU)
    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    if(!pTexture) {                         printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    SDL_RenderCopy (pRenderer, pTexture, NULL, NULL);
    SDL_RenderPresent (pRenderer);

   // SDL_Delay (2000);

    /******************************************************************************************************************
                                                VARIABLES
    *******************************************************************************************************************/
    bool fin = false;
    bool dessiner = true;

    time_t t_Avant_Traitement;
    time_t t_Apres_Traitement;

    int a = 0;
    int current_level = 0;

    t_level my_level;

    SDL_Rect R;
    R.h = 100;
    R.w = 100;
    R.x = 100;
    R.y = 100;

    /******************************************************************************************************************
                                                INIT GAME
    *******************************************************************************************************************/
    SDL_Surface *pSurface_TUILE = SDL_LoadBMP (TILE_FILE);
    if(!pSurface_TUILE) { printf( "SDL_Surface_TUILE ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    init_level(&my_level, current_level, pSurface_TUILE, pRenderer);
    init_texture_obstacle(pRenderer, &my_level);

    /** ANIMATION **/
    t_animation PETIT_BATEAU = { "./images/XnT4umX.bmp", 48, 64, 3, 12, 3, NULL };
    init_animation( &PETIT_BATEAU, pRenderer);
    t_animation PETIT_BATEAU_2 = { "./images/XnT4umX_2.bmp", 48, 64, 3, 12, 3, NULL };
    init_animation( &PETIT_BATEAU_2, pRenderer);

    /** SPRITE **/
    int ENNEMI_NB = 20;
    t_sprite *ENNEMI[ENNEMI_NB];   //tableau de pointeurs
    for (a = 0; a < ENNEMI_NB; a++) {
        if ( a%2 == 1 ) {

            //  init_sprite ->  PositionX, PositionY, VitesseX, VitesseY, NbTour pour l'anim, Direction, &ANIMATION, actif, temps avant départ ;
            ENNEMI[a] = init_sprite( MAP_TAILLE_X - 30 , rand()%700, 2, 2, 5, 3, &PETIT_BATEAU, false, (GAME_FPS * a)+1 );
        } else {
            ENNEMI[a] = init_sprite( MAP_TAILLE_X - 30 , rand()%700, 2, 2, 5, 3, &PETIT_BATEAU_2, false, (GAME_FPS * a)+1 );
        }
    }

    /******************************************************************************************************************
                                                BOUCLE PRINCIPALE
    *******************************************************************************************************************/
    while (!fin) {

        t_Avant_Traitement = clock();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
         // handle your event here

            switch (event.type){

                case SDL_QUIT:
                    fin = true;
                    printf ("By By !!\n");
                    break;

                case SDL_KEYDOWN:

                    switch( event.key.keysym.sym ){
                        case SDLK_ESCAPE:
                            fin = true;
                            printf ("By By !!\n");
                            break;
                        case SDLK_UP:
                            printf ("UP\n");
                            R.y -= 10;
                                                            ENNEMI[0]->direction = 0;
                                                            ENNEMI[0]->compte_tour = 999;
                            break;
                        case SDLK_DOWN:
                            printf ("DOWN\n");
                            R.y += 10;
                                                            ENNEMI[0]->direction = 2;
                                                            ENNEMI[0]->compte_tour = 999;
                            break;
                        case SDLK_LEFT:
                            printf ("LEFT\n");
                            R.x -= 10;
                                                            ENNEMI[0]->direction = 3;
                                                            ENNEMI[0]->compte_tour = 999;
                            break;
                        case SDLK_RIGHT:
                            printf ("RIGHT\n");
                            R.x += 10;
                                                           ENNEMI[0]->direction = 1;
                                                           ENNEMI[0]->compte_tour = 999;
                             break;
                        case SDLK_SPACE:

                            if (current_level == 0) { current_level = 1; } else { current_level = 0; }
                            printf ("Change Level to %d\n", current_level);
                            init_level(&my_level, current_level, pSurface_TUILE, pRenderer);
                            init_texture_obstacle(pRenderer, &my_level);

                        default:
                            printf ("KEY\n");
                            break;
                    }
                    break;

            }

        }


        SDL_RenderClear     (pRenderer);
        // Affichage de la map
        SDL_RenderCopy      (pRenderer, my_level.pTexture_MAP, NULL, NULL);

        // Affichage des obstacles (mode Debug)
         affiche_obstacle    (pRenderer, &my_level);

        // Affichage des Sprites
        for (a = 0; a < ENNEMI_NB; a++) {
            anime_sprite    (ENNEMI[a]);
            avance_sprite   (ENNEMI[a]);
            affiche_sprite  (pRenderer, ENNEMI[a]);
        }

        // Mise a jour de l'affichage
        SDL_RenderPresent   (pRenderer);

        // Calcul du temps de traitement et pause
        t_Apres_Traitement = clock();
        SDL_Delay( 1000 / GAME_FPS - (t_Avant_Traitement - t_Apres_Traitement));
    }

    /******************************************************************************************************************
                                                    FIN
    *******************************************************************************************************************/
    // Nettoyage
    for (a = 0; a < ENNEMI_NB; a++) {
        destroy_sprite(&ENNEMI[a]);
    }

    SDL_DestroyTexture(PETIT_BATEAU.texture);
    SDL_DestroyTexture(PETIT_BATEAU_2.texture);

    SDL_DestroyTexture(my_level.pTexture_MAP);
    SDL_DestroyTexture(pTexture);
    SDL_FreeSurface(pSurface);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow( pWindow );
    SDL_Quit();

    return 0;
}
