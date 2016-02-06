#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "type_sound.h"

typedef struct {

    SDL_Texture     *img;
    int             w;          // weith
    int             h;          // height
    int             x;          // position en x
    int             y;          // position en y
    bool        enable;

} t_button;

typedef struct {

    TTF_Font *police_level_titre;

    SDL_Texture     *img_background;

    t_button    button_start;
    t_button    button_restart;
    t_button    button_resume;
    t_button    button_exit;

    t_button    button_start_p;
    t_button    button_restart_p;
    t_button    button_resume_p;
    t_button    button_exit_p;

    bool    exit;               // vrai à la selection d'une touche
    bool    start;
    bool    restart;
    bool    resume;

    t_button        menu_level_title;
    t_button        button_menu_level_Red;         // bouton rouge
    t_button        button_menu_level_Blue;         // bouton bleu
    t_button        button_menu_level_Grey;         // bouton gris

} t_menu;


void        init_menu               (t_menu *menu, SDL_Renderer *pRenderer);
void        affiche_menu            (t_menu *menu, SDL_Renderer *pRenderer, bool flag_game_started, t_system *system, t_sound *sound);
void        affiche_menu_level      (t_menu *menu, t_system *my_system, SDL_Renderer *pRenderer, int *current_level, int *last_level, bool *flag_fin, t_sound *sound);
void        affiche_button          (t_button *button, SDL_Renderer *pRenderer);
void        affiche_button_number   (t_button *button, int number, TTF_Font *police, int color_txt, SDL_Renderer *pRenderer);

#endif // MENU_H_INCLUDED
