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
    return new Node(new Point(values[0], values[1]), new Point(values[2], values[3]), new Point(values[4], values[5]), new Point(values[6], values[7]));
}

std::vector<Node *> MapLoader::load(std::string filename) {
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