#include "../Header/MapLoader.h"
#include <fstream>

const std::string delimiter = ",";

MapLoader* MapLoader::s_pInstance = nullptr;

MapLoader* MapLoader::getInstance() {
    if(!s_pInstance){
        s_pInstance = new MapLoader();
    }
    return s_pInstance;
}

Node* stringToNode(std::string line) {
    int values[8];
    int i = 0;
    std::string token;
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        values[i] = std::stoi(token);
        line.erase(0, pos + delimiter.length());
        i++;
    }
    return new Node(new Point((float)values[0], (float)values[1]), new Point((float)values[2], (float)values[3]), new Point((float)values[4], (float)values[5]), new Point((float)values[6], (float)values[7]));
}

std::vector<Node *> MapLoader::load(const std::string& filename) {
    std::ifstream file;
    std::string line;
    file.open(filename);

    std::vector<Node *> res;

    if ( file.is_open() ) {
        while ( file ) {
            std::getline (file, line);
            res.push_back(stringToNode(line));
        }
    }

    file.close();
    return res;
}