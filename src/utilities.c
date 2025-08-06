#include <stdlib.h>
#include <time.h>
#include "../header/utilities.h"

int seeded = 0;
int randint(int a, int b) {
      if (a > b) {
            // Error: lower bound is greater than upper bound, return error code
            return -1;
      }

      if (!seeded) {
            srand(time(NULL));
            seeded = 1;
      }
      return rand() % (b-a+1) + a;
}
