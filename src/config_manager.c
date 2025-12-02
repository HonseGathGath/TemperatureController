#include "config_manager.h"
#include <stdio.h>
#include <stdlib.h>

int load_config(config *config) {

  config->seuil_min = 18.0;
  config->seuil_max = 25.0;
  config->intervalle_mesure = 5;

  printf("configuration loaded on default phase 1 values \n");
  return 1;
}

void print_config(const config *config) {
  printf("\n=== configuration ===\n");
  printf("Temperature min: %.1f°C\n", config->seuil_min);
  printf("Temperature max: %.1f°C\n", config->seuil_max);
  printf("Measurement interval: %d seconds\n", config->intervalle_mesure);
  printf("=====================\n");
}
