#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED



// level
typedef struct {
    char            name[256];
    int             my_map[MAP_NB_TILE_X * MAP_NB_TILE_Y];
    int             map_Info[MAP_NB_TILE_X][MAP_NB_TILE_Y];
    int             map_Direction[MAP_NB_TILE_X][MAP_NB_TILE_Y];

    int             cibleX;
    int             cibleY;

    SDL_Texture     *pTexture_MAP;
    SDL_Texture     *pTexture_MAP_Obstacles;        // pour le debug

} t_level;

enum { LIBRE, OBSTACLE, OCCUPE };
enum { INCONNU, VERT_LE_HAUT, VERS_LA_DROITE, VERS_LE_BAS, VERS_LA_GAUCHE };

void init_level             (t_level *pLevel, int level_number, SDL_Surface *pSurface_Tuile, SDL_Renderer *pRenderer);
void init_level_chemins     (t_level *pLevel);

void affiche_map            (SDL_Renderer *pRenderer, t_level *pLevel);

// fonctions de debugage
void init_texture_obstacle  (SDL_Renderer *pRenderer, t_level *pLevel);
void affiche_obstacle       (SDL_Renderer *pRenderer, t_level *pLevel);
void affiche_map_console    (t_level *pLevel);



#endif // LEVEL_H_INCLUDED
