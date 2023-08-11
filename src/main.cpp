#include <cstdlib>
#include <SDL.h>

// Function declarations
void handleEvents(SDL_Event& e, SDL_Rect& redSquare, SDL_Rect& blueSquare, bool& dragging, bool& running, SDL_Window* window);
void render(SDL_Renderer* renderer, SDL_Rect& redSquare, SDL_Rect& blueSquare);

int main(int argc, char* argv[]) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create an SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Drag and Drop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Define the red and blue squares with their positions and sizes
    SDL_Rect redSquare = {100, 100, 50, 50};
    SDL_Rect blueSquare = {500, 300, 50, 50};
    
    // Flag to check if the red square is being dragged
    bool dragging = false;

    SDL_Event e;
    bool running = true;

    // Main event loop
    while (running) {
        handleEvents(e, redSquare, blueSquare, dragging, running, window);
        render(renderer, redSquare, blueSquare);
    }

    // Cleanup and shut down SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void handleEvents(SDL_Event& e, SDL_Rect& redSquare, SDL_Rect& blueSquare, bool& dragging, bool& running, SDL_Window* window) {
    while (SDL_PollEvent(&e)) {
        // Handle window close event
        if (e.type == SDL_QUIT) {
            running = false;
        } 
        // Handle mouse button down event
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            // Check if the mouse is inside the red square
            SDL_Point mousePoint = { e.button.x, e.button.y };
            if (SDL_PointInRect(&mousePoint, &redSquare)) {
                dragging = true;
            }
        } 
        // Handle mouse movement while dragging
        else if (e.type == SDL_MOUSEMOTION && dragging) {
            redSquare.x = e.motion.x - redSquare.w / 2;
            redSquare.y = e.motion.y - redSquare.h / 2;
            // Boundary checks
            if (redSquare.x < 0) redSquare.x = 0;
            if (redSquare.y < 0) redSquare.y = 0;
            if (redSquare.x + redSquare.w > 800) redSquare.x = 800 - redSquare.w;
            if (redSquare.y + redSquare.h > 600) redSquare.y = 600 - redSquare.h;
        } 
        // Handle mouse button up event
        else if (e.type == SDL_MOUSEBUTTONUP) {
            dragging = false;
            // Check if the red square is on top of the blue square
            if (SDL_HasIntersection(&redSquare, &blueSquare)) {
                blueSquare = {rand() % 750, rand() % 550, 50, 50};
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Congratulations", "Well done!", window);
            }
        }
    }
}

void render(SDL_Renderer* renderer, SDL_Rect& redSquare, SDL_Rect& blueSquare) {
    // Clear the renderer with a white background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw the red square
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &redSquare);

    // Draw the blue square
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &blueSquare);

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}