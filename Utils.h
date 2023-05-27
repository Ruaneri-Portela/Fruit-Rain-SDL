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
