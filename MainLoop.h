#include <sstream>
#include "Player.h"
#include "Entity.h"
#include "Audio.h"
#include "Scenario.h"
#include "Time.h"
class mainLoop
{
private:
    int frameCount = 0;
    int startTime = 0;
    AudioDevice mainTrack;
    AudioData touch;
    AudioData music;
    BackgroudImage scene;
    Player playerOne;
    std::string muted = "";
    int speedMove = 20;
    bool debugLogEnabled = false;
    TimeObserver obeserver;
    int currentTime;
    int elapsedTime;
public:
    int gameLoop(SDL_Window *window, SDL_Renderer *renderer)
    {
        std::cout << "@@ Main game loop getted" << std::endl;
        // Audio
        mainTrack.init();
        Mix_Chunk *sound = touch.load("assets/audio/touch.wav");
        Mix_Chunk *sound2 = music.load("assets/audio/audio.wav");
        // Bakcgroud
        scene.loadBackgroud(renderer, "assets/texture/bitmap.png");
        // Triggers
        startTime = SDL_GetTicks();
        bool running = true;
        SDL_Event event;
        obeserver.start();
        obeserver.tick = &elapsedTime;
        playerOne.tick = &elapsedTime;
        while (running)
        {
            currentTime = SDL_GetTicks();
            elapsedTime = currentTime - startTime;
            while (SDL_PollEvent(&event))
            {
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
                        debugLogEnabled =!debugLogEnabled;
                        break;
                    }
                }
                if (!mainTrack.isPlaying(0))
                {
                    mainTrack.play(sound2, 0);
                }
                debugLog();
            }
            SDL_RenderClear(renderer);
            scene.draw(renderer);
            playerOne.draw(renderer);
            SDL_RenderPresent(renderer);
            countFPS(window);
        }
        obeserver.stop();
        scene.destroy();
        touch.unload(sound);
        music.unload(sound2);
        mainTrack.end();
        return 0;
    };
    void countFPS(SDL_Window *window)
    {
        frameCount++;
        if (elapsedTime >= 1000)
        {
            float fps = frameCount / (elapsedTime / 1000.0f);
            std::stringstream title;
            title << "Game Windows FPS: " << fps << muted << std::endl;
            std::string windowTitle = title.str();
            SDL_SetWindowTitle(window, windowTitle.c_str());
            frameCount = 0;
            startTime = currentTime;
        }
    };
    void debugLog(){
        if(debugLogEnabled){
        std::cout << "\033[2J"; // Limpar o terminal
        std::cout << "\033[H" << "Degub Logger\n==========" << std::endl; //Tabular para ponto 1:1
        std::cout << "Player Position: X=>" << playerOne.x << " Y=>" << playerOne.y << std::endl;
        }
    };
};