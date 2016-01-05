#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "config.h"
#include "main.h"
#include "level.h"
#include "anim.h"
#include "Algo_A_star.h"
#include "affichage_texte.h"
#include "tower.h"
#include "Algo_Collision.h"



int main( int argc, char* args[] )
{

    //printf("Go ...!!!\n");
    SDL_Log("Fred DEBUG - Go 14:48\n");


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

    /******************************************************************************************************************
                                                INIT SDL 2  -  Affichage d'une image de chargement ...
    *******************************************************************************************************************/
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

    t_level my_level = {};
    t_score my_score = {};
    t_game  my_game  = {} ;


    unsigned int t_Avant_Traitement;        // permet de gérer les fps
    unsigned int t_Apres_Traitement;
    unsigned int  game_sleep;

    unsigned int CounterSecond = 0;         // traitement toute les second
    int CounterBeforeChgLevel = 0;          // pause avant le changement de level
    int CounterTimeLevel = 0;               // second depuis le demarrage du level

    int a = 0, b = 0, w = 0;

    srand(time(NULL));

    /******************************************************************************************************************
                                                INIT GAME
    *******************************************************************************************************************/
    SDL_Log("Fred DEBUG - INIT GAME\n");

    my_game.flag_fin                    = false;        // fin du programme
    my_game.flag_change_level           = true;         // changement de level
    my_game.flag_affiche_level_titre    = false;

    my_game.flag_event_DOWN             = false;
    my_game.flag_event_UP               = false;
    my_game.flag_event_MOVE             = false;

    my_game.flag_mode_place_tower       = false;        // mode permettant de positionner les tourelles
    my_game.flag_mode_tower_selected    = false;        // la tourelle est choisi
    my_game.flag_mode_game              = true;         // mode normal du jeu, permet de savoir qu'aucun autre mode n'est actif

    my_game.flag_tower_position_ok      = false;        // vrai si la tourelle n'est pas dans l'eau

    my_game.current_level       = 0;
    my_game.current_nb_enemy    = 0;
    my_game.current_enemy_alive = 0;
    my_game.current_nb_tower    = 0;                // nombre de tourelle
    my_game.current_tower       = TOWER_MAX;        // id tourelle selectionnée, TOWER_MAX signifi qu'aucune n'est seletionnée
    my_game.current_nb_missile  = 0;


    /******************************************************************************************************************
                                                INIT DES IMAGES / ANNIMATIONS
    *******************************************************************************************************************/
    /** FICHIER TUILE (chargement) **/
    SDL_Surface *pSurface_TUILE = SDL_LoadBMP (TILE_FILE);
    if(!pSurface_TUILE) { printf( "SDL_Surface_TUILE ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    /** ANIMATION des ennemis  **/
    t_animation ANIM[3];

    strcpy(ANIM[0].file,   "images/PetitBateau1.bmp");
        ANIM[0].tx              = 48;   ANIM[0].ty              = 48;
        ANIM[0].nb_colonne      = 3;    ANIM[0].nb_image        = 12;   ANIM[0].nb_img_by_dir   = 3;    ANIM[0].nb_tour         = 5; ANIM[0].vitesse         = 2;
        init_animation( &ANIM[0], pRenderer);

    strcpy(ANIM[1].file,   "images/PetitBateau2.bmp");
        ANIM[1].tx              = 48;   ANIM[1].ty              = 48;
        ANIM[1].nb_colonne      = 3;    ANIM[1].nb_image        = 12;   ANIM[1].nb_img_by_dir   = 3;    ANIM[1].nb_tour         = 5;    ANIM[1].vitesse         = 2;
        init_animation( &ANIM[1], pRenderer);

    strcpy(ANIM[2].file,   "images/PetitBateau3.bmp");
        ANIM[2].tx              = 48;   ANIM[2].ty              = 48;
        ANIM[2].nb_colonne      = 3;    ANIM[2].nb_image        = 12;   ANIM[2].nb_img_by_dir   = 3;    ANIM[2].nb_tour         = 5;    ANIM[2].vitesse         = 2;
        init_animation( &ANIM[2], pRenderer);


    t_animation DRAPEAU = { "images/Flag.bmp", 31, 40, 11, 11, 11, NULL, 3, 1 };
        init_animation( &DRAPEAU, pRenderer);

    t_animation ANIM_TOWER = { "images/Tower1.bmp", 48, 48, 3, 12, 0, NULL, 0, 1 };
        init_animation( &ANIM_TOWER, pRenderer);

    t_animation ANIM_MISSILE = { "images/Missile.bmp", 10, 10, 1, 1, 0, NULL, 0, 5 };
        init_animation( &ANIM_MISSILE, pRenderer);

//    t_animation ANIM_EXPLOSION = { "images/explosion_1.bmp", 44, 46, 40, 40, 40, NULL, 1, 1 };
    t_animation ANIM_EXPLOSION = { "images/explosion_1_2.bmp", 88, 92, 40, 40, 40, NULL, 1, 1 };
        init_animation( &ANIM_EXPLOSION, pRenderer);

    t_animation IMG_BUTTON_TIR = { "images/Tir_100x80_2.bmp", 100, 80, 1, 1, 1, NULL, 1, 1 };
        init_animation( &IMG_BUTTON_TIR, pRenderer);

    t_animation IMG_BUTTON_TOWER = { "images/Tower_Botton_100x80_3.bmp", 100, 80, 1, 1, 1, NULL, 1, 1 };
        init_animation( &IMG_BUTTON_TOWER, pRenderer);

    /******************************************************************************************************************
                                                INIT DES SPRITES  / Objets afficher
    *******************************************************************************************************************/
    /* SPRITE ENNEMI */
    t_sprite *ENEMY[WAVE_NB * WAVE_ENEMY_MAX_BY_WAVE];      //tableau de pointeurs

     /* SPRITE ARRIVE */
    t_sprite *ARRIVE;
    ARRIVE = init_sprite (&DRAPEAU);

    /* SPRITE TOWER */
    t_tower *TOWER_MOUSE = create_Tower (0,0,&ANIM_TOWER);  // tourelle d'aide au positionnement, sous le pointeur souris
    t_tower *TOWER[TOWER_MAX];                              // tableau de pointeurs

     /* SPRITE BUTTON */
    t_sprite *BUTTON_TIR;
    BUTTON_TIR = init_sprite (&IMG_BUTTON_TIR);
    BUTTON_TIR->x = MAP_TAILLE_X - BUTTON_TIR->anim->tx/2 - 15;
    BUTTON_TIR->y = MAP_TAILLE_Y - BUTTON_TIR->anim->ty/2 - 15 ;

    t_sprite *BUTTON_TOWER;
    BUTTON_TOWER = init_sprite (&IMG_BUTTON_TOWER);
    BUTTON_TOWER->x = BUTTON_TOWER->anim->tx/2 + 15;
    BUTTON_TOWER->y = MAP_TAILLE_Y - BUTTON_TOWER->anim->ty/2 - 15 ;

    t_sprite *EXPLOSION;
    EXPLOSION = init_sprite (&ANIM_EXPLOSION);
    EXPLOSION->x = 200;
    EXPLOSION->y = 100;


    /******************************************************************************************************************
                                                INIT POLICE DE CARACTERE
    *******************************************************************************************************************/
    // charge la police pour l'affichage du score
    my_score.police = TTF_OpenFont(POLICE_SCORE, POLICE_SCORE_SIZE);
    if(!my_score.police) {                  printf( "TTF_OpenFont ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    /******************************************************************************************************************
                                                BOUCLE PRINCIPALE
    *******************************************************************************************************************/
    SDL_Log("Fred DEBUG - START MAIN LOOP\n");
    while (!my_game.flag_fin) {

        t_Avant_Traitement = SDL_GetTicks();


        /******************************************************************************************************************
                                                    GESTION DES EVENEMENTS
        *******************************************************************************************************************/
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type){

                case SDL_QUIT:
                    my_game.flag_fin = true;
                    //printf ("By By !!\n");
                    break;
                case SDL_USEREVENT:
                    SDL_Log("Fred DEBUG - SDL_USEREVENT\n");
                    break;
                case SDL_WINDOWEVENT:
                    SDL_Log("Fred DEBUG - SDL_WINDOWEVENT\n");
                    break;
                case SDL_APP_TERMINATING:
                    SDL_Log("Fred DEBUG - SDL_APP_TERMINATING\n");
                    break;
                case SDL_MULTIGESTURE:
                    SDL_Log("Fred DEBUG - SDL_MULTIGESTURE\n");
                    break;

                /***************************************************************************  CLAVIER **/
                case SDL_KEYDOWN:

                    SDL_Log("Fred DEBUG - SDL_KEYDOWN\n");
                    switch( event.key.keysym.sym ){
                        case SDLK_ESCAPE:
                            my_game.flag_fin = true;
                            break;
                        case SDLK_AC_BACK:
                            SDL_Log("Fred DEBUG - SDLK_AC_BACK\n");
                            my_game.flag_fin = true;
                            break;
                        case SDLK_SPACE:
                            break;
                        default:
                            //printf ("KEY\n");
                            break;
                    }
                    break;

                /***************************************************************************   SOURIS  **/
/*
                case SDL_MOUSEBUTTONDOWN :
                    SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                    //SDL_Log("Fred DEBUG - MOUSEBUTTONDOWN : %d x %d\n", current_mouse_x, current_mouse_y);
                    flag_event_DOWN = true;
                    break;

                case SDL_MOUSEMOTION :
                    SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                    //SDL_Log("Fred DEBUG - MOUSEMOTION : %d x %d\n", current_mouse_x, current_mouse_y);
                    flag_event_MOVE = true;
                    break;

                case SDL_MOUSEBUTTONUP :
                    SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                    //SDL_Log("Fred DEBUG - MOUSEBUTTONUP : %d x %d\n", current_mouse_x, current_mouse_y);
                    flag_event_UP = true;
                    break;
*/
                /***************************************************************************   FINGER  **/
                case SDL_FINGERDOWN:
                    my_game.current_mouse_x = (int)(event.tfinger.x * MAP_TAILLE_X);
                    my_game.current_mouse_y = (int)(event.tfinger.y * MAP_TAILLE_Y);
                    //SDL_Log("Fred DEBUG - FINGERDOWN : %d x %d\n", current_mouse_x, current_mouse_y);
                    my_game.flag_event_DOWN = true;
                    break;

                case SDL_FINGERMOTION :
                    my_game.current_mouse_x = (int)(event.tfinger.x * MAP_TAILLE_X);
                    my_game.current_mouse_y = (int)(event.tfinger.y * MAP_TAILLE_Y);
                    //SDL_Log("Fred DEBUG - FINGERMOTION : %d x %d\n", current_mouse_x, current_mouse_y);
                    my_game.flag_event_MOVE = true;
                    break;

                case SDL_FINGERUP :
                    my_game.current_mouse_x = (int)(event.tfinger.x * MAP_TAILLE_X);
                    my_game.current_mouse_y = (int)(event.tfinger.y * MAP_TAILLE_Y);
                    //SDL_Log("Fred DEBUG - FINGERUP : %d x %d\n", current_mouse_x, current_mouse_y);
                    my_game.flag_event_UP = true;
                   break;

            }

        /******************************************************************************************************************
                                                    TRAITEMENT DES EVENEMENTS
        *******************************************************************************************************************/

            /***************************************************************/
            if (my_game.flag_event_DOWN) {
                my_game.flag_event_DOWN = false;

                if (my_game.flag_mode_game) {
                    if (my_game.current_mouse_x > ZONE_BUTTON_TIR_X && my_game.current_mouse_y > ZONE_BUTTON_TIR_Y) {
                        SDL_Log("Fred DEBUG - BUTTON TIR\n");

                        for (a = 0; a < my_game.current_nb_tower; a++){
                            tir_tower(TOWER[a], my_game.current_nb_tower);
                        }

                    }
                    if (my_game.current_mouse_x < ZONE_BUTTON_TOWER_X && my_game.current_mouse_y > ZONE_BUTTON_TOWER_Y) {
                        SDL_Log("Fred DEBUG - BUTTON TOWER\n");

                        if (my_game.current_nb_tower < TOWER_MAX) {

                            my_game.flag_mode_place_tower = true;
                            my_game.flag_mode_game = false;
                            TOWER_MOUSE->x = MAP_TAILLE_X / 2;
                            TOWER_MOUSE->y = MAP_TAILLE_Y / 2;
                        }
                    }
                }
                else if (my_game.flag_mode_place_tower) {
                    if (my_game.current_mouse_x < ZONE_BUTTON_TOWER_X && my_game.current_mouse_y > ZONE_BUTTON_TOWER_Y) {
                        SDL_Log("Fred DEBUG - BUTTON TOWER\n");
                        my_game.flag_mode_place_tower = false;
                        my_game.flag_mode_game = true;
                    }
                }
            }

            /***************************************************************/
            else if (my_game.flag_event_MOVE) {
                my_game.flag_event_MOVE = false;

                if (my_game.flag_mode_place_tower) {
                    // permet de préparer les coordonnés pour le mode place_tower
                    TOWER_MOUSE->x = my_game.current_mouse_x;
                    TOWER_MOUSE->y = my_game.current_mouse_y;
                    // verifie si la position est valide afin de changer la couleur de souris
                    if ( is_tower_new_valid_position(TOWER_MOUSE, &my_level, TOWER, my_game.current_nb_tower) ) {
                        my_game.flag_tower_position_ok = true;
                    } else {
                        my_game.flag_tower_position_ok = false;
                    }
                }
            }

            /***************************************************************/
            else if (my_game.flag_event_UP) {
                my_game.flag_event_UP = false;

                    // tentative de placer une nouvelle tour
                    if (my_game.flag_mode_place_tower && my_game.flag_tower_position_ok ) {
                        SDL_Log("Fred DEBUG -  PLACE TOWER\n");

                        TOWER[my_game.current_nb_tower] = create_Tower(my_game.current_mouse_x, my_game.current_mouse_y, &ANIM_TOWER);
                        my_game.current_nb_tower++;

                        my_game.flag_mode_place_tower = false;
                        my_game.flag_tower_position_ok = false;
                        my_game.flag_mode_game = true;
                    }

                    // une tourelle est selectionnée , on indique la cible
                    else if (my_game.flag_mode_tower_selected){
                        SDL_Log("Fred DEBUG - TOWER NEW CIBLE\n");

                        TOWER[my_game.current_tower]->cible_x = my_game.current_mouse_x;
                        TOWER[my_game.current_tower]->cible_y = my_game.current_mouse_y;

                        calcul_angle_tower(TOWER[my_game.current_tower]);

                        TOWER[my_game.current_tower]->selected = false;
                        my_game.flag_mode_tower_selected = false;
                        my_game.flag_mode_game = true;
                    }

                    // selection d'une tourelle
                    else if (my_game.flag_mode_game) {
                        my_game.current_tower = is_tower_position(my_game.current_mouse_x, my_game.current_mouse_y, TOWER, my_game.current_nb_tower);
                        if (my_game.current_tower < TOWER_MAX) {   // TOWER_MAX signifi qu'aucune n'est seletionnée
                            SDL_Log("Fred DEBUG - SELECT TOWER\n");
                            TOWER[my_game.current_tower]->selected = true;
                            my_game.flag_mode_tower_selected = true;
                        }
                    }


            }

        }

        /******************************************************************************************************************
                                                    CHANGEMENT  DE NIVEAU
        *******************************************************************************************************************/
        if (my_game.flag_change_level) {

                SDL_Log("Fred DEBUG - Change_level\n");

                /** NETTOYAGE **/
                SDL_Log("Fred DEBUG - Change_level Nettoyage 1\n");
                for (a = 0; a < my_game.current_nb_enemy ; a++) {
                    SDL_Log("Fred DEBUG - clear ENEMY %d\n", a);
                    destroy_sprite(&ENEMY[a]);
                }
                SDL_Log("Fred DEBUG - Change_level Nettoyage 2\n");
                for (a = 0; a <  my_game.current_nb_tower; a++) {
                    SDL_Log("Fred DEBUG - clear TOWER %d\n", a);
                    destroy_tower(&TOWER[a]);
                }
                SDL_Log("Fred DEBUG - Change_level Nettoyage 3\n");
                clear_level (&my_level);


                // RAZ des flags
                my_game.flag_change_level           = false;
                my_game.flag_affiche_level_titre    = true;
                my_game.flag_mode_game              = true;
                my_game.flag_mode_place_tower       = false;
                my_game.flag_mode_tower_selected    = false;
                my_game.flag_tower_position_ok      = false;

                // RAZ des variables currentes
                my_game.current_nb_enemy = 0;
                my_game.current_nb_tower = 0;
                my_game.current_tower    = TOWER_MAX;   // id tourelle selectionnée, TOWER_MAX signifi qu'aucune n'est seletionnée

                my_score.level = my_game.current_level + 1;


                /** LEVEL **/
                SDL_Log("Fred DEBUG - Change_level Init level\n");
                init_level(&my_level, my_game.current_level, pSurface_TUILE, pRenderer);
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
                        ENEMY[my_game.current_nb_enemy++] = create_Enemy( UP ,    my_level.StartPos_UP_s, my_level.StartPos_UP_e,       &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation a droite
                    for (a = 0; a < my_level.wave[w].nb_right; a++ ) {
                        ENEMY[my_game.current_nb_enemy++] = create_Enemy( RIGHT , my_level.StartPos_RIGHT_s, my_level.StartPos_RIGHT_e, &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation en bas
                    for (a = 0; a < my_level.wave[w].nb_down; a++ ) {
                        ENEMY[my_game.current_nb_enemy++] = create_Enemy( DOWN ,  my_level.StartPos_DOWN_s, my_level.StartPos_DOWN_e,   &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in);
                        b++;
                    }
                    // creation a gauche
                    for (a = 0; a < my_level.wave[w].nb_left; a++ ) {
                        ENEMY[my_game.current_nb_enemy++] = create_Enemy( LEFT ,  my_level.StartPos_LEFT_s, my_level.StartPos_LEFT_e,   &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in);
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
            my_game.current_enemy_alive = 0;

            for (a = 0; a < my_game.current_nb_enemy; a++) {
                if ( ENEMY[a]->visible )  { my_game.current_enemy_alive++; }
            }

            // mise à jour du score
            my_score.NbEnemy = my_game.current_enemy_alive;
            init_score( pRenderer, &my_score);


            // decide du changement de level
            if ( my_game.current_enemy_alive == 0 ) {

                CounterBeforeChgLevel++;
                if ( CounterBeforeChgLevel > 5 ) {

                    CounterBeforeChgLevel = 0;
                    my_game.current_level++;
                    if (my_game.current_level >= LEVEL_NB_TOTAL ) {
                        my_game.current_level = 0;
                    }
                    my_game.flag_change_level = true;
                }
            }

            //Affichage du titre en debut de level
            if (CounterTimeLevel < 2 ){
                    my_game.flag_affiche_level_titre = true;
            }
            else {
                    my_game.flag_affiche_level_titre =false;
            }

            CounterTimeLevel++;
            CounterSecond = SDL_GetTicks();

        }
        /******************************************************************************************************************
                                                    COLLISION
        *******************************************************************************************************************/

        test_collision(TOWER, my_game.current_nb_tower, ENEMY, my_game.current_nb_enemy);

        /******************************************************************************************************************
                                                    AFFICHAGE
        *******************************************************************************************************************/
        SDL_RenderClear     (pRenderer);
        // Affichage de la map
        SDL_RenderCopy      (pRenderer, my_level.pTexture_MAP, NULL, NULL);

        // Affichage des obstacles (mode Debug)
        affiche_obstacle    (pRenderer, &my_level);

        // Affichage de l'arrivé
        anime_sprite(ARRIVE);
        affiche_sprite (pRenderer, ARRIVE);

        // Affichage des ENEMY
        for (a = 0; a < my_game.current_nb_enemy; a++) {
            anime_sprite    (ENEMY[a]);
            avance_sprite   (ENEMY[a], &my_level);
            affiche_sprite  (pRenderer, ENEMY[a]);
        }
        // Affichage des tourelles
        for (a = 0; a < my_game.current_nb_tower; a++){


            for ( b = 0; b < TOWER_NB_MISSILE_MAX; b++ ){
                avance_missile(&TOWER[a]->missile[b]);
                affiche_missile (pRenderer, &TOWER[a]->missile[b], &ANIM_MISSILE);
            }
            anime_tower     (TOWER[a]);
            affiche_tower (pRenderer, TOWER[a]);
        }

        // Affichage des explosions
        anime_sprite(EXPLOSION);
        affiche_sprite (pRenderer, EXPLOSION);

        // Affichage de la tourelle de depart, sous la souris
        if (my_game.flag_mode_place_tower) {
            // affichage d'un fond vert ou rouge celon terrain
            TOWER_MOUSE->visible = 180;
            if ( my_game.flag_tower_position_ok )  {
                    TOWER_MOUSE->img_current = 1;
            } else {
                    TOWER_MOUSE->img_current = 0;
            }

            affiche_tower (pRenderer, TOWER_MOUSE);

            TOWER_MOUSE->visible = 254;
            TOWER_MOUSE->img_current = 2;
            affiche_tower (pRenderer, TOWER_MOUSE);
        }

        // Afficahge des boutons
        if (!my_game.flag_affiche_level_titre) {    affiche_sprite (pRenderer, BUTTON_TIR);     }

        if (!my_game.flag_affiche_level_titre && my_game.current_nb_tower < TOWER_MAX) {
                                            affiche_sprite (pRenderer, BUTTON_TOWER);   }

        // Affichage du texte
        if (my_game.flag_affiche_level_titre) {     affiche_titre(pRenderer, &my_level);        }

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
    SDL_Log("Fred DEBUG - FIN\n");
    // Nettoyage
    for (a = 0; a < my_game.current_nb_enemy; a++) {
        destroy_sprite(&ENEMY[a]);
    }
    for (a = 0; a <  my_game.current_nb_tower; a++) {
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

    close();

    return 0;
}
