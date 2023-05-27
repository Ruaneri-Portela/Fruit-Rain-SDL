#include <sstream>
#include "Scenario.h"
#include "Audio.h"
#include "Fruit.h"
#include "Debug.h"
// Esse e o loop principal, pode parecer uma bagunça, mais em resumo as ações são todas invocadas por aqui
class mainLoop
{
private:
    int frameCount = 0;
    int fpsC = 0;
    int currentTime;
    int elapsedTime;
    int startTime = 0;
    int speedMove = 20;
    int mouseX, mouseY;
    int count = 0;
    int lockFPS = 0;
    bool lokedFPS = false;
    bool mouseEnabled = false;
    bool running = true;
    bool debugLogEnabled = false;
    AudioDevice mainTrack;
    AudioData touch;
    AudioData music;
    BackgroudImage scene;
    Player playerOne;
    DebugLogger playerDebug;
    Fruit gameFruits;
    std::string muted = "";
    std::string lokedFrameRate = "";
    std::string spritePlayer = "assets/texture/player.png";
    std::string spritePlayerA = "assets/texture/playerA.png";
    std::stringstream title;

public:
    int gameLoop(SDL_Window *window, SDL_Renderer *renderer)
    {
        // Relativos ao som
        Mix_Chunk *sound = touch.load("assets/audio/audio2.wav");
        Mix_Chunk *sound2 = music.load("assets/audio/audio.wav");
        gameFruits.sound = touch.load("assets/audio/audio6.wav");
        gameFruits.sound2 = touch.load("assets/audio/audio7.wav");
        gameFruits.mainTrack = &mainTrack;
        // Relativos ao Delta Time
        startTime = SDL_GetTicks();
        playerOne.tick = &elapsedTime;
        gameFruits.tick = &elapsedTime;
        gameFruits.onePlayer = &playerOne;
        // Relativos ao desenho de itens da interface
        scene.loadBackgroud(renderer, "assets/texture/bitmap.png", "assets/ttf/CadetTest-Black.otf");
        playerOne.loadSprite(renderer, spritePlayer,spritePlayerA);
        playerOne.mouseEnabled = &mouseEnabled;
        playerOne.speedY = 20;
        gameFruits.init(renderer);
        SDL_ShowWindow(window);
        SDL_Event event;
        while (running)
        {
            title.str(""); // Reinicia o conteúdo como uma string vazia
            title.clear();
            title << "Fruit Rain SDL Edition Version 0.1 MinGW";
            // Isso aqui corrige o tempo para o Delta time
            currentTime = SDL_GetTicks();
            elapsedTime = currentTime - startTime;
            // Ações do jogo (Movimento, som, vida e etc...)
            while (SDL_PollEvent(&event))
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        playerOne.move(0, -speedMove);
                        mainTrack.play(sound, -1);
                        break;
                    case SDLK_a:
                        playerOne.move(-speedMove, 0);
                        mainTrack.play(sound, -1);
                        break;
                    case SDLK_s:
                        playerOne.move(0, speedMove);
                        mainTrack.play(sound, -1);
                        break;
                    case SDLK_d:
                        playerOne.move(speedMove, 0);
                        mainTrack.play(sound, -1);
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_m:
                        mainTrack.playable = !mainTrack.playable;
                        if (mainTrack.playable)
                        {
                            muted = "";
                        }
                        else
                        {
                            Mix_HaltChannel(-1);
                            muted = " (Sem Som)";
                        }
                        mainTrack.play(sound, -1);
                        break;
                    case SDLK_F1:
                        std::cout << "\033[2J"; // Limpar o terminal
                        debugLogEnabled = !debugLogEnabled;
                        if (debugLogEnabled)
                        {
                            playerDebug.start(&playerOne);
                        }
                        else
                        {
                            playerDebug.stop();
                        }
                        break;
                    case SDLK_F2:
                        fullScreen(window);
                        break;
                    case SDLK_F3:
                        mouseEnabled = !mouseEnabled;
                        break;

                    case SDLK_F4:
                        lockFPS = 20;
                        lokedFPS = !lokedFPS;
                        lokedFrameRate = " (FPS Locked)";
                        if (lokedFPS == false)
                        {
                            lockFPS = 0;
                            lokedFrameRate = "";
                        }
                        break;
                    }
                }
                else if (event.type == SDL_KEYUP)
                {
                    switch (event.key.keysym.sym)
                    {
                    }
                }
                if (mouseEnabled)
                {
                    playerOne.moveToMouse(mouseX, mouseY);
                };
                if (!mainTrack.isPlaying(0))
                {
                    mainTrack.play(sound2, 0);
                }
            }
            // Redraw da janela
            if (count > (int)(fpsC / 30))
            {
                SDL_RenderClear(renderer);
                scene.draw(renderer);
                count = 0;
            }
            SDL_Delay(lockFPS);
            scene.scoreUpdate(renderer, gameFruits.update());
            playerOne.draw(renderer);
            SDL_RenderPresent(renderer);
            countFPS(window);

            count++;
            
        }
        // Ponto de descarga
        if (debugLogEnabled)
        {
            playerDebug.stop();
        };
        gameFruits.destroy();
        scene.destroy();
        touch.unload(sound);
        music.unload(sound2);
        return 0;
    };
    // Contador de FPS
    void countFPS(SDL_Window *window)
    {
        frameCount++;
        if (elapsedTime >= 1000)
        {
            float fps = frameCount / (elapsedTime / 1000.0f);
            fpsC = frameCount;
            title << muted <<lokedFrameRate << " (FPS:"<< fpsC << ")" << std::endl;
            std::string windowTitle = title.str();
            SDL_SetWindowTitle(window, windowTitle.c_str());
            frameCount = 0;
            startTime = currentTime;
        }
    };
    // Tela inteira
    void fullScreen(SDL_Window *window)
    {
        Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
        bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
        SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
        SDL_ShowCursor(IsFullscreen);
    };
};