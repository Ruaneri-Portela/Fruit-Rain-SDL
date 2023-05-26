#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
class gameWin
{
public:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int OpenGame(SDL_Window *target)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        Mix_Init(MIX_INIT_MP3);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        TTF_Init();
        if (target == NULL)
        {
            window = SDL_CreateWindow("Fruit Rain SDL Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_HIDDEN);
        }
        else
        {
            window = target;
        };
        return 0;
    }
    int CloseWin()
    {
        SDL_DestroyWindow(window);
        return 0;
    }
    int OpenRender()
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        return 0;
    }
    int CloseRend()
    {
        SDL_DestroyRenderer(renderer);
        return 0;
    }
    int CloseGame()
    {
        CloseRend();
        CloseWin();
        Mix_CloseAudio();
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
};
