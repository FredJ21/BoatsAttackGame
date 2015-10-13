#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "level.h"
#include "anim.h"
#include "tower.h"
#include "Algo_Collision.h"


/*****************************************************************
*****************************************************************/
bool test_collision_circle (int Ax, int Ay, int Aradius, int Bx, int By, int Bradius ) {


    int dx = Ax - Bx;
    int dy = Ay - By;
    int distance = sqrt(dx * dx + dy * dy);

    if (distance < Aradius + Bradius ) {

        printf ("collision détectée ! \n");

    }
}
/*****************************************************************
*****************************************************************/
/*


var rect1 = {x: 5, y: 5, width: 50, height: 50}
var rect2 = {x: 20, y: 10, width: 10, height: 10}

if (rect1.x < rect2.x + rect2.width &&
   rect1.x + rect1.width > rect2.x &&
   rect1.y < rect2.y + rect2.height &&
   rect1.height + rect1.y > rect2.y) {
    // collision détectée !
}

// remplissage des valeurs =>

if (5 < 30 &&
    55 > 20 &&
    5 < 20 &&
    55 > 10) {
    // collision détectée !
}
**/
/*****************************************************************
*****************************************************************/
void test_collision             (t_tower *tower[], int nb_tower, t_sprite *enemy[], int nb_enemy) {

    int a, b, m, s;

    for (a = 0; a < nb_tower; a++) {
        printf ("T%d ", a);

        for( m = 0; m < TOWER_NB_MISSILE_MAX; m++){

            if (tower[a]->missile[m].actif ) {

                printf ("M%d ", m);
            }
        }
    }
    printf ("\n");
}
