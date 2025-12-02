#include "sensor_simulator.h"
#include <stdlib.h> //For rand(), srand()
#include <time.h>   //For time() - to seed random generator

double read_temperature() {
  static int initialized = 0;
  if (!initialized) {
    srand(time(NULL));
    initialized = 1;
  }

  double temp = 15.0 + (rand() % 200) / 10.0;

  return temp;
}
