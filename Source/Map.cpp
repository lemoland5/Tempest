#include "../Header/Map.h"
#include "../Header/MapLoader.h"

//Map::Map(Node* nodes[]) {
//    for(unsigned int i = 0; i < MAX_SEGMENTS; i++){
//        if(!nodes[i]){
//            m_NodeList[i] = nullptr;
//        }
//        else{
//            m_NodeList[i] = nodes[i];
//        }
//    }
//}

void Map::draw(SDL_Renderer *renderer) {
    for(Node* element: m_NodeList){
        element->draw(renderer);
    }
}

Map::Map() {
    m_NodeList = MapLoader::getInstance()->load("../Assets/firstMap.map");
}
