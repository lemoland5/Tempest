#pragma once

struct Point{
public:
    Point( int x,  int y): x(x), y(y) {};
    Point( int xy): x(xy), y(xy) {};
    Point(): x(1), y(1) {};
     int x;
     int y;
};

struct Line{
public:
    Line( int x1,  int y1,  int x2,  int y2): begin(x1, y1), end(x2, y2){};
    Line(Point begin, Point end): begin(begin), end(end){};
    Line(Point* begin, Point* end): begin(*begin), end(*end){};
    Line(): begin(1,1), end(2,1){};

    Point begin;
    Point end;
};

