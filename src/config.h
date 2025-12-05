#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
  double seuil_min;
  double seuil_max;
  int intervalle_mesure;
} config;

config read_config(void);
double get_seuil_min(void);
double get_seuil_max(void);
int get_intervalle_mesure(void);

#endif
