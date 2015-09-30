#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


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
    bool fin            = false;
    bool change_level   = true;

    time_t t_Avant_Traitement;
    time_t t_Apres_Traitement;

    time_t CounterTimeA = clock();
    int CounterBeforeChgLevel = 0;

    int a = 0, b = 0;
    int w = 0;
    int current_level       = 0;
    int current_nb_enemy    = 0;
    int current_enemy_alive = 0;
    t_level my_level;

    srand(time(NULL));

    /******************************************************************************************************************
                                                INIT GAME
    *******************************************************************************************************************/
    SDL_Surface *pSurface_TUILE = SDL_LoadBMP (TILE_FILE);
    if(!pSurface_TUILE) { printf( "SDL_Surface_TUILE ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    /** ANIMATION **/
    t_animation ANIM[3];

    strcpy(ANIM[0].file,   "./images/PetitBateau1.bmp");
    ANIM[0].tx              = 48;
    ANIM[0].ty              = 48;
    ANIM[0].nb_colonne      = 3;
    ANIM[0].nb_image        = 12;
    ANIM[0].nb_img_by_dir   = 3;
    ANIM[0].nb_tour         = 5;
    ANIM[0].vitesse         = 2;

    strcpy(ANIM[1].file,   "./images/PetitBateau2.bmp");
    ANIM[1].tx              = 48;
    ANIM[1].ty              = 48;
    ANIM[1].nb_colonne      = 3;
    ANIM[1].nb_image        = 12;
    ANIM[1].nb_img_by_dir   = 3;
    ANIM[1].nb_tour         = 5;
    ANIM[1].vitesse         = 2;

    strcpy(ANIM[2].file,   "./images/PetitBateau3.bmp");
    ANIM[2].tx              = 48;
    ANIM[2].ty              = 48;
    ANIM[2].nb_colonne      = 3;
    ANIM[2].nb_image        = 12;
    ANIM[2].nb_img_by_dir   = 3;
    ANIM[2].nb_tour         = 5;
    ANIM[2].vitesse         = 2;

    init_animation( &ANIM[0], pRenderer);
    init_animation( &ANIM[1], pRenderer);
    init_animation( &ANIM[2], pRenderer);

    t_animation DRAPEAU = { "./images/flag.bmp", 31, 40, 11, 11, 11, NULL, 3, 1 };
    init_animation( &DRAPEAU, pRenderer);

    /** SPRITE ARRIVE */
    t_sprite *ARRIVE;
    ARRIVE = init_sprite (&DRAPEAU);

    /** SPRITE ENNEMI **/
    t_sprite *ENEMY[WAVE_NB * WAVE_ENEMY_MAX_BY_WAVE];   //tableau de pointeurs


    /******************************************************************************************************************
                                                BOUCLE PRINCIPALE
    *******************************************************************************************************************/
    while (!fin) {

        t_Avant_Traitement = clock();


        /******************************************************************************************************************
                                                    GESTION DES EVENEMENTS
        *******************************************************************************************************************/
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
                            break;
                        case SDLK_l:
                            current_level++;
                            if (current_level >= LEVEL_NB_TOTAL ) {
                                current_level = 0;
                            }
                            change_level = true;
                            break;

                        default:
                            //printf ("KEY\n");
                            break;
                    }
                    break;

            }

        }

        /******************************************************************************************************************
                                                    CHANGEMENT  DE NIVEAU
        *******************************************************************************************************************/
        if (change_level) {

                change_level = false;

                /** NETTOYAGE **/
                for (a = 0; a < WAVE_NB * WAVE_ENEMY_MAX_BY_WAVE; a++) {
                    destroy_sprite(&ENEMY[a]);
                }


                /** LEVEL **/
                init_level(&my_level, current_level, pSurface_TUILE, pRenderer);
                //init_texture_obstacle(pRenderer, &my_level);

                place_sprite(ARRIVE, my_level.cibleX, my_level.cibleY);
                init_level_chemins(&my_level);
                affiche_map_console ( &my_level);


                /** CREATE ENEMY **/
                current_nb_enemy = 0;

                for ( w = 0; w < WAVE_NB; w++ ) {
                    printf ("Level %d - Wave %d - ", current_level, w);
                    b = 0;
                    // creation en haut
                    for (a = 0; a < my_level.wave[w].nb_up; a++ ) {
                        ENEMY[current_nb_enemy++] = create_Enemy( UP ,    my_level.StartPos_UP_s, my_level.StartPos_UP_e,       &ANIM[my_level.wave[w].type], 0.2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation a droite
                    for (a = 0; a < my_level.wave[w].nb_right; a++ ) {
                        ENEMY[current_nb_enemy++] = create_Enemy( RIGHT , my_level.StartPos_RIGHT_s, my_level.StartPos_RIGHT_e, &ANIM[my_level.wave[w].type], 0.2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation en bas
                    for (a = 0; a < my_level.wave[w].nb_down; a++ ) {
                        ENEMY[current_nb_enemy++] = create_Enemy( DOWN ,  my_level.StartPos_DOWN_s, my_level.StartPos_DOWN_e,   &ANIM[my_level.wave[w].type], 0.2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation a gauche
                    for (a = 0; a < my_level.wave[w].nb_left; a++ ) {
                        ENEMY[current_nb_enemy++] = create_Enemy( LEFT ,  my_level.StartPos_LEFT_s, my_level.StartPos_LEFT_e,   &ANIM[my_level.wave[w].type], 0.2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    printf ("%d\n", b);
                }
                printf ("Nombre d'ennemi : %d\n", current_nb_enemy);

        }

       /******************************************************************************************************************
                                                    COMPTEURS
        *******************************************************************************************************************/
        if (clock() > CounterTimeA + 1000) {

            b = 0;
            int current_enemy_alive = 0;

            for (a = 0; a < current_nb_enemy; a++) {

                if ( ENEMY[a]->is_actif ) { b++; }
                if ( ENEMY[a]->visible )  { current_enemy_alive++; }
            }
            printf("Nombre d'ennemi en vie : %d\n", current_enemy_alive);

            if ( current_enemy_alive == 0 ) {

                CounterBeforeChgLevel++;
                if ( CounterBeforeChgLevel > 5 ) {

                    CounterBeforeChgLevel = 0;
                    current_level++;
                    if (current_level >= LEVEL_NB_TOTAL ) {
                        current_level = 0;
                    }
                    change_level = true;
                }
            }
            CounterTimeA = clock();
        }


        /******************************************************************************************************************
                                                    AFFICHAGE
        *******************************************************************************************************************/
        SDL_RenderClear     (pRenderer);
        // Affichage de la map
        SDL_RenderCopy      (pRenderer, my_level.pTexture_MAP, NULL, NULL);

        // Affichage des obstacles (mode Debug)
        // affiche_obstacle    (pRenderer, &my_level);

        // Affichage de l'arrivé
        anime_sprite(ARRIVE);
        affiche_sprite (pRenderer, ARRIVE);

        // Affichage des Sprites
        for (a = 0; a < current_nb_enemy; a++) {
            anime_sprite    (ENEMY[a]);
            avance_sprite   (ENEMY[a], &my_level);
            affiche_sprite  (pRenderer, ENEMY[a]);
        }

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
    for (a = 0; a < WAVE_NB * WAVE_ENEMY_MAX_BY_WAVE; a++) {
        destroy_sprite(&ENEMY[a]);
    }

    SDL_DestroyTexture(ANIM[0].texture);
    SDL_DestroyTexture(ANIM[1].texture);
    SDL_DestroyTexture(ANIM[2].texture);

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
