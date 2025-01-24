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

typedef struct TetrominoNode{
    int tetromino_index;
    struct TetrominoNode *next;
} TetrominoNode;

typedef struct{
    TetrominoNode *front;
    TetrominoNode *rear;
} TetrominoQueue;

typedef struct{
    int tetromino_index;
    int rotation;
    int x;
    int y;
} CurrentTetromino;

typedef struct {
    int **grid;
    TetrominoQueue *queue;
    CurrentTetromino *current_tetromino;
    int score;
} GameParameter;


extern const Tetromino *tetrominos[7];
extern const Color colors[7];
extern const int grid_width;
extern const int grid_height;
extern const int cell_size;

int getRandomTetrominoNumber();
Tetromino *initTetromino(int color, int size, int form[size][size]);
void initTetrominoArray();
void freeTetrominos();
CurrentTetromino *initCurrentTetromino(int tetromino_index);
void enqueue(TetrominoQueue *q);
int dequeue(TetrominoQueue *q);
void destroyQueue(TetrominoQueue *q);


#endif