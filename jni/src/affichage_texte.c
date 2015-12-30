#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "affichage_texte.h"



/*****************************************************************
*****************************************************************/
void init_score       (SDL_Renderer *pRenderer, t_score *s ) {


    SDL_Surface *s_texte = NULL;
    SDL_Color couleur = {100, 50, 0, 0};


    char texte[256];
    sprintf(texte,"Level %d - Enemy:%d   Score:0", s->level, s->NbEnemy);

    s_texte = TTF_RenderText_Blended(s->police, texte, couleur);
    s->Score_position_src.x = 0;
    s->Score_position_src.y = 0;
    s->Score_position_src.h = s_texte->h;
    s->Score_position_src.w = s_texte->w;
    s->Score_position_dst.x = MAP_TAILLE_X -  s_texte->w - 50;
    s->Score_position_dst.y = 5;
    s->Score_position_dst.h = s_texte->h;
    s->Score_position_dst.w = s_texte->w;

    // Création de la texture pour le texte
    SDL_DestroyTexture(s->pTexture_Score);
    s->pTexture_Score = SDL_CreateTextureFromSurface(pRenderer, s_texte);
    if(!s->pTexture_Score) {                  printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(-1);}


    SDL_FreeSurface(s_texte);

}
/*****************************************************************
*****************************************************************/
void affiche_score          (SDL_Renderer *pRenderer, t_score *s ) {

       SDL_RenderCopy      (pRenderer, s->pTexture_Score,  &s->Score_position_src, &s->Score_position_dst);

}
/*****************************************************************
*****************************************************************/
void clear_score            (t_score *s) {

    SDL_DestroyTexture(s->pTexture_Score);

}


