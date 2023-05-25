#include <SDL2/SDL.h>
#include <iostream>
#include "MathUtils.h"
class Entity
{

public:
    int x = randomRange(0,1000), y = 0;
    int speedX = 0, speedY = 0;
    int** time;
    SDL_Rect square = {x, y, 20, 20};
    int draw(SDL_Renderer *renderer)
    {
        if(**time >= 1000){
            moveOverSpeed();
        };
        SDL_Rect square = {x, y, 20, 20};
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
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