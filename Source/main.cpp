#include "../Header/Game.h"

int main(int argc, char* argv[]) {
    if(Game::getInstance()->initialise()){
        while(Game::getInstance()->isRunning()){
            Game::getInstance()->handleInput();
            Game::getInstance()->update();
            Game::getInstance()->render();
        }
    }
    return 0;
}
