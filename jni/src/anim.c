#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "level.h"
#include "anim.h"


/*****************************************************************
*****************************************************************/
void init_animation(t_animation *anim, SDL_Renderer *renderer)  {


    //SDL_Surface *pSurface_tmp = SDL_LoadBMP ( anim->file );
    SDL_Surface *pSurface_tmp = IMG_Load ( anim->file );
            if(!pSurface_tmp && DEBUG) { SDL_Log( "IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    SDL_SetColorKey(pSurface_tmp, SDL_TRUE, SDL_MapRGB(pSurface_tmp->format, 255, 255, 255));

    anim->texture = SDL_CreateTextureFromSurface(renderer, pSurface_tmp);
        if(!anim->texture && DEBUG) { SDL_Log( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}

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
t_sprite*   create_Enemy( int position, int A, int B, t_animation *ANIM, float Frequence, t_system *my_system) {
                            // position --> en haut, � droite, en bas, � gauche
                            // A & B    --> d�limite la zone de cr�ation , entre A et B
                            // *ANIM    --> pointeur sur l'annimation
                            // Frequence --> Frequence de d�marrage entre chaque ennemi

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
                s->x = my_system->map_taille_x + ANIM->tx/2 ;
                s->y = (rand()%(B-A)) + A;;
                s->direction = LEFT;
                break;
        case DOWN:
                s->x = (rand()%(B-A)) + A;;
                s->y = my_system->map_taille_y + ANIM->ty/2 ;
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
	s->pv = ANIM->pv;

	if (s->time_before_ativiation == 0 ) { s->is_actif = true; }

	return s;
}
/*****************************************************************
*****************************************************************/
void avance_sprite(t_sprite *s, t_level *pLevel, t_system *my_system, int *heart_point, t_sound *sound){

    // gestion du retardement au d�marrage
    if (s->time_before_ativiation > 1 ) {
        s->time_before_ativiation--;
    }
    if (s->time_before_ativiation == 1 ) {
        s->time_before_ativiation = 0;
        s->is_actif = true;
    }

    if (s->is_actif == true) {

                t_pos HD;      // postion en haut � droite
                t_pos HG;      // postion en haut � gauche
                t_pos BD;      // postion en bas � droite
                t_pos BG;      // postion en bas � gauche
                t_pos Centre;
                t_pos Arrive;

                srand(time(NULL));



                if (s->is_arrive == false ) {


                    // les ccordonn�es du sprite correspondent � son centre
                    // calcul des coordonn�es des quatres coins
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

                    //if (DEBUG) {SDL_Log("Fred DEBUG - Pos : %d x %d - %d x %d\n", Centre.x, Centre.y, Centre.tileX, Centre.tileY );}

                    // permet de demarrer en dehors de la map
                    if (s->in_the_map == false) {
                        if (   HD.x<my_system->map_taille_x && HG.x<my_system->map_taille_x && BD.x<my_system->map_taille_x && BG.x<my_system->map_taille_x
                            && HD.y<my_system->map_taille_y && HG.y<my_system->map_taille_y && BD.y<my_system->map_taille_y && BG.y<my_system->map_taille_y
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
                                                    //if (DEBUG){SDL_Log ("1 Detection bord\n");}
                                            }
                                            // detection des obstacles
                                            else if ( pLevel->map_Info[HG.tileX][HG.tileY] != LIBRE || pLevel->map_Info[HD.tileX][HD.tileY] != LIBRE ) {
                                                    //if (DEBUG){SDL_Log ("1 Detection obstacle\n");}
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
                                            if ( HD.x >= my_system->map_taille_x ) {
                                                    s->direction = LEFT;
                                                     //if (DEBUG){SDL_Log ("2 Detection bord\n");}
                                            }
                                            // detection des obstacles
                                            else if ( pLevel->map_Info[HD.tileX][HD.tileY] != LIBRE || pLevel->map_Info[BD.tileX][BD.tileY] != LIBRE ) {

                                                    //if (DEBUG){SDL_Log ("2 Detection obstacle\n");}

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
                                            if ( BG.y >= my_system->map_taille_y ) {

                                                    s->direction = UP;
                                                    //if (DEBUG){SDL_Log ("3 Detection bord\n");}
                                            }
                                            // detection des obstacles
                                            else if ( pLevel->map_Info[BG.tileX][BG.tileY] != LIBRE || pLevel->map_Info[BD.tileX][BD.tileY] != LIBRE ) {

                                                    //if (DEBUG){SDL_Log ("3 Detection obstacle\n");}

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
                                                    //if (DEBUG){SDL_Log ("4 Detection bord\n");}
                                            }
                                            // detection des obstacles
                                            else if ( pLevel->map_Info[HG.tileX][HG.tileY] != LIBRE || pLevel->map_Info[BG.tileX][BG.tileY] != LIBRE ) {

                                                    //if (DEBUG){SDL_Log ("4 Detection obstacle\n");}

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


                    //if (DEBUG){SDL_Log ("%d = %dx%d %dx%d %dx%d %dx%d %dx%d %dx%d\n", s->in_the_map, HG.tileX, HG.tileY, HD.tileX, HD.tileY, BG.tileX, BG.tileY, BD.tileX, BD.tileY, Centre.tileX, Centre.tileY, pLevel->cibleX, pLevel->cibleY );}
                    // detection de la position d'arriv�
                    if (
                        (HG.tileX == pLevel->cibleX && HG.tileY == pLevel->cibleY) ||
                        (HD.tileX == pLevel->cibleX && HD.tileY == pLevel->cibleY) ||
                        (BG.tileX == pLevel->cibleX && BG.tileY == pLevel->cibleY) ||
                        (BD.tileX == pLevel->cibleX && BD.tileY == pLevel->cibleY) ||
                        (Centre.tileX == pLevel->cibleX && Centre.tileY == pLevel->cibleY)
                        ) {

                        if (DEBUG){SDL_Log ("Je suis arrive !!!\n");}
                        s->is_arrive = true;

                        Mix_PlayChannel( -1, sound->Oh_non, 0 );


                        if (*heart_point > 0 ) { *heart_point -= 1; }
                    }


                } else if (s->is_arrive == true ) {

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
    }
    //if (DEBUG){SDL_Log("%d %d - %d %d\n", s->x, (int)pLevel->cibleX, s->y, (int)pLevel->cibleY );}


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
void anime_sprite_once(t_sprite*s){

	if (s->is_actif == true ) {

        //  if (DEBUG) {SDL_Log("Fred DEBUG - ANIM compte tour: %d - Img: %d\n", s->compte_tour,s->img_current);}

          s->compte_tour++;
          if (s->compte_tour > s->nb_tour) {

                s->img_current++;

                if(s->img_current > s->anim->nb_img_by_dir) {

                    s->is_actif = false;
                    s->visible  = 0;
                }

                s->compte_tour = 0;
          }
        }
}
/*****************************************************************
*****************************************************************/
void affiche_sprite(SDL_Renderer *r, t_sprite *s){

    if ( s->visible > 0 ) {

            SDL_Rect Src;
            SDL_Rect Dst;

            Src.x = s->img_current * s->anim->tx;
            Src.y = s->direction * s->anim->ty;
            Src.w = s->anim->tx;
            Src.h = s->anim->ty;

            Dst.x = s->x - s->anim->tx/2;     // permet de center le sprite sur les coordonn�es
            Dst.y = s->y - s->anim->ty/2;
            Dst.w = s->anim->tx;
            Dst.h = s->anim->ty;


            // mode transparent de l'animimation � l'arriv�
            if (s->is_actif == false && s->time_before_ativiation == 0 ) {
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
