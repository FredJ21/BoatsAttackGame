#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

// les defines
#define NOIR    al_map_rgb(0,0,0)
#define ROUGE   al_map_rgb(255,0,0)
#define VERT    0x00, 0xFF, 0x00
#define BLEU    0x00, 0x00, 0xFF
#define COLOR_ALEA al_map_rgb(rand()%256,rand()%256,rand()%256)

// CONFIG
#define APP_TITRE           "Battle BOATS - By Fred & Mathis"
#define COULEUR_FENETRE     NOIR
#define START_IMG           "./images/start.bmp"

#define GAME_FPS              30

#define MAP_TAILLE_X        1024
#define MAP_TAILLE_Y         768
#define MAP_NB_TILE_X         32
#define MAP_NB_TILE_Y         24
#define TILE_TAILLE_X         32
#define TILE_TAILLE_Y         32
#define TILE_FILE           "./images/32x32_map_tile_v3.1.bmp"
#define TILE_FILE_NB_COLONNE  23
#define LEVEL_NB_TOTAL         4
#define WAVE_ENEMY_NB_BY_WAVE  100
#define WAVE_NB                 10

#define POLICE_1            "./fonts/Just_Like_This_Demo.TTF"

enum { UP, RIGHT, DOWN, LEFT };


#endif // CONFIG_H_INCLUDED
