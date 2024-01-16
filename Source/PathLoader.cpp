#include "../Header/PathLoader.h"
#include <fstream>
#include <string>

PathLoader *PathLoader::s_pInstance = nullptr;

PathLoader *PathLoader::getInstance() {
    if(!s_pInstance) s_pInstance = new PathLoader;
    return s_pInstance;
}

const std::string delimiter = ",";

Line* stringToLine(std::string line) {
    int values[4];
    int i = 0;
    std::string token;
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        values[i] = std::stoi(token);
        line.erase(0, pos + delimiter.length());
        i++;
    }
    return new Line(new Point(values[0], values[1]), new Point(values[2], values[3]));
}

std::vector<Line *> PathLoader::loadPath(std::string path) {
    std::ifstream file;
    std::string line;
    file.open(path);

    std::vector<Line *> res;

    if ( file.is_open() ) {
        while ( file ) {
            std::getline (file, line);
            res.push_back(stringToLine(line));
        }
    }
    return res;
}