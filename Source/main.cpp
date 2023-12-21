<<<<<<< HEAD
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
=======
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
>>>>>>> 4217a4db963331001f174237192ad3a723382fe7
