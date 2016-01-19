#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "level.h"
#include "Algo_A_star.h"


/*****************************************************************
*****************************************************************/
void init_level (t_level *pLevel, int level_number, SDL_Surface *pSurface_Tuile, SDL_Renderer *pRenderer, t_system *my_system) {

    int a, x, y;
    SDL_Rect Rect_source = { 0, 0, TILE_TAILLE_X, TILE_TAILLE_Y};
    SDL_Rect Rect_Dest   = { 0, 0, TILE_TAILLE_X, TILE_TAILLE_Y};

    SDL_Surface *pSurface_TMP;
    pSurface_TMP = SDL_CreateRGBSurface(0,my_system->map_taille_x,my_system->map_taille_y,32,0,0,0,0);

    /******************************************************************************************************************
                                                DATA MAP
    *******************************************************************************************************************/
   char DataLevelName_1[15]   =   { "LEVEL 1" };
    char DataLevelName_2[15]   =   { "LEVEL 1" };
    char DataLevelName_3[15]   =   { "LEVEL 1" };
    char DataLevelName_4[15]   =   { "LEVEL 1" };
    char DataLevelName_5[15]   =   {};
    char DataLevelName_6[15]   =   {};
    char DataLevelName_7[15]   =   {};
    char DataLevelName_8[15]   =   {};
    char DataLevelName_9[15]   =   {};
    char DataLevelName_10[15]  =   {};
    char DataLevelName_11[15]  =   {};
    char DataLevelName_12[15]  =   {};
    char DataLevelName_13[15]  =   {};
    char DataLevelName_14[15]  =   {};
    char DataLevelName_15[15]  =   {};

    int DataLevel_current[70] = {};
    /*                          Cible   <---       Départ         --->  <---    Wave 1     --->   <---    Wave 2     --->  <---    Wave 3     --->  <---    Wave 4     --->  <---    Wave 5     --->  <---    Wave 6     --->  <---    Wave 7     --->  <---    Wave 8     --->  <---    Wave 9     --->  <---    Wave 10    --->
                                x   y   Haut    Droite  Bas     gauche  t,  H,  D,  B,  G, time,  t,  H,  D,  B,  G, time  t,  H,  D,  B,  G, time  t,  H,  D,  B,  G, time  t,  H,  D,  B,  G, time  t,  H,  D,  B,  G, time  t,  H,  D,  B,  G, time  t,  H,  D,  B,  G, time  t,  H,  D,  B,  G, time  t,  H,  D,  B,  G, time   */
    int DataLevel_1[70]  =  {   4,  7,  10,20,  5,10,   10,20,  5,10,   0,  0, 10,  0,  0,  3,    1, 10, 10, 10,  0, 15,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  };
    int DataLevel_2[70]  =  {   8, 14,  10,20,  5,10,   10,20,  5,10,   0,  0, 10,  0,  0,  0,    0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  };
    int DataLevel_3[70]  =  {   3,  5,  10,20,  5,10,   10,20,  5,10,   0,  0, 10,  0,  0,  0,    0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  };
    int DataLevel_4[70]  =  {  16, 11,  10,20,  5,10,   10,20,  5,10,   0, 80,  0,  0,  0,  0,    1,  0, 80,  0,  0,  0,   2,  0,  0, 80,  0,  0,   0,  0,  0,  0, 80,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  };
    int DataLevel_5[70]  =  {};
    int DataLevel_6[70]  =  {};
    int DataLevel_7[70]  =  {};
    int DataLevel_8[70]  =  {};
    int DataLevel_9[70]  =  {};
    int DataLevel_10[70] =  {};
    int DataLevel_11[70] =  {};
    int DataLevel_12[70] =  {};
    int DataLevel_13[70] =  {};
    int DataLevel_14[70] =  {};
    int DataLevel_15[70] =  {};

    int DataMap_current[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {};
    int DataMap_1[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
                                                    48,48,48,48,48,48,507,561,398,489,  489,489,489,489,489,489,489,489,489,489,  489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,48,48,48,507,561,398,489,  489,489,489,489,489,489,489,489,489,489,  489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,48,48,507,561,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,48,507,561,375,370,489,489,489,489,489,371,422,422,372,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,507,561,375,370,499,489,489,489,489,489,400,444,446,421,422,422,372,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,530,375,370,489,489,489,489,489,489,489,400,467,556,557,557,446,398,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,530,398,489,489,489,489,489,489,489,489,400,467,143,510,511,492,398,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,530,398,489,489,489,489,489,489,489,489,400,467,143,556,446,375,370,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,530,398,489,489,489,489,489,489,489,489,400,490,491,491,492,398,489,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,530,398,489,489,489,489,489,489,489,489,369,376,376,376,376,370,489,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,499,371,422,422,422,372,489,489,489,489,489,
                                                    48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,371,423,444,445,446,398,499,489,489,489,489,
                                                    48,48,48,530,421,422,422,422,372,489,489,489,489,489,489,489,489,489,371,423,444,558,143,469,398,489,489,489,489,489,
                                                    48,48,48,553,514,514,514,515,398,489,489,489,489,489,489,489,499,489,400,444,558,143,510,492,398,489,489,489,489,489,
                                                    48,48,48,48,48,48,48,538,398,489,489,489,489,489,489,489,489,489,400,490,491,491,492,375,370,499,489,489,489,489,
                                                    48,48,48,48,48,48,48,538,398,489,489,489,489,489,489,489,489,489,369,376,376,376,376,370,499,499,489,489,489,489,
                                                    48,48,48,48,48,48,507,561,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    48,48,48,48,48,48,507,561,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
    };
    int DataMap_2[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
                                                    279,280,326,326,326,326,507,561,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    279,280,326,326,326,326,507,561,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    302,303,326,326,326,507,561,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    277,278,326,326,507,561,375,370,489,489,489,489,489,371,422,422,372,489,489,489,489,489,489,489,499,371,422,422,422,372,
                                                    300,301,326,507,561,375,370,499,489,489,489,489,489,400,444,446,421,422,422,372,489,489,489,489,371,423,444,445,446,398,
                                                    326,326,326,530,375,370,489,489,489,489,489,489,489,400,467,556,557,557,446,398,489,489,489,371,423,444,558,143,469,398,
                                                    326,326,326,530,398,489,499,371,422,422,422,372,489,400,467,143,510,511,492,398,489,489,489,400,444,558,143,510,492,398,
                                                    326,279,280,530,398,489,371,423,444,445,446,398,489,400,467,143,556,446,375,370,489,489,489,400,490,491,491,492,375,370,
                                                    326,302,303,530,398,371,423,444,558,143,469,398,489,400,490,491,491,492,398,489,489,489,489,369,376,376,376,376,370,499,
                                                    326,277,278,530,398,400,444,558,143,510,492,398,489,369,376,376,376,376,370,489,489,489,489,489,489,489,489,489,489,489,
                                                    326,300,301,530,398,400,490,491,491,492,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    326,326,326,530,398,369,376,376,376,376,370,499,489,489,489,489,489,489,489,499,371,422,422,422,372,489,489,489,489,489,
                                                    326,326,326,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,371,423,444,445,446,398,499,489,489,489,489,
                                                    326,326,326,530,421,422,422,422,372,489,489,489,489,489,489,489,489,489,371,423,444,558,143,469,398,489,489,489,489,489,
                                                    326,279,280,553,514,514,514,515,398,489,489,489,489,489,489,489,499,489,400,444,558,143,510,492,398,489,499,371,422,422,
                                                    326,302,303,326,326,326,326,538,398,489,489,489,489,489,489,489,489,489,400,490,491,491,492,375,370,489,371,423,444,445,
                                                    326,277,278,326,279,280,326,538,398,489,489,489,499,371,422,422,422,372,369,376,376,376,376,370,499,371,423,444,558,143,
                                                    326,300,301,326,302,303,507,561,398,489,489,489,371,423,444,445,446,398,489,489,489,489,489,489,489,400,444,558,143,510,
                                                    326,300,301,326,302,303,507,561,398,489,489,489,371,423,444,445,446,398,489,489,489,489,489,489,489,400,444,558,143,510,
    };
    int DataMap_3[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
                                                    444,446,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,444,446,487,487,487,487,
                                                    444,446,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,444,446,487,487,487,487,
                                                    467,533,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,467,533,487,487,487,487,
                                                    467,556,445,445,557,487,487,487,557,557,445,445,557,487,487,445,557,557,445,445,557,446,487,487,467,556,487,487,487,487,
                                                    467,510,511,511,512,487,487,487,512,510,511,511,511,487,487,511,512,510,511,511,512,533,487,487,467,510,487,487,487,487,
                                                    467,489,487,487,467,487,487,487,467,533,487,487,487,487,487,487,467,533,487,487,467,533,487,487,487,487,487,487,487,487,
                                                    467,533,487,487,467,487,487,487,467,533,487,487,487,487,487,487,490,492,487,487,467,533,487,487,487,487,487,487,487,487,
                                                    467,469,487,487,467,487,487,487,467,556,445,445,557,446,487,487,487,487,487,487,467,469,487,487,444,446,487,487,487,487,
                                                    467,469,487,487,467,487,487,487,490,511,511,511,512,469,487,487,487,487,487,487,490,492,487,487,467,469,487,487,487,487,
                                                    467,469,487,487,467,487,487,487,487,487,487,487,467,469,487,487,444,446,487,487,487,487,487,487,467,469,487,487,487,487,
                                                    467,469,487,487,467,487,487,487,487,487,487,487,467,556,445,445,558,469,487,487,487,487,487,487,490,492,487,487,487,487,
                                                    467,469,487,487,487,487,487,487,557,446,487,487,490,511,511,511,512,469,487,487,444,446,487,487,487,487,487,487,487,487,
                                                    467,469,487,487,487,487,487,487,512,469,487,487,487,487,487,487,490,492,487,487,467,469,487,487,487,487,487,487,487,487,
                                                    467,469,487,487,487,487,487,487,467,469,487,487,487,487,487,487,487,487,487,487,467,469,487,487,444,446,487,487,487,487,
                                                    467,469,487,487,467,487,487,487,467,556,445,445,557,446,487,487,487,487,487,487,467,556,445,445,558,469,487,487,444,446,
                                                    467,469,487,487,467,487,487,487,490,511,511,511,512,469,487,487,444,446,487,487,467,510,511,511,512,469,487,487,467,533,
                                                    467,469,487,487,467,487,487,487,487,487,487,487,467,469,487,487,467,556,445,445,558,469,487,487,490,492,487,487,467,533,
                                                    467,469,487,487,467,487,487,487,487,487,487,487,467,556,445,445,558,510,511,511,512,469,487,487,487,487,487,487,467,533,
                                                    467,469,487,487,467,487,487,487,487,487,487,487,467,556,445,445,558,510,511,511,512,469,487,487,487,487,487,487,467,533,
    };
    int DataMap_4[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,467,467,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,467,467,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,467,467,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,467,467,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
                                                    489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
    };
    int DataMap_5[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_6[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_7[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_8[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_9[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_10[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_11[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_12[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_13[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_14[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };
    int DataMap_15[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
    };



    /******************************************************************************************************************
                                                DATA COPY
    *******************************************************************************************************************/

    switch (level_number) {

        case 0:
            strcpy(pLevel->name, DataLevelName_1);
            for(a = 0 ; a < 70 ; a++)   {                                   DataLevel_current[a]   = DataLevel_1[a]; }
            for(a = 0 ; a < MAP_NB_TILE_X * MAP_NB_TILE_Y ; a++)   {        DataMap_current[a]     = DataMap_1[a];   }
            break;
        case 1:
            strcpy(pLevel->name, DataLevelName_2);
            for(a = 0 ; a < 70 ; a++)   {                                   DataLevel_current[a]   = DataLevel_2[a]; }
            for(a = 0 ; a < MAP_NB_TILE_X * MAP_NB_TILE_Y ; a++)   {        DataMap_current[a]     = DataMap_2[a];   }
            break;
        case 2:
            strcpy(pLevel->name, DataLevelName_3);
            for(a = 0 ; a < 70 ; a++)   {                                   DataLevel_current[a]   = DataLevel_3[a]; }
            for(a = 0 ; a < MAP_NB_TILE_X * MAP_NB_TILE_Y ; a++)   {        DataMap_current[a]     = DataMap_3[a];   }
            break;
        case 3:
            strcpy(pLevel->name, DataLevelName_4);
            for(a = 0 ; a < 70 ; a++)   {                                   DataLevel_current[a]   = DataLevel_4[a]; }
            for(a = 0 ; a < MAP_NB_TILE_X * MAP_NB_TILE_Y ; a++)   {        DataMap_current[a]     = DataMap_4[a];   }
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
    }





    // DATA de la map
    for (a = 0 ; a < MAP_NB_TILE_X * MAP_NB_TILE_Y; a++) {
        pLevel->my_map[a] = DataMap_current[a];
    }

    pLevel->StartPos_UP_s    =  DataLevel_current[2] * TILE_TAILLE_X;
    pLevel->StartPos_UP_e    =  DataLevel_current[3] * TILE_TAILLE_X + TILE_TAILLE_X;
    pLevel->StartPos_RIGHT_s =  DataLevel_current[4] * TILE_TAILLE_Y;
    pLevel->StartPos_RIGHT_e =  DataLevel_current[5] * TILE_TAILLE_Y + TILE_TAILLE_Y;
    pLevel->StartPos_DOWN_s  =  DataLevel_current[6] * TILE_TAILLE_X;
    pLevel->StartPos_DOWN_e  =  DataLevel_current[7] * TILE_TAILLE_X + TILE_TAILLE_X;
    pLevel->StartPos_LEFT_s  =  DataLevel_current[8] * TILE_TAILLE_Y;;
    pLevel->StartPos_LEFT_e  =  DataLevel_current[9] * TILE_TAILLE_Y + TILE_TAILLE_Y;

    pLevel->cibleX = DataLevel_current[0];
    pLevel->cibleY = DataLevel_current[1];

    // DATA des attacks
    for (a = 0 ; a < WAVE_NB; a++) {
        pLevel->wave[a].type     =  DataLevel_current[a*6 + 10];
        pLevel->wave[a].nb_up    =  DataLevel_current[a*6 + 11];
        pLevel->wave[a].nb_right =  DataLevel_current[a*6 + 12];
        pLevel->wave[a].nb_down  =  DataLevel_current[a*6 + 13];
        pLevel->wave[a].nb_left  =  DataLevel_current[a*6 + 14];
        pLevel->wave[a].start_in =  DataLevel_current[a*6 + 15];
    }

    /******************************************************************************************************************
                                        - Creation de la texture de la map
                                        - Creation de la des obstacles
                                        - Remise à zero de mapDirection
    *******************************************************************************************************************/

    if ( (int)(my_system->window_size_ratio * 100) == 170 ) {            // permet d'ignorer la premiere ligne en ratio 1.7 (16:9)
        a = 30;
        pLevel->cibleY = pLevel->cibleY - 1;
    } else {
        a = 0;
    }

    for (y = 0; y < MAP_NB_TILE_Y; y++ ) {
        for (x = 0; x < MAP_NB_TILE_X; x++ ) {


            Rect_source.y = (pLevel->my_map[a]-1) / TILE_FILE_NB_COLONNE  * (TILE_TAILLE_Y + 1) + 1;
            Rect_source.x = ((pLevel->my_map[a]-1) % TILE_FILE_NB_COLONNE)  * (TILE_TAILLE_Y + 1) + 1;

            Rect_Dest.x = x * TILE_TAILLE_X;
            Rect_Dest.y = y * TILE_TAILLE_Y;

            SDL_BlitSurface(pSurface_Tuile, &Rect_source, pSurface_TMP, &Rect_Dest);

            //if (DEBUG){SDL_Log("x=%d - y=%d - val=%d - valx=%d - valy=%d\n ", x, y, pLevel->my_map[a], Rect_source.x, Rect_source.y );}


            // creation du tableau des obstacles
            if ( pLevel->my_map[a] == 369 ||
                    pLevel->my_map[a] == 370 ||
                    pLevel->my_map[a] == 371 ||
                    pLevel->my_map[a] == 372 ||
                    pLevel->my_map[a] == 375 ||
                    pLevel->my_map[a] == 376 ||
                    pLevel->my_map[a] == 377 ||
                    pLevel->my_map[a] == 381 ||
                    pLevel->my_map[a] == 398 ||
                    pLevel->my_map[a] == 400 ||
                    pLevel->my_map[a] == 421 ||
                    pLevel->my_map[a] == 422 ||
                    pLevel->my_map[a] == 423 ||
                    pLevel->my_map[a] == 433 ||
                    pLevel->my_map[a] == 440 ||
                    pLevel->my_map[a] == 441 ||
                    pLevel->my_map[a] == 443 ||
                    pLevel->my_map[a] == 463 ||
                    pLevel->my_map[a] == 464 ||
                    pLevel->my_map[a] == 466 ||
                    pLevel->my_map[a] == 486 ||
                    pLevel->my_map[a] == 487 ||
                    pLevel->my_map[a] == 499 ||
                    pLevel->my_map[a] == 489 ) {
                // ce n'est pas obstacle
                pLevel->map_Info[x][y] = LIBRE;
            } else {
                // c'est un obstacle
                pLevel->map_Info[x][y] = OBSTACLE;
            }


            pLevel->map_Direction[x][y] = INCONNU;
            a++;
        }
    }


    pLevel->pTexture_MAP = SDL_CreateTextureFromSurface(pRenderer, pSurface_TMP);
    if(!pLevel->pTexture_MAP && DEBUG) {SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Texture_MAP ERREUR! SDL_GetError: %s\n", SDL_GetError() );exit (-1);}


    SDL_FreeSurface(pSurface_TMP);
}
/*****************************************************************
*****************************************************************/
void init_level_chemins     (t_level *pLevel, t_system *my_system) {

    int x, y;

    for (y = 1; y < MAP_NB_TILE_Y; y++){
        x = 0;
        if ( pLevel->map_Info[x][y] == LIBRE ) {    calcul_chemin(x, y, pLevel);    }
        x = MAP_NB_TILE_X - 1;
        if ( pLevel->map_Info[x][y] == LIBRE ) {    calcul_chemin(x, y, pLevel);    }
    }
    for (x = 1; x < MAP_NB_TILE_X; x++ ) {
        y = 0;
        if ( pLevel->map_Info[x][y] == LIBRE ) {    calcul_chemin(x, y, pLevel);    }

        if ( (int)(my_system->window_size_ratio * 100) == 170 ) {            // Une ligne en moins en mode ratio 1.7 (16:9)
            y = MAP_NB_TILE_Y - 2;
        } else {
            y = MAP_NB_TILE_Y - 1;
        }
        if ( pLevel->map_Info[x][y] == LIBRE ) {    calcul_chemin(x, y, pLevel);    }
    }
}
/*****************************************************************
*****************************************************************/
void init_level_titre       (SDL_Renderer *pRenderer, t_level *pLevel, TTF_Font *police, t_system *my_system) {


    SDL_Surface *texte = NULL;
    SDL_Color couleur = {200, 100, 100, 0};

    texte = TTF_RenderText_Blended(police, pLevel->name, couleur);
    pLevel->Titre_position_src.x = 0;
    pLevel->Titre_position_src.y = 0;
    pLevel->Titre_position_src.h = texte->h;
    pLevel->Titre_position_src.w = texte->w;
    pLevel->Titre_position_dst.x = (my_system->map_taille_x - texte->w)/2;
    pLevel->Titre_position_dst.y = (my_system->map_taille_y - texte->h*2)/2;
    pLevel->Titre_position_dst.h = texte->h;
    pLevel->Titre_position_dst.w = texte->w;

    // Création de la texture pour le texte
    pLevel->pTexture_MAP_Titre = SDL_CreateTextureFromSurface(pRenderer, texte);
    if(!pLevel->pTexture_MAP_Titre && DEBUG) { SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(-1);}

    SDL_FreeSurface(texte);

}
/*****************************************************************
*****************************************************************/
void clear_level            (t_level *pLevel) {

    SDL_DestroyTexture(pLevel->pTexture_MAP);
    SDL_DestroyTexture(pLevel->pTexture_MAP_Titre);
    SDL_DestroyTexture(pLevel->pTexture_MAP_Obstacles);

}
/*****************************************************************
*****************************************************************/
void affiche_map            (SDL_Renderer *pRenderer, t_level *pLevel) {

    SDL_RenderCopy (pRenderer, pLevel->pTexture_MAP, NULL, NULL);
}
/*****************************************************************
*****************************************************************/
void affiche_titre          (SDL_Renderer *pRenderer, t_level *p) {

       SDL_RenderCopy      (pRenderer, p->pTexture_MAP_Titre,  &p->Titre_position_src, &p->Titre_position_dst);

}
/*****************************************************************
*****************************************************************/
void init_texture_obstacle  (SDL_Renderer *pRenderer, t_level *pLevel, t_system *my_system) {

    int x, y;
    SDL_Rect Rect_Dest   = { 0, 0, TILE_TAILLE_X, TILE_TAILLE_Y};
    SDL_Surface *pSurface_CroixRouge;
    SDL_Surface *pSurface_TMP;

    // charge l'image
    pSurface_CroixRouge = SDL_LoadBMP ( "images/CroixRouge32x32.bmp" );
            if(!pSurface_CroixRouge && DEBUG) { SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    // création d'une surface temporaire de la taille de la map
    pSurface_TMP = SDL_CreateRGBSurface(0,my_system->map_taille_x,my_system->map_taille_y,32,0,0,0,0);


    // creation de la texture MAP_Obstacle
    for (y = 0; y < MAP_NB_TILE_Y; y++ ) {
        for (x = 0; x < MAP_NB_TILE_X; x++ ) {

            if ( pLevel->map_Info[x][y] == OBSTACLE) {

                Rect_Dest.x = x * TILE_TAILLE_X;
                Rect_Dest.y = y * TILE_TAILLE_Y;
                SDL_BlitSurface(pSurface_CroixRouge, NULL, pSurface_TMP, &Rect_Dest);
            }
        }
    }

    SDL_SetColorKey(pSurface_TMP, SDL_TRUE, SDL_MapRGB(pSurface_TMP->format, 0, 0, 0));


    pLevel->pTexture_MAP_Obstacles = SDL_CreateTextureFromSurface(pRenderer, pSurface_TMP);
        if(!pLevel->pTexture_MAP_Obstacles && DEBUG) { SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture_MAP ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit (-1);}


   SDL_FreeSurface(pSurface_CroixRouge);
   SDL_FreeSurface(pSurface_TMP);
}
/*****************************************************************
*****************************************************************/
void affiche_obstacle       (SDL_Renderer *pRenderer, t_level *pLevel) {

    SDL_RenderCopy (pRenderer, pLevel->pTexture_MAP_Obstacles, NULL, NULL);

}
/*****************************************************************
*****************************************************************/
void affiche_map_console    (t_level *pLevel) {

    int x, y;

    for (y = 0; y < MAP_NB_TILE_Y; y++){
        for (x = 0; x < MAP_NB_TILE_X; x++) {

           if ( pLevel->map_Info[x][y] == OBSTACLE) {
                printf (".");
            } else if ( pLevel->map_Direction[x][y] == VERS_LE_HAUT) {
                printf ("^");
            } else if ( pLevel->map_Direction[x][y] == VERS_LA_DROITE) {
                printf (">");
            } else if ( pLevel->map_Direction[x][y] == VERS_LE_BAS) {
                printf ("v");
            } else if ( pLevel->map_Direction[x][y] == VERS_LA_GAUCHE) {
                printf ("<");
            } else {
                printf (" ");
            }
        }
        printf ("\n");
    }
    printf ("\n");
}

