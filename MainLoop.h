#include <sstream>
#include "Audio.h"
#include "Scenario.h"
#include "Fruit.h"
#include "Debug.h"
#include "TextDraw.h"

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
    int currentTime;
    int elapsedTime;
    DebugLogger playerDebug;
    Fruit gameFruits;
    SDL_Texture *texture;
    SDL_Texture *texture2;
    SDL_Texture *texture3;
    bool interpolation = false;
    TextTexture score;
    int scoreGame=0;
public:
    int gameLoop(SDL_Window *window, SDL_Renderer *renderer)
    {
        std::cout << "@@ Main game loop getted" << std::endl;
        // Audio
        mainTrack.init();
        Mix_Chunk *sound = touch.load("assets/audio/audio2.wav");
        Mix_Chunk *sound2 = music.load("assets/audio/audio.wav");
        gameFruits.sound = touch.load("assets/audio/audio6.wav");
        gameFruits.sound2 = touch.load("assets/audio/audio7.wav");
        gameFruits.mainTrack = &mainTrack;
        // Bakcgroud
        scene.loadBackgroud(renderer, "assets/texture/bitmap.png");
        char filename[] = "assets/ttf/RampartOne-Regular.ttf";
        // Triggers
        startTime = SDL_GetTicks();
        bool running = true;
        SDL_Event event;
        playerOne.tick = &elapsedTime;
        gameFruits.init(renderer);
        gameFruits.tick = &elapsedTime;
        gameFruits.onePlayer = &playerOne;
        char text[10] = "0";
        score.load(filename);
        score.render(renderer, 0, 0, text);
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
                    }
                }
                if (!mainTrack.isPlaying(0))
                {
                    mainTrack.play(sound2, 0);
                }
            }
            SDL_RenderClear(renderer);
            scene.draw(renderer);
            switch (gameFruits.update())
            {
            case 1:
                scoreGame = scoreGame+1;
                sprintf(text, "%d", scoreGame);
                score.render(renderer, 0, 0, text);
                std::cout << scoreGame << "Pt" << std::endl;
                
                break;
            case 2:
                std::cout << "-1Hp" << std::endl;
                break;
            }
            playerOne.draw(renderer);
            score.lazyRender(renderer);
            SDL_RenderPresent(renderer);
            countFPS(window);
        }
        gameFruits.destroy();
        if (debugLogEnabled)
        {
            playerDebug.stop();
        };
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
            title << "Fruit Rain SDL Edition FPS: " << fps << muted << std::endl;
            std::string windowTitle = title.str();
            SDL_SetWindowTitle(window, windowTitle.c_str());
            frameCount = 0;
            startTime = currentTime;
        }
    };
    void fullScreen(SDL_Window *window)
    {
        Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
        bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
        SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
        SDL_ShowCursor(IsFullscreen);
    };
};