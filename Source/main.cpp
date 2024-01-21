#include "../Header/Game.h"

const int TARGET_FPS = 60;
const int TARGET_FRAMETIME = 1000 / TARGET_FPS;
unsigned long long currentFrametime = 0;

int main(int argc, char* argv[]) {
    if(Game::getInstance()->initialise()){
        while(Game::getInstance()->isRunning()){
            currentFrametime = SDL_GetTicks64();

            Game::getInstance()->handleInput();
            Game::getInstance()->update();
            Game::getInstance()->render();

            currentFrametime = SDL_GetTicks64() - currentFrametime;
            if(currentFrametime < TARGET_FRAMETIME){
                SDL_Delay(TARGET_FRAMETIME - currentFrametime);
            }
        }
        Game::getInstance()->quit();
    }
    return 0;
}