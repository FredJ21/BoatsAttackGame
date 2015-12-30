#ifndef ANIM_H_INCLUDED
#define ANIM_H_INCLUDED

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
    float   dx, dy;             // vitesse de déplacement
    int     img_current;        // image current
    int     direction;          // 0 --> vers le haut  ;  1 --> vers la droite  ;  2 --> vers le bas  ;  3 --> vers la gauche

	int compte_tour;            // compte tours
	int nb_tour;                // nombre de tours
	t_animation *anim;          // les images de l'animations

	int     time_before_ativiation; // lancement du sprite à retardement
	bool    is_arrive;
	bool    is_actif;
	bool    in_the_map;          // vrai quand le sprite est rentré entierement dans la map , en debut de jeu
	int     visible;             // effet de transparence  255->visible  0->invisible

} t_sprite;



void init_animation                 (t_animation *a, SDL_Renderer *r);

t_sprite*   init_sprite             (t_animation *a);

t_sprite*   create_Enemy            (int position, int A, int B, t_animation *ANIM, float Frequence);
                                        // position --> en haut, à droite, en bas, à gauche
                                        // A & B    --> délimite la zone de création , entre A et B
                                        // *ANIM    --> pointeur sur l'annimation
                                        // Frequence --> Frequence de démarrage entre chaque ennemi

void        avance_sprite           (t_sprite *s, t_level *pLevel);
void        anime_sprite            (t_sprite *s);
void        affiche_sprite          (SDL_Renderer *r, t_sprite *s);
void        place_sprite            (t_sprite *s, int x, int y);      // X et Y sont des coordonnés de MAP
void        destroy_sprite          (t_sprite **s);


#endif // ANIM_H_INCLUDED
