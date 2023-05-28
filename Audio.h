#ifdef _MSC_VER
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

// Carregador do dispositivo de audio (Criador do Canal no mixer do sistema) e o tocador de audio
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
// Carregador do audio na memoria
class AudioData
{
private:
    Mix_Chunk *sound = NULL;

public:
    Mix_Chunk *load(const char *filename)
    {
        sound = Mix_LoadWAV(filename);
        return sound;
    };
    void unload(Mix_Chunk *sound)
    {
        Mix_FreeChunk(sound);
    };
};