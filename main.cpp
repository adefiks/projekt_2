// main project 06.02.2019

#include "include/main.h"

int WinMain(int argc, char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    uint32_t frameStart;
    int frameTime;

    // Game object
    Game game;

    game.init("2D platform game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, false);

    while (game.running())
    {
        frameStart = SDL_GetTicks();

        game.handleEvents();
        game.update();
        game.render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        // cout << frameTime << endl;
    }

    game.clean();

    return 0;
}
