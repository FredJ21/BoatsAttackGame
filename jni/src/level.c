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
    int map_size = MAP_NB_TILE_X * MAP_NB_TILE_Y;
    SDL_Rect Rect_source = { 0, 0, TILE_TAILLE_X, TILE_TAILLE_Y};
    SDL_Rect Rect_Dest   = { 0, 0, TILE_TAILLE_X, TILE_TAILLE_Y};

    SDL_Surface *pSurface_TMP;
    pSurface_TMP = SDL_CreateRGBSurface(0,my_system->map_taille_x,my_system->map_taille_y,32,0,0,0,0);

    /******************************************************************************************************************
                                                DATA MAP
    *******************************************************************************************************************/
    int map[LEVEL_NB_TOTAL][MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
        { // level 1
        1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,
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
        1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,
        },
        { // level 2
        1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,
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
        1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,
        },
        { // level 3
        1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,
        444,446,487,487,487,487,487,487,557,557,487,487,487,487,487,487,487,487,487,487,487,487,487,487,444,446,487,487,487,487,
        467,533,487,487,487,487,487,487,557,557,487,487,487,487,487,487,487,487,487,487,487,487,487,487,467,533,487,487,487,487,
        467,556,445,445,557,487,487,487,557,557,445,445,557,487,487,445,557,557,445,445,557,446,487,487,467,556,557,557,487,487,
        467,510,511,511,512,487,487,487,512,510,511,511,511,487,487,511,512,510,511,511,512,533,487,487,467,510,491,491,487,487,
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
        1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,
        },
        { // level 4
        1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,
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
        1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,
        }
    };

    int StartPos[LEVEL_NB_TOTAL][8] = { /** positions de depart des ennemis , couple start/end
          Haut      Droite    Bas       Gauche   **/
        { 300, my_system->map_taille_x-50, 100, my_system->map_taille_y-100, 300, my_system->map_taille_x-50, 0, 0 },                            // level 1
        { 100, 400, 100, 400, 100, 400, 100, 400 },                                                 // level 2
        { 100, 400, 100, 400, 100, 400, 100, 400 },                                                 // level 3
        { 100, my_system->map_taille_x-100, 100, my_system->map_taille_y-100, 100, my_system->map_taille_x-100, 100, my_system->map_taille_y-100}       // level 4
    };

    int cible[LEVEL_NB_TOTAL][2] = {        /** position de la cible en X et Y **/
        {  4,  9 },          // level 1
        {  8, 14 },          // level 2
        {  2,  4 },          // level 3
        { 16, 11 }           // level 4
    };

    char name [LEVEL_NB_TOTAL][256] = {
        { "LEVEL 1" },
        { "LEVEL 2" },
        { "LEVEL 3" },
        { "LEVEL 4" }
    };

    int wave[LEVEL_NB_TOTAL][WAVE_NB * WAVE_nb_variable_struct_wave] = {    /** definition des vagues d'attack
          type, Nb_up, Nb_right, Nb_Down, Nb_left, d�lais avant d�part  **/
        {   // level 1
            0,  0, 10,  0,  0,  3,          // wave 1
            1,  10, 10,  10,  0,  15,
            0,  0, 0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0            // wave 10
        },
        {   // level 2
            0,  0, 10,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0
        },
        {   // level 3
            0,  0, 10,  0,  0,  0,
            1,  0,  50,  0,  0,  10,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0
        },
        {   // level 4
          /** type,   Nb_up,   Nb_right,   Nb_Down,   Nb_left,   d�lai avant d�part  **/
            0,  80,  0,  0,  0,  0,
            1,  0,  80,  0,  0,  0,
            2,  0,  0,  80,  0,  0,
            0,  0,  0,  0,  80,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            2,  0,  0,  0,  0,  0
        }
    };

    /******************************************************************************************************************
                                                DATA COPY
    *******************************************************************************************************************/
    // DATA de la map
    for (a = 0 ; a < map_size; a++) {
        pLevel->my_map[a] = map[level_number][a];
    }

    pLevel->StartPos_UP_s    =  StartPos[level_number][0];
    pLevel->StartPos_UP_e    =  StartPos[level_number][1];
    pLevel->StartPos_RIGHT_s =  StartPos[level_number][2];
    pLevel->StartPos_RIGHT_e =  StartPos[level_number][3];
    pLevel->StartPos_DOWN_s  =  StartPos[level_number][4];
    pLevel->StartPos_DOWN_e  =  StartPos[level_number][5];
    pLevel->StartPos_LEFT_s  =  StartPos[level_number][6];
    pLevel->StartPos_LEFT_e  =  StartPos[level_number][7];

    pLevel->cibleX = cible[level_number][0];
    pLevel->cibleY = cible[level_number][1];

    strcpy(pLevel->name, name[level_number]);

    // DATA des attacks
    for (a = 0 ; a < WAVE_NB; a++) {
        pLevel->wave[a].type     =  wave[level_number][a*WAVE_nb_variable_struct_wave + 0];
        pLevel->wave[a].nb_up    =  wave[level_number][a*WAVE_nb_variable_struct_wave + 1];
        pLevel->wave[a].nb_right =  wave[level_number][a*WAVE_nb_variable_struct_wave + 2];
        pLevel->wave[a].nb_down  =  wave[level_number][a*WAVE_nb_variable_struct_wave + 3];
        pLevel->wave[a].nb_left  =  wave[level_number][a*WAVE_nb_variable_struct_wave + 4];
        pLevel->wave[a].start_in =  wave[level_number][a*WAVE_nb_variable_struct_wave + 5];
    }

    /******************************************************************************************************************
                                        - Creation de la texture de la map
                                        - Creation de la des obstacles
                                        - Remise � zero de mapDirection
    *******************************************************************************************************************/
    SDL_Log("Fred DEBUG - TEST: %d x %d - ratio: %f\n", my_system->window_size_w, my_system->window_size_h, my_system->window_size_ratio);

    if ( (int)(my_system->window_size_ratio * 100) == 170 ) {            // permet d'ignorer la premiere ligne en ratio 1.7 (16:9)
        SDL_Log("Fred DEBUG - TEST OKKKKK\n");
        a = 30;
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

            //printf("x=%d - y=%d - val=%d - valx=%d - valy=%d\n ", x, y, pLevel->my_map[a], Rect_source.x, Rect_source.y );


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
    if(!pLevel->pTexture_MAP) {                         printf( "SDL_Texture_MAP ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit (-1);}


    SDL_FreeSurface(pSurface_TMP);
}
/*****************************************************************
*****************************************************************/
void init_level_chemins     (t_level *pLevel) {

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
        y = MAP_NB_TILE_Y - 1;
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

    // Cr�ation de la texture pour le texte
    pLevel->pTexture_MAP_Titre = SDL_CreateTextureFromSurface(pRenderer, texte);
    if(!pLevel->pTexture_MAP_Titre) {                  printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(-1);}

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
            if(!pSurface_CroixRouge) { printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    // cr�ation d'une surface temporaire de la taille de la map
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
        if(!pLevel->pTexture_MAP_Obstacles) { printf( "SDL_Texture_MAP ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit (-1);}


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

