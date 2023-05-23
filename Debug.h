#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
class DebugLogger
{
private:
    Player* player;
    std::thread debuggerA;
    void action()
    {
        while (true)
        {
            std::cout << "\033[H" << "Degub Logger\n==========" << std::endl; //Tabular para ponto 1:1
            std::cout << "Player Position: X=>" << player->x << " Y=>" << player->y << std::endl;
        }
    };

public:
    void start(Player* PlayerPointer)
    {
        debuggerA = std::thread(&DebugLogger::action, this);
        player = PlayerPointer;
    };
    void stop()
    {
        debuggerA.join();
    }
};