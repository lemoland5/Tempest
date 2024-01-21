#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

//// Windowsowy cmath nie zawiera M_PI, bruh
//#if defined(_WIN32) || defined(WIN32)
//#define M_PI 3.1415
//#endif

const int LINE_T_SCALE = 200;

struct Point{
public:
    Point( float x,  float y): x(x), y(y) {};
    explicit Point( float xy): x(xy), y(xy) {};
    Point(): x(1), y(1) {};
     float x;
     float y;
};

struct Line{
public:
    Line( int x1,  int y1,  int x2,  int y2): m_pBegin(new Point(x1, y1)), m_pEnd(new Point(x2, y2)){};
    Line(Point* m_pBegin, Point* m_pEnd): m_pBegin(m_pBegin), m_pEnd(m_pEnd){};
    Line(): m_pBegin(new Point(1,1)), m_pEnd(new Point(2,1)){};
    ~Line();


    [[nodiscard]] float getLength() const;
    [[nodiscard]] float getAngle() const;

    [[nodiscard]] Point* calculateTValuePoint(float t) const;

    Point* m_pBegin;
    Point* m_pEnd;
};

inline float degreeToRadian(float angle){
    return angle * M_PI / 180;
}

inline float radianToDegree(float angle){
    return (angle * 180) / M_PI;
}
inline Point* rotatePoint(Point* pivot, Point* point, float angle){
//    return new Point(
//            (int)(cos(angle) * (float)(point->x - pivot->x) - sin(angle) * (float)(point->y - pivot->y) + (float)pivot->x),
//            (int)(sin(angle) * (float)(point->x - pivot->x) - cos(angle) * (float)(point->y - pivot->y) + (float)pivot->y)
//            );

    angle = degreeToRadian(angle);
    float s = sin(angle);
    float c = cos(angle);

    point->x -= pivot->x;
    point->y -= pivot->y;

    float newX = (point->x * c) - (point->y * s);
    float newY = (point->x * s) + (point->y * c);

    point->x = newX + pivot->x;
    point->y = newY + pivot->y;
//
//    point->x = ((point->x - pivot->x) * c) - ((point->x - pivot->y) * s) + pivot->x;
//    point->x = ((point->x - pivot->x) * c) + ((point->x - pivot->y) * s) + pivot->y;

    return point;
}