#include <stdlib.h>
#include <time.h>
#include "../header/utilities.h"


int randint(int a, int b) {
      static int seeded = 0;
      if (!seeded) {
            srand(time(NULL));
            seeded = 1;
      }
      return rand() % (b-a+1) + a;
}
