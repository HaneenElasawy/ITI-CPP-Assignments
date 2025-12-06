#include <SDL2/SDL.h>
#include "shapes.h"

int main() {
    // 1) Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    // 2) Create Window
    SDL_Window* window = SDL_CreateWindow(
        "OOP House (SDL2)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        0
    );

    if (!window) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 3) Create Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // Roof (triangle)
    Line roof[] = {
        Line(Point(200, 200), Point(400, 200)),  // base
        Line(Point(200, 200), Point(300, 120)),  // left side
        Line(Point(300, 120), Point(400, 200))   // right side
    };

    // House body (big rectangle)
    Rectangle house(Point(220, 200), Point(380, 350));

    // Door (small rectangle)
    Rectangle door(Point(290, 260), Point(330, 350));

    // Sun (circle)
    Circle sun(Point(450, 100), 40);

    // Prepare arrays for Picture
    Line lines[] = {
        roof[0], roof[1], roof[2]
    };

    Rectangle rects[] = {
        house,
        door
    };

    Circle circles[] = {
        sun
    };

    // Create Picture object
    Picture pic(lines, 3, rects, 2, circles, 1);

    // 5) Main Loop

    bool running = true;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // Clear screen (background color)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderClear(renderer);

        // Set draw color for shapes (white)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Draw our picture (house + sun)
        pic.draw(renderer);

        // Present on screen
        SDL_RenderPresent(renderer);
    }

    // 6) Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
