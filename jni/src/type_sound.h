#ifndef TYPE_SOUND_H_INCLUDED
#define TYPE_SOUND_H_INCLUDED


typedef struct {

    Mix_Music *Music;

    Mix_Chunk *Start;
    Mix_Chunk *Button;
    Mix_Chunk *Exit;
    Mix_Chunk *Danger;
    Mix_Chunk *Explosion;
    Mix_Chunk *Tir;
    Mix_Chunk *GameOver;



    Mix_Chunk *BeBack;


} t_sound;



#endif // TYPE_SOUND_H_INCLUDED
