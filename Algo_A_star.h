#ifndef ALGO_A_STAR_H_INCLUDED
#define ALGO_A_STAR_H_INCLUDED


#define false   0
#define true    1
#define bool    short int

typedef struct {
    int     x;
    int     y;
} t_position;

typedef struct {
    int     x;
    int     y;
    int     poid;
    int     parent_x;
    int     parent_y;
    bool    is_open;
    bool    is_close;
} t_table_Algo_A_Star;
//data
typedef struct {
    int     depart_X;
    int     depart_Y;
    int     arrive_X;
    int     arrive_Y;
    int     derniere_position_ok_X;
    int     derniere_position_ok_Y;
} t_Algo_A_Star;




void calcul_chemin ( int depart_x, int depart_y, t_level *pLevel );

int calcul_cout         (int x, int y, t_Algo_A_Star *data);

t_position cherche_meilleur_position (t_table_Algo_A_Star Algo_list[MAP_NB_TILE_X][MAP_NB_TILE_Y]);

void retrouve_chemin_vers_depart (t_Algo_A_Star *data, t_table_Algo_A_Star Algo_list[MAP_NB_TILE_X][MAP_NB_TILE_Y], t_level *pLevel);



#endif // ALGO_A_STAR_H_INCLUDED
