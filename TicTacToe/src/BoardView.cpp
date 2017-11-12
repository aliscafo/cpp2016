#include <stdio.h>
#include <iostream>
#include "Board.h"
#include "BoardView.h"           


void View::showBoard() const {
  std::cout << "\n";

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++)
      std::cout << b.getCell(i, j);

    std::cout << "\n";
  }     
} 
  
  
void View::doGameCycle(bool is_silent) {
  int turn = 0, is_bad = 0;
  char sign[2] = {'O', 'X'};

  while (b.isWin() == GAME_IN_PROGRESS) {
    int x, y;

    if (!is_silent && !is_bad)
      showBoard();

    std::cout << sign[turn] << " move: ";
    std::cin >> x >> y;

    if (x == -1 && y == -1)
      return;

    if (b.canMove(x, y)) {
      b.move(x, y, sign[turn]);
      turn = (1 ^ turn);
      is_bad = 0;
    }
    else {
      std::cout << "Bad move!\n";
      is_bad = 1;
    }
  }

  showBoard();

  if (b.isWin() == DRAW)
    std::cout << "Draw.\n";
  if (b.isWin() == X_WINS)
    std::cout << "X wins!\n";
  if (b.isWin() == O_WINS)
    std::cout << "O wins!\n";
        
}

