#include "config.h"
#include "decision.h"
#include "sensor.h"
#include <stdio.h>
#include <unistd.h>
int main() {
  config config = read_config();

  printf("\nStarting monitoring (5 readings) ... \n");
  printf("Press Ctrl+C to stop anytime \n\n");
  for (int i = 0; i < 5; ++i) {
    double temperature = read_temperature();
    AlertLevel alert = check_temperature(temperature, &config);

    printf("[%d]", i + 1);
    print_alert(alert, temperature);

    sleep(config.intervalle_mesure);
  }
  printf("\n Phase 1 test Complete \n");

  return 0;
}
