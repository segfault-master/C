#include "tetris.h"

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

Tetromino **initTetrominoArray() {
    Tetromino **tetrominos = (Tetromino **)malloc(7 * sizeof(Tetromino *));
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
    return tetrominos;
}

void freeTetromino(Tetromino *tetromino) {
    for (int i = 0; i < tetromino->size; i++) {
        free(tetromino->form[i]);
    }
    free(tetromino->form);
    free(tetromino);
}