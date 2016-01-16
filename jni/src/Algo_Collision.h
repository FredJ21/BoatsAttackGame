#ifndef ALGO_COLLISION_H_INCLUDED
#define ALGO_COLLISION_H_INCLUDED

#include "type_game.h"


bool test_collision_circle      (int Ax, int Ay, int Aradius, int Bx, int By, int Bradius );

void test_collision             (t_game *my_game, t_animation ANIM_EXPLOSION[]);


#endif // ALGO_COLLISION_H_INCLUDED
