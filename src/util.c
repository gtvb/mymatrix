#include "util.h"
#include <stdlib.h>

// https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range
long random_range(long max) {
  unsigned long
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do { x = rand(); } while (num_rand - defect <= (unsigned long) x);

  return x / bin_size;
}


