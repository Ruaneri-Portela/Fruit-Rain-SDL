#include "Game.h"
#include "MainLoop.h"
int WinMain()
{
    std::cout << "Starting Game" << std::endl;
    gameWin game;
    mainLoop masterBehaviour;
    if (!game.OpenWin())
    {
        std::cout << "Windows system over SDL started" << std::endl;
    }
    if (!game.OpenRender())
    {
        std::cout << "Acelerated rendering started" << std::endl;
    }
    if (!masterBehaviour.gameLoop(game.window, game.renderer))
    {
        std::cout << "Game loop drop" << std::endl;
    }
    if (!game.CloseAll())
    {
        std::cout << "End SDL successfully" << std::endl;
    }
    std::cout << "Exiting" << std::endl;
    return 0;
}
