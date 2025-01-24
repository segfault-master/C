#include "tetris.h"

GameParameter *initGameParameter(int cellSize) {
    GameParameter *param = (GameParameter*)malloc(sizeof(GameParameter));
    param->cellSize = cellSize;
    return param;
}

void freeAll(GameParameter *gameParameter, Tetromino **tetrominos) {
    free(gameParameter);
    for(int i = 0; i < 7; i++) {
        freeTetromino(tetrominos[i]);
    }
    free(tetrominos);
    return;
}

void drawGrid(SDL_Renderer *renderer, GameParameter *gameDisplay) {
    int window_width = gameDisplay->cellSize * 10;
    int window_height = gameDisplay->cellSize * 20;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
    // Draw the grid
        SDL_SetRenderDrawColor(renderer, 91, 91, 91, 91); // White grid lines

        // Draw vertical lines
        for (int x = 0; x <= window_width; x += gameDisplay->cellSize) {
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        }

        // Draw horizontal lines
        for (int y = 0; y <= window_height; y += gameDisplay->cellSize) {
            SDL_RenderDrawLine(renderer, 0, y, window_width, y);
        }
}

int main(int argc, char *argv[]) {
    GameParameter *param = initGameParameter(30);
    Tetromino **tetrominos = initTetrominoArray();
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window and renderer
    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, param->cellSize * 10 + 1, param->cellSize * 20 + 1, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Variables to track arrow key state
    int arrow_up = 0, arrow_down = 0, arrow_left = 0, arrow_right = 0;

    // Program state
    int running = 1;

    // Event handling
    SDL_Event event;

    // Main loop
    while (running) {
        // Process events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0; // Exit when the window is closed
                    break;

                // Handle key press
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            arrow_up = 1;
                            break;
                        case SDLK_DOWN:
                            arrow_down = 1;
                            break;
                        case SDLK_LEFT:
                            arrow_left = 1;
                            break;
                        case SDLK_RIGHT:
                            arrow_right = 1;
                            break;
                    }
                    break;

                // Handle key release
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            arrow_up = 0;
                            break;
                        case SDLK_DOWN:
                            arrow_down = 0;
                            break;
                        case SDLK_LEFT:
                            arrow_left = 0;
                            break;
                        case SDLK_RIGHT:
                            arrow_right = 0;
                            break;
                    }
                    break;
            }
        }

        /*// Rendering (change background color based on arrow keys)
        if (arrow_up) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);      // Blue for UP
        else if (arrow_down) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for DOWN
        else if (arrow_left) SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow for LEFT
        else if (arrow_right) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for RIGHT
        else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   // Black by default

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);*/
        drawGrid(renderer, param);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    freeAll(param, tetrominos);

    return 0;
}
