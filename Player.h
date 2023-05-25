#include <SDL2/SDL.h>
#include <iostream>
class Player
{
public:
    int speedX = 0, speedY = 0;
    int x = 500, y = 10;
    int health = 4;
    int *tick;
    SDL_Rect square = {x, y, 20, 20};
    int draw(SDL_Renderer *renderer)
    {
        if (y > 510)
        {
            y = 510;
        }
        else if (y < 510 & *tick >= 1000)
        {
            move(0, 20);
        }
        SDL_Rect square = {x, y, 10, 10};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &square);
        return 0;
    };
    void move(int addX, int addY)
    {
        x = x + addX;
        y = y + addY;
    }
    void speedAdd(int X, int Y)
    {
        speedX = speedX + X;
        speedY = speedY + Y;
    };
    void moveOverSpeed()
    {
        move(speedX, speedY);
    };
};