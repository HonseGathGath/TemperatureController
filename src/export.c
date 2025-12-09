#include "export.h"
#include <stdio.h>

void exporter_csv() {
  FILE *input = fopen("data/journal_temperature.txt", "r");
  FILE *output = fopen("data/export.csv", "w");
  
  if (!input || !output) return;
  
  fprintf(output, "Timestamp,Temperature,Status\n");
  
  char line[256];
  while (fgets(line, sizeof(line), input)) {
    fprintf(output, "%s", line);
  }
  
  fclose(input);
  fclose(output);
  printf("Export CSV créé: data/export.csv\n");
}
