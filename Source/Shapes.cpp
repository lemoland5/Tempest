#include "../Header/Shapes.h"
#include <cmath>

Point* Line::calculateTValuePoint(float t) const {
//    float d = getLength();
//    float dt = d * t;
//    float ratio = dt/d;

    return new Point((m_pBegin->x * (1 - t)) + (m_pEnd->x * t), (m_pBegin->y * (1 - t)) + (m_pEnd->y * t));
}

float Line::getLength() const {
    return sqrt(pow(m_pBegin->x - m_pEnd->x, 2) + pow(m_pBegin->y - m_pEnd->y, 2));
}

float Line::getAngle() const {
    return radianToDegree(atan2(m_pEnd->x - m_pBegin->x, m_pBegin->y - m_pEnd->y));
}
