#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED


#define DEBUG           1
#define DEBUG_MAP       1       // permet de voir les chemins en console
#define DEBUG_MAP2      0       // positionne des croix rouge sur les obstacles
#define DEBUG_ALL_MAP   1       // permet d'accèder à toutes les map

#define NOIR    al_map_rgb(0,0,0)
#define ROUGE   al_map_rgb(255,0,0)
#define VERT    0x00, 0xFF, 0x00
#define BLEU    0x00, 0x00, 0xFF
#define COLOR_ALEA al_map_rgb(rand()%256,rand()%256,rand()%256)

#define false   0
#define true    1
#define bool    short int

// CONFIG
#define DATAFILE            "data160227_2.bin"
#define APP_TITRE           "Battle BOATS - By Fred & Mathis"
#define COULEUR_FENETRE     NOIR
#define START_IMG           "images/start.png"

#define GAME_FPS              30       // a repasser à 30

/**
    Samsung Galaxy S5   :       1920 x 1080     16:9    ratio: 1.77         ===Jeu==>   /2      :   960 x 540   ==Tile==>   30 x 16.8
    Samsung Galaxy Tab3 :       1280 x 800      16:10   ratio: 1.60                     /1.33   :   960 x 600               30 x 18.75

**/


#define MAP_TAILLE_X_177      960
#define MAP_TAILLE_Y_177      540
#define MAP_TAILLE_X_160      960
#define MAP_TAILLE_Y_160      600

#define MAP_NB_TILE_X         30
#define MAP_NB_TILE_Y         19

#define TILE_TAILLE_X         32
#define TILE_TAILLE_Y         32
#define TILE_FILE           "images/32x32_map_tile_v3.1.png"
#define TILE_FILE_NB_COLONNE  23
#define LEVEL_NB_TOTAL            21
#define WAVE_ENEMY_MAX_BY_WAVE  100
#define WAVE_NB                  10
#define TOWER_MAX                 3
#define TOWER_NB_MISSILE_MAX      1          // par tourelle
#define MISSILE_SPEED            15

#define POLICE_LEVEL_TITRE      "fonts/Alex_Bold.ttf"
#define POLICE_LEVEL_TITRE_SIZE 150
#define POLICE_LEVEL_BUTTON_SIZE 50

#define POLICE_SCORE            "fonts/DS-DIGIB.TTF"
#define POLICE_SCORE_SIZE       30

#define NB_ANIM_EXPLOSION       5

#define MENU_IMG_BACKGROUND     "images/menu_background.png"    //images de l'arrière plan
#define MENU_IMG_START          "images/menu_start.png"         //images des boutons
#define MENU_IMG_EXIT           "images/menu_exit.png"
#define MENU_IMG_RESTART        "images/menu_restart.png"
#define MENU_IMG_RESUME         "images/menu_resume.png"
#define MENU_IMG_START_P        "images/menu_start_p.png"       //images des boutons pressés
#define MENU_IMG_EXIT_P         "images/menu_exit_p.png"
#define MENU_IMG_RESTART_P      "images/menu_restart_p.png"
#define MENU_IMG_RESUME_P       "images/menu_resume_p.png"
#define MENU_IMG_LEVEL_TITLE    "images/level.png"
#define MENU_IMG_BUTTON1_LEVEL   "images/menu_button1_level.png"
#define MENU_IMG_BUTTON2_LEVEL   "images/menu_button2_level.png"
#define MENU_IMG_BUTTON3_LEVEL   "images/menu_button3_level.png"

#define SCORE_DESTROY_TOWER     50      // point PERDU quand on detruit une autre tourelle
#define SCORE_DESTROY_ENEMY     11      // point GAGNEE quand on tue un ennemi
#define SCORE_TIR               1       // point PERDU pour chaque TIR
#define SCORE_HEART_POINT       10


enum { UP, RIGHT, DOWN, LEFT };


#endif // CONFIG_H_INCLUDED
