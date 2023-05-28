#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <string>
#include "Utils.h"
// Instanciamento do objeto jogavel
class Player
{
public:
    int speedX = 0, speedY = 0;
    int x = 500, y = 10, h = 41, w = 74;
    int health = 4;
    int *tick;
    bool *mouseEnabled;
    bool lock = true;
    bool inverted = false;
    bool atack = false;
    MoveDeltaTime MoveY;
    MoveDeltaTime MoveX;
    SDL_Rect square = {x, y, h, w};
    SDL_Texture *texture;
    SDL_Texture *texture2;
    SDL_Texture *texture3;
    SDL_Texture *texture4;
    void loadSprite(SDL_Renderer *renderer, std::string location, std::string location2)
    {
        texture = setSprite(renderer, location.c_str());
        texture2 = invertTexture(renderer, texture, true, location);
        texture3 = setSprite(renderer, location2.c_str());
        texture4 = invertTexture(renderer, texture, true, location2);
    };
    int draw(SDL_Renderer *renderer)
    {
        if (y > 450 && lock)
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
        if (x < 0)
        {
            x = 1000;
        }
        else if (x > 1000)
        {
            x = 0;
        };
        MoveY.speed = (float)speedY;
        MoveX.speed = (float)speedX;
        square.x = x;
        square.y = y;
        moveOverSpeed();
        if (atack)
        {
            if (inverted)
            {
                SDL_RenderCopy(renderer, texture4, NULL, &square);
            }
            else
            {
                SDL_RenderCopy(renderer, texture3, NULL, &square);
            }
        }
        else
        {
            if (inverted)
            {
                SDL_RenderCopy(renderer, texture2, NULL, &square);
            }
            else
            {
                SDL_RenderCopy(renderer, texture, NULL, &square);
            };
        };
        return 0;
    };
    void move(int addX, int addY)
    {
        if (addX > 0)
        {
            inverted = true;
        }
        else if (addX < 0)
        {
            inverted = false;
        }
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
        return (int)round(speed);
    };
};