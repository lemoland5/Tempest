#include "../Header/SfxManager.h"
#include <filesystem>
#include <iostream>

SfxManager* SfxManager::m_pInstance = nullptr;

SfxManager* SfxManager::getInstance(){
    if(!m_pInstance){
        m_pInstance = new SfxManager;
    }
    return m_pInstance;
}

void SfxManager::loadSound(std::string path, std::string id) {

    if(std::filesystem::exists(path.c_str())){
        std::cout<<"Sound file exists chilllax \n";
    }

    m_pSounds[id] = NULL;
    m_pSounds[id] = Mix_LoadWAV(path.c_str());

    testSound = Mix_LoadWAV(path.c_str());
    if(testSound == NULL){
        std::cout<<"testSound is fucked :3 \n";
    }
    else{
        std::cout<<"testsound is cool \n";
    }

    if(m_pSounds[id] == NULL){
        printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void SfxManager::playSound(std::string id) {
    Mix_PlayChannel(-1, m_pSounds[id], 0);
}
