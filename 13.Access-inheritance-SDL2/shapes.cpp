#include "shapes.h"

// ----- Point -----
Point::Point(int x, int y) : x(x), y(y) {}
int Point::getX() const { return x; }
int Point::getY() const { return y; }

void Point::draw(SDL_Renderer* renderer) const {
    SDL_RenderDrawPoint(renderer, x, y);
}

// ----- Line -----
Line::Line(Point a, Point b) : p1(a), p2(b) {}

void Line::draw(SDL_Renderer* renderer) const {
    SDL_RenderDrawLine(renderer,
        p1.getX(), p1.getY(),
        p2.getX(), p2.getY()
    );
}

// ----- Rectangle -----
Rectangle::Rectangle(Point a, Point b) : tl(a), br(b) {}

void Rectangle::draw(SDL_Renderer* renderer) const {
    SDL_Rect rect;
    rect.x = tl.getX();
    rect.y = tl.getY();
    rect.w = br.getX() - tl.getX();
    rect.h = br.getY() - tl.getY();

    SDL_RenderDrawRect(renderer, &rect);
}

// ----- Circle -----
Circle::Circle(Point c, int r) : center(c), radius(r) {}

void Circle::draw(SDL_Renderer* renderer) const {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, center.getX() + x, center.getY() + y);
        SDL_RenderDrawPoint(renderer, center.getX() + y, center.getY() + x);
        SDL_RenderDrawPoint(renderer, center.getX() - y, center.getY() + x);
        SDL_RenderDrawPoint(renderer, center.getX() - x, center.getY() + y);
        SDL_RenderDrawPoint(renderer, center.getX() - x, center.getY() - y);
        SDL_RenderDrawPoint(renderer, center.getX() - y, center.getY() - x);
        SDL_RenderDrawPoint(renderer, center.getX() + y, center.getY() - x);
        SDL_RenderDrawPoint(renderer, center.getX() + x, center.getY() - y);

        y++;
        if (err <= 0) {
            err += 2*y + 1;
        } else {
            x--;
            err -= 2*x + 1;
        }
    }
}

// ----- Picture -----
Picture::Picture(Line* l, int lc, Rectangle* r, int rc, Circle* c, int cc)
    : lines(l), lineCount(lc), rects(r), rectCount(rc), circles(c), circleCount(cc) {}

void Picture::draw(SDL_Renderer* renderer) const {
    for (int i = 0; i < lineCount; ++i)
        lines[i].draw(renderer);

    for (int i = 0; i < rectCount; ++i)
        rects[i].draw(renderer);

    for (int i = 0; i < circleCount; ++i)
        circles[i].draw(renderer);
}
//g++ main.cpp shapes.cpp -o picture_app `sdl2-config --cflags --libs`
// ./picture_app