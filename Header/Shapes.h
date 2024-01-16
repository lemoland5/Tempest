#pragma once

#include <cmath>

const int LINE_T_SCALE = 200;

struct Point{
public:
    Point( int x,  int y): x(x), y(y) {};
    explicit Point( int xy): x(xy), y(xy) {};
    Point(): x(1), y(1) {};
     double x;
     double y;
};

struct Line{
public:
    Line( int x1,  int y1,  int x2,  int y2): m_pBegin(new Point(x1, y1)), m_pEnd(new Point(x2, y2)){};
    Line(Point* m_pBegin, Point* m_pEnd): m_pBegin(m_pBegin), m_pEnd(m_pEnd){};
    Line(): m_pBegin(new Point(1,1)), m_pEnd(new Point(2,1)){};

    float getLength();

    [[nodiscard]] Point* calculateTValuePoint(float t) const;

    Point* m_pBegin;
    Point* m_pEnd;
};

inline double degreeToRadian(double angle){
    return angle * M_PI / 180;
    return angle * 0.01745f;
}

inline Point* rotatePoint(Point* pivot, Point* point, double angle){
//    return new Point(
//            (int)(cos(angle) * (float)(point->x - pivot->x) - sin(angle) * (float)(point->y - pivot->y) + (float)pivot->x),
//            (int)(sin(angle) * (float)(point->x - pivot->x) - cos(angle) * (float)(point->y - pivot->y) + (float)pivot->y)
//            );

    angle = degreeToRadian(angle);
    double s = sin(angle);
    double c = cos(angle);

    point->x -= pivot->x;
    point->y -= pivot->y;

    double xNew = (point->x * c) - (point->y * s);
    double yNew = (point->x * s) + (point->y * c);

    point->x = xNew + pivot->x;
    point->y = yNew + pivot->y;
//
//    point->x = ((point->x - pivot->x) * c) - ((point->x - pivot->y) * s) + pivot->x;
//    point->x = ((point->x - pivot->x) * c) + ((point->x - pivot->y) * s) + pivot->y;

    return point;
}