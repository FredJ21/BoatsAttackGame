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
#include "affichage_texte.h"
#include "tower.h"
#include "Algo_Collision.h"



int main( int argc, char* args[] )
{

    //printf("Go ...!!!\n");
    SDL_Log("Fred DEBUG - Go 15:54\n");


    /******************************************************************************************************************
                                                INIT SDL 2
    *******************************************************************************************************************/

    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO) != 0 ) {  printf( "SDL_Init ERREUR ! SDL_GetError: %s\n", SDL_GetError() ); return -1; }

    // Création de la fenêtre
    SDL_Window *pWindow = NULL;
    pWindow = SDL_CreateWindow( APP_TITRE , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAP_TAILLE_X, MAP_TAILLE_Y, SDL_WINDOW_SHOWN );
//    pWindow = SDL_CreateWindow( APP_TITRE , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP );
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

    SDL_Delay( 1000 );

    /******************************************************************************************************************
                                                INIT SDL 2 TTF
    *******************************************************************************************************************/
    // Initialize SDL TTF
    if( TTF_Init() != 0 ) {  printf( "TTF_Init ERREUR ! SDL_GetError: %s\n", SDL_GetError() ); return -1; }

    // pour le titre de chaque level
    TTF_Font *police_level_titre;
    police_level_titre = TTF_OpenFont(POLICE_LEVEL_TITRE, POLICE_LEVEL_TITRE_SIZE);
    if(!police_level_titre) {                  printf( "TTF_OpenFont ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    SDL_Log("Fred DEBUG - INIT SDL OK\n");
    /******************************************************************************************************************
                                                VARIABLES
    *******************************************************************************************************************/
    bool flag_fin                    = false;        // fin du programme
    bool flag_change_level           = true;         // changement de level
    bool flag_affiche_level_titre    = false;

    bool flag_mode_place_tower       = false;        // mode permettant de positionner les tourelles
    bool flag_mode_tower_selected    = false;        // la tourelle est choisi
    bool flag_mode_game              = true;         // mode normal du jeu, permet de savoir qu'aucun autre mode n'est actif

    bool flag_tower_position_ok      = false;        // vrai si la tourelle n'est pas dans l'eau

    unsigned int t_Avant_Traitement;          // permet de gérer les fps
    unsigned int t_Apres_Traitement;

    unsigned int CounterSecond = 0;     // traitement toute les second
    int CounterBeforeChgLevel = 0;      // pause avant le changement de level
    int CounterTimeLevel = 0;            // second depuis le demarrage du level

    int a = 0, b = 0, w = 0;
    int current_level       = 0;
    int current_nb_enemy    = 0;
    int current_enemy_alive = 0;
    int current_nb_tower    = 0;                // nombre de tourelle
    int current_tower       = TOWER_MAX;        // id tourelle selectionnée, TOWER_MAX signifi qu'aucune n'est seletionnée
    int current_nb_missile  = 0;

    t_level my_level = {};
    t_score my_score = {};

    int current_mouse_x, current_mouse_y;

    unsigned int  game_sleep;

    srand(time(NULL));

    SDL_Log("Fred DEBUG - INIT GAME\n");
    /******************************************************************************************************************
                                                INIT GAME
    *******************************************************************************************************************/
    SDL_Surface *pSurface_TUILE = SDL_LoadBMP (TILE_FILE);
    if(!pSurface_TUILE) { printf( "SDL_Surface_TUILE ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    /** ANIMATION **/
    t_animation ANIM[3];

    strcpy(ANIM[0].file,   "images/PetitBateau1.bmp");
    ANIM[0].tx              = 48;
    ANIM[0].ty              = 48;
    ANIM[0].nb_colonne      = 3;
    ANIM[0].nb_image        = 12;
    ANIM[0].nb_img_by_dir   = 3;
    ANIM[0].nb_tour         = 5;
    ANIM[0].vitesse         = 2;

    strcpy(ANIM[1].file,   "images/PetitBateau2.bmp");
    ANIM[1].tx              = 48;
    ANIM[1].ty              = 48;
    ANIM[1].nb_colonne      = 3;
    ANIM[1].nb_image        = 12;
    ANIM[1].nb_img_by_dir   = 3;
    ANIM[1].nb_tour         = 5;
    ANIM[1].vitesse         = 2;

    strcpy(ANIM[2].file,   "images/PetitBateau3.bmp");
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

    t_animation DRAPEAU = { "images/Flag.bmp", 31, 40, 11, 11, 11, NULL, 3, 1 };
    init_animation( &DRAPEAU, pRenderer);

    t_animation ANIM_TOWER = { "images/Tower1.bmp", 48, 48, 3, 12, 0, NULL, 0, 1 };
    init_animation( &ANIM_TOWER, pRenderer);

    t_animation ANIM_MISSILE = { "images/Missile.bmp", 10, 10, 1, 1, 0, NULL, 0, 5 };
    init_animation( &ANIM_MISSILE, pRenderer);


    /* SPRITE ENNEMI */
    t_sprite *ENEMY[WAVE_NB * WAVE_ENEMY_MAX_BY_WAVE];   //tableau de pointeurs

     /* SPRITE ARRIVE */
    t_sprite *ARRIVE;
    ARRIVE = init_sprite (&DRAPEAU);

    /* SPRITE TOWER */
    t_tower *TOWER_MOUSE = create_Tower (0,0,&ANIM_TOWER);  // tourelle d'aide au positionnement, sous pointeur souris
    t_tower *TOWER[TOWER_MAX];                         // tableau de pointeurs

    // charge la police pour l'affichage du score
    my_score.police = TTF_OpenFont(POLICE_SCORE, POLICE_SCORE_SIZE);
    if(!my_score.police) {                  printf( "TTF_OpenFont ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    SDL_Log("Fred DEBUG - START MAIN LOOP\n");
    /******************************************************************************************************************
                                                BOUCLE PRINCIPALE
    *******************************************************************************************************************/
    while (!flag_fin) {

        t_Avant_Traitement = SDL_GetTicks();


        /******************************************************************************************************************
                                                    GESTION DES EVENEMENTS
        *******************************************************************************************************************/
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type){

                case SDL_QUIT:
                    flag_fin = true;
                    //printf ("By By !!\n");
                    break;

                case SDL_KEYDOWN:

                    switch( event.key.keysym.sym ){
                        case SDLK_ESCAPE:
                            flag_fin = true;
                            break;
                        case SDLK_l:
                            current_level++;
                            if (current_level >= LEVEL_NB_TOTAL ) {
                                current_level = 0;
                            }
                            flag_change_level = true;
                            break;
                        case SDLK_m:

                            break;
                        case SDLK_t :
                            if (flag_mode_game && current_nb_tower < TOWER_MAX) {

                                flag_mode_place_tower = true;
                                flag_mode_game = false;

                            } else if (flag_mode_place_tower) {

                                flag_mode_place_tower = false;
                                flag_mode_game = true;

                            }
                            break;
                        case SDLK_SPACE:
                            for (a = 0; a < current_nb_tower; a++){
                                tir_tower(TOWER[a], current_nb_tower);
                            }
                            break;
                        default:
                            //printf ("KEY\n");
                            break;
                    }
                    break;

                case SDL_FINGERDOWN:
                    if (flag_mode_game && current_nb_tower < TOWER_MAX) {

                                flag_mode_place_tower = true;
                                flag_mode_game = false;

                            } else if (flag_mode_place_tower) {

                                flag_mode_place_tower = false;
                                flag_mode_game = true;

                            }


                // Souris
//                case SDL_MOUSEMOTION :
                case SDL_FINGERMOTION :
                    SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                    // permet de préparer les coordonnés pour le mode place_tower
                    TOWER_MOUSE->x = current_mouse_x;
                    TOWER_MOUSE->y = current_mouse_y;

                    // verifie si la position est valide afin de changer la couleur de souris
                    if (flag_mode_place_tower) {
                        if ( is_tower_new_valid_position(TOWER_MOUSE, &my_level, TOWER, current_nb_tower) ) {
                            flag_tower_position_ok = true;
                        } else {
                            flag_tower_position_ok = false;
                        }
                    }
                    break;

 //               case SDL_MOUSEBUTTONDOWN :
                case SDL_FINGERUP :

                    // tentative de placer une nouvelle tour
                    if (flag_mode_place_tower && flag_tower_position_ok ) {
                        printf ("1\n");

                        TOWER[current_nb_tower] = create_Tower(current_mouse_x, current_mouse_y, &ANIM_TOWER);
                        current_nb_tower++;

                        flag_mode_place_tower = false;
                        flag_tower_position_ok = false;
                        flag_mode_game = true;
                    }

                    // une tourelle est selectionnée , on indique la cible
                    else if (flag_mode_tower_selected){
                        printf ("2\n");

                        TOWER[current_tower]->cible_x = current_mouse_x;
                        TOWER[current_tower]->cible_y = current_mouse_y;

                        calcul_angle_tower(TOWER[current_tower]);

                        TOWER[current_tower]->selected = false;
                        flag_mode_tower_selected = false;
                        flag_mode_game = true;
                    }

                    // selection d'une tourelle
                    else if (flag_mode_game) {
                        printf ("3\n");
                        current_tower = is_tower_position(current_mouse_x, current_mouse_y, TOWER, current_nb_tower);
                        if (current_tower < TOWER_MAX) {   // TOWER_MAX signifi qu'aucune n'est seletionnée

                            TOWER[current_tower]->selected = true;
                            flag_mode_tower_selected = true;
                        }
                    }

                   break;
            }
        }
        /******************************************************************************************************************
                                                    CHANGEMENT  DE NIVEAU
        *******************************************************************************************************************/
        if (flag_change_level) {

                SDL_Log("Fred DEBUG - Change_level\n");

                /** NETTOYAGE **/
                SDL_Log("Fred DEBUG - Change_level Nettoyage 1\n");
                for (a = 0; a < current_nb_enemy ; a++) {
                    SDL_Log("Fred DEBUG - clear ENEMY %d\n", a);
                    destroy_sprite(&ENEMY[a]);
                }
                SDL_Log("Fred DEBUG - Change_level Nettoyage 2\n");
                for (a = 0; a <  current_nb_tower; a++) {
                    SDL_Log("Fred DEBUG - clear TOWER %d\n", a);
                    destroy_tower(&TOWER[a]);
                }
                SDL_Log("Fred DEBUG - Change_level Nettoyage 3\n");
                clear_level (&my_level);


                // RAZ des flags
                flag_change_level           = false;
                flag_affiche_level_titre    = true;
                flag_mode_game              = true;
                flag_mode_place_tower       = false;
                flag_mode_tower_selected    = false;
                flag_tower_position_ok      = false;

                // RAZ des variables currentes
                current_nb_enemy = 0;
                current_nb_tower = 0;
                current_tower    = TOWER_MAX;   // id tourelle selectionnée, TOWER_MAX signifi qu'aucune n'est seletionnée

                my_score.level = current_level + 1;


                /** LEVEL **/
                SDL_Log("Fred DEBUG - Change_level Init level\n");
                init_level(&my_level, current_level, pSurface_TUILE, pRenderer);
                //init_texture_obstacle(pRenderer, &my_level);
                SDL_Log("Fred DEBUG - Change_level Init level 2\n");
                init_level_titre(pRenderer, &my_level, police_level_titre);

                SDL_Log("Fred DEBUG - Change_level Init level 3\n");
                place_sprite(ARRIVE, my_level.cibleX, my_level.cibleY);

                SDL_Log("Fred DEBUG - Change_level Init level 4\n");
                init_level_chemins(&my_level);
                //affiche_map_console ( &my_level);


                /** CREATE ENEMY **/
                SDL_Log("Fred DEBUG - Change_level Create Enemy\n");
                for ( w = 0; w < WAVE_NB; w++ ) {
                    //printf ("Level %d - Wave %d - ", current_level, w);
                    b = 0;
                    // creation en haut
                    for (a = 0; a < my_level.wave[w].nb_up; a++ ) {
                        ENEMY[current_nb_enemy++] = create_Enemy( UP ,    my_level.StartPos_UP_s, my_level.StartPos_UP_e,       &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation a droite
                    for (a = 0; a < my_level.wave[w].nb_right; a++ ) {
                        ENEMY[current_nb_enemy++] = create_Enemy( RIGHT , my_level.StartPos_RIGHT_s, my_level.StartPos_RIGHT_e, &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation en bas
                    for (a = 0; a < my_level.wave[w].nb_down; a++ ) {
                        ENEMY[current_nb_enemy++] = create_Enemy( DOWN ,  my_level.StartPos_DOWN_s, my_level.StartPos_DOWN_e,   &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation a gauche
                    for (a = 0; a < my_level.wave[w].nb_left; a++ ) {
                        ENEMY[current_nb_enemy++] = create_Enemy( LEFT ,  my_level.StartPos_LEFT_s, my_level.StartPos_LEFT_e,   &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in);
                        b++;
                    }
                }
               // printf ("Nombre d'ennemi : %d\n", current_nb_enemy);

                CounterTimeLevel = 0;

                SDL_Log("Fred DEBUG - Change_level OK\n");

        }

       /******************************************************************************************************************
                                                    TRAITEMENTS TOUTES LES SECONDES
        *******************************************************************************************************************/
        if (SDL_GetTicks() > CounterSecond + 1000) {

            // compte le nombre d'ennemi en vie
            current_enemy_alive = 0;

            for (a = 0; a < current_nb_enemy; a++) {
                if ( ENEMY[a]->visible )  { current_enemy_alive++; }
            }

            // mise à jour du score
            my_score.NbEnemy = current_enemy_alive;
            init_score( pRenderer, &my_score);


            // decide du changement de level
            if ( current_enemy_alive == 0 ) {

                CounterBeforeChgLevel++;
                if ( CounterBeforeChgLevel > 5 ) {

                    CounterBeforeChgLevel = 0;
                    current_level++;
                    if (current_level >= LEVEL_NB_TOTAL ) {
                        current_level = 0;
                    }
                    flag_change_level = true;
                }
            }

            //Affichage du titre en debut de level
            if (CounterTimeLevel < 2 ){
                    flag_affiche_level_titre = true;
            }
            else {
                    flag_affiche_level_titre =false;
            }

            CounterTimeLevel++;
            CounterSecond = SDL_GetTicks();

        }
        /******************************************************************************************************************
                                                    COLLISION
        *******************************************************************************************************************/

        test_collision(TOWER, current_nb_tower, ENEMY, current_nb_enemy);

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
        // Affichage des tourelles
        for (a = 0; a < current_nb_tower; a++){


            for ( b = 0; b < TOWER_NB_MISSILE_MAX; b++ ){
                avance_missile(&TOWER[a]->missile[b]);
                affiche_missile (pRenderer, &TOWER[a]->missile[b], &ANIM_MISSILE);
            }
            anime_tower     (TOWER[a]);
            affiche_tower (pRenderer, TOWER[a]);
        }

        // Affichage de la tourelle de depart, sous la souris
        if (flag_mode_place_tower) {
            // affichage d'un fond vert ou rouge celon terrain
            TOWER_MOUSE->visible = 180;
            if ( flag_tower_position_ok )  {
                    TOWER_MOUSE->img_current = 1;
            } else {
                    TOWER_MOUSE->img_current = 0;
            }

            affiche_tower (pRenderer, TOWER_MOUSE);

            TOWER_MOUSE->visible = 254;
            TOWER_MOUSE->img_current = 2;
            affiche_tower (pRenderer, TOWER_MOUSE);
        }


        // Affichage du texte
        if (flag_affiche_level_titre) {       affiche_titre(pRenderer, &my_level);    }

        // Affichage du score
        affiche_score( pRenderer, &my_score);

        // Mise a jour de l'affichage
        SDL_RenderPresent   (pRenderer);


        /************************************************/
        /**   Calcul du temps de traitement et pause   **/
        /************************************************/
        t_Apres_Traitement = SDL_GetTicks();
        game_sleep = (1000 / GAME_FPS) - (t_Avant_Traitement - t_Apres_Traitement);
        /** TODO :  calcul du temps de traitement sur Android **/
        //game_sleep = 1000 / GAME_FPS;

        SDL_Delay( game_sleep );
    }

    /******************************************************************************************************************
                                                    FIN
    *******************************************************************************************************************/
    // Nettoyage
    for (a = 0; a < current_nb_enemy; a++) {
        destroy_sprite(&ENEMY[a]);
    }
    for (a = 0; a <  current_nb_tower; a++) {
        destroy_tower(&TOWER[a]);
    }


    destroy_sprite(&ARRIVE);
    destroy_tower(&TOWER_MOUSE);

    SDL_DestroyTexture(ANIM[0].texture);
    SDL_DestroyTexture(ANIM[1].texture);
    SDL_DestroyTexture(ANIM[2].texture);

    SDL_DestroyTexture(DRAPEAU.texture);
    SDL_DestroyTexture(ANIM_TOWER.texture);
    SDL_DestroyTexture(ANIM_MISSILE.texture);
    SDL_DestroyTexture(my_score.pTexture_Score);

    clear_level (&my_level);
    clear_score (&my_score);

    SDL_DestroyTexture(pTexture);
    SDL_FreeSurface(pSurface);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow( pWindow );

    TTF_CloseFont(police_level_titre);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
