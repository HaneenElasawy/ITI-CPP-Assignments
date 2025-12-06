#ifndef SHAPES_H
#define SHAPES_H

#include <SDL2/SDL.h>       
#include <iostream>
using namespace std;

// ---------- Point ----------
class Point {
private:
    int x, y;
public:
    Point(int x = 0, int y = 0);
    int getX() const;
    int getY() const;
    void draw(SDL_Renderer* renderer) const;
};

// ---------- Line ----------
class Line {
private:
    Point p1, p2;
public:
    Line(Point p1, Point p2);
    void draw(SDL_Renderer* renderer) const;
};

// ---------- Rectangle ----------
class Rectangle {
private:
    Point tl, br;
public:
    Rectangle(Point tl, Point br);
    void draw(SDL_Renderer* renderer) const;
};

// ---------- Circle ----------
class Circle {
private:
    Point center;
    int radius;
public:
    Circle(Point c, int r);
    void draw(SDL_Renderer* renderer) const;
};

// ---------- Picture ----------
class Picture {
private:
    Line* lines;     int lineCount;
    Rectangle* rects; int rectCount;
    Circle* circles; int circleCount;

public:
    Picture(Line* l, int lc, Rectangle* r, int rc, Circle* c, int cc);
    void draw(SDL_Renderer* renderer) const;
};

#endif
