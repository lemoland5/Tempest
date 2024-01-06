#include "../Header/Shapes.h"
#include <cmath>

Point Line::calculateTValuePoint(float t) const {
//    float d = getLength();
//    float dt = d * t;
//    float ratio = dt/d;

    Point tValuePoint((begin.x * (1 - t)) + (end.x * t), (begin.x * (1 - t)) + (end.x * t));
    return tValuePoint;
}

float Line::getLength() {
    return sqrt(pow(begin.x - end.x, 2) + pow(begin.y - end.y, 2));
}
