#ifndef ANIM_H_INCLUDED
#define ANIM_H_INCLUDED

#define false   0
#define true    1
#define bool    short int

typedef struct {
    int     x;
    int     y;
} t_pos;

// animation
typedef struct {
    char    file[256];          // nom du fichier
    int     tx, ty;             // taille d'une image
    int     nb_colonne;
    int     nb_image;           // nombre total d'image dans le fichier
    int     nb_img_by_dir;      // nombre d'image par direction
    SDL_Texture *texture;       // les images de l'animation
} t_animation;

// sprite
typedef struct {
    float   x, y;               // position
    float   dx, dy;             // vitesse de déplacement
    int     img_current;        // image current
    int     direction;          // 0 --> vers le haut  ;  1 --> vers la droite  ;  2 --> vers le bas  ;  3 --> vers la gauche

	int compte_tour;            // compte tours
	int nb_tour;                // nombre de tours
	t_animation *anim;          // les images de l'animations

	bool    actif;
	bool    time_before_ativiation; // lancement du sprite à retardement
} t_sprite;

enum { UP, RIGHT, DOWN, LEFT };

void init_animation(t_animation *a, SDL_Renderer *r);

t_sprite*   init_sprite(int posx, int posy, int dx, int dy, int nbtour, int dir, t_animation*a, bool actif, int time_before_ativiation);
void        avance_sprite(t_sprite *s, t_level *pLevel);
void        anime_sprite(t_sprite *s);
void        affiche_sprite(SDL_Renderer *r, t_sprite *s);
void        destroy_sprite(t_sprite **s);

void place_sprite  (t_sprite *s, int x, int y);      // X et Y sont des coordonnés de MAP



#endif // ANIM_H_INCLUDED
