#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
class BackgroudImage
{
public:
    SDL_Texture *texture = nullptr;
    SDL_Texture *back = nullptr;
    void loadBackgroud(SDL_Renderer *renderer, const char * filename)
    {
        SDL_Surface *surface = IMG_Load(filename);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    };
    void draw(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    };
    void destroy()
    {
        SDL_DestroyTexture(texture);
    };
};
