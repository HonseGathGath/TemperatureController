#include "logger.h"
#include "config.h"
#include "decision.h"
#include "sensor.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static Statistiques stats;
static int alertes_consecutives = 0;

void journal() {
  config config = read_config();
  initialiser_statistiques(&stats);
  printf("\nStarting monitoring (5 readings) ... \n");
  printf("Press Ctrl+C to stop anytime \n\n");
  for (int i = 0; i < 5; ++i) {
    double temperature = read_temperature();
    char formatted_temperature[5];
    sprintf(formatted_temperature, "%.2f", temperature);
    AlertLevel alert = check_temperature(temperature, &config);

    if (alert != ALERT_NONE) {
      alertes_consecutives++;
      if (alertes_consecutives >= 3) {
        printf("!!! 3 ALERTES CONSECUTIVES - CONFIRME !!!\n");
      }
    } else {
      alertes_consecutives = 0;
    }

    mettre_a_jour_stats(&stats, temperature, alert, config.intervalle_mesure);

    char *printed_alert = print_alert(alert);
    time_t reading_timestamp;
    time(&reading_timestamp);
    char *timestamp = ctime(&reading_timestamp);
    timestamp[strlen(timestamp) - 1] = '\0';
    int buffer_size = strlen("[ ] Temperature:  - Status: ") +
                      strlen(timestamp) + strlen(formatted_temperature) +
                      strlen(printed_alert) + 3;
    char *temperature_reading = malloc(buffer_size * sizeof(char));
    if (temperature_reading == NULL) {
      printf("Memory allocation failed!\n");
      exit(1);
    }
    sprintf(temperature_reading, "[ %s ] Temperature: %s - Status: %s",
            timestamp, formatted_temperature, printed_alert);
    printf("%s\n", temperature_reading);
    FILE *file;
    file = fopen("data/journal_temperature.txt", "a+");
    if (file == NULL) {
      printf("Error opening file!\n");
      free(temperature_reading);
      exit(0);
    }
    fprintf(file, "%s\n", temperature_reading);
    fclose(file);
    free(temperature_reading);
    sleep(config.intervalle_mesure);
  }
  generer_rapport(&stats, config.seuil_min, config.seuil_max);
  printf("\nRapport genere dans rapport_journalier.txt\n");
  printf("\n Phase 1 test Complete \n");
}

Statistiques *get_stats() { return &stats; }
