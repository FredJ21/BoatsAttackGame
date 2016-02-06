#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "config.h"
#include "main.h"
#include "level.h"
#include "anim.h"
#include "Algo_A_star.h"
#include "score.h"
#include "tower.h"
#include "Algo_Collision.h"
#include "type_game.h"
#include "type_system.h"
#include "menu.h"
#include "type_sound.h"


int main( int argc, char* args[] )
{
    if (DEBUG) {SDL_Log("Fred DEBUG - Go ...\n"); }

    /******************************************************************************************************************
                                                VARIABLES
    *******************************************************************************************************************/
    t_level     my_level    = {};
    t_score     my_score    = {};
    t_game      my_game     = {};
    t_system    my_system   = {};
    t_menu      my_menu     = {};
    t_sound     my_sound    = {};

    long t_Avant_Traitement;        // permet de gérer les fps
    long t_Apres_Traitement;
    int t_total_Traitement;
    int  game_sleep;

    unsigned int CounterSecond = 0;         // traitement toute les seconds
    int CounterBeforeChgLevel = 0;          // pause avant le changement de level
    int CounterTimeLevel = 0;               // second depuis le demarrage du level
    int TimerSoundGameOver = 0;             //

    int a = 0, b = 0, w = 0;

    srand(time(NULL));

    SDL_RWops* file                 = NULL;

    SDL_Window *pWindow             = NULL;
    SDL_Renderer *pRenderer         = NULL;
    SDL_Surface *pSurface           = NULL;
    SDL_Texture *pTexture           = NULL;
    TTF_Font *police_level_titre    = NULL;
    SDL_Surface *pSurface_TUILE     = NULL;

    SDL_Event event;


    /******************************************************************************************************************
                                                INIT SDL 2
    *******************************************************************************************************************/
    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 && DEBUG ) {  SDL_Log( "SDL_Init ERREUR ! SDL_GetError: %s\n", SDL_GetError() ); return -1; }

    my_system.Platform = SDL_GetPlatform();
    if (DEBUG) {SDL_Log("Fred DEBUG - Platform: %s\n", my_system.Platform);}


    // Création de la fenêtre
#if __WIN32__
    pWindow = SDL_CreateWindow( APP_TITRE , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAP_TAILLE_X_177, MAP_TAILLE_Y_177, SDL_WINDOW_SHOWN );
//    pWindow = SDL_CreateWindow( APP_TITRE , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP );
#else
    pWindow = SDL_CreateWindow( APP_TITRE , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP );
