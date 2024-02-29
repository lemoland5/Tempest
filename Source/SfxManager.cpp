#include "../Header/SfxManager.h"
#include <filesystem>

SfxManager* SfxManager::m_pInstance = nullptr;

SfxManager* SfxManager::getInstance(){
    if(!m_pInstance){
        m_pInstance = new SfxManager;
    }
    return m_pInstance;
}

void SfxManager::loadSound(const std::string& path, const std::string& id) {

    m_pSounds[id] = nullptr;
    m_pSounds[id] = Mix_LoadWAV(path.c_str());

    if(m_pSounds[id] == nullptr){
        printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

int SfxManager::playSound(const std::string& id) {
    return Mix_PlayChannel(-1, m_pSounds[id], 0);
}
