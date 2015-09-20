#include <SDL2/SDL.h>
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
t_sprite *init_sprite(int posx, int posy,
	int dx, int dy,
	int nbtour, int dir,
	t_animation *a,
	bool actif,
	int time_before_ativiation)
{
	t_sprite *s = (t_sprite*)malloc(sizeof(t_sprite));
	s->x = posx;
	s->y = posy;
	s->dx = dx;
	s->dy = dy;
	s->img_current = 0;
	s->compte_tour = 0;
	s->nb_tour = nbtour;
	s->direction = dir;
	s->anim = a;
	s->is_actif = actif;
	s->is_arrive = false;
	s->time_before_ativiation = time_before_ativiation;
	s->visible = 255;
	return s;
}
/*****************************************************************
*****************************************************************/
void avance_sprite(t_sprite *s, t_level *pLevel)
{

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

        Centre.x = s->x / TILE_TAILLE_X;
        Centre.y = s->y / TILE_TAILLE_Y;



        switch (s->direction) {
                case UP :
                                s->y -= s->dy;

                                // detection des bords
                                if ( HD.y <= 0 ) {
                                        s->direction = DOWN;
                                        printf ("1 Detection bord\n");
                                }
                                // detection des obstacles
                                else if ( pLevel->map_Info[HG.tileX][HG.tileY] == OBSTACLE || pLevel->map_Info[HD.tileX][HD.tileY] == OBSTACLE ) {
                                        printf ("1 Detection obstacle\n");
                                        if ( pLevel->map_Info[HG.tileX][HG.tileY] == LIBRE ) {

                                            s->direction = LEFT;

                                        } else if ( pLevel->map_Info[HD.tileX][HD.tileY] == LIBRE ) {

                                            s->direction = RIGHT;

                                        } else {

                                            s->direction = RIGHT + ( rand()%2 * 2 );
                                            s->y += s->dy*2;
                                        }
                                // essai de suivre le chemin si possible
                                } else  {

                                        if ( pLevel->map_Direction[Centre.x][Centre.y] == VERS_LA_DROITE
                                            && pLevel->map_Info[HD.tileX+1][HD.tileY] != OBSTACLE
                                            && pLevel->map_Info[BD.tileX+1][BD.tileY] != OBSTACLE) {

                                                s->direction = RIGHT;

                                        }else if ( pLevel->map_Direction[Centre.x][Centre.y] == VERS_LA_GAUCHE
                                            && pLevel->map_Info[HG.tileX-1][HG.tileY] != OBSTACLE
                                            && pLevel->map_Info[BG.tileX-1][BG.tileY] != OBSTACLE) {

                                                s->direction = LEFT;
                                        }
                                }
                                break;
                case RIGHT :
                                s->x += s->dx;

                                // detection des bords
                                if ( HD.x >= MAP_TAILLE_X ) {
                                        s->direction = LEFT;
                                         printf ("2 Detection bord\n");
                                }
                                // detection des obstacles
                                else if ( pLevel->map_Info[HD.tileX][HD.tileY] == OBSTACLE || pLevel->map_Info[BD.tileX][BD.tileY] == OBSTACLE ) {

                                        printf ("2 Detection obstacle\n");

                                        if ( pLevel->map_Info[HD.tileX][HD.tileY] == LIBRE ) {

                                            s->direction = UP;

                                        } else if ( pLevel->map_Info[BD.tileX][BD.tileY] == LIBRE ) {

                                            s->direction = DOWN;

                                        } else {

                                            s->direction = UP + ( rand()%2 * 2 );
                                            s->x -= s->dx*2;
                                        }
                                // essai de suivre le chemin si possible
                                } else  {

                                        if ( pLevel->map_Direction[Centre.x][Centre.y] == VERS_LE_HAUT
                                            && pLevel->map_Info[HD.tileX][HD.tileY-1] != OBSTACLE
                                            && pLevel->map_Info[HG.tileX][HG.tileY-1] != OBSTACLE) {

                                                s->direction = UP;

                                        }else if ( pLevel->map_Direction[Centre.x][Centre.y] == VERS_LE_BAS
                                            && pLevel->map_Info[BD.tileX][BD.tileY+1] != OBSTACLE
                                            && pLevel->map_Info[BG.tileX][BG.tileY+1] != OBSTACLE) {

                                                s->direction = DOWN;
                                        }
                                }
                                break;
                case DOWN :
                                s->y += s->dy;

                                // detection des bords
                                if ( BG.y >= MAP_TAILLE_Y ) {

                                        s->direction = UP;
                                        printf ("3 Detection bord\n");
                                }
                                // detection des obstacles
                                else if ( pLevel->map_Info[BG.tileX][BG.tileY] == OBSTACLE || pLevel->map_Info[BD.tileX][BD.tileY] == OBSTACLE ) {

                                        printf ("3 Detection obstacle\n");

                                        if ( pLevel->map_Info[BG.tileX][BG.tileY] == LIBRE ) {

                                            s->direction = LEFT;

                                        } else if ( pLevel->map_Info[BD.tileX][BD.tileY] == LIBRE ) {

                                            s->direction = RIGHT;

                                        } else {

                                            s->direction = RIGHT + ( rand()%2 * 2 );
                                            s->y -= s->dy*2;
                                        }
                                 // essai de suivre le chemin si possible
                                } else  {

                                        if ( pLevel->map_Direction[Centre.x][Centre.y] == VERS_LA_DROITE
                                            && pLevel->map_Info[HD.tileX+1][HD.tileY] != OBSTACLE
                                            && pLevel->map_Info[BD.tileX+1][BD.tileY] != OBSTACLE) {

                                                s->direction = RIGHT;

                                        }else if ( pLevel->map_Direction[Centre.x][Centre.y] == VERS_LA_GAUCHE
                                            && pLevel->map_Info[HG.tileX-1][HG.tileY] != OBSTACLE
                                            && pLevel->map_Info[BG.tileX-1][BG.tileY] != OBSTACLE) {

                                                s->direction = LEFT;
                                        }
                                }
                                break;
                case LEFT :
                                s->x -= s->dx;

                                // detection des bords
                                if ( BG.x <= 0 ) {
                                        s->direction = RIGHT;
                                        printf ("4 Detection bord\n");
                                }
                                // detection des obstacles
                                else if ( pLevel->map_Info[HG.tileX][HG.tileY] == OBSTACLE || pLevel->map_Info[BG.tileX][BG.tileY] == OBSTACLE ) {

                                        printf ("4 Detection obstacle\n");

                                        if ( pLevel->map_Info[HG.tileX][HG.tileY] == LIBRE ) {

                                            s->direction = UP;

                                        } else if ( pLevel->map_Info[BG.tileX][BG.tileY] == LIBRE ) {

                                            s->direction = DOWN;
                                        } else {

                                            s->direction = UP + ( rand()%2 *2 );
                                            s->x += s->dx*2;
                                        }

                                // essai de suivre le chemin si possible
                                } else  {

                                        if ( pLevel->map_Direction[Centre.x][Centre.y] == VERS_LE_HAUT
                                            && pLevel->map_Info[HD.tileX][HD.tileY-1] != OBSTACLE
                                            && pLevel->map_Info[HG.tileX][HG.tileY-1] != OBSTACLE) {

                                                s->direction = RIGHT;

                                        }else if ( pLevel->map_Direction[Centre.x][Centre.y] == VERS_LE_BAS
                                            && pLevel->map_Info[BD.tileX][BD.tileY+1] != OBSTACLE
                                            && pLevel->map_Info[BG.tileX][BG.tileY+1] != OBSTACLE) {

                                                s->direction = LEFT;
                                        }
                                }
                                break;
        }

        // detection de la position d'arrivé
        if (
            (HG.tileX == pLevel->cibleX && HG.tileY == pLevel->cibleY) ||
            (HD.tileX == pLevel->cibleX && HD.tileY == pLevel->cibleY) ||
            (BG.tileX == pLevel->cibleX && BG.tileY == pLevel->cibleY) ||
            (BD.tileX == pLevel->cibleX && BD.tileY == pLevel->cibleY)
            ) {

            printf ("Je suis arrive !!!\n");
            s->is_arrive = true;
        }


    } else if (s->is_actif == true && s->is_arrive == true ) {

        Arrive.x = pLevel->cibleX*TILE_TAILLE_X + TILE_TAILLE_X/2;
        Arrive.y = pLevel->cibleY*TILE_TAILLE_Y + TILE_TAILLE_Y/2;

                if ( s->y > Arrive.y + s->dy ) {
                        s->y -= s->dy;
                        s->direction = UP;
                        printf ("A1\n");
                }
                else if ( s->x < Arrive.x - s->dx) {
                        s->x += s->dx;
                        s->direction = RIGHT;
                        printf ("A2\n");
                }
                else if ( s->y < Arrive.y - s->dy) {
                        s->y += s->dy;
                        s->direction = DOWN;
                        printf ("A3\n");
                }
                else if ( s->x > Arrive.x + s->dx) {
                        s->x -= s->dx;
                        s->direction = LEFT;
                        printf ("A1\n");
                }
                else {
                        s->is_actif = false;
                }
    }

    //printf("%d %d - %d %d\n", s->x, (int)pLevel->cibleX, s->y, (int)pLevel->cibleY );


}
/*****************************************************************
*****************************************************************/
void anime_sprite(t_sprite*s)
{
	if (s->is_actif == true ) {
      if (++s->compte_tour > s->nb_tour) {

        s->img_current = (s->img_current + 1)%s->anim->nb_img_by_dir;

		s->compte_tour = 0;
	  }
	}
}
/*****************************************************************
*****************************************************************/
void affiche_sprite(SDL_Renderer *r, t_sprite *s)
{
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

    // Affichage
    SDL_RenderCopy ( r, s->anim->texture , &Src, &Dst);

}
/*****************************************************************
*****************************************************************/
void destroy_sprite(t_sprite **s)
{

    free(*s);
    *s = NULL;
}
/*****************************************************************
*****************************************************************/
void place_sprite (t_sprite *p, int x, int y) {

    p->x = TILE_TAILLE_X * x;
    p->y = TILE_TAILLE_Y * y;
}
/*****************************************************************
*****************************************************************/


