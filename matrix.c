#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int rand_interval(int min, int max) {
    int ret;

    do { 
        ret = (rand() % (max + 1 - min)) + min; 
    } while(ret == 0);

    return ret;
}


matrix* create_matrix(int width, int height) {
    int i, j;
    // TODO: check for allocation errors
    matrix* m = malloc(sizeof(matrix));

    m->width = width;
    m->height = height;
    // TODO: check for allocation errors
    m->top_chunk = malloc(width * sizeof(char));
    // TODO: check for allocation errors
    m->stream_lenghts = malloc(width * sizeof(int));

    // fill stream_lenghts with random values. Positive values
    // indicate a non ' ' stream's length. Negative values indicate
    // a ' ' stream length
    for(i = 0; i < width; i++) {
        m->stream_lenghts[i] = rand_interval(MATRIX_NEGATIVE_LOWER_BOUND, MATRIX_POSITIVE_UPPER_BOUND - 3);
    }


    char **grid = malloc(height * sizeof(char*));
    if(grid == NULL) { 
        perror("could not allocate matrix's main array");
        exit(1);
    }

    for(i = 0; i < height; i++) {
        grid[i] = malloc(width * sizeof(char));
        if(grid == NULL) {
            perror("could not allocate matrix's i array");
            exit(1);
        }
    }

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            grid[i][j] = MATRIX_WHITESPACE;
        }
    }

    m->grid = grid;

    return m;
}

void free_matrix(matrix* m) {
    for(int i = 0; i < m->height; i++)
        free(m->grid[i]);
    free(m->grid);
    free(m->top_chunk);
    free(m->stream_lenghts);
    free(m);
}

char random_character() {
    return MATRIX_CHARACTERS[rand_interval(0, MATRIX_CHARACTERS_LENGTH - 1)];
}

void update_top_chunk(matrix* m) {
    int i;
    for(i = 0; i < m->width; i++) {
        if(m->stream_lenghts[i] > 0 && m->stream_lenghts[i] - 1 > 0) {
            m->top_chunk[i] = random_character();
            m->stream_lenghts[i]--;
        } else if(m->stream_lenghts[i] > 0 && m->stream_lenghts[i] - 1 == 0) {
            m->top_chunk[i] = random_character();
            m->stream_lenghts[i]--;

            m->stream_lenghts[i] = rand_interval(MATRIX_NEGATIVE_LOWER_BOUND, MATRIX_NEGATIVE_UPPER_BOUND);
        } else if(m->stream_lenghts[i] < 0 && m->stream_lenghts[i] + 1 < 0) {
            m->top_chunk[i] = MATRIX_WHITESPACE;
            m->stream_lenghts[i]++;
        } else {
            m->top_chunk[i] = MATRIX_WHITESPACE;
            m->stream_lenghts[i]++;

            m->stream_lenghts[i] = rand_interval(MATRIX_POSITIVE_LOWER_BOUND, MATRIX_POSITIVE_UPPER_BOUND);
        }
    }
}

void shift_chunks(matrix* m) {
    for(int j = 0; j <= m->width - 1; j += 2) {
        for(int i = m->height - 1; i >= 1; i--) {
            m->grid[i][j] = m->grid[i - 1][j];
        }
    }
}

void update_frame(matrix* m) {
    shift_chunks(m);
    update_top_chunk(m);

    for(int i = 0; i < m->width; i++)
        m->grid[0][i] = m->top_chunk[i];
}
