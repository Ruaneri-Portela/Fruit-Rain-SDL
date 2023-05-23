#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
class AudioDevice
{
public:
    bool playable = true;
    void init()
    {
        std::cout << "&& Starting audio engine" << std::endl;
        Mix_Init(MIX_INIT_MP3);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    };
    void play(Mix_Chunk *sound, int channelNumber)
    {
        if (playable)
        {
            Mix_PlayChannel(channelNumber, sound, 0);
        };
    };
    void end()
    {
        Mix_CloseAudio();
        Mix_Quit();
        std::cout << "&& Ending audio engine" << std::endl;
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