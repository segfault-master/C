#include "tetris.h"

int getRandomTetrominoNumber() {
    int max = 6;
    int min = 0;
    int random_number = rand() % (max - min + 1) + min;

    return random_number;
}

Tetromino *initTetromino(int color, int size, int form[size][size]) {
    Tetromino *tetromino = (Tetromino*)malloc(sizeof(Tetromino));
    tetromino->color = color;
    tetromino->size = size;
    tetromino->form = (int **)malloc(size * sizeof(int *));
    if (tetromino->form == NULL) {
        printf("Tetromino form memory allocation failed\n");
        abort();
    }

    for (int i = 0; i < size; i++) {
        tetromino->form[i] = (int *)malloc(size * sizeof(int));
        if (tetromino->form[i] == NULL) {
            printf("Tetromino form memory allocation failed for columns in row %d\n", i);
            abort();
        } else {
            for (int j = 0; j < size; j++) {
                tetromino->form[i][j] = form[i][j];
            }
        }
    }

    return tetromino;
}

const Tetromino *tetrominos[7];

void initTetrominoArray() {
    int form_0[2][2] = {{1, 1}, {1, 1}};
    int form_1[3][3] = {{0, 0, 0}, {0, 0, 1}, {1, 1, 1}};
    int form_2[3][3] = {{0, 0, 0}, {1, 0, 0}, {1, 1, 1}};
    int form_3[3][3] = {{0, 0, 0}, {0, 1, 1}, {1, 1, 0}};
    int form_4[3][3] = {{0, 0, 0}, {1, 1, 0}, {0, 1, 1}};
    int form_5[3][3] = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
    int form_6[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};

    tetrominos[0] = initTetromino(1, 2, form_0);
    tetrominos[1] = initTetromino(2, 3, form_1);
    tetrominos[2] = initTetromino(3, 3, form_2);
    tetrominos[3] = initTetromino(4, 3, form_3);
    tetrominos[4] = initTetromino(5, 3, form_4);
    tetrominos[5] = initTetromino(6, 3, form_5);
    tetrominos[6] = initTetromino(7, 4, form_6);
}

void freeTetrominos() {
    for(int i = 0; i < 7; i++) {
        for (int j = 0; j < tetrominos[i]->size; j++) {
            free(tetrominos[i]->form[j]);
        }
        free(tetrominos[i]->form);
        free((void*)tetrominos[i]);
    }
}

CurrentTetromino *initCurrentTetromino(int tetromino_index) {
    CurrentTetromino *ct;
    ct->tetromino_index = getRandomTetrominoNumber();
    ct->rotation = 0;
    ct->x = 0;
    ct->y = 0;
    return ct;
}

void enqueue(TetrominoQueue *q) {
    TetrominoNode *newNode = malloc(sizeof(TetrominoNode));
    if (!newNode) {
        printf("Tetromino queue memory allocation failed\n");
        exit(1);
    }
    newNode->tetromino_index = getRandomTetrominoNumber();
    newNode->next = NULL;

    if (q->front == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(TetrominoQueue *q) {
    if (q->front == NULL) {
        printf("Queue is empty, cannot dequeue\n");
        return -1;
    }
    
    int value = q->front->tetromino_index;

    TetrominoNode *temp = q->front;
    q->front = q->front->next;
    free(temp);

    if (q->front == NULL) {
        q->rear = NULL;
    }

    return value;
}

void destroyQueue(TetrominoQueue *q) {
    while (q->front != NULL) {
        dequeue(q);
    }
}