#include "decision.h"

AlertLevel check_temperature(double temperature, const config *config) {
  if (temperature < config->seuil_min) {
    return ALERT_TEMP_LOW;
  } else if (temperature > config->seuil_max) {
    return ALERT_TEMP_HIGH;
  } else {
    return ALERT_NONE;
  }
}

char *print_alert(AlertLevel alert) {
  switch (alert) {
  case ALERT_NONE:
    return "jawwek behi";
    break;
  case ALERT_TEMP_LOW:
    return "Low temperature";
    break;
  case ALERT_TEMP_HIGH:
    return "High temperature";
    break;
  default:
    return "unknown";
  }
}
