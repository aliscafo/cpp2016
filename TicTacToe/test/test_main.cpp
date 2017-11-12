#include <stdio.h>
//#include "Test.h"
//#include "Board.h"
#include "BoardTest.h"

int main() {
  BoardTest bt = BoardTest();
  bt.runAllTests();
  BoardTest::showFinalResults();
  return 0;
}
