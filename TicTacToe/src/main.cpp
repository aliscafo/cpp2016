#include <string.h>
#include "Board.h"
#include "BoardView.h"

int main (int argc, char** argv) {
  Board b;
  View bv(b);

  bool is_s = 0;
  char silent[7] = "silent";

  if (argc == 2 && strcmp(argv[1], silent) == 0)
    is_s = 1;
  
  bv.doGameCycle(is_s);
  
  return 0;
}