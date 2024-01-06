#include "../Header/Shapes.h"
#include <cmath>

Point* Line::calculateTValuePoint(float t) const {
//    float d = getLength();
//    float dt = d * t;
//    float ratio = dt/d;

    return new Point((begin.x * (1 - t)) + (end.x * t), (begin.y * (1 - t)) + (end.y * t));
}

float Line::getLength() {
    return sqrt(pow(begin.x - end.x, 2) + pow(begin.y - end.y, 2));
}
