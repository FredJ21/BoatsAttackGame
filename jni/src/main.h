#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define false   0
#define true    1
#define bool    short int


typedef struct {

    bool flag_fin;                          // fin du programme
    bool flag_change_level;                 // changement de level
    bool flag_affiche_level_titre;

    bool flag_event_DOWN;
    bool flag_event_UP;
    bool flag_event_MOVE;

    bool flag_mode_place_tower;             // mode permettant de positionner les tourelles
    bool flag_mode_tower_selected;          // la tourelle est choisi
    bool flag_mode_game;                    // mode normal du jeu, permet de savoir qu'aucun autre mode n'est actif

    bool flag_tower_position_ok;            // vrai si la tourelle n'est pas dans l'eau

    int current_level;                      // Level 0.....x
    int current_nb_enemy;                   // nombre d'ennemi
    int current_enemy_alive;                // nombre d'ennemi en vie
    int current_nb_tower;                   // nombre de tourelle
    int current_tower;                      // id tourelle selectionnée, TOWER_MAX signifie qu'aucune n'est seletionnée
    int current_nb_missile;                 // nombre total de missile

    int current_mouse_x, current_mouse_y;   // position de la souris ou du doigt

} t_game;


#endif // MAIN_H_INCLUDED
