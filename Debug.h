#include <iostream>
#include <SDL2/SDL.h>

struct ThreadData
{
    Player* player;
    bool trigger;
};

class DebugLogger
{
private:
    static int action(void* data)
    {
        ThreadData* threadData = static_cast<ThreadData*>(data);
        while (threadData->trigger)
        {
            std::cout << "\033[H"<< "Debug Logger\n==============================" << std::endl;
            std::cout << "Player Position: X=>" << threadData->player->square.x << " Y=>" << threadData->player->square.y << std::endl;
            std::cout << "==============================" << std::endl;
        }
        return 0;
    }

public:
    SDL_Thread* thread;
    ThreadData dataThead;
    void start(Player* playerPointer)
    {
        dataThead.player = playerPointer;
        dataThead.trigger = true;
        thread = SDL_CreateThread(action, "MinhaThread", &dataThead);
    }
    void stop()
    {
        dataThead.trigger = false;
    }
};
