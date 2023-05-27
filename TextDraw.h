#include <SDL2/SDL_ttf.h>
#include <string>
// Carregador de textos na tela
class TextTexture
{
public:
    TTF_Font *font;
    SDL_Color color = {0, 0, 0};
    SDL_Surface *textSurface;
    SDL_Texture *textTexture;
    SDL_Rect destRect;
    void load(std::string file)
    {
        font = TTF_OpenFont(file.c_str(), 90);
    }
    void render(SDL_Renderer *renderer, int x, int y, const char *text)
    {
        textSurface = TTF_RenderText_Solid(font, text, color);
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        destRect.x = x;
        destRect.y = y;
        destRect.w = 32*strlen(text);
        destRect.h = 50;
    }
    void lazyRender(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, textTexture, NULL, &destRect);
    }
    void freeTexture()
    {
        SDL_DestroyTexture(textTexture);
    }
};