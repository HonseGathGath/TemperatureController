#include "decision.h"

AlertLevel check_temperature(double temperature, const config *config) {
  double ecart_min = config->seuil_min - temperature;
  double ecart_max = temperature - config->seuil_max;

  if (ecart_min > 10 || ecart_max > 10) {
    return ALERT_NIVEAU3; // Critique: +10°C dépassement
  } else if (ecart_min > 5 || ecart_max > 5) {
    return ALERT_NIVEAU2; // Modéré: 5-10°C dépassement
  } else if (ecart_min > 0 || ecart_max > 0) {
    return ALERT_NIVEAU1; // Léger: 0-5°C dépassement
  } else {
    return ALERT_NONE;
  }
}

char *print_alert(AlertLevel alert) {
  switch (alert) {
  case ALERT_NONE:
    return "pas de problème";
  case ALERT_NIVEAU1:
    return "Avertissement léger";
  case ALERT_NIVEAU2:
    return "Alerte modérée";
  case ALERT_NIVEAU3:
    return "ALERTE CRITIQUE";
  default:
    return "unknown";
  }
}
