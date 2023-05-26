#include "Game.h"
#include "MainLoop.h"
// Abaixo e o codigo que carrega o icone de janela
static void setIcon(SDL_Window *window)
{
#include "Icon.c"
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int shift = (icomImage.bytes_per_pixel == 3) ? 8 : 0;
    rmask = 0xff000000 >> shift;
    gmask = 0x00ff0000 >> shift;
    bmask = 0x0000ff00 >> shift;
    amask = 0x000000ff >> shift;
#else // little endian, para CPUs x86
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
// Esse e o ponto de entrada, aqui estamos cheando se e Windows, pois no Windows o ponto de entrada e WinMain
#ifdef _WIN32
int WinMain()
#else
int Main()
#endif
{
    gameWin game;
    mainLoop masterBehaviour;
    if (!game.OpenGame(NULL)) //Verificando se os componentes iniciram com sucesso
    {
        setIcon(game.window);
        game.OpenRender();
        masterBehaviour.gameLoop(game.window, game.renderer);
        game.CloseGame();
    }
    return 0;
}
