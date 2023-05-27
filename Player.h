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
    bool *mouseEnabled;
    bool lock = true;
    MoveDeltaTime MoveY;
    MoveDeltaTime MoveX;
    SDL_Rect square = {x, y, 41, 74};
    SDL_Surface *imageSurface;
    SDL_Texture *texture;
    void loadSprite(SDL_Renderer *renderer, std::string location)
    {
        texture = setSprite(renderer, location.c_str());
    };
    int draw(SDL_Renderer *renderer)
    {
        if (y > 450 & lock)
        {
            speedY = 0;
            y = 450;
            lock = false;
        }
        else if (speedY != 0)
        {
            lock = true;
        }
        else
        {
            y = 450;
        };
        MoveY.speed = speedY;
        MoveX.speed = speedX;
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
        move(MoveX.move(), MoveY.move());
    };
    void moveToMouse(int MouseX, int MouseY)
    {
        int xDiff = x - MouseX;
        int yDiff = y - MouseY;
        int newX = x, newY = y;
        if (xDiff < 0)
        {
            newX = logMoviment(xDiff, 10, 5);
        }
        else
        {
            newX = logMoviment(xDiff, 10, -5);
        }
        /*
        if (yDiff < 0)
        {
            newY = logMoviment(yDiff, 10, 5);
        }
        else
        {
            newY = logMoviment(yDiff, 10, -5);
        }*/
        move(newX, newY);
    }
    int logMoviment(int distance, int max_distance, int max_speed)
    {
        float fractionDistance = (float)distance / max_distance;
        float speed = log(1 + abs(fractionDistance)) * max_speed;
        return round(speed);
    }
};