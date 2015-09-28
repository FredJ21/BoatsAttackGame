#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "Battle_boats.h"
#include "level.h"
#include "anim.h"
#include "Algo_A_star.h"


int main( int argc, char* args[] )
{

    //printf("Go ...!!!\n");

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
    SDL_RenderSetLogicalSize(pRenderer, MAP_TAILLE_X, MAP_TAILLE_Y);


    // Chargement de l'image
    SDL_Surface *pSurface = SDL_LoadBMP (START_IMG);
    if(!pSurface) {                          printf( "SDL_Surface ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    // Création de la texture (texture = surface dans le GPU)
    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    if(!pTexture) {                         printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    SDL_RenderCopy (pRenderer, pTexture, NULL, NULL);
    SDL_RenderPresent (pRenderer);


    /******************************************************************************************************************
                                                INIT SDL 2 TTF
    *******************************************************************************************************************/
    // Initialize SDL TTF
    if( TTF_Init() != 0 ) {  printf( "TTF_Init ERREUR ! SDL_GetError: %s\n", SDL_GetError() ); return -1; }

    TTF_Font *police = NULL;
    SDL_Surface *texte = NULL;
    SDL_Color couleurNoire = {200, 100, 100, 0};
    SDL_Rect texte_position_start;
    SDL_Rect texte_position;

    police = TTF_OpenFont(POLICE_1, 50);
    if(!police) {                  printf( "TTF_OpenFont ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    texte = TTF_RenderText_Blended(police, "Salut FRED !", couleurNoire);
    texte_position_start.x = 0;
    texte_position_start.y = 0;
    texte_position_start.h = texte->h;
    texte_position_start.w = texte->w;
    texte_position.x = 200;
    texte_position.y = 50;
    texte_position.h = texte->h;
    texte_position.w = texte->w;

    // Création de la texture pour le texte
    SDL_Texture *pTexture_texte = SDL_CreateTextureFromSurface(pRenderer, texte);
    if(!pTexture_texte) {                  printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    /******************************************************************************************************************
                                                VARIABLES
    *******************************************************************************************************************/
    bool fin = false;

    time_t t_Avant_Traitement;
    time_t t_Apres_Traitement;

    time_t timeA, timeB;

    int a = 0;
    int current_level = 3;
    int current_wave  = 0;

    t_level my_level;

    srand(time(NULL));

    /******************************************************************************************************************
                                                INIT GAME
    *******************************************************************************************************************/
    SDL_Surface *pSurface_TUILE = SDL_LoadBMP (TILE_FILE);
    if(!pSurface_TUILE) { printf( "SDL_Surface_TUILE ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    /** ANIMATION **/
    /*
                            typedef struct {
                                char    file[256];          // nom du fichier
                                int     tx, ty;             // taille d'une image
                                int     nb_colonne;
                                int     nb_image;           // nombre total d'image dans le fichier
                                int     nb_img_by_dir;      // nombre d'image par direction
                                int     nb_tour             // frequence des image
                                SDL_Texture *texture;       // les images de l'animation
                                int     vitesse;            // vitesse de deplacement de l'animation
                            } t_animation;
    */
    t_animation PETIT_BATEAU = { "./images/XnT4umX_3.bmp", 48, 48, 3, 12, 3, NULL, 5, 3 };
    init_animation( &PETIT_BATEAU, pRenderer);

    t_animation PETIT_BATEAU_2 = { "./images/XnT4umX_4.bmp", 48, 48, 3, 12, 3, NULL, 5, 3 };
    init_animation( &PETIT_BATEAU_2, pRenderer);

    t_animation DRAPEAU = { "./images/flag.bmp", 31, 40, 11, 11, 11, NULL, 3, 1 };
    init_animation( &DRAPEAU, pRenderer);

    /** SPRITE ARRIVE */
    t_sprite *ARRIVE;
    ARRIVE = init_sprite (&DRAPEAU);

    /** LEVEL **/
    init_level(&my_level, current_level, pSurface_TUILE, pRenderer);
    //init_texture_obstacle(pRenderer, &my_level);
    place_sprite(ARRIVE, my_level.cibleX, my_level.cibleY);
    init_level_chemins(&my_level);
    affiche_map_console ( &my_level);

    /** SPRITE ENNEMI **/
    t_sprite *ENNEMI_WAVE_0[WAVE_ENEMY_NB_BY_WAVE];   //tableau de pointeurs
    t_sprite *ENNEMI_WAVE_1[WAVE_ENEMY_NB_BY_WAVE];
    t_sprite *ENNEMI_WAVE_2[WAVE_ENEMY_NB_BY_WAVE];
    t_sprite *ENNEMI_WAVE_3[WAVE_ENEMY_NB_BY_WAVE];
    t_sprite *ENNEMI_WAVE_4[WAVE_ENEMY_NB_BY_WAVE];
    t_sprite *ENNEMI_WAVE_5[WAVE_ENEMY_NB_BY_WAVE];
    t_sprite *ENNEMI_WAVE_6[WAVE_ENEMY_NB_BY_WAVE];
    t_sprite *ENNEMI_WAVE_7[WAVE_ENEMY_NB_BY_WAVE];
    t_sprite *ENNEMI_WAVE_8[WAVE_ENEMY_NB_BY_WAVE];
    t_sprite *ENNEMI_WAVE_9[WAVE_ENEMY_NB_BY_WAVE];

    /**          create_Enemy            **/
    // position --> en haut, à droite, en bas, à gauche
    // A & B    --> délimite la zone de création , entre A et B
    // *ANIM    --> pointeur sur l'annimation
    // Frequence --> Frequence de démarrage entre chaque ennemi

/**
    for (a = 0; a < my_level.wave[0].nombre; a++) {
            ENNEMI_WAVE_0[a] = create_Enemy( RIGHT , 100, MAP_TAILLE_Y-100, &PETIT_BATEAU, 0.2*a);
    }
    for (a = 0; a < my_level.wave[1].nombre; a++) {
            ENNEMI_WAVE_1[a] = create_Enemy( UP , 300, MAP_TAILLE_X-50, &PETIT_BATEAU, 0.5*a);
    }
    for (a = 0; a < my_level.wave[2].nombre; a++) {
            ENNEMI_WAVE_2[a] = create_Enemy( DOWN , 200, 600, &PETIT_BATEAU, 0.5*a);
    }
    for (a = 0; a < my_level.wave[3].nombre; a++) {
            ENNEMI_WAVE_3[a] = create_Enemy( LEFT , 100, MAP_TAILLE_Y-100, &PETIT_BATEAU, 0.5*a);
    }
**/






    /******************************************************************************************************************
                                                BOUCLE PRINCIPALE
    *******************************************************************************************************************/
    while (!fin) {

        t_Avant_Traitement = clock();


        /** Gestion des evenements */
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type){

                case SDL_QUIT:
                    fin = true;
                    //printf ("By By !!\n");
                    break;

                case SDL_KEYDOWN:

                    switch( event.key.keysym.sym ){
                        case SDLK_ESCAPE:
                            fin = true;
                            //printf ("By By !!\n");
                            break;
                        case SDLK_UP:

                            break;
                        case SDLK_DOWN:

                            break;
                        case SDLK_LEFT:

                            break;
                        case SDLK_RIGHT:

                             break;
                        case SDLK_l:

                            current_level++;
                            if (current_level >= LEVEL_NB_TOTAL ) {
                                current_level = 0;
                            }


                            //printf ("Change Level to %d\n", current_level);

                            /* Change LEVEL */
                            init_level(&my_level, current_level, pSurface_TUILE, pRenderer);
                            init_texture_obstacle(pRenderer, &my_level);
                            place_sprite(ARRIVE, my_level.cibleX, my_level.cibleY);

                            affiche_map_console ( &my_level);

                            break;

                        case SDLK_c:

                            timeA = clock();

                            init_level_chemins(&my_level);

                            timeB = clock();
                            //printf ("Temps de traitement : %ld\n", timeB - timeA);

                            affiche_map_console ( &my_level);

                            break;

                        default:
                            //printf ("KEY\n");
                            break;
                    }
                    break;

            }

        }

        /*******************/
        /**   AFFICHAGE   **/
        /*******************/
        SDL_RenderClear     (pRenderer);
        // Affichage de la map
        SDL_RenderCopy      (pRenderer, my_level.pTexture_MAP, NULL, NULL);

        // Affichage des obstacles (mode Debug)
        // affiche_obstacle    (pRenderer, &my_level);

        // Affichage de l'arrivé
        anime_sprite(ARRIVE);
        affiche_sprite (pRenderer, ARRIVE);

        // Affichage des Sprites
/**
        for (a = 0; a < my_level.wave[0].nombre; a++) {
            anime_sprite    (ENNEMI_WAVE_0[a]);
            avance_sprite   (ENNEMI_WAVE_0[a], &my_level);
            affiche_sprite  (pRenderer, ENNEMI_WAVE_0[a]);
        }
        for (a = 0; a < my_level.wave[1].nombre; a++) {
            anime_sprite    (ENNEMI_WAVE_1[a]);
            avance_sprite   (ENNEMI_WAVE_1[a], &my_level);
            affiche_sprite  (pRenderer, ENNEMI_WAVE_1[a]);
        }
        for (a = 0; a < my_level.wave[2].nombre; a++) {
            anime_sprite    (ENNEMI_WAVE_2[a]);
            avance_sprite   (ENNEMI_WAVE_2[a], &my_level);
            affiche_sprite  (pRenderer, ENNEMI_WAVE_2[a]);
        }
        for (a = 0; a < my_level.wave[3].nombre; a++) {
            anime_sprite    (ENNEMI_WAVE_3[a]);
            avance_sprite   (ENNEMI_WAVE_3[a], &my_level);
            affiche_sprite  (pRenderer, ENNEMI_WAVE_3[a]);
        }

**/
        // Affichage du texte
        //SDL_RenderCopy      (pRenderer, pTexture_texte, &texte_position_start, &texte_position);

        // Mise a jour de l'affichage
        SDL_RenderPresent   (pRenderer);


        /************************************************/
        /**   Calcul du temps de traitement et pause   **/
        /************************************************/
        t_Apres_Traitement = clock();
        SDL_Delay( 1000 / GAME_FPS - (t_Avant_Traitement - t_Apres_Traitement));
    }

    /******************************************************************************************************************
                                                    FIN
    *******************************************************************************************************************/
    // Nettoyage
/**
    for (a = 0; a < my_level.wave[0].nombre; a++) {
        destroy_sprite(&ENNEMI_WAVE_0[a]);
    }
*/
    SDL_DestroyTexture(PETIT_BATEAU.texture);
    SDL_DestroyTexture(PETIT_BATEAU_2.texture);
    SDL_DestroyTexture(DRAPEAU.texture);

    SDL_DestroyTexture(my_level.pTexture_MAP);
    SDL_DestroyTexture(pTexture);
    SDL_DestroyTexture(pTexture_texte);
    SDL_FreeSurface(pSurface);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow( pWindow );

    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
