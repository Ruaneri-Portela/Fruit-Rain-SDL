<<<<<<< HEAD
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
class gameWin
{
public:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int OpenWin()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        window = SDL_CreateWindow("Fruit Rain SDL Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_SHOWN);
        std::cout << "!! SDL_Init" << std::endl;
        return 0;
    }
    int CloseWin()
    {
        SDL_DestroyWindow(window);
        std::cout << "!! SDL_DestroyWindow" << std::endl;
        return 0;
    }
    int OpenRender()
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        std::cout << "!! SDL_Renderer" << std::endl;
        return 0;
    }
    int CloseRend()
    {
        SDL_DestroyRenderer(renderer);
        std::cout << "!! SDL_DestroyRenderer" << std::endl;
        return 0;
    }
    int CloseAll()
    {
        CloseRend();
        CloseWin();
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
};
=======
#include <SDL2>
#include <iostream>
class gameWin
{
public:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int OpenWin()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Fruit Rain SDL Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_SHOWN);
        std::cout << "!! SDL_Init" << std::endl;
        return 0;
    }
    int CloseWin()
    {
        SDL_DestroyWindow(window);
        std::cout << "!! SDL_DestroyWindow" << std::endl;
        return 0;
    }
    int OpenRender()
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        std::cout << "!! SDL_Renderer" << std::endl;
        return 0;
    }
    int CloseRend()
    {
        SDL_DestroyRenderer(renderer);
        std::cout << "!! SDL_DestroyRenderer" << std::endl;
        return 0;
    }
    int CloseAll()
    {
        CloseRend();
        CloseWin();
        SDL_Quit();
        return 0;
    }
};
>>>>>>> 5a57d31cbd6ac76b21c2a4997018e5c6666e809c
