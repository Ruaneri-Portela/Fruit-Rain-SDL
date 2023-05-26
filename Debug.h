#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
// Area de debug, sem muitos comentarios
class DebugLogger
{
private:
    Player *player;
    Entity *entity;
    std::thread debuggerA;
    bool trigger;
    void action()
    {
        while (trigger)
        {
            std::cout << "\033[H"
                      << "Degub Logger\n==========" << std::endl; // Tabular para ponto 1:1
            std::cout << "Player Position: X=>" << player->square.x << " Y=>" << player->square.y << std::endl;
        }
    };
    void action2()
    {
        while (trigger)
        {
            std::cout << "\033[H"
                      << "Degub Logger\n==========" << std::endl; // Tabular para ponto 1:1
            std::cout << "Player Position: X=>" << entity->x << " Y=>" << entity->y << std::endl;
        }
    };

public:
    void start(Player *PlayerPointer)
    {
        trigger = true;
        debuggerA = std::thread(&DebugLogger::action, this);
        player = PlayerPointer;
    };
    void start2(Entity *entityPointer)
    {
        trigger = true;
        debuggerA = std::thread(&DebugLogger::action2, this);
        entity = entityPointer;
    };
    void stop()
    {
        trigger = false;
    }
};