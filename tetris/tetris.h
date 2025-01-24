#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int red;
    int green;
    int blue;
} Color;

typedef struct{
    int color;
    int size;
    int **form;
} Tetromino;

typedef struct {
    int **grid;

} GameParameter;


extern const Color colors[7];
extern const int grid_width;
extern const int grid_height;
extern const int cell_size;

Tetromino *initTetromino(int color, int size, int form[size][size]);
void initTetrominoArray();
void freeTetromino();

#endif