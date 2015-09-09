#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

// level
typedef struct {
    char            name[256];
    int             my_map[MAP_NB_TILE_X * MAP_NB_TILE_Y];
    SDL_Texture     *pTexture_MAP;

} t_level;


void init_level (t_level *pLevel, int level_number, SDL_Surface *pSurface_Tuile, SDL_Renderer *pRenderer);

#endif // LEVEL_H_INCLUDED
