#ifndef __BOARDVIEW_H__
#define __BOARDVIEW_H__     

class View {
private:
  Board &b;
public:
  View(Board &board):b(board) {};
  void showBoard() const; 
  void doGameCycle(bool is_s); 
};

#endif
