#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "Algo_A_star.h"

int a;

t_position close_list[MAP_NB_TILE_X][MAP_NB_TILE_Y] = {};
t_position open_list[MAP_NB_TILE_X][MAP_NB_TILE_Y] ={};
t_position current_position;
int map_Obstacle[MAP_NB_TILE_X][MAP_NB_TILE_Y];

int arrive_x;
int arrive_y;
int derniere_position_ok_x;
int derniere_position_ok_y;

/*****************************************************************
*****************************************************************/
void calcul_chemin( int d_x, int d_y, int a_x, int a_y, int mapO[MAP_NB_TILE_X][MAP_NB_TILE_Y], SDL_Renderer *pRenderer) {

    int x, y, c;
    int cout_vers_arrivee;
    int cout_depuis_depart;
    int fin = false;

    int depart_x;
    int depart_y;

    for ( y = 0; y < MAP_NB_TILE_Y; y++) {
        for ( x = 0; x < MAP_NB_TILE_X; x++) {
            map_Obstacle[x][y] = mapO[x][y];
        }
    }

    depart_x = d_x / TILE_TAILLE_X;
    depart_y = d_y / TILE_TAILLE_Y;
    arrive_x = a_x;
    arrive_y = a_y;

/*
    printf ("----------------------------------------\n");
    printf ("Nb de Position X * Y : %d x %d\n", MAP_NB_TILE_X, MAP_NB_TILE_Y);
    printf ("Nb de Pixel en X * Y : %d x %d\n", MAP_TAILLE_X, MAP_NB_TILE_Y);
    printf ("Position de depart : x=%d  y=%d\n", depart_x, depart_y);
    printf ("Position d'arrivee : x=%d  y=%d\n", arrive_x, arrive_y);
    printf ("----------------------------------------\n");
*/


    /** Point de depart **/
    derniere_position_ok_x = depart_x;
    derniere_position_ok_y = depart_y;
    c = calcul_cout (depart_x, depart_y);
    add_in_open_list(depart_x, depart_y, c, 0, 0);


    while (!fin) {

        current_position = cherche_meilleur_position();
        add_in_close_list (current_position);


        /** Voisin du dessus **/
        x = current_position.x;
        y = current_position.y - 1;

        if ( !is_obstacle(x,y) && !is_in_close_list(x,y)) {
            c = calcul_cout(x, y);
            if ( !is_in_open_list(x,y) ) {
                        add_in_open_list( x, y, c, current_position.x, current_position.y);
            }
        }

        /** Voisin de droite **/
        x = current_position.x + 1;
        y = current_position.y;

        if ( !is_obstacle(x,y) && !is_in_close_list(x,y)) {
            c = calcul_cout(x, y);
            if ( !is_in_open_list(x,y) ) {
                        add_in_open_list( x, y, c, current_position.x, current_position.y);
            }
        }

        /** Voisin du dessous **/
        x = current_position.x;
        y = current_position.y + 1;

        if ( !is_obstacle(x,y) && !is_in_close_list(x,y)) {
            c = calcul_cout(x, y);
            if ( !is_in_open_list(x,y) ) {
                        add_in_open_list( x, y, c, current_position.x, current_position.y);
           }
        }

        /** Voisin de gauche **/
        x = current_position.x - 1;
        y = current_position.y;

        if ( !is_obstacle(x,y) && !is_in_close_list(x,y)) {
            c = calcul_cout(x, y);
            if ( !is_in_open_list(x,y) ) {
                        add_in_open_list( x, y, c, current_position.x, current_position.y);
            }
        }


        //affiche_map_console();


        if (current_position.x == arrive_x && current_position.y == arrive_y) {
            fin =true;
        }

    }

    printf (" FIN calcul\n");

    retrouve_chemin_vers_depart(depart_x, depart_y, pRenderer);
    clear_list();


    SDL_RenderPresent   (pRenderer);
    SDL_Delay ( 2000 );



}
/*****************************************************************
*****************************************************************/
void affiche_map_console (void) {

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
bool is_obstacle        (int x, int y) {

    if ( map_Obstacle[x][y] == 1 || x < 0 || x > MAP_NB_TILE_X - 1) {
        return true;
    } else {
        return false;
    }
}
/*****************************************************************
*****************************************************************/
bool is_in_close_list   (int x, int y){

    if ( close_list[x][y].valeur != 0 ) {
        return true;
    } else {
        return false;
    }
}
/*****************************************************************
*****************************************************************/
bool is_in_open_list    (int x, int y){

    if ( open_list[x][y].valeur != 0 ) {
        return true;
    } else {
        return false;
    }

}
/*****************************************************************
*****************************************************************/
int calcul_cout    (int x, int y){

    int cout_depuis_depart   = abs(x - derniere_position_ok_x) + abs(y - derniere_position_ok_y);
    int cout_vers_arrivee    = abs(x - arrive_x) + abs(y - arrive_y);

    return cout_depuis_depart + cout_vers_arrivee;

}
/*****************************************************************
*****************************************************************/
void add_in_open_list   (int x, int y, int valeur, int parent_x, int parent_y) {

    if (open_list[x][y].valeur == 0 || valeur < open_list[x][y].valeur ) {

        open_list[x][y].x = x;
        open_list[x][y].y = y;
        open_list[x][y].parent_x = parent_x;
        open_list[x][y].parent_y = parent_y;
        open_list[x][y].valeur = valeur;
    }

}
/*****************************************************************
*****************************************************************/
void add_in_close_list  (t_position t){

    int x = t.x;
    int y = t.y;

    close_list[x][y].x = t.x;
    close_list[x][y].y = t.y;
    close_list[x][y].valeur = t.valeur;
    close_list[x][y].parent_x = t.parent_x;
    close_list[x][y].parent_y = t.parent_y;

    derniere_position_ok_x = t.x;
    derniere_position_ok_y = t.y;

    open_list[x][y].valeur = 0;

}
/*****************************************************************
*****************************************************************/
t_position cherche_meilleur_position (void) {

    int x, y;

    t_position meilleur;
    meilleur.valeur = 9999;

    //printf ("cherche meilleur\n");

    for (y = 0; y < MAP_NB_TILE_Y; y++){
        for (x = 0; x < MAP_NB_TILE_X; x++) {

            if (open_list[x][y].valeur != 0){

                //printf ("x=%d y=%d v=%d px=%d py=%d\n", open_list[x][y].x, open_list[x][y].y, open_list[x][y].valeur, open_list[x][y].parent_x, open_list[x][y].parent_y);

                if ( open_list[x][y].valeur < meilleur.valeur ) {
                        meilleur.x = open_list[x][y].x;
                        meilleur.y = open_list[x][y].y;
                        meilleur.valeur = open_list[x][y].valeur;
                        meilleur.parent_x = open_list[x][y].parent_x;
                        meilleur.parent_y = open_list[x][y].parent_y;
                }
            }
        }
    }

    //printf ("MEILLEUR : x=%d y=%d v=%d px=%d py=%d\n", meilleur.x, meilleur.y, meilleur.valeur, meilleur.parent_x, meilleur.parent_y);


    return meilleur;
}
/*****************************************************************
*****************************************************************/
void retrouve_chemin_vers_depart (int depart_x, int depart_y, SDL_Renderer *pRenderer) {

    int x = derniere_position_ok_x;
    int y = derniere_position_ok_y;
    int new_x, new_y;
    bool fin = false;

    while (!fin) {
  //      printf ("x=%d y=%d v=%d px=%d py=%d\n", close_list[x][y].x, close_list[x][y].y, close_list[x][y].valeur, close_list[x][y].parent_x, close_list[x][y].parent_y);

        new_x = close_list[x][y].parent_x;
        new_y = close_list[x][y].parent_y;
        x = new_x;
        y = new_y;

        if (x == depart_x && y == depart_y ) {
            fin = true;
        }


    /** Affichge d'un point pour verifier */
    SDL_Surface *pSurface_tmp = SDL_LoadBMP ( "./images/point_orange.bmp" );
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
void clear_list(void) {


    int x, y;

    for (y = 0; y < MAP_NB_TILE_Y; y++){
        for (x = 0; x < MAP_NB_TILE_X; x++) {

            close_list[x][y].parent_x = 0;
            close_list[x][y].parent_y = 0;
            close_list[x][y].x = 0;
            close_list[x][y].y = 0;
            close_list[x][y].valeur = 0;

            open_list[x][y].parent_x = 0;
            open_list[x][y].parent_y = 0;
            open_list[x][y].x = 0;
            open_list[x][y].y = 0;
            open_list[x][y].valeur = 0;


        }
    }

}
/*****************************************************************
*****************************************************************/