#endif
    if(!pWindow && DEBUG ) { SDL_Log( "SDL_Window ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    SDL_GetWindowSize(pWindow, &my_system.window_size_w, &my_system.window_size_h);
    my_system.window_size_ratio = (float)my_system.window_size_w/(float)my_system.window_size_h;

    if ( my_system.window_size_ratio > 1.7 && my_system.window_size_ratio < 1.8 ) {
            my_system.window_size_ratio = 1.7;
            my_system.map_taille_x  = MAP_TAILLE_X_177;
            my_system.map_taille_y  = MAP_TAILLE_Y_177;
    } else {
            my_system.map_taille_x  = MAP_TAILLE_X_160;
            my_system.map_taille_y  = MAP_TAILLE_Y_160;
    }
    if (DEBUG) {SDL_Log("Fred DEBUG - Window Size: %d x %d - ratio: %f\n", my_system.window_size_w, my_system.window_size_h, my_system.window_size_ratio);}

    // Création du Renderer
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!pRenderer && DEBUG) { SDL_Log( "SDL_Renderer ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    // permet d'obtenir les redimensionnements plus doux.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(pRenderer, my_system.map_taille_x, my_system.map_taille_y);
    if (DEBUG) {SDL_Log("Fred DEBUG - Window Logical Size: %d x %d\n", my_system.map_taille_x, my_system.map_taille_y);}

    /******************************************************************************************************************
                                                INIT SDL 2  -  Affichage d'une image de chargement ...
    *******************************************************************************************************************/
    // Chargement de l'image
    //pSurface = SDL_LoadBMP (START_IMG);
    pSurface = SDL_LoadBMP (START_IMG);
    if(!pSurface && DEBUG) {  SDL_Log( "SDL_Surface ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    // Création de la texture (texture = surface dans le GPU)
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    if(!pTexture && DEBUG) { SDL_Log( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}


    SDL_RenderCopy (pRenderer, pTexture, NULL, NULL);
    SDL_RenderPresent (pRenderer);

    SDL_Delay( 100 );

    /******************************************************************************************************************
                                                INIT SDL 2 TTF
    *******************************************************************************************************************/
    // Initialize SDL TTF
    if( TTF_Init() != 0 && DEBUG) {  SDL_Log( "TTF_Init ERREUR ! SDL_GetError: %s\n", SDL_GetError() ); return -1; }

    // pour le titre de chaque level
    police_level_titre = TTF_OpenFont(POLICE_LEVEL_TITRE, POLICE_LEVEL_TITRE_SIZE);
    if(!police_level_titre&& DEBUG ) {  SDL_Log( "TTF_OpenFont ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    if (DEBUG) {SDL_Log("Fred DEBUG - INIT SDL OK\n");}

    /******************************************************************************************************************
                                                INIT SDL 2 MIXER (Audio)
    *******************************************************************************************************************/

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) != 0 )
    {        SDL_Log("Fred DEBUG - SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() ); return -1;}

    /******************************************************************************************************************
                                                INIT MENU
    *******************************************************************************************************************/
    if (DEBUG) {SDL_Log("Fred DEBUG - INIT MENU\n");}
    init_menu(&my_menu, pRenderer);


    /******************************************************************************************************************
                                                INIT GAME
    *******************************************************************************************************************/
    if (DEBUG) {SDL_Log("Fred DEBUG - INIT GAME\n");}

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

    my_game.current_level               = 0;
    my_game.current_nb_enemy            = 0;
    my_game.current_enemy_alive         = 0;
    my_game.current_nb_tower            = 0;                // nombre de tourelle
    my_game.current_tower               = TOWER_MAX;        // id tourelle selectionnée, TOWER_MAX signifi qu'aucune n'est seletionnée
    my_game.current_nb_missile          = 0;
    my_game.current_nb_explosion        = 0;

    my_game.flag_game_over              = false;

    my_game.score                       = 0;
    my_game.heart_point                 = SCORE_HEART_POINT;

    init_level_gameover_txt (pRenderer, &my_level, police_level_titre, &my_system);

    /******************************************************************************************************************
                                                READ DATA FILE
    *******************************************************************************************************************/

    file = SDL_RWFromFile( DATAFILE, "r+b" );
    // si le fichier n'existe pas
    if ( file == NULL ) {
            if (DEBUG) { SDL_Log("Fred DEBUG - file not found -> create"); }

            // creation du fichier data
            file = SDL_RWFromFile( DATAFILE, "w+b" );
            if ( file == NULL ) {
                    if (DEBUG) { SDL_Log("Fred DEBUG - create file failed"); return -1; }

            } else {
                    my_game.last_level                  = 0;
                    SDL_RWwrite( file, &my_game.max_level_win, sizeof(int), 1 );
                    my_game.last_level  =  my_game.max_level_win;
            }
    // si le fichier existe --> lecture du fichier
    } else {
            if (DEBUG) {SDL_Log("Fred DEBUG - Read File Data"); }

            SDL_RWread( file, &my_game.last_level, sizeof(int), 1 );
    }

    SDL_RWclose( file );

    if (DEBUG) {SDL_Log("Fred DEBUG - last_level : %d", my_game.last_level); }


    /******************************************************************************************************************
                                                INIT DES IMAGES / ANNIMATIONS
    *******************************************************************************************************************/
    if (DEBUG) {SDL_Log("Fred DEBUG - INIT IMAGES/ANIM\n");}

    /** FICHIER TUILE (chargement) **/
    pSurface_TUILE = SDL_LoadBMP (TILE_FILE);
    if(!pSurface_TUILE & DEBUG) { SDL_Log( "SDL_Surface_TUILE ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    /** ANIMATION des ennemis  **/
    t_animation ANIM[4];

    strcpy(ANIM[0].file,   "images/PetitBateau1.bmp");
        ANIM[0].tx              = 48;   ANIM[0].ty              = 48;
        ANIM[0].nb_colonne      = 3;    ANIM[0].nb_image        = 12;   ANIM[0].nb_img_by_dir   = 3;    ANIM[0].nb_tour         = 5; ANIM[0].vitesse         = 2;
        init_animation( &ANIM[0], pRenderer);

    strcpy(ANIM[1].file,   "images/PetitBateau2.bmp");
        ANIM[1].tx              = 48;   ANIM[1].ty              = 48;
        ANIM[1].nb_colonne      = 3;    ANIM[1].nb_image        = 12;   ANIM[1].nb_img_by_dir   = 3;    ANIM[1].nb_tour         = 5;    ANIM[1].vitesse         = 2;
        init_animation( &ANIM[1], pRenderer);

    strcpy(ANIM[2].file,   "images/Fred-Bateau_soleil_61x55.png");
        ANIM[2].tx              = 61;   ANIM[2].ty              = 55;
        ANIM[2].nb_colonne      = 9;    ANIM[2].nb_image        = 36;   ANIM[2].nb_img_by_dir   = 3;    ANIM[2].nb_tour         = 5;    ANIM[2].vitesse         = 2;
        init_animation( &ANIM[2], pRenderer);

    strcpy(ANIM[3].file,   "images/Fred-Bateau_Pirate_61x55.png");
        ANIM[3].tx              = 61;   ANIM[3].ty              = 55;
        ANIM[3].nb_colonne      = 4;    ANIM[3].nb_image        = 16;   ANIM[3].nb_img_by_dir   = 3;    ANIM[3].nb_tour         = 5;    ANIM[3].vitesse         = 2;
        init_animation( &ANIM[3], pRenderer);


    t_animation DRAPEAU = { "images/Flag.bmp", 31, 40, 11, 11, 11, NULL, 3, 1 };
        init_animation( &DRAPEAU, pRenderer);

    t_animation ANIM_TOWER = { "images/Tower1.bmp", 48, 48, 3, 12, 0, NULL, 0, 1 };
        init_animation( &ANIM_TOWER, pRenderer);

    t_animation ANIM_MISSILE = { "images/Missile.bmp", 10, 10, 1, 1, 0, NULL, 0, 1 };
        init_animation( &ANIM_MISSILE, pRenderer);

    if (DEBUG) {SDL_Log("Fred DEBUG - INIT EXPLOSION\n");}
//    t_animation ANIM_EXPLOSION = { "images/explosion_1.bmp", 44, 46, 40, 40, 40, NULL, 1, 1 };
    t_animation ANIM_EXPLOSION[5] = {};
    strcpy( ANIM_EXPLOSION[0].file, "images/explosion_1.png");  ANIM_EXPLOSION[0].tx = 88;  ANIM_EXPLOSION[0].ty = 93;
        ANIM_EXPLOSION[0].nb_colonne = 40;  ANIM_EXPLOSION[0].nb_image = 40;  ANIM_EXPLOSION[0].nb_img_by_dir = 40; ANIM_EXPLOSION[0].nb_tour = 1;  ANIM_EXPLOSION[0].vitesse = 1;

    strcpy( ANIM_EXPLOSION[1].file, "images/explosion_2.png");  ANIM_EXPLOSION[1].tx = 75;  ANIM_EXPLOSION[1].ty = 109;
        ANIM_EXPLOSION[1].nb_colonne = 30;  ANIM_EXPLOSION[1].nb_image = 30;  ANIM_EXPLOSION[1].nb_img_by_dir = 30; ANIM_EXPLOSION[1].nb_tour = 1;  ANIM_EXPLOSION[1].vitesse = 1;

    strcpy( ANIM_EXPLOSION[2].file, "images/explosion_3.png");  ANIM_EXPLOSION[2].tx = 103;  ANIM_EXPLOSION[2].ty = 97;
        ANIM_EXPLOSION[2].nb_colonne = 35;  ANIM_EXPLOSION[2].nb_image = 35;  ANIM_EXPLOSION[2].nb_img_by_dir = 35; ANIM_EXPLOSION[2].nb_tour = 1;  ANIM_EXPLOSION[2].vitesse = 1;

    strcpy( ANIM_EXPLOSION[3].file, "images/explosion_4.png");  ANIM_EXPLOSION[3].tx = 113;  ANIM_EXPLOSION[3].ty = 105;
        ANIM_EXPLOSION[3].nb_colonne = 35;  ANIM_EXPLOSION[3].nb_image = 35;  ANIM_EXPLOSION[3].nb_img_by_dir = 35; ANIM_EXPLOSION[3].nb_tour = 1;  ANIM_EXPLOSION[3].vitesse = 1;

    strcpy( ANIM_EXPLOSION[4].file, "images/explosion_5.png");  ANIM_EXPLOSION[4].tx = 94;  ANIM_EXPLOSION[4].ty = 91;
        ANIM_EXPLOSION[4].nb_colonne = 35;  ANIM_EXPLOSION[4].nb_image = 35;  ANIM_EXPLOSION[4].nb_img_by_dir = 35; ANIM_EXPLOSION[4].nb_tour = 1;  ANIM_EXPLOSION[4].vitesse = 1;

    init_animation( &ANIM_EXPLOSION[0], pRenderer);
    init_animation( &ANIM_EXPLOSION[1], pRenderer);
    init_animation( &ANIM_EXPLOSION[2], pRenderer);
    init_animation( &ANIM_EXPLOSION[3], pRenderer);
    init_animation( &ANIM_EXPLOSION[4], pRenderer);

    if (DEBUG) {SDL_Log("Fred DEBUG - INIT BUTTON\n");}
    t_animation IMG_BUTTON_TIR = { "images/Tir_100x80_2.bmp", 100, 80, 1, 1, 1, NULL, 1, 1 };
        init_animation( &IMG_BUTTON_TIR, pRenderer);

    t_animation IMG_BUTTON_TOWER = { "images/Tower_Botton_100x80_3.bmp", 100, 80, 1, 1, 1, NULL, 1, 1 };
        init_animation( &IMG_BUTTON_TOWER, pRenderer);


    t_animation HEART = { "images/coeur_32x32.png", 32, 32, 1, 1, 1, NULL, 1, 1 };
        init_animation( &HEART, pRenderer);



    /******************************************************************************************************************
                                                INIT DES SPRITES  / Objets afficher
    *******************************************************************************************************************/
    if (DEBUG) {SDL_Log("Fred DEBUG - INIT STRITES\n");}

     /* SPRITE ARRIVE */
    my_game.sp_ARRIVE = init_sprite (&DRAPEAU);

    /* SPRITE TOWER */
    my_game.sp_TOWER_MOUSE = create_Tower (0,0,&ANIM_TOWER);  // tourelle d'aide au positionnement, sous le pointeur souris

     /* SPRITE BUTTON */
    my_game.sp_BUTTON_TIR = init_sprite (&IMG_BUTTON_TIR);
    my_game.sp_BUTTON_TIR->x = my_system.map_taille_x - my_game.sp_BUTTON_TIR->anim->tx/2 - 15;
    my_game.sp_BUTTON_TIR->y = my_system.map_taille_y - my_game.sp_BUTTON_TIR->anim->ty/2 - 15 ;

    my_game.sp_BUTTON_TOWER = init_sprite (&IMG_BUTTON_TOWER);
    my_game.sp_BUTTON_TOWER->x = my_game.sp_BUTTON_TOWER->anim->tx/2 + 15;
    my_game.sp_BUTTON_TOWER->y = my_system.map_taille_y - my_game.sp_BUTTON_TOWER->anim->ty/2 - 15 ;

    my_game.sp_HEART = init_sprite(&HEART);
    my_game.sp_HEART->visible = 255;
    my_game.sp_HEART->is_actif = true;
    my_game.sp_HEART->y = 22;


    /******************************************************************************************************************
                                                INIT POLICE DE CARACTERE
    *******************************************************************************************************************/
    // charge la police pour l'affichage du score
    my_score.police = TTF_OpenFont(POLICE_SCORE, POLICE_SCORE_SIZE);
    if(!my_score.police && DEBUG) { SDL_Log( "TTF_OpenFont ERREUR! SDL_GetError: %s\n", SDL_GetError() ); return -1;}

    /******************************************************************************************************************
                                                LOAD SOUND
    *******************************************************************************************************************/

	//Load music
	my_sound.Music      = Mix_LoadMUS( "sound/music.wav" );
	if( my_sound.Music  == NULL && DEBUG) {  		SDL_Log( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

	//Load sound effects
	my_sound.Start      = Mix_LoadWAV( "sound/start.wav" );
	if( my_sound.Start == NULL && DEBUG)	{		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

	my_sound.Click      = Mix_LoadWAV( "sound/click.wav" );
	if( my_sound.Click  == NULL && DEBUG)	{		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

	my_sound.Cancel     = Mix_LoadWAV( "sound/cancel.wav" );
	if( my_sound.Cancel == NULL && DEBUG)	{		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

	my_sound.StartGame  = Mix_LoadWAV( "sound/start_game.wav" );
	if( my_sound.StartGame == NULL && DEBUG)	{		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

	my_sound.Exit       = Mix_LoadWAV( "sound/exit.wav" );
	if( my_sound.Exit   == NULL && DEBUG)	{		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

	my_sound.Explosion  = Mix_LoadWAV( "sound/explosion.wav" );
	if( my_sound.Explosion == NULL && DEBUG)	{		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

	my_sound.Tir        = Mix_LoadWAV( "sound/tir.wav" );
	if( my_sound.Tir    == NULL && DEBUG)	{		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

	my_sound.GameOver   = Mix_LoadWAV( "sound/game_over.wav" );
	if( my_sound.GameOver == NULL && DEBUG)	{		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );		return -1;	}

    /******************************************************************************************************************
                                                BOUCLE PRINCIPALE
    *******************************************************************************************************************/
    if (DEBUG) {SDL_Log("Fred DEBUG - START MAIN LOOP\n");}

    Mix_PlayChannel( -1, my_sound.Start, 0 );

    my_game.flag_game_started = false;

    while (!my_menu.exit) {

        if (DEBUG) {SDL_Log("Fred DEBUG - Affiche menu\n");}
        affiche_menu(&my_menu, pRenderer, my_game.flag_game_started, &my_system, &my_sound);

        if (my_menu.exit)       { my_game.flag_fin = true; }
        if (my_menu.resume)     { my_menu.resume = false;
                                  my_game.flag_fin = false;}

        if (my_menu.start || my_menu.restart ) {

            my_menu.start = false;
            my_menu.restart = false;
            my_game.current_level = 0;              // TODO : a supprimer
            my_game.flag_change_level = true;
            my_game.flag_fin = false;

            if (DEBUG) {SDL_Log("Fred DEBUG - Affiche menu level - last_level:%d\n", my_game.last_level);}
            affiche_menu_level(&my_menu, &my_system, pRenderer, &my_game.current_level, &my_game.last_level, &my_game.flag_fin, &my_sound);
        }

        if (DEBUG) {SDL_Log("Fred DEBUG - current_level = %d\n", my_game.current_level);}


                while (!my_game.flag_fin) {

                    t_Avant_Traitement = SDL_GetTicks();
                    my_game.flag_game_started = true;


                    /******************************************************************************************************************
                                                                GESTION DES EVENEMENTS
                    *******************************************************************************************************************/
                    while (SDL_PollEvent(&event)) {

                        switch (event.type){

                            case SDL_QUIT:
                                my_game.flag_fin = true;
                                break;
                            case SDL_USEREVENT:
                                if (DEBUG) {SDL_Log("Fred DEBUG - SDL_USEREVENT\n");}
                                break;
                            case SDL_WINDOWEVENT:
                                if (DEBUG) {SDL_Log("Fred DEBUG - SDL_WINDOWEVENT\n");}
                                break;
                            case SDL_APP_TERMINATING:
                                if (DEBUG) {SDL_Log("Fred DEBUG - SDL_APP_TERMINATING\n");}
                                break;
                            case SDL_MULTIGESTURE:
                                if (DEBUG) {SDL_Log("Fred DEBUG - SDL_MULTIGESTURE\n");}
                                break;

                            /***************************************************************************  CLAVIER **/
                            case SDL_KEYDOWN:

                                if (DEBUG) {SDL_Log("Fred DEBUG - SDL_KEYDOWN\n");}
                                switch( event.key.keysym.sym ){
                                    case SDLK_ESCAPE:
                                        my_game.flag_fin = true;
                                        break;
                                    case SDLK_AC_BACK:
                                        if (DEBUG) {SDL_Log("Fred DEBUG - SDLK_AC_BACK\n");}
                                        my_game.flag_fin = true;
                                        break;
                                    case SDLK_SPACE:
                                        for (a=0; a < my_game.current_nb_tower; a++) {
                                            if (DEBUG) {SDL_Log("Test: -%d-%d-\n", a, my_game.sp_TOWER[a]->x);}
                                        }
                                        break;
                                    default:
                                        break;
                                }
                                break;

                            /***************************************************************************   SOURIS  **/
            #if __WIN32__
                            case SDL_MOUSEBUTTONDOWN :
                                SDL_GetMouseState( &my_game.current_mouse_x, &my_game.current_mouse_y );
                                //if (DEBUG) {SDL_Log("Fred DEBUG - MOUSEBUTTONDOWN : %d x %d\n", current_mouse_x, current_mouse_y);}
                                my_game.flag_event_DOWN = true;
                                break;

                            case SDL_MOUSEMOTION :
                                SDL_GetMouseState( &my_game.current_mouse_x, &my_game.current_mouse_y );
                                //if (DEBUG) {SDL_Log("Fred DEBUG - MOUSEMOTION : %d x %d\n", current_mouse_x, current_mouse_y);}
                                my_game.flag_event_MOVE = true;
                                break;

                            case SDL_MOUSEBUTTONUP :
                                SDL_GetMouseState( &my_game.current_mouse_x, &my_game.current_mouse_y );
                                //if (DEBUG) {SDL_Log("Fred DEBUG - MOUSEBUTTONUP : %d x %d\n", current_mouse_x, current_mouse_y);}
                                my_game.flag_event_UP = true;
                                break;
            #endif
                            /***************************************************************************   FINGER  **/

                            case SDL_FINGERDOWN:
                                my_game.current_mouse_x = (int)(event.tfinger.x * my_system.map_taille_x);
                                my_game.current_mouse_y = (int)(event.tfinger.y * my_system.map_taille_y);
                                //if (DEBUG) {SDL_Log("Fred DEBUG - FINGERDOWN : %d x %d\n", current_mouse_x, current_mouse_y);}
                                my_game.flag_event_DOWN = true;
                                break;

                            case SDL_FINGERMOTION :
                                my_game.current_mouse_x = (int)(event.tfinger.x * my_system.map_taille_x);
                                my_game.current_mouse_y = (int)(event.tfinger.y * my_system.map_taille_y);
                                //if (DEBUG) {SDL_Log("Fred DEBUG - FINGERMOTION : %d x %d\n", current_mouse_x, current_mouse_y);}
                                my_game.flag_event_MOVE = true;
                                break;

                            case SDL_FINGERUP :
                                my_game.current_mouse_x = (int)(event.tfinger.x * my_system.map_taille_x);
                                my_game.current_mouse_y = (int)(event.tfinger.y * my_system.map_taille_y);
                                //if (DEBUG) {SDL_Log("Fred DEBUG - FINGERUP : %d x %d\n", current_mouse_x, current_mouse_y);}
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
                                if (my_game.current_mouse_x > ZONE_BUTTON_TIR_X && my_game.current_mouse_y > ZONE_BUTTON_TIR_Y && !my_game.flag_game_over) { /** CLICK BUTTON TIR **/
                                    if (DEBUG) {SDL_Log("Fred DEBUG - BUTTON TIR\n");}

                                    for (a = 0; a < my_game.current_nb_tower; a++){
                                        tir_tower(my_game.sp_TOWER[a], my_game.current_nb_tower, &my_game.score, &my_sound);                           /** ==>  TIR    **/
                                    }

                                }
                                if (my_game.current_mouse_x < ZONE_BUTTON_TOWER_X && my_game.current_mouse_y > ZONE_BUTTON_TOWER_Y && !my_game.flag_game_over) {/** CLICK BUTTON TOWER **/
                                    if (DEBUG) {SDL_Log("Fred DEBUG - BUTTON TOWER\n");}

                                    if (my_game.current_nb_tower < TOWER_MAX) {

                                        my_game.flag_mode_place_tower = true;                                                                   /** ==> Passage en mode "place new tower" **/
                                        my_game.flag_mode_game = false;
                                        my_game.sp_TOWER_MOUSE->x = my_system.map_taille_x / 2;
                                        my_game.sp_TOWER_MOUSE->y = my_system.map_taille_y / 2;
                                    }
                                }
                            }
                            else if (my_game.flag_mode_place_tower) {
                                if ( (my_game.current_mouse_x < ZONE_BUTTON_TOWER_X && my_game.current_mouse_y > ZONE_BUTTON_TOWER_Y)
                                    || (my_game.current_mouse_x > ZONE_BUTTON_TIR_X && my_game.current_mouse_y > ZONE_BUTTON_TIR_Y)) {       /** CLICK BUTTON TIR ou TOWER en mode "place TOWER" **/
                                    if (DEBUG) {SDL_Log("Fred DEBUG - BUTTON TOWER\n");}                                                                     /** ==> Passage en mode "place new tower" **/
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
                                my_game.sp_TOWER_MOUSE->x = my_game.current_mouse_x;
                                my_game.sp_TOWER_MOUSE->y = my_game.current_mouse_y;
                               // verifie si la position est valide afin de changer la couleur de souris
                                if ( is_tower_new_valid_position(my_game.sp_TOWER_MOUSE, &my_level, my_game.sp_TOWER, my_game.current_nb_tower) ) {
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
                                    if (DEBUG) {SDL_Log("Fred DEBUG -  PLACE TOWER\n");}

                                    my_game.sp_TOWER[my_game.current_nb_tower] = create_Tower(my_game.current_mouse_x, my_game.current_mouse_y, &ANIM_TOWER);
                                    my_game.current_nb_tower++;

                                    my_game.flag_mode_place_tower = false;
                                    my_game.flag_tower_position_ok = false;
                                    my_game.flag_mode_game = true;
                                }

                                // une tourelle est selectionnée , on indique la cible
                                else if (my_game.flag_mode_tower_selected){
                                    if (DEBUG) {SDL_Log("Fred DEBUG - TOWER NEW CIBLE\n");}

                                    my_game.sp_TOWER[my_game.current_tower]->cible_x = my_game.current_mouse_x;
                                    my_game.sp_TOWER[my_game.current_tower]->cible_y = my_game.current_mouse_y;

                                    calcul_angle_tower(my_game.sp_TOWER[my_game.current_tower]);

                                    my_game.sp_TOWER[my_game.current_tower]->selected = false;
                                    my_game.flag_mode_tower_selected = false;
                                    my_game.flag_mode_game = true;
                                }

                                // selection d'une tourelle
                                else if (my_game.flag_mode_game) {
                                    my_game.current_tower = is_tower_position(my_game.current_mouse_x, my_game.current_mouse_y, my_game.sp_TOWER, my_game.current_nb_tower);
                                    if (my_game.current_tower < TOWER_MAX) {   // TOWER_MAX signifi qu'aucune n'est seletionnée
                                        if (DEBUG) {SDL_Log("Fred DEBUG - SELECT TOWER\n");}
                                        my_game.sp_TOWER[my_game.current_tower]->selected = true;
                                        my_game.flag_mode_tower_selected = true;
                                    }
                                }


                        }

                    }

                    /******************************************************************************************************************
                                                                CHANGEMENT  DE NIVEAU
                    *******************************************************************************************************************/
                    if (my_game.flag_change_level) {

                            Mix_PlayChannel( -1, my_sound.StartGame, 0 );

                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level\n");}

                            /** NETTOYAGE **/
                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level Nettoyage 1\n");}
                            for (a = 0; a < my_game.current_nb_enemy ; a++) {
                                if (DEBUG) {SDL_Log("Fred DEBUG - clear ENEMY %d\n", a);}
                                destroy_sprite(&my_game.sp_ENEMY[a]);
                            }
                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level Nettoyage 2\n");}
                            for (a = 0; a <  my_game.current_nb_tower; a++) {
                                if (DEBUG) {SDL_Log("Fred DEBUG - clear TOWER %d\n", a);}
                                destroy_tower(&my_game.sp_TOWER[a]);
                            }
                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level Nettoyage 3\n");}
                            for (a = 0; a <  my_game.current_nb_explosion; a++) {
                                if (DEBUG) {SDL_Log("Fred DEBUG - clear explosions %d\n", a);}
                                destroy_sprite(&my_game.sp_EXPLOSION[a]);
                            }

                            clear_level (&my_level);


                            // RAZ des flags
                            my_game.flag_change_level           = false;
                            my_game.flag_affiche_level_titre    = true;
                            my_game.flag_mode_game              = true;
                            my_game.flag_mode_place_tower       = false;
                            my_game.flag_mode_tower_selected    = false;
                            my_game.flag_tower_position_ok      = false;
                            my_game.flag_game_over              = false;

                            // RAZ des variables currentes
                            my_game.current_nb_enemy            = 0;
                            my_game.current_nb_tower            = 0;
                            my_game.current_nb_explosion        = 0;
                            my_game.current_tower               = TOWER_MAX;   // id tourelle selectionnée, TOWER_MAX signifi qu'aucune n'est seletionnée

                            my_score.level                      = my_game.current_level + 1;

                            my_game.heart_point                 = SCORE_HEART_POINT;


                            /** LEVEL **/
                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level Init level\n");}
                            init_level(&my_level, my_game.current_level, pSurface_TUILE, pRenderer, &my_system);
                            /** DEBUG OBSTACLES **/
                            if(DEBUG_MAP){init_texture_obstacle(pRenderer, &my_level, &my_system);}

                            if (DEBUG) { SDL_Log("Fred DEBUG - Change_level Init level 2\n"); }
                            init_level_titre        (pRenderer, &my_level, police_level_titre, &my_system);

                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level Init level 3\n");}
                            place_sprite(my_game.sp_ARRIVE, my_level.cibleX, my_level.cibleY);

                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level Init level 4\n");}
                            init_level_chemins(&my_level, &my_system);
                            if (DEBUG_MAP) {affiche_map_console ( &my_level);}


                            /** CREATE ENEMY **/
                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level Create Enemy\n");}
                            for ( w = 0; w < WAVE_NB; w++ ) {
                                b = 0;
                                // creation en haut
                                for (a = 0; a < my_level.wave[w].nb_up; a++ ) {
                                    my_game.sp_ENEMY[my_game.current_nb_enemy++] = create_Enemy( UP ,    my_level.StartPos_UP_s, my_level.StartPos_UP_e,       &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in, &my_system);
                                    b++;
                                }
                                // creation a droite
                                for (a = 0; a < my_level.wave[w].nb_right; a++ ) {
                                    my_game.sp_ENEMY[my_game.current_nb_enemy++] = create_Enemy( RIGHT , my_level.StartPos_RIGHT_s, my_level.StartPos_RIGHT_e, &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in, &my_system);
                                    b++;
                                }
                                // creation en bas
                                for (a = 0; a < my_level.wave[w].nb_down; a++ ) {
                                    my_game.sp_ENEMY[my_game.current_nb_enemy++] = create_Enemy( DOWN ,  my_level.StartPos_DOWN_s, my_level.StartPos_DOWN_e,   &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in, &my_system);
                                    b++;
                                }
                                // creation a gauche
                                for (a = 0; a < my_level.wave[w].nb_left; a++ ) {
                                    my_game.sp_ENEMY[my_game.current_nb_enemy++] = create_Enemy( LEFT ,  my_level.StartPos_LEFT_s, my_level.StartPos_LEFT_e,   &ANIM[my_level.wave[w].type], 2*a + my_level.wave[w].start_in, &my_system);
                                    b++;
                                }
                            }

                            CounterTimeLevel = 0;
                            TimerSoundGameOver = 0;

                            if (DEBUG) {SDL_Log("Fred DEBUG - Change_level OK\n");}

                    }

                   /******************************************************************************************************************
                                                                TRAITEMENTS TOUTES LES SECONDES
                    *******************************************************************************************************************/
                    if (SDL_GetTicks() > CounterSecond + 1000) {

                        // compte le nombre d'ennemi en vie
                        my_game.current_enemy_alive = 0;

                        for (a = 0; a < my_game.current_nb_enemy; a++) {
                            if ( my_game.sp_ENEMY[a]->visible )  { my_game.current_enemy_alive++; }
                        }

                        // mise à jour du score
                        my_score.NbEnemy = my_game.current_enemy_alive;
                        init_score( pRenderer, &my_score, &my_system, my_game.score );


                        // decide du changement de level
                        if ( my_game.current_enemy_alive == 0 && !my_game.flag_game_over) {

                            CounterBeforeChgLevel++;
                            if ( CounterBeforeChgLevel > 5 ) {
                                CounterBeforeChgLevel = 0;


                                my_game.current_level++;
                                if (my_game.current_level >= LEVEL_NB_TOTAL ) {     my_game.current_level = 0;  }


                                if (my_game.current_level > my_game.last_level ){   my_game.last_level = my_game.current_level; }

                                my_game.flag_change_level = true;
                            }

                                // SAUVEGARDE du niveau
                                if (my_game.current_level > my_game.max_level_win) {

                                        my_game.max_level_win = my_game.current_level ;
                                        if (DEBUG) { SDL_Log("Fred DEBUG - save data max_level_win : %d", my_game.max_level_win); }

                                        file = SDL_RWFromFile( DATAFILE, "w+b" );
                                        if ( file == NULL ) {
                                                if (DEBUG) { SDL_Log("Fred DEBUG - save data failed"); return -1; }

                                        } else {
                                            SDL_RWwrite( file, &my_game.max_level_win, sizeof(int), 1 );
                                        }

                                        SDL_RWclose( file );
                                }
                        }

                        //Affichage du titre en debut de level
                        if (CounterTimeLevel < 2 ){
                                my_game.flag_affiche_level_titre = true;
                        }
                        else {
                                my_game.flag_affiche_level_titre =false;
                        }

                        // ********** GAME OVER ************
                        if (my_game.heart_point <= 0 ) {
                                my_game.flag_game_over = true;

                                TimerSoundGameOver++;
                                if (TimerSoundGameOver == 3) {    Mix_PlayChannel( -1, my_sound.GameOver, 0 ); }
                        }

                        CounterTimeLevel++;
                        CounterSecond = SDL_GetTicks();

                    }
                    /******************************************************************************************************************
                                                                COLLISION
                    *******************************************************************************************************************/

                    test_collision(&my_game, ANIM_EXPLOSION, &my_sound);

                    /******************************************************************************************************************
                                                                AFFICHAGE
                    *******************************************************************************************************************/
                    SDL_RenderClear     (pRenderer);
                    // Affichage de la map
                    SDL_RenderCopy      (pRenderer, my_level.pTexture_MAP, NULL, NULL);

                    // Affichage des obstacles (mode Debug)
                    if (DEBUG_MAP) {affiche_obstacle    (pRenderer, &my_level);}

                    // Affichage de l'arrivé
                    anime_sprite(my_game.sp_ARRIVE);
                    affiche_sprite (pRenderer, my_game.sp_ARRIVE);

                    // Affichage des ENEMY
                    for (a = 0; a < my_game.current_nb_enemy; a++) {
                        anime_sprite    (my_game.sp_ENEMY[a]);
                        avance_sprite   (my_game.sp_ENEMY[a], &my_level, &my_system, &my_game.heart_point);
                        affiche_sprite  (pRenderer, my_game.sp_ENEMY[a]);
                    }
                    // Affichage des tourelles
                    for (a = 0; a < my_game.current_nb_tower; a++){


                        for ( b = 0; b < TOWER_NB_MISSILE_MAX; b++ ){
                            avance_missile(&my_game.sp_TOWER[a]->missile[b], &my_system);
                            affiche_missile (pRenderer, &my_game.sp_TOWER[a]->missile[b], &ANIM_MISSILE);
                        }
                        anime_tower     (my_game.sp_TOWER[a]);
                        affiche_tower (pRenderer, my_game.sp_TOWER[a]);
                    }

                    // Affichage des explosions
                    for (a = 0; a < my_game.current_nb_explosion; a++) {
                        anime_sprite_once(my_game.sp_EXPLOSION[a]);
                        affiche_sprite (pRenderer, my_game.sp_EXPLOSION[a]);
                    }

                    // Affichage de la tourelle de depart, sous la souris
                    if (my_game.flag_mode_place_tower) {
                        // affichage d'un fond vert ou rouge celon terrain
                        my_game.sp_TOWER_MOUSE->visible = 180;
                        if ( my_game.flag_tower_position_ok )  {
                                my_game.sp_TOWER_MOUSE->img_current = 1;
                        } else {
                                my_game.sp_TOWER_MOUSE->img_current = 0;
                        }

                        affiche_tower (pRenderer, my_game.sp_TOWER_MOUSE);

                        my_game.sp_TOWER_MOUSE->visible = 254;
                        my_game.sp_TOWER_MOUSE->img_current = 2;
                        affiche_tower (pRenderer, my_game.sp_TOWER_MOUSE);
                    }

                    // Afficahge des boutons
                    if (!my_game.flag_game_over) {
                            if (!my_game.flag_affiche_level_titre) {    affiche_sprite (pRenderer, my_game.sp_BUTTON_TIR);     }

                            if (!my_game.flag_affiche_level_titre && my_game.current_nb_tower < TOWER_MAX) {
                                                        affiche_sprite (pRenderer, my_game.sp_BUTTON_TOWER);   }
                    }

                    // Affichage du texte
                    if (my_game.flag_affiche_level_titre) {     affiche_titre(pRenderer, &my_level);        }

                    if (my_game.flag_game_over) {               affiche_gameover(pRenderer, &my_level);     }


                    // Affichage du score
                    affiche_score( pRenderer, &my_score, &my_system);

                    // Affichage des vies restantes
                    for (a=0; a<my_game.heart_point; a++){
                        my_game.sp_HEART->x = 30 + (my_game.sp_HEART->anim->tx * a);
                        affiche_sprite (pRenderer, my_game.sp_HEART);
                    }


                    // Mise a jour de l'affichage
                    SDL_RenderPresent   (pRenderer);


                    /************************************************/
                    /**   Calcul du temps de traitement et pause   **/
                    /************************************************/
                    t_Apres_Traitement = (long)SDL_GetTicks();
                    t_total_Traitement = (int)(t_Apres_Traitement - t_Avant_Traitement);
                    game_sleep = (1000 / GAME_FPS) - t_total_Traitement;

                   //if (DEBUG) { SDL_Log("Fred DEBUG - total_Traitement: %d - FPS: %d - Sleep: %d\n", t_total_Traitement, 1000 / GAME_FPS, game_sleep);}

                    if ( game_sleep > 0 ) { SDL_Delay( game_sleep ); };
                }
    }
    /******************************************************************************************************************
                                                    FIN
    *******************************************************************************************************************/
    if (DEBUG) {SDL_Log("Fred DEBUG - FIN\n");}

    Mix_PlayChannel( -1, my_sound.Exit, 0 );
    SDL_Delay( 2000 );

    // Nettoyage
    for (a = 0; a < my_game.current_nb_enemy; a++) {
        destroy_sprite(&my_game.sp_ENEMY[a]);
    }
    for (a = 0; a <  my_game.current_nb_tower; a++) {
        destroy_tower(&my_game.sp_TOWER[a]);
    }
    for (a = 0; a <  my_game.current_nb_explosion; a++) {
        destroy_sprite(&my_game.sp_EXPLOSION[a]);
    }


    destroy_sprite(&my_game.sp_ARRIVE);
    destroy_tower(&my_game.sp_TOWER_MOUSE);
    destroy_sprite(&my_game.sp_BUTTON_TOWER);
    destroy_sprite(&my_game.sp_BUTTON_TIR);


    SDL_DestroyTexture(ANIM[0].texture);
    SDL_DestroyTexture(ANIM[1].texture);
    SDL_DestroyTexture(ANIM[2].texture);

    SDL_DestroyTexture(DRAPEAU.texture);
    SDL_DestroyTexture(ANIM_TOWER.texture);
    SDL_DestroyTexture(ANIM_MISSILE.texture);
    SDL_DestroyTexture(my_score.pTexture_Score);
    SDL_DestroyTexture(HEART.texture);

    clear_level (&my_level);
    clear_score (&my_score);

    SDL_DestroyTexture(pTexture);
    SDL_FreeSurface(pSurface);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow( pWindow );

    TTF_CloseFont(police_level_titre);

/*
  	//Free the sound effects
  	my_sound.Music = NULL;
	my_sound.Start = NULL;
	my_sound.Exit  = NULL;
	my_sound.Danger = NULL;
	my_sound.BeBack = NULL;
	my_sound.Tir = NULL;
    my_sound.BeBack = NULL;
*/

    Mix_CloseAudio();

    TTF_Quit();
	Mix_Quit();
	IMG_Quit();
    SDL_Quit();

    //close();

    return 0;
}
