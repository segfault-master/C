#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int red;
    int green;
    int blue;
    int size;
    int **form;
} Tetromino;

typedef struct {
    int cellSize;
} GameParameter;

Tetromino *initTetromino(int red, int green, int blue, int size, int form[size][size]);
Tetromino **initTetrominoArray();
void freeTetromino(Tetromino *tetromino);

#endif