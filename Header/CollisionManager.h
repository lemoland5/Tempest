#pragma once
#include "iostream"
#include "vector"

class CollisionManager {
public:
    template<class T>
    static void ObjectsColliding(std::vector<int> m_NodeRep, std::vector<T*> m_pActors) {
        for (int i = 0; i<m_NodeRep.size(); i++) {
            if (m_NodeRep[i] < 2) continue;
            std::vector<T*> tmp;
            for(int j = 0; j < m_pActors.size(); j++){
                if (m_pActors[j]->getMapPosition()->x == i) tmp.push_back(m_pActors[j]);
            }
            for(int j = 0; j < tmp.size(); j++) {
                for (int k = j+1; k < tmp.size(); k++) {
                    if (tmp[j]->getMapPosition()->y == tmp[k]->getMapPosition()->y) {
                        //std::cout << "Collision Detected Between: " << tmp[j] << " & " << tmp[k] << std::endl;
                        tmp[j]->onCollide(tmp[k]->getType());
                        tmp[k]->onCollide(tmp[j]->getType());
                    }
                }
            }
        }
    }
};