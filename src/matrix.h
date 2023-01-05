#ifndef _MATRIX_H
#define _MATRIX_H

#define MATRIX_CHARACTERS "abcdefghijklmnopqrstuvwxyz \
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%&*()_-+={[]}"
#define MATRIX_CHARACTERS_LENGTH 79 

struct matrix {
    /* grid* grid; */
    unsigned int width;
    unsigned int height;

    char **grid;
    char* current_chunk;
};

typedef struct matrix matrix;

matrix* create_matrix(unsigned int width, unsigned int height);
void free_matrix(matrix* m);

void copy_array(char* from, char* to, int size);
char generate_random_matrix_character();

void update_current_chunk(matrix* m);
void shift_chunks(matrix *m);
void update_frame(matrix* m);
void display(matrix* m);

#endif
