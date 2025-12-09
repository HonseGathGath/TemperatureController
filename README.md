# Application pour gérer un Contrôleur Intelligent de Température

## 1. Description générale

Ce projet implémente un **système de monitoring de température** qui lit une température simulée, prend des décisions d’alerte en fonction de seuils configurables, enregistre un journal des mesures, et génère un rapport de statistiques. Il s’agit d’une simulation de contrôle climatique (serre, serveur, maison, etc.).

Langage : **C (C99)**  
Compilation : via `Makefile` et `gcc`

---

## 2. Structure du projet

- `src/main.c` : point d’entrée du programme
- `src/config.c`, `src/config.h` : gestion de la configuration (seuils, intervalle)
- `src/sensor.c`, `src/sensor.h` : simulation du capteur de température
- `src/decision.c`, `src/decision.h` : moteur de décision (niveaux d’alerte)
- `src/logger.c`, `src/logger.h` : journalisation des mesures + orchestration générale
- `src/stats.c`, `src/stats.h` : collecte de statistiques et génération du rapport
- `src/export.c`, `src/export.h` : **export CSV** des journaux (tâche optionnelle)
- `data/config.txt` : fichier de configuration
- `data/journal_temperature.txt` : journal des mesures
- `data/rapport_journalier.txt` : rapport quotidien généré
- `data/export.csv` : export CSV des mesures
- `Makefile` : commandes de compilation / exécution

---

## 3. Compilation et exécution

### Prérequis

- Compilateur C compatible C99 (ex : `gcc`)
- Utilisation recommandée : `make`

### Commandes principales

Dans le répertoire du projet :

```sh
make          # Compile le projet (cible par défaut)
make run      # Compile puis exécute ./temp_controller
make clean    # Supprime l’exécutable
make reset    # Réinitialise les fichiers journaux et le CSV
```

L’exécutable généré est : `./temp_controller`.

L’exécution standard :

1. Lance la phase de **monitoring** (journalisation + statistiques) via `journal()`.
2. À la fin, génère `data/rapport_journalier.txt`.
3. Ensuite, appelle `exporter_csv()` pour produire `data/export.csv` à partir du journal.

---

## 4. Fichier de configuration (`data/config.txt`)

Le programme lit la configuration dans `data/config.txt` au démarrage.

Format attendu :

```txt
seuil_min=<float>
seuil_max=<float>
intervalle_mesure=<int>
```

Exemple :

```txt
seuil_min=15.0
seuil_max=30.0
intervalle_mesure=2
```

- `seuil_min` : température minimale acceptable (°C)
- `seuil_max` : température maximale acceptable (°C)
- `intervalle_mesure` : intervalle entre deux lectures (en secondes)

Si le fichier n’existe pas ou est invalide, le programme affiche un message et utilise des **valeurs par défaut** définies dans `config.c`.

---

## 5. Détail par tâche de l’énoncé

### Tâche 1 : Gestion de la Configuration

> Enregistrer les valeurs : seuil_min, seuil_max, intervalle_mesure.  
> Écrire/Lire ces paramètres depuis un fichier `config.txt`.

Implémentation :

- Fichiers : `src/config.c`, `src/config.h`
- Fonction principale : `config read_config(void);`
- Rôle :
  - Ouvre `data/config.txt` en lecture.
  - Lit `seuil_min`, `seuil_max`, `intervalle_mesure` avec `fscanf`.
  - Si la lecture échoue, affiche un message et garde des valeurs par défaut.
  - Retourne une structure `config` contenant les trois paramètres.

### Tâche 2 : Simulation de Capteur

> Simuler un capteur en retournant une valeur aléatoire ou fixe pour les tests.

Implémentation :

- Fichiers : `src/sensor.c`, `src/sensor.h`
- Fonction principale : `double read_temperature(void);`
- Rôle :
  - Initialise le générateur aléatoire (`srand(time(NULL))`) une seule fois.
  - Génère une température pseudo‑aléatoire dans une plage réaliste (via `rand()` et une division).

### Tâche 3 : Moteur de Décision

> Comparer la température lue avec les seuils et afficher les messages d’alerte.

Implémentation :

- Fichiers : `src/decision.c`, `src/decision.h`
- Types et fonctions clés :
  - `typedef enum { ALERT_NONE, ALERT_NIVEAU1, ALERT_NIVEAU2, ALERT_NIVEAU3 } AlertLevel;`
  - `AlertLevel check_temperature(double temperature, const config *cfg);`
  - `char *print_alert(AlertLevel alert);`
- Rôle :
  - Calcule l’écart par rapport à `seuil_min` et `seuil_max`.
  - Retourne un des 3 niveaux d’alerte selon l’importance du dépassement.
  - `print_alert` fournit un message texte adapté au niveau.

