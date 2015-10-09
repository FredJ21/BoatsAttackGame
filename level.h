#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#define WAVE_nb_variable_struct_wave    6

// Attack wave
typedef struct {

    int type;           // type d'ennemi
    int nb_up;          // nombre d'ennemi en haut
    int nb_right;       // nombre d'ennemi à droite
    int nb_down;        // nombre d'ennemi en bas
    int nb_left;        // nombre d'ennemi à gauche
    int start_in;       // délai, en seconde, avant démarrage de la vaque

} t_wave;

// level
typedef struct {

    char        name[256];
    int         my_map[MAP_NB_TILE_X * MAP_NB_TILE_Y];              // permet de dessiner la map
    int         map_Info[MAP_NB_TILE_X][MAP_NB_TILE_Y];             // info sur la postion des obstacles
    int         map_Direction[MAP_NB_TILE_X][MAP_NB_TILE_Y];        // info sur le parcour vers la cible

    int         cibleX;         // placement du drapeau
    int         cibleY;

    int         StartPos_UP_s,      StartPos_UP_e;        // postion de démarrage en haut
    int         StartPos_RIGHT_s,   StartPos_RIGHT_e;     // postion de démarrage à droite
    int         StartPos_DOWN_s,    StartPos_DOWN_e;      // postion de démarrage en bas
    int         StartPos_LEFT_s,    StartPos_LEFT_e;      // postion de démarrage en gauche


    t_wave          wave[WAVE_NB];

    SDL_Texture     *pTexture_MAP;
    SDL_Texture     *pTexture_MAP_Obstacles;        // pour le debug

    SDL_Texture     *pTexture_MAP_Titre;
    SDL_Rect        Titre_position_src;
    SDL_Rect        Titre_position_dst;


} t_level;

enum { LIBRE, OBSTACLE };
enum { INCONNU, VERS_LE_HAUT, VERS_LA_DROITE, VERS_LE_BAS, VERS_LA_GAUCHE };

void init_level             (t_level *pLevel, int level_number, SDL_Surface *pSurface_Tuile, SDL_Renderer *pRenderer);
void init_level_chemins     (t_level *pLevel);
void init_level_titre       (SDL_Renderer *pRenderer, t_level *pLevel, TTF_Font *police);

void clear_level            (t_level *pLevel);

void affiche_map            (SDL_Renderer *pRenderer, t_level *pLevel);
void affiche_titre          (SDL_Renderer *pRenderer, t_level *pLevel);

// fonctions de debugage
void init_texture_obstacle  (SDL_Renderer *pRenderer, t_level *pLevel);
void affiche_obstacle       (SDL_Renderer *pRenderer, t_level *pLevel);
void affiche_map_console    (t_level *pLevel);



#endif // LEVEL_H_INCLUDED
