#include "Entity.h"
#include "Player.h"
class Fruit
{
private:
    SDL_Renderer *renderer;
    Entity *entity = NULL;
    bool triggered = false;
    float diff = 20;
public:
    int *tick;
    Player *onePlayer;
    Mix_Chunk *sound;
    Mix_Chunk *sound2;
    AudioDevice *mainTrack;
    int returnState;
    void init(SDL_Renderer *rd)
    {
        renderer = rd;
        triggered = true;
    };
    int update()
    {
        returnState = 0;
        if (triggered)
        {
            if (entity != NULL)
            {
                entity->draw(renderer);
            }
            else
            {
                entity = new Entity();
                entity->speedAdd(0, 6.5);
            };
            if (entity->y > 510)
            {
                mainTrack->play(sound2,-1);
                returnState = 2;
                entity = NULL;
            }
            else if (distance(onePlayer->x, onePlayer->y, entity->x, entity->y) < diff)
            {
                mainTrack->play(sound,-1);
                returnState = 1;
                entity = NULL;
            };
        };
        return returnState;
    };
    void destroy()
    {
        triggered = false;
        delete entity;
    };
};