#include <SDL2/SDL.h>
#include <string>
#include "Utils.h"
// Instanciamento do objeto jogavel
class Player
{
public:
    int speedX = 0, speedY = 0;
    int x = 500, y = 10;
    int health = 4;
    int *tick;
    MoveDeltaTime Move;
    SDL_Rect square = {x, y, 41, 74};
    SDL_Surface *imageSurface;
    SDL_Texture *texture;
    void loadSprite(SDL_Renderer *renderer, std::string location)
    {
        texture = setSprite(renderer,location.c_str());
    };
    int draw(SDL_Renderer *renderer)
    {
        Move.speed = 20;
        if (y > 450)
        {
            y = 450;
        }
        else if (y < 450)
        {
            move(0, Move.move());
        }
        square.x = x;
        square.y = y;
        moveOverSpeed();
        SDL_RenderCopy(renderer, texture, NULL, &square);
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