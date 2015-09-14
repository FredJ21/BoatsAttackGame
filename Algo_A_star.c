#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "Algo_A_star.h"


/*****************************************************************
*****************************************************************/
void calcul_chemin( int d_x, int d_y, int a_x, int a_y, int map_Obstacle[MAP_NB_TILE_X][MAP_NB_TILE_Y], SDL_Renderer *pRenderer) {

    int x, y, c;
    int fin = false;

    t_Algo_A_Star data;
    t_position current_position;

    t_table_Algo_A_Star list[MAP_NB_TILE_X][MAP_NB_TILE_Y] = {};

    data.depart_X = d_x / TILE_TAILLE_X;
    data.depart_Y = d_y / TILE_TAILLE_Y;
    data.arrive_X = a_x;
    data.arrive_Y = a_y;


    /** Point de depart **/
    data.derniere_position_ok_X = data.depart_X;
    data.derniere_position_ok_Y = data.depart_Y;
    c = calcul_cout (data.depart_X, data.depart_Y, &data);

    list[data.depart_X][data.depart_Y].poid     = c;
    list[data.depart_X][data.depart_Y].parent_x = 0;
    list[data.depart_X][data.depart_Y].parent_y = 0;
    list[data.depart_X][data.depart_Y].is_open  = true;


    while (!fin) {

        current_position = cherche_meilleur_position(list);

        list[current_position.x][current_position.y].is_open = false;
        list[current_position.x][current_position.y].is_close = true;
        data.derniere_position_ok_X = current_position.x;
        data.derniere_position_ok_Y = current_position.y;


        /** Voisin du dessus **/
        x = current_position.x;
        y = current_position.y - 1;

        if ( !is_obstacle(x,y,map_Obstacle) && !list[x][y].is_close) {
            c = calcul_cout(x, y, &data);
            if ( !list[x][y].is_open ) {
                        list[x][y].poid     = c;
                        list[x][y].parent_x = current_position.x;
                        list[x][y].parent_y = current_position.y;
                        list[x][y].is_open  = true;
            }
        }

        /** Voisin de droite **/
        x = current_position.x + 1;
        y = current_position.y;

        if ( !is_obstacle(x,y,map_Obstacle) && !list[x][y].is_close) {
            c = calcul_cout(x, y, &data);
            if ( !list[x][y].is_open ) {
                        list[x][y].poid     = c;
                        list[x][y].parent_x = current_position.x;
                        list[x][y].parent_y = current_position.y;
                        list[x][y].is_open  = true;
            }
        }

        /** Voisin du dessous **/
        x = current_position.x;
        y = current_position.y + 1;

        if ( !is_obstacle(x,y,map_Obstacle) && !list[x][y].is_close) {
            c = calcul_cout(x, y, &data);
            if ( !list[x][y].is_open ) {
                        list[x][y].poid     = c;
                        list[x][y].parent_x = current_position.x;
                        list[x][y].parent_y = current_position.y;
                        list[x][y].is_open  = true;
           }
        }

        /** Voisin de gauche **/
        x = current_position.x - 1;
        y = current_position.y;

        if ( !is_obstacle(x,y,map_Obstacle) && !list[x][y].is_close) {
            c = calcul_cout(x, y, &data);
            if ( !list[x][y].is_open ) {
                        list[x][y].poid     = c;
                        list[x][y].parent_x = current_position.x;
                        list[x][y].parent_y = current_position.y;
                        list[x][y].is_open  = true;
            }
        }


        //affiche_map_console(map_Obstacle, current_position);


        if (current_position.x == data.arrive_X && current_position.y == data.arrive_Y) {
            fin =true;
        }

    }

    printf (" FIN calcul\n");

    retrouve_chemin_vers_depart(&data, list, pRenderer);


    SDL_RenderPresent   (pRenderer);
    SDL_Delay ( 2000 );



}
/*****************************************************************
*****************************************************************/
void affiche_map_console (int map_Obstacle[MAP_NB_TILE_X][MAP_NB_TILE_Y], t_position current_position) {

    int x, y;

    for (y = 0; y < MAP_NB_TILE_Y; y++){
        for (x = 0; x < MAP_NB_TILE_X; x++) {

            if (x == current_position.x && y == current_position.y){
                printf ("X");
            } else {
                printf ("%d", map_Obstacle[x][y]);
            }
        }
        printf ("\n");
    }
    printf ("\n");
}
/*****************************************************************
*****************************************************************/
bool is_obstacle        (int x, int y, int map_Obstacle[MAP_NB_TILE_X][MAP_NB_TILE_Y]) {

    if ( map_Obstacle[x][y] == 1 || x < 0 || x > MAP_NB_TILE_X - 1) {
        return true;
    } else {
        return false;
    }
}
/*****************************************************************
*****************************************************************/
int calcul_cout    (int x, int y, t_Algo_A_Star *data){

    int cout_depuis_depart   = abs(x - data->derniere_position_ok_X) + abs(y - data->derniere_position_ok_Y);
    int cout_vers_arrivee    = abs(x - data->arrive_X) + abs(y - data->arrive_Y);

    return cout_depuis_depart + cout_vers_arrivee;

}
/*****************************************************************
*****************************************************************/
t_position cherche_meilleur_position (t_table_Algo_A_Star list[MAP_NB_TILE_X][MAP_NB_TILE_Y]) {

    int x, y;

    t_position meilleur;
    int tmp_poid = 9999;


    for (y = 0; y < MAP_NB_TILE_Y; y++){
        for (x = 0; x < MAP_NB_TILE_X; x++) {

            if (list[x][y].is_open){

                if ( list[x][y].poid < tmp_poid ) {
                        tmp_poid = list[x][y].poid;
                        meilleur.x = x;
                        meilleur.y = y;
                }
            }
        }
    }


    return meilleur;
}
/*****************************************************************
*****************************************************************/
void retrouve_chemin_vers_depart (t_Algo_A_Star *data, t_table_Algo_A_Star Algo_list[MAP_NB_TILE_X][MAP_NB_TILE_Y], SDL_Renderer *pRenderer) {

    int x = data->derniere_position_ok_X;
    int y = data->derniere_position_ok_Y;
    int new_x, new_y;
    bool fin = false;

    while (!fin) {

        new_x = Algo_list[x][y].parent_x;
        new_y = Algo_list[x][y].parent_y;
        x = new_x;
        y = new_y;

        if (x == data->depart_X && y == data->depart_Y ) {
            fin = true;
        }


    /** Affichge d'un point pour verifier */
    SDL_Surface *pSurface_tmp = SDL_LoadBMP ( "./images/point_rouge.bmp" );
        if(!pSurface_tmp) { printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

        SDL_SetColorKey(pSurface_tmp, SDL_TRUE, SDL_MapRGB(pSurface_tmp->format, 255, 255, 255));

    SDL_Texture *pTexture_tmp;
    pTexture_tmp = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
        if(!pTexture_tmp) { printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}

    SDL_Rect Dst;
    Dst.x = x * TILE_TAILLE_X ;
    Dst.y = y * TILE_TAILLE_Y;
    Dst.w = TILE_TAILLE_X;
    Dst.h = TILE_TAILLE_Y;

    SDL_RenderCopy ( pRenderer, pTexture_tmp , NULL, &Dst);


    }
}
/*****************************************************************
*****************************************************************/
