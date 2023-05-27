#include "Player.h"
#include "Entity.h"
class Object
{
public:
    Entity *entity = NULL;
    SDL_Texture *sprite;
    void object(bool *triggered, SDL_Renderer *renderer, AudioDevice *mainTrack, Mix_Chunk *sound, Mix_Chunk *sound2, int *returnState, Player *onePlayer, float *diff)
    {
        if (triggered)
        {
            if (entity != NULL)
            {
                entity->draw(renderer,sprite);
            }
            else
            {
                entity = new Entity();
                switch (randomRange(0,2))
                {
                case 0:
                    sprite=setSprite(renderer,"assets/texture/fruit1.png");
                    break;
                case 1:
                    sprite=setSprite(renderer,"assets/texture/fruit2.png");
                    break;
                case 2:
                    sprite=setSprite(renderer,"assets/texture/fruit3.png");
                    break;
                }
                entity->speedAdd(0, 10);
            };
            if (entity->y > 510)
            {
                mainTrack->play(sound2, -1);
                *returnState = 2;
                delete entity;
                entity = NULL;
            }
            else if (distance(onePlayer->x, onePlayer->y, entity->x, entity->y) < *diff)
            {
                mainTrack->play(sound, -1);
                *returnState = 1;
                delete entity;
                entity = NULL;
            };
        }
        else
        {
            delete entity;
        };
    };
};
struct Node
{
    Object *data;
    Node *next;
};
void addToBeginning(Node *&head, Object *value)
{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}
// Aqui instanciamos as frutas (entidades)
class Fruit
{
private:
    SDL_Renderer *renderer;
    bool triggered = false;
    float diff = 20;
    Object *nodeStart;
    Node *head = nullptr;

public:
    int *tick;
    MoveDeltaTime *objManager;
    Player *onePlayer;
    Mix_Chunk *sound;
    Mix_Chunk *sound2;
    AudioDevice *mainTrack;
    int returnState;
    void init(SDL_Renderer *rd)
    {
        renderer = rd;
        triggered = true;
        nodeStart = new Object();
        addToBeginning(head, nodeStart);
        objManager = new MoveDeltaTime();
        objManager->speed = 0.2f;
    };
    int update()
    {
        returnState = 0;
        Node *current = head;
        while (current != nullptr)
        {
            current->data->object(&triggered, renderer, mainTrack, sound, sound2, &returnState, onePlayer, &diff);
            current = current->next;
        }
        if (objManager->move() >= 1)
        {
            addToBeginning(head, new Object());
        }
        return returnState;
    };
    void destroy()
    {
        triggered = false;
        delete sound;
        delete sound2;
    };
};
