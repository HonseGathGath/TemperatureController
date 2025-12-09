#ifndef STAT_H
#define STAT_H

typedef struct {
    float temp_totale;
    float temp_min;
    float temp_max;
    int nb_mesures;
    int alertes_niveau1;
    int alertes_niveau2;
    int alertes_niveau3;
    int temps_alerte_total;
} Statistiques;

void initialiser_statistiques(Statistiques *stats);
void mettre_a_jour_stats(Statistiques *stats, float temp, int niveau, int intervalle);
void generer_rapport(Statistiques *stats, float seuil_min, float seuil_max);

#endif
