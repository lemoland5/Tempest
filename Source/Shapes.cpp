#include "../Header/Shapes.h"
#include <cmath>

Point* Line::calculateTValuePoint(float t) const {




    return new Point((m_pBegin->x * (1 - t)) + (m_pEnd->x * t), (m_pBegin->y * (1 - t)) + (m_pEnd->y * t));
}

[[maybe_unused]] float Line::getLength() const {
    return (float)sqrt(pow(m_pBegin->x - m_pEnd->x, 2) + pow(m_pBegin->y - m_pEnd->y, 2));
}

float Line::getAngle() const {
    return radianToDegree(atan2(m_pEnd->x - m_pBegin->x, m_pBegin->y - m_pEnd->y));
}

Line::~Line() {
    delete m_pBegin;
    delete m_pEnd;
}
