#include <random>
#include <cmath>
// Utilitarios de matematica usados nos codigos
int randomRange(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}
double distance(double x1, double y1, double x2, double y2)
{
    double diff = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return diff;
}
SDL_Texture *setSprite(SDL_Renderer *renderer, std::string location)
{
    SDL_Surface *imageSurface = IMG_Load(location.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    return texture;
};
class MoveDeltaTime
{
private:
    Uint32 startTime = SDL_GetTicks();
    Uint32 currentTime;
    Uint32 elapsedTime;

    int callback;

public:
    float divSpeed, mov;
    float speed;
    int move()
    {
        currentTime = SDL_GetTicks();
        if (speed != 0)
        {
            elapsedTime = currentTime - startTime;
            divSpeed = 1000 / abs(speed);
            if (elapsedTime >= divSpeed)
            {
                if (mov >= 1)
                {
                    callback = (int)mov;
                    mov = 0;
                    if (speed > 0)
                    {
                        return callback;
                    }
                    else
                    {
                        return -callback;
                    };
                }
                else
                {
                    mov = mov + (speed / 1);
                };
                startTime = currentTime;
            }
            return 0;
        }
        else
            return 0;
    };
};

SDL_Texture *invertTexture(SDL_Renderer *renderer, SDL_Texture *texture, bool horizontalMirror, std::string location)
{
    // Obter as informações da textura
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    // Criar uma superfície temporária para copiar a textura
    SDL_Surface *surface = IMG_Load(location.c_str());
    SDL_Surface *mirroredSurface = SDL_CreateRGBSurface(0, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    // Espelhar a superfície original
    for (int y = 0; y < surface->h; y++)
    {
        for (int x = 0; x < surface->w; x++)
        {
            Uint32 pixel = 0;
            if (horizontalMirror)
                pixel = ((Uint32 *)surface->pixels)[(surface->w - 1 - x) + y * surface->pitch / sizeof(Uint32)];
            else
                pixel = ((Uint32 *)surface->pixels)[x + (surface->h - 1 - y) * surface->pitch / sizeof(Uint32)];

            ((Uint32 *)mirroredSurface->pixels)[x + y * mirroredSurface->pitch / sizeof(Uint32)] = pixel;
        }
    }
    // Criar uma nova textura a partir da superfície invertida
    SDL_Texture *invertedTexture = SDL_CreateTextureFromSurface(renderer, mirroredSurface);
    // Limpar a superfície temporária
    SDL_FreeSurface(surface);
    SDL_FreeSurface(mirroredSurface);
    return invertedTexture;
};