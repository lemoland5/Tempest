#pragma once

const int LINE_T_SCALE = 200;

struct Point{
public:
    Point( int x,  int y): x(x), y(y) {};
    explicit Point( int xy): x(xy), y(xy) {};
    Point(): x(1), y(1) {};
     int x;
     int y;
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
