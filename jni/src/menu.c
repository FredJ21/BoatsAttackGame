#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
//#include "level.h"
//#include "anim.h"
#include "menu.h"


void init_menu (t_menu *my_menu, SDL_Renderer *pRenderer) {

    SDL_Surface *pSurface_tmp;

    my_menu->exit    = false;
    my_menu->start   = false;
    my_menu->restart = false;
    my_menu->resume  = false;

    /** FICHIER background **/
    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_BACKGROUND);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->img_background         = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->img_background) {  printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}


    /** FICHIER bouton START**/
    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_START);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_start.img       = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_start.img){ printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}

    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_START_P);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_start_p.img     = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_start_p.img){ printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}


    /** FICHIER bouton RESTART**/
    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_RESTART);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_restart.img     = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_restart.img){ printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}

    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_RESTART_P);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_restart_p.img   = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_restart_p.img){ printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}


    /** FICHIER bouton RESUME**/
    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_RESUME);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_resume.img     = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_resume.img){ printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}

    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_RESUME_P);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_resume_p.img   = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_resume_p.img){ printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}


    /** FICHIER bouton EXIT**/
    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_EXIT);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_exit.img        = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_exit.img){  printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}

    pSurface_tmp                    = SDL_LoadBMP (MENU_IMG_EXIT_P);
    if(!pSurface_tmp) {             printf( "LOAD BMP ERROR : %s\n", SDL_GetError() ); exit(1);}

    my_menu->button_exit_p.img      = SDL_CreateTextureFromSurface(pRenderer, pSurface_tmp);
    if(!my_menu->button_exit_p.img){ printf( "SDL_Texture ERREUR! SDL_GetError: %s\n", SDL_GetError() ); exit(1);}




    SDL_FreeSurface(pSurface_tmp);
}
