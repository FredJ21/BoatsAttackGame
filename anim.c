#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "level.h"
#include "anim.h"

/*****************************************************************
*****************************************************************/
void init_animation(t_animation *a, SDL_Renderer *r)  {


    SDL_Surface *pSurface_tmp = SDL_LoadBMP ( a->file );
            if(!pSurface_tmp) { printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    SDL_SetColorKey(pSurface_tmp, SDL_TRUE, SDL_MapRGB(pSurface_tmp->format, 255, 255, 255));

    a->texture = SDL_CreateTextureFromSurface(r, pSurface_tmp);
        if(!a->texture) { printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}

    SDL_FreeSurface(pSurface_tmp);

}
/*****************************************************************
*****************************************************************/
t_sprite    *init_sprite(t_animation *a){
	t_sprite *s = (t_sprite*)malloc(sizeof(t_sprite));

	s->x = 0;
	s->y = 0;
	s->dx = 0;
	s->dy = 0;
	s->img_current = 0;
	s->compte_tour = 0;
	s->nb_tour = a->nb_tour;
	s->direction = 0;
	s->anim = a;
	s->is_actif = true;
	s->is_arrive = false;
	s->in_the_map = false;
	s->time_before_ativiation = 0;
	s->visible = 255;

	return s;
}
/*****************************************************************
*****************************************************************/
t_sprite*   create_Enemy( int position, int A, int B, t_animation *ANIM, float Frequence) {
                            // position --> en haut, à droite, en bas, à gauche
                            // A & B    --> délimite la zone de création , entre A et B
                            // *ANIM    --> pointeur sur l'annimation
                            // Frequence --> Frequence de démarrage entre chaque ennemi

 //           ENNEMI[e] = init_sprite( MAP_TAILLE_X + 3, (rand()%(MAP_TAILLE_Y-200))+100, 2, 2, 5, LEFT, ANIM, (GAME_FPS * e*3)+1 );
//    srand(time(NULL));

	t_sprite *s = (t_sprite*)malloc(sizeof(t_sprite));

    switch ( position ){

        case UP:
                s->x = (rand()%(B-A)) + A;
                s->y = 0 - ANIM->ty/2 ;
                s->direction = DOWN;
                break;
        case RIGHT:
                s->x = MAP_TAILLE_X + ANIM->tx/2 ;
                s->y = (rand()%(B-A)) + A;;
                s->direction = LEFT;
                break;
        case DOWN:
                s->x = (rand()%(B-A)) + A;;
                s->y = MAP_TAILLE_Y + ANIM->ty/2 ;
                s->direction = UP;
                break;
        case LEFT:
                s->x = 0 - ANIM->tx/2 ;
                s->y = (rand()%(B-A)) + A;;
                s->direction = RIGHT;
                break;
    }

	s->dx = ANIM->vitesse;
	s->dy = ANIM->vitesse;
	s->img_current = 0;
	s->compte_tour = 0;
	s->nb_tour = ANIM->nb_tour;
	s->anim = ANIM;
	s->is_actif = false;
	s->is_arrive = false;
	s->in_the_map = false;
	s->time_before_ativiation = (GAME_FPS * Frequence) +1 ;
	s->visible = 255;

	if (s->time_before_ativiation == 0 ) { s->is_actif = true; }

	return s;
}
/*****************************************************************
*****************************************************************/
void avance_sprite(t_sprite *s, t_level *pLevel){

    t_pos HD;      // postion en haut à droite
    t_pos HG;      // postion en haut à gauche
    t_pos BD;      // postion en bas à droite
    t_pos BG;      // postion en bas à gauche
    t_pos Centre;
    t_pos Arrive;

    srand(time(NULL));

    // gestion du retardement au démarrage
    if (s->time_before_ativiation > 1 ) {
        s->time_before_ativiation--;
    }
    if (s->time_before_ativiation == 1 ) {
        s->time_before_ativiation = 0;
        s->is_actif = true;
    }


    if (s->is_actif == true && s->is_arrive == false ) {

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

        Centre.x = s->x;
        Centre.y = s->y;
        Centre.tileX = s->x / TILE_TAILLE_X;
        Centre.tileY = s->y / TILE_TAILLE_Y;

        // permet de demarrer en dehors de la map
        if (s->in_the_map == false) {
            if (   HD.x<MAP_TAILLE_X && HG.x<MAP_TAILLE_X && BD.x<MAP_TAILLE_X && BG.x<MAP_TAILLE_X
                && HD.y<MAP_TAILLE_Y && HG.y<MAP_TAILLE_Y && BD.y<MAP_TAILLE_Y && BG.y<MAP_TAILLE_Y
                && HD.x>0 && HG.x>0 && BD.x>0 && BG.x>0 && HD.y>0 && HG.y>0 && BD.y>0 && BG.y>0 ) {

                    s->in_the_map = true;
            }
        }

        switch (s->direction) {
                case UP :
                            s->y -= s->dy;
                            if (s->in_the_map == true) {

                                // detection des bords
                                if ( HD.y <= 0 ) {
                                        s->direction = DOWN;
                                        //printf ("1 Detection bord\n");
                                }
                                // detection des obstacles
                                else if ( pLevel->map_Info[HG.tileX][HG.tileY] != LIBRE || pLevel->map_Info[HD.tileX][HD.tileY] != LIBRE ) {
                                        //printf ("1 Detection obstacle\n");
                                        if ( pLevel->map_Info[HG.tileX][HG.tileY] == LIBRE ) {

                                            s->direction = LEFT;

                                        } else if ( pLevel->map_Info[HD.tileX][HD.tileY] == LIBRE ) {

                                            s->direction = RIGHT;

                                        } else {

                                            s->direction = RIGHT + ( rand()%2 * 2 );
                                            s->y += s->dy*2;
                                        }
                                // essai de suivre le chemin si possible
                                } else {

                                        if ( pLevel->map_Direction[Centre.tileX][Centre.tileY] == VERS_LA_DROITE
                                            && pLevel->map_Info[HD.tileX+1][HD.tileY] == LIBRE
                                            && pLevel->map_Info[BD.tileX+1][BD.tileY] == LIBRE) {

                                                s->direction = RIGHT;

                                        }else if ( pLevel->map_Direction[Centre.tileX][Centre.tileY] == VERS_LA_GAUCHE
                                            && pLevel->map_Info[HG.tileX-1][HG.tileY] == LIBRE
                                            && pLevel->map_Info[BG.tileX-1][BG.tileY] == LIBRE) {

                                                s->direction = LEFT;
                                        }
                                }
                            }
                            break;
                case RIGHT :

                            s->x += s->dx;
                            if (s->in_the_map == true) {

                                // detection des bords
                                if ( HD.x >= MAP_TAILLE_X ) {
                                        s->direction = LEFT;
                                         //printf ("2 Detection bord\n");
                                }
                                // detection des obstacles
                                else if ( pLevel->map_Info[HD.tileX][HD.tileY] != LIBRE || pLevel->map_Info[BD.tileX][BD.tileY] != LIBRE ) {

                                        //printf ("2 Detection obstacle\n");

                                        if ( pLevel->map_Info[HD.tileX][HD.tileY] == LIBRE ) {

                                            s->direction = UP;

                                        } else if ( pLevel->map_Info[BD.tileX][BD.tileY] == LIBRE ) {

                                            s->direction = DOWN;

                                        } else {

                                            s->direction = UP + ( rand()%2 * 2 );
                                            s->x -= s->dx*2;
                                        }
                                // essai de suivre le chemin si possible
                                } else {

                                        if ( pLevel->map_Direction[Centre.tileX][Centre.tileY] == VERS_LE_HAUT
                                            && pLevel->map_Info[HD.tileX][HD.tileY-1] == LIBRE
                                            && pLevel->map_Info[HG.tileX][HG.tileY-1] == LIBRE) {

                                                s->direction = UP;

                                        }else if ( pLevel->map_Direction[Centre.tileX][Centre.tileY] == VERS_LE_BAS
                                            && pLevel->map_Info[BD.tileX][BD.tileY+1] == LIBRE
                                            && pLevel->map_Info[BG.tileX][BG.tileY+1] == LIBRE) {

                                                s->direction = DOWN;
                                        }
                                }
                            }
                            break;
                case DOWN :

                            s->y += s->dy;
                            if (s->in_the_map == true) {
                                // detection des bords
                                if ( BG.y >= MAP_TAILLE_Y ) {

                                        s->direction = UP;
                                        //printf ("3 Detection bord\n");
                                }
                                // detection des obstacles
                                else if ( pLevel->map_Info[BG.tileX][BG.tileY] != LIBRE || pLevel->map_Info[BD.tileX][BD.tileY] != LIBRE ) {

                                        //printf ("3 Detection obstacle\n");

                                        if ( pLevel->map_Info[BG.tileX][BG.tileY] == LIBRE ) {

                                            s->direction = LEFT;

                                        } else if ( pLevel->map_Info[BD.tileX][BD.tileY] == LIBRE ) {

                                            s->direction = RIGHT;

                                        } else {

                                            s->direction = RIGHT + ( rand()%2 * 2 );
                                            s->y -= s->dy*2;
                                        }
                                 // essai de suivre le chemin si possible
                                } else {

                                        if ( pLevel->map_Direction[Centre.tileX][Centre.tileY] == VERS_LA_DROITE
                                            && pLevel->map_Info[HD.tileX+1][HD.tileY] == LIBRE
                                            && pLevel->map_Info[BD.tileX+1][BD.tileY] == LIBRE) {

                                                s->direction = RIGHT;

                                        }else if ( pLevel->map_Direction[Centre.tileX][Centre.tileY] == VERS_LA_GAUCHE
                                            && pLevel->map_Info[HG.tileX-1][HG.tileY] == LIBRE
                                            && pLevel->map_Info[BG.tileX-1][BG.tileY] == LIBRE) {

                                                s->direction = LEFT;
                                        }
                                }
                            }
                            break;
                case LEFT :
                            s->x -= s->dx;

                            if (s->in_the_map == true) {
                                // detection des bords
                                if ( BG.x <= 0 ) {
                                        s->direction = RIGHT;
                                        //printf ("4 Detection bord\n");
                                }
                                // detection des obstacles
                                else if ( pLevel->map_Info[HG.tileX][HG.tileY] != LIBRE || pLevel->map_Info[BG.tileX][BG.tileY] != LIBRE ) {

                                        //printf ("4 Detection obstacle\n");

                                        if ( pLevel->map_Info[HG.tileX][HG.tileY] == LIBRE ) {

                                            s->direction = UP;

                                        } else if ( pLevel->map_Info[BG.tileX][BG.tileY] == LIBRE ) {

                                            s->direction = DOWN;
                                        } else {

                                            s->direction = UP + ( rand()%2 *2 );
                                            s->x += s->dx*2;
                                        }

                                // essai de suivre le chemin si possible
                                } else {

                                        if ( pLevel->map_Direction[Centre.tileX][Centre.tileY] == VERS_LE_HAUT
                                            && pLevel->map_Info[HD.tileX][HD.tileY-1] == LIBRE
                                            && pLevel->map_Info[HG.tileX][HG.tileY-1] == LIBRE) {

                                                s->direction = UP;

                                        }else if ( pLevel->map_Direction[Centre.tileX][Centre.tileY] == VERS_LE_BAS
                                            && pLevel->map_Info[BD.tileX][BD.tileY+1] == LIBRE
                                            && pLevel->map_Info[BG.tileX][BG.tileY+1] == LIBRE) {

                                                s->direction = DOWN;
                                        }
                                }
                            }
                            break;
        }


        //printf ("%d = %dx%d %dx%d %dx%d %dx%d %dx%d %dx%d\n", s->in_the_map, HG.tileX, HG.tileY, HD.tileX, HD.tileY, BG.tileX, BG.tileY, BD.tileX, BD.tileY, Centre.tileX, Centre.tileY, pLevel->cibleX, pLevel->cibleY );
        // detection de la position d'arrivé
        if (
            (HG.tileX == pLevel->cibleX && HG.tileY == pLevel->cibleY) ||
            (HD.tileX == pLevel->cibleX && HD.tileY == pLevel->cibleY) ||
            (BG.tileX == pLevel->cibleX && BG.tileY == pLevel->cibleY) ||
            (BD.tileX == pLevel->cibleX && BD.tileY == pLevel->cibleY) ||
            (Centre.tileX == pLevel->cibleX && Centre.tileY == pLevel->cibleY)
            ) {

            //printf ("Je suis arrive !!!\n");
            s->is_arrive = true;
        }


    } else if (s->is_actif == true && s->is_arrive == true ) {

        Arrive.x = pLevel->cibleX*TILE_TAILLE_X + TILE_TAILLE_X/2;
        Arrive.y = pLevel->cibleY*TILE_TAILLE_Y + TILE_TAILLE_Y/2;

                if ( s->y > Arrive.y + s->dy ) {
                        s->y -= s->dy;
                        s->direction = UP;
                }
                else if ( s->x < Arrive.x - s->dx) {
                        s->x += s->dx;
                        s->direction = RIGHT;
                }
                else if ( s->y < Arrive.y - s->dy) {
                        s->y += s->dy;
                        s->direction = DOWN;
                }
                else if ( s->x > Arrive.x + s->dx) {
                        s->x -= s->dx;
                        s->direction = LEFT;
                }
                else {
                        s->is_actif = false;
                }
    }

    //printf("%d %d - %d %d\n", s->x, (int)pLevel->cibleX, s->y, (int)pLevel->cibleY );


}
/*****************************************************************
*****************************************************************/
void anime_sprite(t_sprite*s){
	if (s->is_actif == true ) {
      s->compte_tour++;
      if (s->compte_tour > s->nb_tour) {

        s->img_current = (s->img_current + 1)%s->anim->nb_img_by_dir;

		s->compte_tour = 0;
	  }
	}
}
/*****************************************************************
*****************************************************************/
void affiche_sprite(SDL_Renderer *r, t_sprite *s){
    SDL_Rect Src;
    SDL_Rect Dst;

    Src.x = s->img_current * s->anim->tx;
    Src.y = s->direction * s->anim->ty;
    Src.w = s->anim->tx;
    Src.h = s->anim->ty;

    Dst.x = s->x - s->anim->tx/2;     // permet de center le sprite sur les coordonnées
    Dst.y = s->y - s->anim->ty/2;
    Dst.w = s->anim->tx;
    Dst.h = s->anim->ty;


    // mode transparent de l'animimation à l'arrivé
    if (s->is_actif == false && s->visible > 0 && s->time_before_ativiation == 0 ) {
        s->visible -=10 ;
    }
    if (s->visible < 0 ) {
        s->visible = 0;
    }
    SDL_SetTextureAlphaMod (s->anim->texture, s->visible);
 //   SDL_SetRenderDrawColor (r, 254, 0, 0, 50);

    // Affichage
    SDL_RenderCopy ( r, s->anim->texture , &Src, &Dst);

}
/*****************************************************************
*****************************************************************/
void place_sprite (t_sprite *p, int x, int y) {

    p->x = TILE_TAILLE_X * x;
    p->y = TILE_TAILLE_Y * y;
}
/*****************************************************************
*****************************************************************/
void destroy_sprite(t_sprite **s) {

    free(*s);
    *s = NULL;
}
/*****************************************************************
*****************************************************************/
