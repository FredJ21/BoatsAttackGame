#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED


// sprite de type tower
typedef struct {
    int     x, y;               // position
    int     img_current;        // image current
    int     angle;

	int     compte_tour;        // compte tours
	int     nb_tour;            // nombre de tours

	t_animation *anim;          // les images de l'animations

	int     visible;            // effet de transparence  255->visible  0->invisible

} t_tower;


t_tower*    create_Tower            ( int x, int y, t_animation *ANIM);
void        anime_tower             (t_tower *s);
void        calcul_angle_tower      (t_tower *s, int cible_x, int cible_y);

void        affiche_tower           (SDL_Renderer *r, t_tower *s);
bool        is_tower_valid_position (t_tower *s, t_level *pLevel);
void        add_tower_position      (t_tower *s, t_level *pLevel);
void        destroy_tower           (t_tower **s);


#endif // TOWER_H_INCLUDED
