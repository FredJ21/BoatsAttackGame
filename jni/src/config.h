#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

// les defines
#define NOIR    al_map_rgb(0,0,0)
#define ROUGE   al_map_rgb(255,0,0)
#define VERT    0x00, 0xFF, 0x00
#define BLEU    0x00, 0x00, 0xFF
#define COLOR_ALEA al_map_rgb(rand()%256,rand()%256,rand()%256)

#define false   0
#define true    1
#define bool    short int

// CONFIG
#define APP_TITRE           "Battle BOATS - By Fred & Mathis"
#define COULEUR_FENETRE     NOIR
#define START_IMG           "images/start.bmp"

#define GAME_FPS              30       // a repasser à 30

#define MAP_TAILLE_X         960
#define MAP_TAILLE_Y         540
#define MAP_NB_TILE_X         30
#define MAP_NB_TILE_Y         17



#define TILE_TAILLE_X         32
#define TILE_TAILLE_Y         32
#define TILE_FILE           "images/32x32_map_tile_v3.1.bmp"
#define TILE_FILE_NB_COLONNE  23
#define LEVEL_NB_TOTAL            4
#define WAVE_ENEMY_MAX_BY_WAVE  100
#define WAVE_NB                  10
#define TOWER_MAX                10
#define TOWER_NB_MISSILE_MAX      1          // par tourelle
#define MISSILE_SPEED            15

#define POLICE_LEVEL_TITRE      "fonts/Alex_Bold.ttf"
#define POLICE_LEVEL_TITRE_SIZE 150

#define POLICE_SCORE            "fonts/DS-DIGIB.TTF"
#define POLICE_SCORE_SIZE       30



enum { UP, RIGHT, DOWN, LEFT };


#endif // CONFIG_H_INCLUDED
