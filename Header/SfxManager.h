#pragma once

#include <map>
#include <SDL_mixer.h>
#include <string>

class SfxManager {
public:

    void loadSound(std::string path, std::string id);
    void playSound(std::string id);

    static SfxManager* getInstance();
private:
    SfxManager(){};
    static SfxManager* m_pInstance;

    std::map<std::string, Mix_Chunk*> m_pSounds;

    Mix_Chunk* testSound = NULL;
};