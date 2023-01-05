#include "matrix.h"
#include "util.h"
#include <unistd.h>

int main(void) {
    matrix* m = create_matrix(20, 20);

    clear_screen();
    display(m);

    while(1) {
        sleep(1);
        clear_screen();
        update_frame(m);
        display(m);
    }

    free_matrix(m);
    return 0;
}
