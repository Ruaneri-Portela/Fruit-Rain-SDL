#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
// Aqui tem a instancia de objetos não jogaveis, apilidados de entidades
class Entity
{
private:
    MoveDeltaTime xMove;
    MoveDeltaTime yMove;

public:
    int x = randomRange(0, 1000), y = randomRange(20, 100) * -1;
    float speedX = 0, speedY = 0;
    SDL_Rect square = {x, y, 20, 20};
    int draw(SDL_Renderer *renderer, SDL_Texture *texture)
    {
        moveOverSpeed();
        SDL_Rect square = {x, y, 35, 30};
        SDL_RenderCopy(renderer, texture, NULL, &square);
        xMove.speed = speedX;
        yMove.speed = speedY;
        return 0;
    };
    void move(int addX, int addY)
    {
        x = x + addX;
        y = y + addY;
    }
    void speedAdd(float X, float Y)
    {
        speedX = speedX + X;
        speedY = speedY + Y;
    };
    void moveOverSpeed()
    {
        move(xMove.move(), yMove.move());
    };
};
