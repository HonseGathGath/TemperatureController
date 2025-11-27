#include <stdio.h>

static int intervalle_mesure = 10.0;
static double seuil_max = 10.0;
static double seuil_min = 10.0;

void read_config() {
  FILE *file = fopen("data/config.txt", "r");
  if (file == NULL) {
    printf("couldn't open file !!!! wenou ya 7mayza\n");
  }

  int items = fscanf(file, "seuil_min=%lf\nseuil_max=%lf\nintervalle_mesure=%d",
                     &seuil_min, &seuil_max, &intervalle_mesure);
  fclose(file);

  if (items == 3) {
    printf("these are the values: \n");
    printf("seuil_min: %1f\n", seuil_min);
    printf("seuil_max: %1f\n", seuil_max);
    printf("intervalle_mesure: %d seconds\n", intervalle_mesure);
  } else {
    printf("couldnt read config. fallback to defaults.\n");
  }
}

double get_seuil_min() { return seuil_min; }

double get_seuil_max() { return seuil_max; }

int get_intervalle_mesure() { return intervalle_mesure; }
