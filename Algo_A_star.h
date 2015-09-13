#ifndef ALGO_A_STAR_H_INCLUDED
#define ALGO_A_STAR_H_INCLUDED


#define false   0
#define true    1
#define bool    short int


// position
typedef struct {
    int     x;
    int     y;
    int     valeur;
    int     parent_x;
    int     parent_y;
} t_position;


void calcul_chemin ( int depart_x, int depart_y, int arrive_x, int arrive_y, int mapO[MAP_NB_TILE_X][MAP_NB_TILE_Y] );

void affiche_map_console (void);

bool is_obstacle        (int x, int y);
bool is_in_close_list   (int x, int y);
bool is_in_open_list    (int x, int y);
int calcul_cout         (int x, int y);
void add_in_open_list   (int x, int y, int valeur, int parent_x, int parent_y );
void add_in_close_list  (t_position t);

t_position cherche_meilleur_position (void);

void retrouve_chemin_vers_depart (int depart_x, int depart_y);


#endif // ALGO_A_STAR_H_INCLUDED
