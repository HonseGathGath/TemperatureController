#include "sensor.h"
#include <stdlib.h> //For rand(), srand()
#include <time.h>   //For time() - to seed random generator

double read_temperature() {
  static int initialized = 0;
  if (!initialized) {
    srand(time(NULL));
    initialized = 1;
  }

  double temp = (rand() % 200) / 5.0;

  return temp;
}
