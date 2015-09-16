#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "level.h"
#include "Algo_A_star.h"


/*****************************************************************
*****************************************************************/
void init_level (t_level *pLevel, int level_number, SDL_Surface *pSurface_Tuile, SDL_Renderer *pRenderer) {

    int a, x, y;
    int map_size = MAP_NB_TILE_X * MAP_NB_TILE_Y;
    SDL_Rect Rect_source = { 0, 0, TILE_TAILLE_X, TILE_TAILLE_Y};
    SDL_Rect Rect_Dest   = { 0, 0, TILE_TAILLE_X, TILE_TAILLE_Y};

    SDL_Surface *pSurface_TMP;
    pSurface_TMP = SDL_CreateRGBSurface(0,MAP_TAILLE_X,MAP_TAILLE_Y,32,0,0,0,0);

    int map[LEVEL_NB_TOTAL][MAP_NB_TILE_X * MAP_NB_TILE_Y] = {
        { // level 1
        48,48,48,48,48,48,507,561,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,48,48,507,561,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,48,507,561,375,370,489,489,489,489,489,371,422,422,372,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,507,561,375,370,499,489,489,489,489,489,400,444,446,421,422,422,372,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,375,370,489,489,489,489,489,489,489,400,467,556,557,557,446,398,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,400,467,143,510,511,492,398,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,400,467,143,556,446,375,370,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,400,490,491,491,492,398,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,369,376,376,376,376,370,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,499,371,422,422,422,372,489,489,489,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,371,423,444,445,446,398,499,489,489,489,489,489,489,
        48,48,48,530,421,422,422,422,372,489,489,489,489,489,489,489,489,489,371,423,444,558,143,469,398,489,489,489,489,489,489,489,
        48,48,48,553,514,514,514,515,398,489,489,489,489,489,489,489,499,489,400,444,558,143,510,492,398,489,489,489,489,489,489,489,
        48,48,48,48,48,48,48,538,398,489,489,489,489,489,489,489,489,489,400,490,491,491,492,375,370,499,489,489,489,489,489,489,
        48,48,48,48,48,48,48,538,398,489,489,489,489,489,489,489,489,489,369,376,376,376,376,370,499,499,489,489,489,489,489,489,
        48,48,48,48,48,48,507,561,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,48,48,507,561,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,48,507,561,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,507,561,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,513,564,564,564,564,515,489,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,513,565,48,48,48,48,563,515,489,489,489,
        48,48,48,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,513,565,48,48,48,48,48,48,538,489,489,489
        },
        { // level 2
        279,280,326,326,326,326,507,561,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        302,303,326,326,326,507,561,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        277,278,326,326,507,561,375,370,489,489,489,489,489,371,422,422,372,489,489,489,489,489,489,489,499,371,422,422,422,372,489,489,
        300,301,326,507,561,375,370,499,489,489,489,489,489,400,444,446,421,422,422,372,489,489,489,489,371,423,444,445,446,398,489,489,
        326,326,326,530,375,370,489,489,489,489,489,489,489,400,467,556,557,557,446,398,489,489,489,371,423,444,558,143,469,398,489,489,
        326,326,326,530,398,489,499,371,422,422,422,372,489,400,467,143,510,511,492,398,489,489,489,400,444,558,143,510,492,398,489,489,
        326,279,280,530,398,489,371,423,444,445,446,398,489,400,467,143,556,446,375,370,489,489,489,400,490,491,491,492,375,370,489,489,
        326,302,303,530,398,371,423,444,558,143,469,398,489,400,490,491,491,492,398,489,489,489,489,369,376,376,376,376,370,499,489,489,
        326,277,278,530,398,400,444,558,143,510,492,398,489,369,376,376,376,376,370,489,489,489,489,489,489,489,489,489,489,489,489,489,
        326,300,301,530,398,400,490,491,491,492,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        326,326,326,530,398,369,376,376,376,376,370,499,489,489,489,489,489,489,489,499,371,422,422,422,372,489,489,489,489,489,489,489,
        326,326,326,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,371,423,444,445,446,398,499,489,489,489,489,489,489,
        326,326,326,530,421,422,422,422,372,489,489,489,489,489,489,489,489,489,371,423,444,558,143,469,398,489,489,489,489,489,489,489,
        326,279,280,553,514,514,514,515,398,489,489,489,489,489,489,489,499,489,400,444,558,143,510,492,398,489,499,371,422,422,422,372,
        326,302,303,326,326,326,326,538,398,489,489,489,489,489,489,489,489,489,400,490,491,491,492,375,370,489,371,423,444,445,446,398,
        326,277,278,326,279,280,326,538,398,489,489,489,499,371,422,422,422,372,369,376,376,376,376,370,499,371,423,444,558,143,469,398,
        326,300,301,326,302,303,507,561,398,489,489,489,371,423,444,445,446,398,489,489,489,489,489,489,489,400,444,558,143,510,492,398,
        326,326,326,326,277,278,561,375,370,489,489,371,423,444,558,143,469,398,489,489,489,489,489,489,489,400,490,491,491,492,375,370,
        326,326,326,326,300,301,375,370,489,489,489,400,444,558,143,510,492,398,489,489,489,489,489,489,489,369,376,376,376,376,370,499,
        279,280,326,507,561,375,370,489,489,489,489,400,490,491,491,492,375,370,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
        302,303,326,530,375,370,489,489,489,489,489,369,376,376,376,376,370,499,489,489,489,381,422,422,422,422,422,422,372,489,489,489,
        277,278,326,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,381,433,513,564,564,564,564,515,421,372,489,489,
        300,301,326,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,381,433,513,565,326,326,326,326,563,515,398,489,489,
        326,326,326,530,398,489,489,489,489,489,489,489,489,489,489,489,489,489,489,433,513,565,326,326,326,326,326,326,538,398,489,489
        },
        { // level 3
        444,446,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,444,446,487,487,487,487,487,487,
        467,533,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,467,533,487,487,487,487,487,487,
        467,556,445,445,557,557,445,445,557,557,445,445,557,557,445,445,557,557,445,445,557,446,487,487,467,556,557,557,557,446,487,487,
        467,510,511,511,512,510,511,511,512,510,511,511,511,511,511,511,512,510,511,511,512,533,487,487,467,510,491,491,512,533,487,487,
        467,489,487,487,467,533,487,487,467,533,487,487,487,487,487,487,467,533,487,487,467,533,487,487,487,487,487,487,467,533,487,487,
        467,533,487,487,467,533,487,487,467,533,487,487,487,487,487,487,490,492,487,487,467,533,487,487,487,487,487,487,467,533,487,487,
        467,469,487,487,467,469,487,487,467,556,445,445,557,446,487,487,487,487,487,487,467,469,487,487,444,446,487,487,467,533,487,487,
        467,469,487,487,467,469,487,487,490,511,511,511,512,469,487,487,487,487,487,487,490,492,487,487,467,469,487,487,467,533,487,487,
        467,469,487,487,467,469,487,487,487,487,487,487,467,469,487,487,444,446,487,487,487,487,487,487,467,469,487,487,467,533,487,487,
        467,469,487,487,467,469,487,487,487,487,487,487,467,556,445,445,558,469,487,487,487,487,487,487,490,492,487,487,467,533,487,487,
        467,469,487,487,467,556,445,445,557,446,487,487,490,511,511,511,512,469,487,487,444,446,487,487,487,487,487,487,490,492,487,487,
        467,469,487,487,467,510,511,511,512,469,487,487,487,487,487,487,490,492,487,487,467,469,487,487,487,487,487,487,487,487,487,487,
        467,469,487,487,467,469,487,487,467,469,487,487,487,487,487,487,487,487,487,487,467,469,487,487,444,446,487,487,487,487,487,487,
        467,469,487,487,467,469,487,487,467,556,445,445,557,446,487,487,487,487,487,487,467,556,445,445,558,469,487,487,444,446,487,487,
        467,469,487,487,467,469,487,487,490,511,511,511,512,469,487,487,444,446,487,487,467,510,511,511,512,469,487,487,467,533,487,487,
        467,469,487,487,467,469,487,487,487,487,487,487,467,469,487,487,467,556,445,445,558,469,487,487,490,492,487,487,467,533,487,487,
        467,469,487,487,467,469,487,487,487,487,487,487,467,556,445,445,558,510,511,511,512,469,487,487,487,487,487,487,467,533,487,487,
        467,533,487,487,467,533,487,487,444,446,487,487,490,511,511,511,512,533,487,487,490,492,487,487,487,487,487,487,467,533,487,487,
        467,533,487,487,467,556,445,445,558,533,487,487,487,487,487,487,467,533,487,487,487,487,487,487,444,446,487,487,467,533,487,487,
        467,533,487,487,467,510,511,511,512,533,487,487,487,487,487,487,467,533,487,487,487,487,487,487,467,533,487,487,467,533,487,487,
        467,533,487,487,467,533,487,487,467,533,487,487,444,446,487,487,490,492,487,487,444,446,487,487,467,533,487,487,467,533,487,487,
        467,533,487,487,490,492,487,487,490,492,487,487,490,492,487,487,487,487,487,487,467,533,487,487,467,533,487,487,490,492,487,487,
        467,533,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,487,467,533,487,487,467,533,487,487,487,487,487,487,
        467,533,487,487,487,487,487,487,487,487,487,487,487,487,487,487,444,446,487,487,467,533,487,487,467,533,487,487,487,487,487,487
        }
    };

    switch(level_number) {
        case 0 :
            strcpy(pLevel->name, "LEVEL 1");
            pLevel->cibleX = 4;
            pLevel->cibleY = 9;
            break;

        case 1 :
            strcpy(pLevel->name, "LEVEL 2");
            pLevel->cibleX = 8;
            pLevel->cibleY = 14;
            break;
        case 2 :
            strcpy(pLevel->name, "LEVEL 3");
            pLevel->cibleX = 1;
            pLevel->cibleY = 4;
            break;
    }

    // DATA de la map
    for (a = 0 ; a < map_size; a++) {
        pLevel->my_map[a] = map[level_number][a];
    }


    // Creation de la texture de la map et remise � zero de mapDirection
    a = 0;
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
void affiche_map   (SDL_Renderer *pRenderer, t_level *pLevel) {

    SDL_RenderCopy (pRenderer, pLevel->pTexture_MAP, NULL, NULL);

}
/*****************************************************************
*****************************************************************/
void init_texture_obstacle  (SDL_Renderer *pRenderer, t_level *pLevel) {

    int x, y;
    SDL_Rect Rect_Dest   = { 0, 0, TILE_TAILLE_X, TILE_TAILLE_Y};
    SDL_Surface *pSurface_CroixRouge;
    SDL_Surface *pSurface_TMP;

    // charge l'image
    pSurface_CroixRouge = SDL_LoadBMP ( "images/CroixRouge32x32.bmp" );
            if(!pSurface_CroixRouge) { printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    // cr�ation d'une surface temporaire de la taille de la map
    pSurface_TMP = SDL_CreateRGBSurface(0,MAP_TAILLE_X,MAP_TAILLE_Y,32,0,0,0,0);


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
void affiche_obstacle   (SDL_Renderer *pRenderer, t_level *pLevel) {

    SDL_RenderCopy (pRenderer, pLevel->pTexture_MAP_Obstacles, NULL, NULL);

}
/*****************************************************************
*****************************************************************/
void affiche_map_console (t_level *pLevel) {

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
