void generer_rapport(Statistiques *stats, Configuration *config) {
    FILE *fichier = fopen("rapport_journalier.txt", "w");
    
    if(fichier == NULL) {
        printf("[Erreur] Impossible de créer le rapport!\n");
        return;
    }
    
    time_t maintenant = time(NULL);
    
    fprintf(fichier, "========================================\n");
    fprintf(fichier, "    RAPPORT JOURNALIER - TEMPERATURE\n");
    fprintf(fichier, "========================================\n");
    fprintf(fichier, "Date: %s\n", ctime(&maintenant));
    fprintf(fichier, "Configuration:\n");
    fprintf(fichier, "  - Seuil min: %.2f°C\n", config->seuil_min);
    fprintf(fichier, "  - Seuil max: %.2f°C\n", config->seuil_max);
    fprintf(fichier, "----------------------------------------\n\n");
    
    if(stats->nb_mesures > 0) {
        float moyenne = stats->temp_totale / stats->nb_mesures;
        
        fprintf(fichier, "STATISTIQUES:\n");
        fprintf(fichier, "  Nombre de mesures: %d\n", stats->nb_mesures);
        fprintf(fichier, "  Température moyenne: %.2f°C\n", moyenne);
        fprintf(fichier, "  Température minimale: %.2f°C\n", stats->temp_min);
        fprintf(fichier, "  Température maximale: %.2f°C\n\n", stats->temp_max);
        
        fprintf(fichier, "ALERTES:\n");
        fprintf(fichier, "  Niveau 1 (légères): %d\n", stats->alertes_niveau1);
        fprintf(fichier, "  Niveau 2 (modérées): %d\n", stats->alertes_niveau2);
        fprintf(fichier, "  Niveau 3 (critiques): %d\n", stats->alertes_niveau3);
        fprintf(fichier, "  Total alertes: %d\n\n", 
                stats->alertes_niveau1 + stats->alertes_niveau2 + stats->alertes_niveau3);
        
        fprintf(fichier, "TEMPS EN ALERTE:\n");
        fprintf(fichier, "  Durée totale: %d secondes\n", stats->temps_alerte_total);
        fprintf(fichier, "  Soit: %d minutes\n", stats->temps_alerte_total / 60);
    } else {
        fprintf(fichier, "Aucune mesure enregistrée.\n");
    }
    
    fprintf(fichier, "\n========================================\n");
    fclose(fichier);
}
