#ifndef AFFICHAGE_TEXTE_H_INCLUDED
#define AFFICHAGE_TEXTE_H_INCLUDED



typedef struct {


    int             level;
    int             NbEnemy;


    TTF_Font        *police;

    SDL_Texture     *pTexture_Score;
    SDL_Rect        Score_position_src;
    SDL_Rect        Score_position_dst;

} t_score;

void init_score       (SDL_Renderer *pRenderer, t_score *s );
void affiche_score    (SDL_Renderer *pRenderer, t_score *s );
void clear_score      (t_score *s);




#endif // AFFICHAGE_TEXTE_H_INCLUDED
