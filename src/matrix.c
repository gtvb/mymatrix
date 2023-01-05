// I have a simple grid than can be changed and freed, but now,
// I need to discover how the matrix works, and create module
// to implement it
//
// to generate the matrix, one could first generate an auxiliary
// array to keep random numbers 0 <= n <= 1 (randomness can be explored
// later on). For now, we could consider that 0.5 <= n <= 1 populates 
// the given position with a random character. Values lower than 0.5
// don't generate a random character, but only a ' ' character.
//
// beggining:
// we could start our random array like this(considering a 4x4 grid)
// [0.1, 0.3, 0.8, 0.5]
//
// that could possibly generate the following matrix's values:
// [' ', ' ', '*', 'A']
//
// the starting matric would be:
// [
//      [' ', ' ', ' ', ' '],
//      [' ', ' ', ' ', ' '],
//      [' ', ' ', ' ', ' '],
//      [' ', ' ', ' ', ' '],
// ]
//
// in this case, the current position would be 0, so, we copy
// the generated values into array 0, leaving us with:
// [
//      [' ', ' ', '*', 'A']
//      [' ', ' ', ' ', ' '],
//      [' ', ' ', ' ', ' '],
//      [' ', ' ', ' ', ' '],
// ]
//
// now, we need to discover what to do with the next generated array:
// [' ', 'T', 'b', '@']
//
// [
//      [' ', 'T', 'b', '@']
//      [' ', ' ', '*', 'A'],
//      [' ', ' ', ' ', ' '],
//      [' ', ' ', ' ', ' '],
// ]
//
//
// ['g', ' ', '$', ' ']
// 
// [
//      ['g', ' ', '$', ' ']
//      [' ', 'T', 'b', '@']
//      [' ', ' ', '*', 'A'],
//      [' ', ' ', ' ', ' '],
// ]
//
//
// ['&', ' ', ')', ' ']
//
// [
//      ['&', ' ', ')', ' ']
//      ['g', ' ', '$', ' ']
//      [' ', 'T', 'b', '@']
//      [' ', ' ', '*', 'A'],
// ]
//
// ['2', 'c', ' ', ' ']
//
// [
//      ['2', 'c', ' ', ' ']
//      ['&', ' ', ')', ' ']
//      ['g', ' ', '$', ' ']
//      [' ', 'T', 'b', '@']
// ]
//
// can I say that, for every newly generated array of random values,
// it takes the position of the first one, and, all the other ones are 
// shifted by one position?
//
// while true do:
//      for i = 1; i < matrix.height; i++ do:
//          matrix[i] = matrix[i - 1]
//
//      matrix[0] = new_random_array 

#include "matrix.h"
#include "util.h"

#include <stdlib.h>

matrix* create_matrix(unsigned int width, unsigned int height) {
    matrix* m = malloc(sizeof(matrix));

    m->width = width;
    m->height = height;

    char **grid = malloc(height * sizeof(char*));
    if(grid == NULL) { 
        perror("could not allocate matrix's main array");
        exit(1);
    }

    for(unsigned int i = 0; i < height; i++) {
        grid[i] = malloc(width * sizeof(char));
        if(grid == NULL) {
            perror("could not allocate matrix's i array");
            exit(1);
        }
    }

    for(unsigned int i = 0; i < height; i++) {
        for(unsigned int j = 0; j < width; j++) {
            grid[i][j] = ' ';
        }
    }

    m->grid = grid;

    return m;
}

void free_matrix(matrix* m) {
    for(unsigned int i = 0; i < m->height; i++)
        free(m->grid[i]);
    free(m->grid);
    free(m->current_chunk);
    free(m);
}

void copy_array(char* from, char* to, int size) {
    for(int i = 0; i < size; i++)
        to[i] = from[i];
}

char generate_random_matrix_character() {
    return MATRIX_CHARACTERS[random_range((long)MATRIX_CHARACTERS_LENGTH)];
}

void update_current_chunk(matrix* m) {
    if(m->current_chunk == NULL) {
        m->current_chunk = malloc(m->width * sizeof(char));
    }

    for(unsigned int i = 0; i < m->width; i++) {
        long random_num = random_range(10);
        if(random_num > 2)
            m->current_chunk[i] = generate_random_matrix_character();
        else
            m->current_chunk[i] = ' ';
    }
}

void shift_chunks(matrix* m) {
    char* prev = m->grid[0];
    char* tmp = malloc(sizeof(char));
    for(unsigned int i = 1; i < m->height; i++) {
        copy_array(m->grid[i], tmp, m->width);
        copy_array(prev, m->grid[i], m->width);
        copy_array(tmp, prev, m->width);
    }

    free(tmp);
}

void update_frame(matrix* m) {
    shift_chunks(m);
    update_current_chunk(m);

    copy_array(m->current_chunk, m->grid[0], m->width);
}

void display(matrix* m) {
    for(unsigned int i = 0; i < m->height; i++) {
        for(unsigned int j = 0; j < m->width; j++) {
            if(i == 0 || i + 1 >= m->height) {
                color_print("%s%c%s", FG_WHITE, m->grid[i][j], FG_RESET);
                continue;
            } 

            if(m->grid[i + 1][j] == ' ') {
                color_print("%s%c%s", FG_WHITE, m->grid[i][j], FG_RESET);
            } else {
                color_print("%s%c%s", FG_GREEN, m->grid[i][j], FG_RESET);
            }
        }
        printf("\n");
    }
}
