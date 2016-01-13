#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef struct {

    SDL_Texture     *img;
    int             width;      // largeur
    int             heigth;     // hauteur
    int             x;          // position en x
    int             y;          // position en y

} t_button;

typedef struct {

    SDL_Texture     *img_background;

    t_button    button_start;
    t_button    button_restart;
    t_button    button_resume;
    t_button    button_exit;

    bool    exit;           // vrai à la selection d'une touche
    bool    start;
    bool    restart;
    bool    resume;

} t_menu;


void        affiche_menu            ();
void        affiche_button          ();

#endif // MENU_H_INCLUDED
