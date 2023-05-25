#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
class DebugLogger
{
private:
    Player* player;
    Entity* entity;
    std::thread debuggerA;
    void action()
    {
        while (true)
        {
            std::cout << "\033[H" << "Degub Logger\n==========" << std::endl; //Tabular para ponto 1:1
            std::cout << "Player Position: X=>" << entity->x << " Y=>" << entity->y << std::endl;
        }
    };
    void action2()
    {
        while (true)
        {
            std::cout << "\033[H" << "Degub Logger\n==========" << std::endl; //Tabular para ponto 1:1
            std::cout << "Player Position: X=>" << entity->x << " Y=>" << entity->y << std::endl;
        }
    };

public:
    void start(Player* PlayerPointer)
    {
        debuggerA = std::thread(&DebugLogger::action, this);
        player = PlayerPointer;
    };
    void start2(Entity* entityPointer)
    {
        debuggerA = std::thread(&DebugLogger::action2, this);
        entity = entityPointer;
    };
    void stop()
    {
        debuggerA.join();
    }
};