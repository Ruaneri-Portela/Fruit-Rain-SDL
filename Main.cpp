#include "Game.h"
#include "MainLoop.h"

static void SetSDLIcon(SDL_Window *window)
{
#include "Icon.c"
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int shift = (icomImage.bytes_per_pixel == 3) ? 8 : 0;
    rmask = 0xff000000 >> shift;
    gmask = 0x00ff0000 >> shift;
    bmask = 0x0000ff00 >> shift;
    amask = 0x000000ff >> shift;
#else // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = (icomImage.bytes_per_pixel == 3) ? 0 : 0xff000000;
#endif
    SDL_Surface *icon = SDL_CreateRGBSurfaceFrom((void *)icomImage.pixel_data, icomImage.width,
                                                 icomImage.height, icomImage.bytes_per_pixel * 8, icomImage.bytes_per_pixel * icomImage.width,
                                                 rmask, gmask, bmask, amask);
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
}

#ifdef _WIN32 // Verifica se e windows para por o WINMAIN como entrypoint
int WinMain()
#else
int Main()
#endif
{
    std::cout << "Starting Game" << std::endl;
    gameWin game;
    mainLoop masterBehaviour;
    int returnReset = false;
    if (!game.OpenGame(NULL))
    {
        std::cout << "Windows system over SDL started" << std::endl;
        SetSDLIcon(game.window);
    }
    if (!game.OpenRender())
    {
        std::cout << "Acelerated rendering started" << std::endl;
    }
    if (!masterBehaviour.gameLoop(game.window, game.renderer))
    {
        std::cout << "Game loop drop" << std::endl;
    }
    if (!game.CloseGame())
    {
        std::cout << "End SDL successfully" << std::endl;
    }
    std::cout << "Exiting" << std::endl;
    return 0;
}