#ifndef TYPE_GAME_H_INCLUDED
#define TYPE_GAME_H_INCLUDED

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
    bool flag_game_started;                 // vrai d�s le d�marrage du jeu

    bool flag_tower_position_ok;            // vrai si la tourelle n'est pas dans l'eau

    bool flag_game_over;

    int current_level;                      // Level 0.....x
    int last_level;                         // dernier niveau effectu� par l'utilisateur
    int max_level_win;                      // niveau maximum atteind
    int current_nb_enemy;                   // nombre d'ennemi
    int current_enemy_alive;                // nombre d'ennemi en vie
    int current_nb_tower;                   // nombre de tourelle
    int current_tower;                      // id tourelle selectionn�e, TOWER_MAX signifie qu'aucune n'est seletionn�e
    int current_nb_missile;                 // nombre total de missile
    int current_nb_explosion;               // nombre total de missile

    int current_mouse_x, current_mouse_y;   // position de la souris ou du doigt

    t_sprite *sp_ENEMY[WAVE_NB * WAVE_ENEMY_MAX_BY_WAVE];       // annimation ennemis - tableau de pointeurs
    t_tower  *sp_TOWER[TOWER_MAX];                              // annimation tourelle - tableau de pointeurs
    t_sprite *sp_ARRIVE;                                        // annimation de l'arrive
    t_tower  *sp_TOWER_MOUSE;                                   // annimation sous la souris
    t_sprite *sp_BUTTON_TIR;                                    // bouton de tir
    t_sprite *sp_BUTTON_TOWER;                                  // bouton de nouvelle tourelle
    t_sprite *sp_EXPLOSION[(WAVE_NB * WAVE_ENEMY_MAX_BY_WAVE) + TOWER_MAX];                                     // annimation explosions
    t_sprite *sp_TOWER_TARGET;                                  // annimation de la vis�
    t_sprite *sp_HEART;                     // Coeur de point de vie

    int score;
    int heart_point;

    int zone_button_tir_x;
    int zone_button_tir_y;
    int zone_button_tower_x;
    int zone_button_tower_y;


} t_game;




#endif // GAME_H_INCLUDED
