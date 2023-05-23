#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
class TimeObserver
{
private:
    std::thread observeThread;
public:
    bool trigger;
    int* tick;
    void observeTime ()
    {
        while (trigger)
        {
        }
    };
    void start()
    {   
        trigger = true;
        observeThread = std::thread(&TimeObserver::observeTime, this);
    };
    void stop(){
        trigger = false;
        observeThread.join();
    }
};