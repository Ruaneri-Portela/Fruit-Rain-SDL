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
// Esse e o ponto de entrada, aqui estamos checando se e Windows, pois no Windows o ponto de entrada e WinMain
#ifdef _WIN32
#ifdef _MSC_VER
int SDL_main(int argc, char *argv[]) // Para o Visual Studio via Microsoft Visual C++ Compiler
#else
int WinMain(int argc, char *argv[]) // Para o ambiente de compilação MinGw/MSYS2
#endif
#else
int main(int argc, char *argv[]) // Unix-like (Linux, BSDs e MacOS)
#endif
{
    if(argc > 0){
        for(int i = 0; i < argc; i++){
           // printf("%s\n", argv[i]);
        };
    };
    gameWin game;
    MainLoop *masterBehaviour = NULL;
    int resetStatus = 1;
    if (!game.OpenGame(NULL)) // Verificando se os componentes iniciram com sucesso
    {
        setIcon(game.window);
        game.OpenRender();
        while (resetStatus == 1) {
            masterBehaviour = new MainLoop;
            resetStatus = masterBehaviour->gameLoop(game.window, game.renderer);
            delete masterBehaviour;
            printf("Exit with code ->%d", resetStatus);
        }
        game.CloseGame();
    }
    return 0;
}
