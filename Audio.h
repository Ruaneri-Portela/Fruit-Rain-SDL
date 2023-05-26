#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
class AudioDevice
{
public:
    bool playable = true;
    void play(Mix_Chunk *sound, int channelNumber)
    {
        if (playable)
        {
            Mix_PlayChannel(channelNumber, sound, 0);
        };
    };
    bool isPlaying(int channelNumber)
    {
        return Mix_Playing(channelNumber) != 0;
    };
};
class AudioData
{
private:
    Mix_Chunk *sound = NULL;
public:
    Mix_Chunk *load(const char *filename)
    {
        sound = Mix_LoadWAV(filename);
        std::cout << "&& Load audio " << filename << std::endl;
        return sound;
    };
    void unload(Mix_Chunk *sound)
    {
        Mix_FreeChunk(sound);
    };
};