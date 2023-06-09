#ifdef _MSC_VER
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include "TextDraw.h"
// Rendenizador dos itens de fundo e GUI
class BackgroudImage
{
public:
    SDL_Texture *texture = NULL;
    SDL_Texture *back = NULL;
    int scoreGame = 0;
    std::string text = "0";
    TextTexture score;
    void loadBackgroud(SDL_Renderer *renderer, const char *filename, std::string file)
    {
        SDL_Surface *surface = IMG_Load(filename);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        score.load(file);
        score.render(renderer, 5, 5, 32, 50, text.c_str());
    };
    void draw(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    };
    void scoreUpdate(SDL_Renderer *renderer, int scoreStauts)
    {
        switch (scoreStauts)
        {
        case 1:
            scoreGame = scoreGame + 1;
            score.freeTexture();
            text = std::to_string(scoreGame);
            score.render(renderer, 5, 5, 32, 50, text.c_str());
            break;
        case 2:
            break;
        }
        score.lazyRender(renderer);
    };
    void destroy()
    {
        SDL_DestroyTexture(texture);
    };
};
