<<<<<<< HEAD
#include "../Header/Map.h"

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
    m_NodeList.push_back(new Node(new Point(50, 50), new Point(590, 50), new Point(185, 145), new Point(455, 145)));
    m_NodeList.push_back(new Node(new Point(50, 50), new Point(50, 430), new Point(185, 145), new Point(185, 335)));
    m_NodeList.push_back(new Node(new Point(50, 430), new Point(590, 430), new Point(185, 335), new Point(455, 335)));
    m_NodeList.push_back(new Node(new Point(590, 50), new Point(590, 430), new Point(455, 145), new Point(455, 335)));
}
=======
//
// Created by lukasz on 12/12/23.
//

#include "../Header/Map.h"

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
    //m_NodeList.push_back(new Node(new Point(50, 50), new Point(590, 50), new Point(185, 145), new Point(455, 145)));
    //m_NodeList.push_back(new Node(new Point(50, 50), new Point(50, 430), new Point(185, 145), new Point(185, 335)));
    //m_NodeList.push_back(new Node(new Point(50, 430), new Point(590, 430), new Point(185, 335), new Point(455, 335)));
    //m_NodeList.push_back(new Node(new Point(590, 50), new Point(590, 430), new Point(455, 145), new Point(455, 335)));

    m_NodeList = MapLoader::getInstance()->load("../Assets/triangle.map");

}
>>>>>>> 4217a4db963331001f174237192ad3a723382fe7