### Tâche 4 : Journalisation

> Écrire chaque mesure avec timestamp dans un fichier.

Implémentation :

- Fichiers : `src/logger.c`, `src/logger.h`
- Fonction principale : `void journal(void);`
- Rôle :
  - Récupère la configuration via `read_config()`.
  - Pour un nombre de mesures (fixé à 5 pour la démo) :
    - Lit la température (`read_temperature`).
    - Calcule le niveau d’alerte (`check_temperature`).
    - Récupère l’heure courante (`time`, `ctime`).
    - Construit une ligne de log avec : timestamp, température formatée, statut.
    - Affiche la ligne sur la console.
    - L’écrit dans `data/journal_temperature.txt` (mode append).
  - Respecte l’intervalle entre mesures avec `sleep(intervalle_mesure)`.

### Tâche 5 : Système d’Alerte Avancé

> Gérer 3 niveaux d’alerte et compter les alertes consécutives pour éviter les fausses alarmes.

Implémentation :

- Niveaux d’alerte : gérés par l’`enum AlertLevel` dans `decision.h` et la fonction `check_temperature`.
- Comptage d’alertes consécutives :
  - Dans `logger.c` :
    - `static int alertes_consecutives = 0;`
    - Incrémenté si `alert != ALERT_NONE`, remis à 0 sinon.
    - Si `alertes_consecutives >= 3`, affichage d’un message :
      `"!!! 3 ALERTES CONSECUTIVES - CONFIRME !!!"`.

### Tâche 6 : Module de Statistiques et Rapports

> Générer un rapport quotidien dans `rapport_journalier.txt`.  
> Calculer : moyenne, min, max, nombre d’alertes par type, durée totale en état d’alerte.

Implémentation :

- Fichiers : `src/stats.c`, `src/stats.h`
- Structure :
  - `typedef struct { float temp_totale; float temp_min; float temp_max; int nb_mesures; int alertes_niveau1; int alertes_niveau2; int alertes_niveau3; int temps_alerte_total; } Statistiques;`
- Fonctions principales :
  - `void initialiser_statistiques(Statistiques *stats);`
  - `void mettre_a_jour_stats(Statistiques *stats, float temp, int niveau, int intervalle);`
  - `void generer_rapport(Statistiques *stats, float seuil_min, float seuil_max);`
- Rôle :
  - À chaque mesure, `mettre_a_jour_stats` :
    - Met à jour le total, min, max, nombre de mesures.
    - Incrémente les compteurs d’alertes par niveau (1, 2, 3).
    - Ajoute `intervalle` à `temps_alerte_total` si `niveau > 0`.
  - En fin de journalisation, `generer_rapport` :
    - Ouvre `data/rapport_journalier.txt` en écriture.
    - Affiche la date, les seuils, et si au moins une mesure :
      - température moyenne, minimale, maximale,
      - nombre d’alertes par niveau,
      - total d’alertes,
      - temps total passé en état d’alerte (secondes et minutes).

### Tâche Optionnelle : Module d’Export CSV

> Ajouter au minimum une autre tâche pour améliorer le traitement de cette application.

Implémentation : **Export CSV des journaux**

- Fichiers : `src/export.c`, `src/export.h`
- Fonction : `void exporter_csv(void);`
- Rôle :
  - Ouvre `data/journal_temperature.txt` en lecture.
  - Crée `data/export.csv` en écriture.
  - Écrit un en‑tête : `Timestamp,Temperature,Status`.
  - Recopie les lignes du journal pour faciliter l’analyse dans un tableur ou outil de data‑viz.
- Appelée depuis `main.c` juste après l’appel à `journal()`.

---

## 6. Utilisation typique

1. Configurer les seuils dans `data/config.txt`.
2. Lancer :
   ```sh
   make run
   ```
3. Observer les mesures et alertes dans la console.
4. Consulter ensuite :
   - `data/journal_temperature.txt` pour le détail des mesures,
   - `data/rapport_journalier.txt` pour le résumé statistique,
   - `data/export.csv` pour charger les données dans Excel, LibreOffice Calc, etc.

---

## 7. Améliorations possibles

Quelques idées d’extensions (non obligatoires) :

- Lire le **nombre de mesures** ou la **durée totale** depuis `config.txt` au lieu d’avoir 5 mesures en dur.
- Ajouter un mode "test" où la température est fixe (utile pour des scénarios reproductibles).
- Ajouter des couleurs dans la console selon le niveau d’alerte.
- Envoyer des notifications ou des commandes à un autre système (simulation d’action IOT).

Ce README résume comment chaque partie du code répond aux tâches de l’énoncé et comment exécuter le projet.