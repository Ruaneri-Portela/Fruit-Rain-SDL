#include <SDL2/SDL.h>
#include <iostream>
class Entity
{
private:
    int x = 10, y = 10;
    int speedX = 0, speedY = 0;
public:
    Entity *pre;
    Entity *pos;
    SDL_Rect square = {x, y, 20, 20};
    int draw(SDL_Renderer *renderer)
    {
        moveOverSpeed();
        SDL_Rect square = {x, y, 20, 20};
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