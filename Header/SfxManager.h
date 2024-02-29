#pragma once

#include <map>
#include <SDL_mixer.h>
#include <string>

class SfxManager {
public:

    void loadSound(const std::string& path, const std::string& id);
    int playSound(const std::string& id);

    static SfxManager* getInstance();
private:
    SfxManager(){};
    static SfxManager* m_pInstance;

    std::map<std::string, Mix_Chunk*> m_pSounds;
};