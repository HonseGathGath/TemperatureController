#include "decision_engine.h"
#include <stdio.h>

AlertLevel check_temperature(double temperature, const config *config) {
  if (temperature < config->seuil_min) {
    return ALERT_TEMP_LOW;
  } else if (temperature > config->seuil_max) {
    return ALERT_TEMP_HIGH;
  } else {
    return ALERT_NONE;
  }
}

void print_alert(AlertLevel alert, double temperature) {
  switch (alert) {
  case ALERT_NONE:
    printf("jawwek behi:%.1f°c\n", temperature);
    break;
  case ALERT_TEMP_LOW:
    printf("Low temperature: %.1f°c\n", temperature);
    break;
  case ALERT_TEMP_HIGH:
    printf("High temperature: %.1f°c\n", temperature);
    break;
  }
}
