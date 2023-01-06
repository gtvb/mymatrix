#ifndef _MATRIX_H
#define _MATRIX_H

#define MATRIX_NEGATIVE_LOWER_BOUND  -10
#define MATRIX_NEGATIVE_UPPER_BOUND  -3
#define MATRIX_POSITIVE_LOWER_BOUND  4
#define MATRIX_POSITIVE_UPPER_BOUND  6

#define MATRIX_WHITESPACE ' ';
#define MATRIX_CHARACTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
0123456789!@#$%&*()_-+={[]}"
#define MATRIX_CHARACTERS_LENGTH 79

struct matrix {
    int width;
    int height;
    char **grid;

    char* top_chunk;
    int* stream_lenghts;
};

typedef struct matrix matrix;

matrix* create_matrix(int width, int height);
void free_matrix(matrix* m);

char random_character();

void update_top_chunk(matrix* m);
void shift_chunks(matrix *m);
void update_frame(matrix* m);

#endif
