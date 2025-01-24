#include "tetris.h"

GameParameter *initGameParameter() {
    GameParameter *param = (GameParameter*)malloc(sizeof(GameParameter));
    param->grid = (int **)malloc(grid_height * sizeof(int *));
    TetrominoQueue *q;
    q->front = NULL;
    q->rear = NULL;
    param->queue = q;
    param->score = 0;
    param->current_tetromino = initCurrentTetromino(getRandomTetrominoNumber());
    for (int i = 0; i < 3; i++) {
        enqueue(param->queue);
    }
    if (param->grid == NULL) {
        printf("Tetromino form memory allocation failed\n");
        abort();
    }

    for (int i = 0; i < grid_height; i++) {
        param->grid[i] = (int *)malloc(grid_width * sizeof(int));
        if (param->grid[i] == NULL) {
            printf("Tetromino form memory allocation failed for columns in row %d\n", i);
            abort();
        } else {
            for (int j = 0; j < grid_width; j++) {
                param->grid[i][j] = 0;
            }
        }
    }
    return param;
}

void freeGameParameter(GameParameter *param) {
    for (int i = 0; i < grid_height; i++) {
        free(param->grid[i]);
    }
    free(param);
}

void freeAll(GameParameter *gameParameter) {
    freeGameParameter(gameParameter);
    freeTetrominos();
    return;
}

void drawCell(SDL_Renderer *renderer, int x, int y, int color) {
    SDL_SetRenderDrawColor(renderer, colors[color].red, colors[color].green, colors[color].blue, 255);
    // Define the rectangle (x, y, width, height)
    SDL_Rect filledRect = {(x * cell_size) + 1, (y * cell_size) + 1, cell_size - 1, cell_size - 1};
    SDL_RenderFillRect(renderer, &filledRect);
}


void drawGridContent(SDL_Renderer *renderer, GameParameter *param) {
    for (int i = 0; i < grid_height; i++) {
        for (int j = 0; j < grid_width; j++) {
            if (param->grid[i][j] != 0) {
                drawCell(renderer, i, j, param->grid[i][j]);
            }
        }
    
    }
}

void drawGrid(SDL_Renderer *renderer, GameParameter *gameDisplay) {
    int window_width = cell_size * grid_width;
    int window_height = cell_size * grid_height;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
    // Draw the grid
        SDL_SetRenderDrawColor(renderer, 91, 91, 91, 91); // White grid lines

        // Draw vertical lines
        for (int x = 0; x <= window_width; x += cell_size) {
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        }

        // Draw horizontal lines
        for (int y = 0; y <= window_height; y += cell_size) {
            SDL_RenderDrawLine(renderer, 0, y, window_width, y);
        }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    initTetrominoArray();
    GameParameter *param = initGameParameter();
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window and renderer
    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, cell_size * 10 + 1, cell_size * 20 + 1, SDL_WINDOW_SHOWN);
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
    freeAll(param);

    return 0;
}
