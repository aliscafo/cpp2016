#ifndef __BOARD_H__
#define __BOARD_H__

const int BOARD_SIZE = 10;
enum game { GAME_IN_PROGRESS, DRAW, X_WINS, O_WINS };

class Board {
private:
  char board[BOARD_SIZE][BOARD_SIZE];
  bool isLine(int x, int y, bool is_vert) const;
  bool isDiagonal(int x, int y, int orient) const;
public:
  Board();
  void move(int x, int y, char c);
  bool canMove(int x, int y) const;
  game isWin() const;
  char getCell(int x, int y) const;
};

#endif
