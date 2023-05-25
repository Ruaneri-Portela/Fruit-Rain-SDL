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
    void init(SDL_Renderer *rd)
    {
        renderer = rd;
        triggered = true;
    };
    void update()
    {
        if (triggered)
        {
            if (entity != NULL)
            {
                entity->draw(renderer);
            }
            else
            {
                entity = new Entity();
                entity->speedAdd(0, 10);
                entity->time = &tick;
            };
            if (entity->y > 510)
            {
                mainTrack->play(sound2,-1);
                entity = NULL;
            }
            else if (distance(onePlayer->x, onePlayer->y, entity->x, entity->y) < diff)
            {
                mainTrack->play(sound,-1);
                entity = NULL;
            };
        };
    };
    void destroy()
    {
        triggered = false;
        delete entity;
    };
};