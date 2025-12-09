#include "logger.h"
#include "stat.h"
#include "export.h"
#include <unistd.h>

int main() {
  journal();
  exporter_csv();
  return 0;
}
