#ifndef TYPE_SOUND_H_INCLUDED
#define TYPE_SOUND_H_INCLUDED


typedef struct {

    Mix_Music *Music;

    Mix_Chunk *Start;
    Mix_Chunk *Exit;

    Mix_Chunk *Click;
    Mix_Chunk *Cancel;

    Mix_Chunk *StartGame;
    Mix_Chunk *GameOver;

    Mix_Chunk *Tir;
    Mix_Chunk *Explosion;

    Mix_Chunk *PlaceTower;
    Mix_Chunk *Oh_non;


} t_sound;



#endif // TYPE_SOUND_H_INCLUDED
