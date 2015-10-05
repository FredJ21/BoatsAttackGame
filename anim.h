#ifndef ANIM_H_INCLUDED
#define ANIM_H_INCLUDED

#define false   0
#define true    1
#define bool    short int

typedef struct {
    int     x;
    int     y;
    int     tileX;
    int     tileY;
} t_pos;

// animation
typedef struct {
    char    file[256];          // nom du fichier
    int     tx, ty;             // taille d'une image
    int     nb_colonne;
    int     nb_image;           // nombre total d'image dans le fichier
    int     nb_img_by_dir;      // nombre d'image par direction
    SDL_Texture *texture;       // les images de l'animation
    int     nb_tour;            // frequence des image
    int     vitesse;            // vitesse de deplacement de l'animation
} t_animation;

// sprite
typedef struct {
    float   x, y;               // position
    float   dx, dy;             // vitesse de d�placement
    int     img_current;        // image current
    int     direction;          // 0 --> vers le haut  ;  1 --> vers la droite  ;  2 --> vers le bas  ;  3 --> vers la gauche

	int compte_tour;            // compte tours
	int nb_tour;                // nombre de tours
	t_animation *anim;          // les images de l'animations

	int     time_before_ativiation; // lancement du sprite � retardement
	bool    is_arrive;
	bool    is_actif;
	bool    in_the_map;          // vrai quand le sprite est rentr� entierement dans la map , en debut de jeu
	int     visible;             // effet de transparence  255->visible  0->invisible

} t_sprite;

// sprite de type tower
typedef struct {
    int     x, y;               // position
    int     img_current;        // image current
    int     angle;

	int compte_tour;            // compte tours
	int nb_tour;                // nombre de tours

	t_animation *anim;          // les images de l'animations

	int     visible;             // effet de transparence  255->visible  0->invisible

} t_tower;


void init_animation                 (t_animation *a, SDL_Renderer *r);

t_sprite*   init_sprite             (t_animation *a);

t_sprite*   create_Enemy            (int position, int A, int B, t_animation *ANIM, float Frequence);
                                        // position --> en haut, � droite, en bas, � gauche
                                        // A & B    --> d�limite la zone de cr�ation , entre A et B
                                        // *ANIM    --> pointeur sur l'annimation
                                        // Frequence --> Frequence de d�marrage entre chaque ennemi

void        avance_sprite           (t_sprite *s, t_level *pLevel);
void        anime_sprite            (t_sprite *s);
void        affiche_sprite          (SDL_Renderer *r, t_sprite *s);
void        place_sprite            (t_sprite *s, int x, int y);      // X et Y sont des coordonn�s de MAP
void        destroy_sprite          (t_sprite **s);

t_tower*   create_Tower             ( int x, int y, t_animation *ANIM);
void        anime_tower             (t_tower *s);
void        affiche_tower           (SDL_Renderer *r, t_tower *s);
bool        is_tower_valid_position (t_tower *s, t_level *pLevel);
void        add_tower_position      (t_tower *s, t_level *pLevel);
void        destroy_tower           (t_tower **s);


#endif // ANIM_H_INCLUDED
