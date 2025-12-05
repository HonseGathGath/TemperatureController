#ifndef DECISION_H
#define DECISION_H

#include "config.h"

typedef enum {
  ALERT_NONE = 0,
  ALERT_TEMP_LOW = 1,
  ALERT_TEMP_HIGH = 2
} AlertLevel;

AlertLevel check_temperature(double temperature, const config *config);

void print_alert(AlertLevel alert, double temperature);
#endif
