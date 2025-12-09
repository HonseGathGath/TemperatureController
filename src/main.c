#include "export.h"
#include "logger.h"
#include <unistd.h>

int main() {
  journal();
  exporter_csv();
  return 0;
}
