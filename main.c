#include "matrix.h"

#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <signal.h>

volatile sig_atomic_t signal_status = 0;

void setup_curses(void);
void finish_curses(void);
void sighandler(int signum);

int main(void) {
    srand(time(NULL));
    setup_curses();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);

    matrix* m = create_matrix(COLS, LINES);

    int key;
    while(1) {
       if(signal_status == SIGINT || signal_status == SIGQUIT) {
           free_matrix(m);
           finish_curses();
       }

       key = getch();

       if(key != ERR)
           if(key == 'q') {
               free_matrix(m);
               finish_curses();
           }

       erase();
       update_frame(m);
       for(int i = 0; i < m->height - 1; i++) {
           for(int j = 0; j < m->width; j++) {
               attron(COLOR_PAIR(1));
               addch(m->grid[i][j]);
               attroff(COLOR_PAIR(1));
           }
       }

       napms(75);
    }

    free_matrix(m);
    finish_curses();
}

void setup_curses(void) {
    initscr();
    cbreak();
    timeout(10);
    curs_set(0);
    noecho();
}

void finish_curses() {
    // sets cursor visibility (1 for normal)
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}

void sighandler(int signum) {
    signal_status = signum;
}
