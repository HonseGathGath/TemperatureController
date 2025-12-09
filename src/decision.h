#ifndef DECISION_H
#define DECISION_H

#include "config.h"

typedef enum {
  ALERT_NONE = 0,
  ALERT_NIVEAU1 = 1,  // Avertissement léger
  ALERT_NIVEAU2 = 2,  // Alerte modérée
  ALERT_NIVEAU3 = 3   // Alerte critique
} AlertLevel;

AlertLevel check_temperature(double temperature, const config *config);

char *print_alert(AlertLevel alert);
#endif
