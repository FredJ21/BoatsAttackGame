#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "config.h"
#include "level.h"
#include "anim.h"
#include "tower.h"

/*****************************************************************
*****************************************************************/

t_tower*   create_Tower( int x, int y, t_animation *ANIM) {

	t_tower *s = (t_tower*)malloc(sizeof(t_tower));

    s->x            = x;
    s->y            = y;
    s->HG_x         = x - ANIM->tx/2;
    s->HG_y         = y - ANIM->ty/2;
    s->BD_x         = x + ANIM->tx/2;
    s->BD_y         = y + ANIM->ty/2;

    s->cible_x      = 0;
    s->cible_y      = 0;

    s->selected     = false;

	s->img_current  = 2;
	s->angle        = 0;
	s->compte_tour  = 0;
	s->nb_tour      = ANIM->nb_tour;
	s->anim         = ANIM;
	s->visible      = 254;

	return s;


}
/*****************************************************************
*****************************************************************/
void        anime_tower             (t_tower *s) {

    if (s->cible_x == 0 && s->cible_y == 0) {

        s->angle = s->angle + 3;
        if (s->angle > 360 ) { s->angle = 0; }

    } else {

        // TODO TIR
    }

}
/*****************************************************************
*****************************************************************/
void        calcul_angle_tower      (t_tower *s) {

    int angle;
    int xx = s->x - s->cible_x;
    int yy = s->y - s->cible_y;

    angle = abs( atan((float)xx/(float)yy) * 180 / M_PI );

    if          ( xx > 0 && yy >= 0 ) {          angle = 360 - angle;
    } else if   ( xx <= 0 && yy < 0 ) {          angle = 180 - angle;
    } else if   ( xx > 0 && yy < 0 ) {          angle = 180 + angle;
    }

    //printf ("%d  %d   angle = %d\n", xx, yy, angle);
    s->angle = angle;
}
/*****************************************************************
*****************************************************************/
void        affiche_tower(SDL_Renderer *r, t_tower *s){



    SDL_Rect Src;
    SDL_Rect Dst;

    Src.x = s->img_current * s->anim->tx;
    Src.y = 0;
    Src.w = s->anim->tx;
    Src.h = s->anim->ty;

    Dst.x = s->x - s->anim->tx/2;     // permet de center le sprite sur les coordonnées
    Dst.y = s->y - s->anim->ty/2;
    Dst.w = s->anim->tx;
    Dst.h = s->anim->ty;

    SDL_SetTextureAlphaMod (s->anim->texture, s->visible);
    SDL_SetRenderDrawColor (r, 254, 0, 0, 50);

    // Affichage
    if (s->selected) {
        SDL_RenderDrawRect(r, &Dst);
    }
    SDL_RenderCopyEx(r, s->anim->texture, &Src, &Dst, s->angle, NULL, 0);

}
/*****************************************************************
*****************************************************************/
bool        is_tower_new_valid_position(t_tower *s, t_level *pLevel) {

    t_pos HD;      // postion en haut à droite
    t_pos HG;      // postion en haut à gauche
    t_pos BD;      // postion en bas à droite
    t_pos BG;      // postion en bas à gauche


    // les ccordonnées du sprite correspondent à son centre
    // calcul des coordonnées des quatres coins
    HD.x = s->x + s->anim->tx/2 ;
    BD.x = HD.x;
    HD.tileX = HD.x / TILE_TAILLE_X;
    BD.tileX = HD.tileX;

    HG.x = s->x - s->anim->tx/2 ;
    BG.x = HG.x;
    HG.tileX = HG.x / TILE_TAILLE_X;
    BG.tileX = HG.tileX;

    HD.y = s->y - s->anim->ty/2 ;
    HG.y = HD.y;
    HD.tileY = HD.y / TILE_TAILLE_Y;
    HG.tileY = HD.tileY;

    BD.y = s->y + s->anim->ty/2 ;
    BG.y = BD.y;
    BD.tileY = BD.y / TILE_TAILLE_Y;
    BG.tileY = BD.tileY;

    // test si la position n'est ni LIBRE (sur eau) ni OCCUPE (par une tourelle)
    if ( pLevel->map_Info[HD.tileX][HD.tileY] == OBSTACLE &&
         pLevel->map_Info[HG.tileX][HG.tileY] == OBSTACLE &&
         pLevel->map_Info[BD.tileX][BD.tileY] == OBSTACLE &&
         pLevel->map_Info[BG.tileX][BG.tileY] == OBSTACLE ) {

         return true;

    } else {

        return false;
    }


}
/*****************************************************************
*****************************************************************/
int         is_tower_position       (int x, int y, t_tower *s[], int current_nb_tower ){

    int a;
    int result = TOWER_MAX;

    for (a = 0; a < current_nb_tower; a++) {

        if (x >= s[a]->HG_x && x <= s[a]->BD_x && y >= s[a]->HG_y && y <= s[a]->BD_y ) {

            result = a;
        }
    }

    return result;
}
/*****************************************************************
*****************************************************************/
void        add_tower_position      (t_tower *s, t_level *pLevel) {

    t_pos HD;      // postion en haut à droite
    t_pos HG;      // postion en haut à gauche
    t_pos BD;      // postion en bas à droite
    t_pos BG;      // postion en bas à gauche

    int x, y;

    // les ccordonnées du sprite correspondent à son centre
    // calcul des coordonnées des quatres coins
    HD.x = s->x + s->anim->tx/2 ;
    BD.x = HD.x;
    HD.tileX = HD.x / TILE_TAILLE_X;
    BD.tileX = HD.tileX;

    HG.x = s->x - s->anim->tx/2 ;
    BG.x = HG.x;
    HG.tileX = HG.x / TILE_TAILLE_X;
    BG.tileX = HG.tileX;

    HD.y = s->y - s->anim->ty/2 ;
    HG.y = HD.y;
    HD.tileY = HD.y / TILE_TAILLE_Y;
    HG.tileY = HD.tileY;

    BD.y = s->y + s->anim->ty/2 ;
    BG.y = BD.y;
    BD.tileY = BD.y / TILE_TAILLE_Y;
    BG.tileY = BD.tileY;

    // toute la zone est occupée
    for ( y = HG.tileY; y <= BG.tileY; y++) {
        for ( x = HG.tileX; x <= HD.tileX; x++ ) {

            printf ("%d-%d\n", x, y) ;
            pLevel->map_Info[x][y] = OCCUPE;
        }
    }

}
/*****************************************************************
*****************************************************************/
void destroy_tower(t_tower **s) {

    free(*s);
    *s = NULL;
}
/*****************************************************************
*****************************************************************/
