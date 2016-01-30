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

    // pour le titre de chaque level
    my_menu->police_level_titre = TTF_OpenFont(POLICE_LEVEL_TITRE, POLICE_LEVEL_BUTTON_SIZE);
    if(!my_menu->police_level_titre && DEBUG ) {  SDL_Log( "TTF_OpenFont ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}


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


    /** FICHIER TITRE LEVEL **/
    pSurface_tmp                    = IMG_Load (MENU_IMG_LEVEL_TITLE);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->menu_level_title.img = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->menu_level_title.img && DEBUG){  SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->menu_level_title.w    = pSurface_tmp->w;
    my_menu->menu_level_title.h    = pSurface_tmp->h;

    /** FICHIER bouttons LEVEL **/
    pSurface_tmp                    = IMG_Load (MENU_IMG_BUTTON1_LEVEL);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_menu_level_Red.img = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_menu_level_Red.img && DEBUG){  SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_menu_level_Red.w    = pSurface_tmp->w;
    my_menu->button_menu_level_Red.h    = pSurface_tmp->h;

    pSurface_tmp                    = IMG_Load (MENU_IMG_BUTTON2_LEVEL);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_menu_level_Blue.img  = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_menu_level_Red.img && DEBUG){  SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_menu_level_Blue.w    = pSurface_tmp->w;
    my_menu->button_menu_level_Blue.h    = pSurface_tmp->h;

    pSurface_tmp                    = IMG_Load (MENU_IMG_BUTTON3_LEVEL);
    if(!pSurface_tmp && DEBUG) {             SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"IMG_Load ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_menu_level_Grey.img  = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_menu_level_Red.img && DEBUG){  SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,"SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}
    my_menu->button_menu_level_Grey.w    = pSurface_tmp->w;
    my_menu->button_menu_level_Grey.h    = pSurface_tmp->h;




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
void affiche_menu_level       (t_menu *menu, t_system *my_system, SDL_Renderer *pRenderer, int *current_level, int *last_level) {


    int a, b, level, x, y, xx, yy;

    bool exit               = false;
    int current_mouse_x     = 0;
    int current_mouse_y     = 0;
    bool flag_event_down    = false;
    bool flag_event_up      = false;

    bool flag_button_red    = true;
    int flash_button_count  = 0;
    int flash_button_max    = 3;

    int  sleep;


    int nb_button_x     = 10;
    int nb_button_y     = 5;
    int entre_button    =  17;
    int marge_x         =  (MAP_TAILLE_X_160 - (nb_button_x * (menu->button_menu_level_Red.w + entre_button )))/2;
    int marge_y         =  90;


    menu->menu_level_title.x    = (MAP_TAILLE_X_160 - menu->menu_level_title.w)/2;
    menu->menu_level_title.y    = 10;

    SDL_Event event;


    while (!exit) {

            /******************************************************************************************************************
                                                        AFFICHAGE
            *******************************************************************************************************************/
            SDL_RenderClear     (pRenderer);

            SDL_RenderCopy      (pRenderer, menu->img_background, NULL, NULL);
            affiche_button (&menu->menu_level_title, pRenderer);

            level = 0;
            for (b=0; b<nb_button_y; b++) {
                for (a=0; a<nb_button_x; a++) {

                    x = marge_x + (menu->button_menu_level_Red.w + entre_button)*a;
                    y = marge_y + (menu->button_menu_level_Red.h + entre_button)*b;
                    xx = x + menu->button_menu_level_Red.w;
                    yy = y + menu->button_menu_level_Red.h;

                    if ( level <= *last_level && flag_event_up && current_mouse_x > x && current_mouse_x < xx && current_mouse_y > y && current_mouse_y < yy ) {

                            *current_level = level;
                            exit = true;

                            menu->button_menu_level_Red.x = x ;
                            menu->button_menu_level_Red.y = y ;
                            affiche_button_number (&menu->button_menu_level_Red, (a+1)+b*10, menu->police_level_titre, 1, pRenderer);      // affiche bouton rouge

                    } else if (flag_event_down && level < *last_level && current_mouse_x > x && current_mouse_x < xx && current_mouse_y > y && current_mouse_y < yy)  {
                            menu->button_menu_level_Red.x = x ;
                            menu->button_menu_level_Red.y = y ;
                            affiche_button_number (&menu->button_menu_level_Red, (a+1)+b*10, menu->police_level_titre, 1, pRenderer);      // affiche bouton rouge

                    } else if ( level == *last_level ) {
                            if (flag_button_red) {
                                menu->button_menu_level_Red.x = x ;
                                menu->button_menu_level_Red.y = y ;
                                affiche_button_number (&menu->button_menu_level_Red, (a+1)+b*10, menu->police_level_titre, 1, pRenderer);      // affiche bouton rouge
                            } else {
                                menu->button_menu_level_Blue.x = x ;
                                menu->button_menu_level_Blue.y = y ;
                                affiche_button_number (&menu->button_menu_level_Blue, (a+1)+b*10, menu->police_level_titre, 0, pRenderer);      // affiche  bouton bleu
                            }


                    } else if ( level <= *last_level ) {
                            menu->button_menu_level_Blue.x = x;
                            menu->button_menu_level_Blue.y = y;
                            affiche_button_number (&menu->button_menu_level_Blue, (a+1)+b*10, menu->police_level_titre, 0, pRenderer);      // affiche  bouton bleu

                    } else {
                            menu->button_menu_level_Grey.x = x ;
                            menu->button_menu_level_Grey.y = y ;
                            affiche_button_number (&menu->button_menu_level_Grey, (a+1)+b*10, menu->police_level_titre, 2, pRenderer);      // affiche bouton gris
                    }

                    level++;
                }
            }


            SDL_RenderPresent   (pRenderer);

            /******************************************************************************************************************
                                                        GESTION DES EVENEMENTS
            *******************************************************************************************************************/
            flag_event_up = false;

            while (SDL_PollEvent(&event)) {

                switch (event.type){

                    case SDL_QUIT:
                        exit = true;
                        break;

                    case SDL_KEYDOWN:
                        switch( event.key.keysym.sym ){
                            case SDLK_ESCAPE:
                                exit = true;
                                break;
                            case SDLK_AC_BACK:
                                exit = true;
                                break;
                        }
                        break;
                    /***************************************************************************   SOURIS  **/
#if __WIN32__
                    case SDL_MOUSEBUTTONDOWN :
                        SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                        flag_event_up = false;
                        flag_event_down = true;
                        break;

                    case SDL_MOUSEMOTION :
                        SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                        break;

                    case SDL_MOUSEBUTTONUP :
                        SDL_GetMouseState( &current_mouse_x, &current_mouse_y );
                        flag_event_up = true;
                        flag_event_down = false;
                        break;
#endif
                    /***************************************************************************   FINGER  **/
                    case SDL_FINGERDOWN:
                        current_mouse_x = (int)(event.tfinger.x * my_system->map_taille_x);
                        current_mouse_y = (int)(event.tfinger.y * my_system->map_taille_y);
                        flag_event_down = true;
                        flag_event_up = false;
                        break;

                    case SDL_FINGERMOTION :
                        current_mouse_x = (int)(event.tfinger.x * my_system->map_taille_x);
                        current_mouse_y = (int)(event.tfinger.y * my_system->map_taille_y);
                        break;

                    case SDL_FINGERUP :
                        current_mouse_x = (int)(event.tfinger.x * my_system->map_taille_x);
                        current_mouse_y = (int)(event.tfinger.y * my_system->map_taille_y);
                        flag_event_up = true;
                        flag_event_down = false;
                        break;

                }
            }


            sleep = (1000 / GAME_FPS);
            SDL_Delay( sleep );



            /***************************************************************************   Flash Button */
            flash_button_count++;
            if (flash_button_count >= flash_button_max) {
                flash_button_count = 0;
                if (flag_button_red) { flag_button_red = false; } else {flag_button_red = true;}

            }

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
/*****************************************************************
*****************************************************************/
void affiche_button_number (t_button *button, int number, TTF_Font *police, int color_txt, SDL_Renderer *pRenderer){

    SDL_Rect Src;
    SDL_Rect Dst;
    SDL_Rect Dst_txt;

    Src.x = 0;
    Src.y = 0;
    Src.w = button->w;
    Src.h = button->h;

    Dst.x = button->x;
    Dst.y = button->y;
    Dst.w = Src.w;
    Dst.h = Src.h;

    Dst_txt.x = button->x + 20;
    Dst_txt.y = button->y + 20;
    Dst_txt.w = Src.w - 40;
    Dst_txt.h = Src.h - 40;

    SDL_Surface *texte = NULL;
    SDL_Texture *texture = NULL;
    SDL_Color couleur;

    if (color_txt == 0 ) {
            couleur.r = 50; couleur.g = 50; couleur.b = 50;
    } else {
            couleur.r = 200; couleur.g = 200; couleur.b = 200;
    }
    char name[5];
    sprintf(name, "%d", number);

    texte   = TTF_RenderText_Blended(police, name , couleur);
    texture = SDL_CreateTextureFromSurface(pRenderer, texte);

    SDL_RenderCopy      ( pRenderer, button->img, &Src, &Dst );
    SDL_RenderCopy      ( pRenderer, texture, &Src, &Dst_txt );
    //SDL_RenderCopy      ( pRenderer, texture, NULL, NULL );

    SDL_FreeSurface(texte);
    SDL_DestroyTexture(texture);
}











