#include <stdio.h>
#include <time.h>
#include "stat.h"

void initialiser_statistiques(Statistiques *stats) {
    stats->temp_totale = 0.0;
    stats->temp_min = 999.0;
    stats->temp_max = -999.0;
    stats->nb_mesures = 0;
    stats->alertes_niveau1 = 0;
    stats->alertes_niveau2 = 0;
    stats->alertes_niveau3 = 0;
    stats->temps_alerte_total = 0;
}

void mettre_a_jour_stats(Statistiques *stats, float temp, int niveau, int intervalle) {
    stats->temp_totale += temp;
    stats->nb_mesures++;
    
    if(temp < stats->temp_min)
        stats->temp_min = temp;
    
    if(temp > stats->temp_max)
        stats->temp_max = temp;
    
    if(niveau == 1)
        stats->alertes_niveau1++;
    else if(niveau == 2)
        stats->alertes_niveau2++;
    else if(niveau == 3)
        stats->alertes_niveau3++;
    
    if(niveau > 0)
        stats->temps_alerte_total += intervalle;
}

void generer_rapport(Statistiques *stats, float seuil_min, float seuil_max) {
    FILE *fichier = fopen("rapport_journalier.txt", "w");
    if(!fichier) return;
    
    time_t maintenant = time(NULL);
    
    fprintf(fichier, "RAPPORT JOURNALIER\n");
    fprintf(fichier, "Date: %s\n", ctime(&maintenant));
    fprintf(fichier, "Seuils: %.2f°C - %.2f°C\n\n", seuil_min, seuil_max);
    
    if(stats->nb_mesures > 0) {
        float moyenne = stats->temp_totale / stats->nb_mesures;
        
        fprintf(fichier, "Mesures: %d\n", stats->nb_mesures);
        fprintf(fichier, "Moyenne: %.2f°C\n", moyenne);
        fprintf(fichier, "Min: %.2f°C\n", stats->temp_min);
        fprintf(fichier, "Max: %.2f°C\n\n", stats->temp_max);
        
        fprintf(fichier, "Alertes Niveau 1: %d\n", stats->alertes_niveau1);
        fprintf(fichier, "Alertes Niveau 2: %d\n", stats->alertes_niveau2);
        fprintf(fichier, "Alertes Niveau 3: %d\n\n", stats->alertes_niveau3);
        
        int total = stats->alertes_niveau1 + stats->alertes_niveau2 + stats->alertes_niveau3;
        fprintf(fichier, "Total alertes: %d\n", total);
        fprintf(fichier, "Temps alerte: %d sec (%d min)\n", 
                stats->temps_alerte_total, stats->temps_alerte_total/60);
    } else {
        fprintf(fichier, "Aucune mesure.\n");
    }
    
    fclose(fichier);
}
