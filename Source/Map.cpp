#include "../Header/Map.h"
#include "../Header/MapLoader.h"

void Map::draw(SDL_Renderer *renderer) {
    for(Node* element: m_NodeList){
        element->draw(renderer,m_Color);
    }
}

Map::Map() {
    m_NodeList = MapLoader::getInstance()->load("../Assets/final.map");
    m_Color = COLOR_MAP_PURPLE;
}