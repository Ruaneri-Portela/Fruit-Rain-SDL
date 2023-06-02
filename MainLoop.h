#include <sstream>
#include "Scenario.h"
#include "Audio.h"
#include "Fruit.h"
#include "Debug.h"
// Esse e o loop principal, pode parecer uma bagunça, mais em resumo as ações são todas invocadas por aqui
class MainLoop
{
private:
    // Variaveis do jogo
    int resetStatus = 0;
    int speedMove = 20;
    int frameCount = 0;
    int startTime = 0;
    int fpsCount = 0;
    int lockFPS = 0;
    int count = 0;
    int currentTime = 0;
    int elapsedTime = 0;
    int mouseX = 0;
    int mouseY = 0;
    float fallSpeed = 10;
    bool debugLogEnabled = false;
    bool mouseEnabled = false;
    bool lokedFPS = false;
    bool paused = false;
    bool running = true;
    bool gameover = false;
    AudioDevice mainTrack;
    AudioData touch;
    AudioData music;
    BackgroudImage scene;
    Player playerOne;
    DebugLogger playerDebug;
    Fruit gameFruits;
    std::string pauseFont = "assets/ttf/RampartOne-Regular.ttf";
    std::string spritePlayerA = "assets/texture/playerA.png";
    std::string spritePlayer = "assets/texture/player.png";
    std::string lokedFrameRate = "";
    std::string muted = "";
    std::stringstream title;
    TextTexture pauseAlert;
    SDL_Event event;

public:
    void GameControler(Mix_Chunk *sound, SDL_Window *window, Mix_Chunk *sound2, SDL_Renderer *renderer, Mix_Chunk* sound3)
    {
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
                case SDLK_p:
                    paused = !paused;
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

                case SDLK_F5:
                    resetStatus = 1;
                    running = false;
                    break;
                }
            };
            // Switch do mouse controler
            if (mouseEnabled)
            {
                playerOne.moveToMouse(mouseX, mouseY);
            }
            if (!mainTrack.isPlaying(0))
            {
                mainTrack.play(sound2, 0);
            }
            // Fluxo de Pause
            while (paused)
            {
                Mix_HaltChannel(-1);
                Mix_HaltChannel(0);
                pauseAlert.render(renderer, 250, 200, 64, 100, "Paused!");
                pauseAlert.lazyRender(renderer);
                SDL_RenderPresent(renderer);
                while (paused) {
                    while (SDL_PollEvent(&event))
                    {
                        SDL_SetWindowTitle(window, "Paused");
                        if (event.type == SDL_QUIT)
                        {
                            running = false;
                            paused = false;
                        }
                        else if (event.type == SDL_KEYDOWN)
                        {
                            switch (event.key.keysym.sym)
                            {
                            case SDLK_p:
                                paused = false;
                                break;

                            case SDLK_ESCAPE:
                                playerOne.move(0, -speedMove);
                                running = false;
                                paused = false;
                                break;
                            }
                        }
                    }
                }
                
            };
            while (gameover) {
                Mix_HaltChannel(-1);
                Mix_HaltChannel(0);
                mainTrack.play(sound3, -1);
                pauseAlert.render(renderer, 200, 200, 64, 100, "Game Over!");
                pauseAlert.lazyRender(renderer);
                SDL_RenderPresent(renderer);
                while (gameover){
                    while (SDL_PollEvent(&event))
                    {
                        SDL_SetWindowTitle(window, "Game Over");
                        if (event.type == SDL_QUIT)
                        {
                            running = false;
                            gameover = false;
                        }
                        else if (event.type == SDL_KEYDOWN)
                        {
                            switch (event.key.keysym.sym)
                            {
                            case SDLK_F5:
                                resetStatus = 1;
                                running = false;
                                gameover = false;
                                break;
                            case SDLK_ESCAPE:
                                running = false;
                                gameover = false;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    int gameLoop(SDL_Window *window, SDL_Renderer *renderer)
    {
        // Relativos ao som
        Mix_Chunk *sound = touch.load("assets/audio/audio2.wav");
        Mix_Chunk *sound2 = music.load("assets/audio/audio.wav");
        Mix_Chunk* sound3 = music.load("assets/audio/audio5.wav");
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
        playerOne.loadSprite(renderer, spritePlayer, spritePlayerA);
        playerOne.mouseEnabled = &mouseEnabled;
        gameFruits.init(renderer);
        SDL_ShowWindow(window);
        pauseAlert.load(pauseFont);
        while (running)
        {
            title.str(""); // Reinicia o conteúdo como uma string vazia
            title.clear();
            title << "Fruit Rain SDL Edition Version 0.1";
#ifdef _MSC_VER
            title << " (MSVC)";
#else
            title << " (G++ or MinGw for Windows)";
#endif
            // Isso aqui corrige o tempo para o Delta time
            currentTime = SDL_GetTicks();
            elapsedTime = currentTime - startTime;
            // Ações do jogo (Movimento, som, vida e etc...)
            GameControler(sound, window, sound2, renderer, sound3);
            if (playerOne.health < 0) {
                gameover = true;
            }
            // Redraw da janela
            if (count > (int)(fpsCount / 30))
            {
                SDL_RenderClear(renderer);
                scene.draw(renderer);
                count = 0;
            }
            SDL_Delay(lockFPS);
            scene.scoreUpdate(renderer, gameFruits.update(&fallSpeed));
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
        return resetStatus;
    };
    // Contador de FPS
    void countFPS(SDL_Window *window)
    {
        if (elapsedTime >= 1000)
        {
            fpsCount = frameCount;
            title << muted << lokedFrameRate << " (FPS:" << fpsCount << ")" << std::endl;
            std::string windowTitle = title.str();
            SDL_SetWindowTitle(window, windowTitle.c_str());
            frameCount = 0;
            startTime = currentTime;
        }
        frameCount++;
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