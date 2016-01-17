#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "type_system.h"
#include "menu.h"


/*****************************************************************
*****************************************************************/
void init_menu      (t_menu *my_menu, SDL_Renderer *pRenderer) {

    SDL_Surface *pSurface_tmp;

    my_menu->exit    = false;
    my_menu->start   = false;
    my_menu->restart = false;
    my_menu->resume  = false;

    /** FICHIER background **/
    pSurface_tmp                    = IMG_Load (MENU_IMG_BACKGROUND);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->img_background         = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->img_background && DEBUG) {  SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}


    /** FICHIER bouton START**/
    pSurface_tmp                    = IMG_Load (MENU_IMG_START);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_start.img       = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_start.img && DEBUG){ SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_start.w         = pSurface_tmp->w;
    my_menu->button_start.h         = pSurface_tmp->h;

    pSurface_tmp                    = IMG_Load (MENU_IMG_START_P);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_start_p.img     = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_start_p.img && DEBUG){ SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_start_p.w       = pSurface_tmp->w;
    my_menu->button_start_p.h       = pSurface_tmp->h;


    /** FICHIER bouton RESTART**/
    pSurface_tmp                    = IMG_Load (MENU_IMG_RESTART);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_restart.img     = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_restart.img && DEBUG){ SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_restart.w       = pSurface_tmp->w;
    my_menu->button_restart.h       = pSurface_tmp->h;

    pSurface_tmp                    = IMG_Load (MENU_IMG_RESTART_P);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_restart_p.img   = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_restart_p.img && DEBUG){ SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_restart_p.w     = pSurface_tmp->w;
    my_menu->button_restart_p.h     = pSurface_tmp->h;


    /** FICHIER bouton RESUME**/
    pSurface_tmp                    = IMG_Load (MENU_IMG_RESUME);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_resume.img      = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_resume.img && DEBUG){ SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_resume.w        = pSurface_tmp->w;
    my_menu->button_resume.h        = pSurface_tmp->h;

    pSurface_tmp                    = IMG_Load (MENU_IMG_RESUME_P);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_resume_p.img    = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_resume_p.img && DEBUG){ SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_resume_p.w      = pSurface_tmp->w;
    my_menu->button_resume_p.h      = pSurface_tmp->h;


    /** FICHIER bouton EXIT**/
    pSurface_tmp                    = IMG_Load (MENU_IMG_EXIT);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_exit.img        = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_exit.img && DEBUG){  SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_exit.w          = pSurface_tmp->w;
    my_menu->button_exit.h          = pSurface_tmp->h;

    pSurface_tmp                    = IMG_Load (MENU_IMG_EXIT_P);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_exit_p.img      = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_exit_p.img && DEBUG){ SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_exit_p.w        = pSurface_tmp->w;
    my_menu->button_exit_p.h        = pSurface_tmp->h;




    SDL_FreeSurface(pSurface_tmp);
}
/*****************************************************************
*****************************************************************/
void affiche_menu   (t_menu *menu, SDL_Renderer *pRenderer, bool flag_game_started, t_system *my_system) {

    bool exit               = false;
    int current_mouse_x     = 0;
    int current_mouse_y     = 0;
    bool flag_event_down    = false;
    bool flag_event_up      = false;

    int  sleep;


    SDL_Event event;

    if (!flag_game_started) {
        menu->button_start.enable      = true;
        menu->button_restart.enable    = false;
        menu->button_resume.enable     = false;
        menu->button_exit.enable       = true;

        menu->button_start.x    = (my_system->map_taille_x - menu->button_start.w)/2 ;
        menu->button_start.y    = (my_system->map_taille_y - 60 - 2*menu->button_start.h)/2;
        menu->button_exit.x     = (my_system->map_taille_x - menu->button_exit.w)/2;
        menu->button_exit.y     = menu->button_start.y + menu->button_start.h + 30;
        menu->button_start_p.x    = menu->button_start.x;
        menu->button_start_p.y    = menu->button_start.y;
        menu->button_exit_p.x     = menu->button_exit.x;
        menu->button_exit_p.y     = menu->button_exit.y;

    } else {
        menu->button_start.enable       = false;
        menu->button_restart.enable     = true;
        menu->button_resume.enable      = true;
        menu->button_exit.enable        = true;

        menu->button_restart.x  = (my_system->map_taille_x - menu->button_restart.w)/2;
        menu->button_restart.y  = (my_system->map_taille_y - 60 - 3*menu->button_restart.h)/2;;
        menu->button_resume.x   = (my_system->map_taille_x - menu->button_resume.w)/2;
        menu->button_resume.y    = menu->button_restart.y + menu->button_restart.h + 30;
        menu->button_exit.x     = (my_system->map_taille_x - menu->button_exit.w)/2;
        menu->button_exit.y     = menu->button_resume.y + menu->button_resume.h + 30;

        menu->button_restart_p.x  = menu->button_restart.x;
        menu->button_restart_p.y  = menu->button_restart.y;
        menu->button_resume_p.x   = menu->button_resume.x;
        menu->button_resume_p.y   = menu->button_resume.y;
        menu->button_exit_p.x     = menu->button_exit.x;
        menu->button_exit_p.y     = menu->button_exit.y;

    }


    while (!exit) {

            /******************************************************************************************************************
                                                        AFFICHAGE
            *******************************************************************************************************************/
            SDL_RenderClear     (pRenderer);

            SDL_RenderCopy      (pRenderer, menu->img_background, NULL, NULL);

            if (menu->button_start.enable) {
                    affiche_button (&menu->button_start, pRenderer);
                    if (   current_mouse_x > menu->button_start.x && current_mouse_x < menu->button_start.x + menu->button_start.w
                        && current_mouse_y > menu->button_start.y && current_mouse_y < menu->button_start.y + menu->button_start.h
                        ) {
                            if      (flag_event_down)  { affiche_button (&menu->button_start_p, pRenderer); }
                            else if (flag_event_up)    { menu->start = true; exit = true; }
                        }
            }
            if (menu->button_restart.enable) {
                    affiche_button (&menu->button_restart, pRenderer);
                    if (   current_mouse_x > menu->button_restart.x && current_mouse_x < menu->button_restart.x + menu->button_restart.w
                        && current_mouse_y > menu->button_restart.y && current_mouse_y < menu->button_restart.y + menu->button_restart.h
                        ) {
                            if      (flag_event_down)  { affiche_button (&menu->button_restart_p, pRenderer); }
                            else if (flag_event_up)    { menu->restart = true; exit = true; }
                        }
            }
            if (menu->button_resume.enable) {
                    affiche_button (&menu->button_resume, pRenderer);
                    if (   current_mouse_x > menu->button_resume.x && current_mouse_x < menu->button_resume.x + menu->button_resume.w
                        && current_mouse_y > menu->button_resume.y && current_mouse_y < menu->button_resume.y + menu->button_resume.h
                        ) {
                            if      (flag_event_down)  { affiche_button (&menu->button_resume_p, pRenderer); }
                            else if (flag_event_up)    { menu->resume = true; exit = true; }
                        }
            }
            if (menu->button_exit.enable) {
                    affiche_button (&menu->button_exit, pRenderer);
                    if (   current_mouse_x > menu->button_exit.x && current_mouse_x < menu->button_exit.x + menu->button_exit.w
                        && current_mouse_y > menu->button_exit.y && current_mouse_y < menu->button_exit.y + menu->button_exit.h
                        ) {
                            if      (flag_event_down)  { affiche_button (&menu->button_exit_p, pRenderer); }
                            else if (flag_event_up)    { menu->exit = true; exit = true; }
                        }
            }

            flag_event_up = false;

            SDL_RenderPresent   (pRenderer);


            /******************************************************************************************************************
                                                        GESTION DES EVENEMENTS
            *******************************************************************************************************************/
            while (SDL_PollEvent(&event)) {

                switch (event.type){

                    case SDL_QUIT:
                        exit = true;
                        menu->exit = true;
                        break;

                    case SDL_KEYDOWN:
                        switch( event.key.keysym.sym ){
                            case SDLK_ESCAPE:
                                exit = true;
                                menu->exit = true;
                                break;
                            case SDLK_AC_BACK:
                                exit = true;
                                menu->exit = true;
                                break;
                        }
                        break;
                    /***************************************************************************   SOURIS  **/
#if __WIN32__
                    case SDL_MOUSEBUTTONDOWN :
                        SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                        flag_event_down = true;
                        break;

                    case SDL_MOUSEMOTION :
                        SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                        break;

                    case SDL_MOUSEBUTTONUP :
                        SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                        flag_event_down = false;
                        flag_event_up   = true;
                        break;
#endif
                    /***************************************************************************   FINGER  **/
                    case SDL_FINGERDOWN:
                        current_mouse_x = (int)(event.tfinger.x * my_system->map_taille_x);
                        current_mouse_y = (int)(event.tfinger.y * my_system->map_taille_y);
                        flag_event_down = true;
                        break;

                    case SDL_FINGERMOTION :
                        current_mouse_x = (int)(event.tfinger.x * my_system->map_taille_x);
                        current_mouse_y = (int)(event.tfinger.y * my_system->map_taille_y);
                        break;

                    case SDL_FINGERUP :
                        current_mouse_x = (int)(event.tfinger.x * my_system->map_taille_x);
                        current_mouse_y = (int)(event.tfinger.y * my_system->map_taille_y);
                        flag_event_down = false;
                        flag_event_up   = true;
                        break;

                }
            }


            sleep = (1000 / GAME_FPS);
            SDL_Delay( sleep );

    }
}
/*****************************************************************
*****************************************************************/
void affiche_button (t_button *button, SDL_Renderer *pRenderer){

    SDL_Rect Src;
    SDL_Rect Dst;

    Src.x = 0;
    Src.y = 0;
    Src.w = button->w;
    Src.h = button->h;

    Dst.x = button->x;
    Dst.y = button->y;
    Dst.w = Src.w;
    Dst.h = Src.h;

    SDL_RenderCopy      ( pRenderer, button->img , &Src, &Dst);

}
