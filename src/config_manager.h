#ifndef CONFIG_MANAGER_H

#define CONFIG_MANAGER_H

typedef struct {
  double seuil_min;
  double seuil_max;
  int intervalle_mesure;
} config;

int load_config(config *config);
void print_config(const config *config);

#endif // !CONFIG_MANAGER_H
//
//
