#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "config.h"
#include "level.h"
#include "anim.h"
#include "tower.h"
#include "Algo_Collision.h"


/*****************************************************************
*****************************************************************/
bool test_collision_circle      (int Ax, int Ay, int Aradius, int Bx, int By, int Bradius ) {


  //  printf ("%d %d %d %d %d %d\n", Ax, Ay, Aradius, Bx, By, Bradius);

    int dx = Ax - Bx;
    int dy = Ay - By;
    int distance = sqrt((dx * dx) + (dy * dy));

    if (distance < (Aradius + Bradius) ) {

        return true;

    } else {

        return false;
    }
}
/*****************************************************************
*****************************************************************/
//void test_collision             (t_tower *tower[], int nb_tower, t_sprite *enemy[], int nb_enemy) {
void test_collision             (t_game *my_game) {

    int a, b, m, s;
    int nb = 0;

    for (a = 0; a < my_game->current_nb_tower; a++) {                        // pour chaque tourelle  A
        for( m = 0; m < TOWER_NB_MISSILE_MAX; m++){         // pour chaque missile   M

            if (my_game->sp_TOWER[a]->missile[m].actif ) {

                // test de collision avec les autres tourelle   B
                for (b = 0; b < my_game->current_nb_tower; b++) {

                    if ( my_game->sp_TOWER[b]->actif && a != b) {       // pas de test entre une tourelle et elle meme

                        nb++;
                                                            // test de collision entre le missile M de la tourelle A avec la position de tourelle B
                        if ( test_collision_circle( my_game->sp_TOWER[a]->missile[m].x, my_game->sp_TOWER[a]->missile[m].y, 5, my_game->sp_TOWER[b]->x, my_game->sp_TOWER[b]->y, my_game->sp_TOWER[b]->anim->tx/2 ) ) {

                            my_game->sp_TOWER[a]->missile[m].actif = false;
                            my_game->sp_TOWER[b]->actif = false;

                        }
                    }
                }

                // test de collision avec les enemy
                for ( s = 0; s < my_game->current_nb_enemy; s++ ){

                    if ( my_game->sp_ENEMY[s]->is_actif ) {

                        nb++;
                                                            // test de collision entre le missile M de la tourelle A
                        if ( test_collision_circle( my_game->sp_TOWER[a]->missile[m].x, my_game->sp_TOWER[a]->missile[m].y, 5, my_game->sp_ENEMY[s]->x, my_game->sp_ENEMY[s]->y, my_game->sp_ENEMY[s]->anim->tx/2 )) {

                            if ( my_game->sp_TOWER[a]->missile[m].actif ) {
                                my_game->sp_TOWER[a]->missile[m].actif = false;
                                my_game->sp_ENEMY[s]->is_actif = false;
                            }

                        }
                    }
                }
            }
        }
    }
}
















