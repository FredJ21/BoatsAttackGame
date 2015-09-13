#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
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
	s->actif = actif;
	s->time_before_ativiation = time_before_ativiation;

	return s;
}
/*****************************************************************
*****************************************************************/
void avance_sprite(t_sprite*s)
{
    // gestion du retardement au démarrage
    if (s->time_before_ativiation > 1 ) {
        s->time_before_ativiation--;
    }
    if (s->time_before_ativiation == 1 ) {
        s->time_before_ativiation = 0;
        s->actif = true;
    }


    if (s->actif == true ) {
      switch (s->direction) {
        case 0 :                    // vers le haut
                s->y -= s->dy;
                break;
        case 1 :                    // vers la droite
                s->x += s->dy;
                break;
        case 2 :                    // vers le bas
                s->y += s->dy;
                break;
        case 3 :                    // vers la gauche
                s->x -= s->dx;
                break;
      }
    }

}
/*****************************************************************
*****************************************************************/
void anime_sprite(t_sprite*s)
{
	if (s->actif == true ) {
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

    Dst.x = s->x - s->anim->tx/2;     // permet de center le sprite sur les coordonées
    Dst.y = s->y - s->anim->ty/2;
    Dst.w = s->anim->tx;
    Dst.h = s->anim->ty;

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
/*****************************************************************
*****************************************************************/
void place_sprite (t_sprite *p, int x, int y) {

    p->x = TILE_TAILLE_X * x;
    p->y = TILE_TAILLE_Y * y;
}


