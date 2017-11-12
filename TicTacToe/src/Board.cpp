#include "Board.h"


Board::Board() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      board[i][j] = '.';
}

  
void Board::move(int x, int y, char c) {
  if (canMove(x, y)) 
    board[x][y] = c;
}
  
  
bool Board::canMove(int x, int y) const {
  return (0 <= x && x < BOARD_SIZE && 0 <= y && y < BOARD_SIZE && board[x][y] == '.');
}


bool Board::isLine(int x, int y, bool is_vert = false) const {
  if (!is_vert && (y < 2 || y + 2 >= BOARD_SIZE))  
    return false;
  if (is_vert && (x < 2 || x + 2 >= BOARD_SIZE))  
    return false;

  for (int i = -2; i <= 2; i++)
   if (!is_vert) { 
     if (board[x][y + i] != board[x][y])
       return false;
   }
   else if (board[x + i][y] != board[x][y])
      return false;    
 
  return true;
}


bool Board::isDiagonal(int x, int y, int orient = 1) const {
  if (x < 2 || x + 2 >= BOARD_SIZE || y < 2 || y + 2 >= BOARD_SIZE)  
    return false;

  for (int i = -2; i <= 2; i++)
    if (board[x + i][y + orient * i] != board[x][y])
      return false;
  return true;
}


game Board::isWin() const {
  bool dots = false;

  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == '.') {
        dots = true;
        continue;
      }
      if (isLine(i, j) || isLine(i, j, true) || isDiagonal(i, j) || isDiagonal(i, j, -1))
        return ((board[i][j] == 'X') ? X_WINS : O_WINS);
    }
      
  return ((dots) ? GAME_IN_PROGRESS : DRAW);
}
  
  
char Board::getCell(int x, int y) const {
  return board[x][y];
}                                     


