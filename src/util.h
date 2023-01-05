#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>

#define clear_screen() printf("\033[H\033[2J")
#define color_print(fmt, ...) do { printf(fmt, __VA_ARGS__); } while(0)

#define FG_BLACK "\033[30m"
#define FG_GREEN "\033[32m"
#define FG_YELLOW "\033[33m"
#define FG_BLUE "\033[34m"
#define FG_MAGENTA "\033[35m"
#define FG_CYAN "\033[36m"
#define FG_WHITE "\033[37m"
#define FG_DEFAULT "\033[39m"
#define FG_RESET "\033[0m"

long random_range(long max);

#endif
