#define DO_CHECK(EXPR) check((EXPR), __FUNCTION__, __FILE__, __LINE__) 
#include <iostream>
#include "BoardTest.h"
#include "Board.h"

void BoardTest::testIsWin1() {
  Board b = Board();
  b.move(0, 0, 'X');
  b.move(1, 1, 'X');
  b.move(2, 2, 'X');
  b.move(3, 3, 'X');
  b.move(4, 4, 'X');
  DO_CHECK(b.isWin() == X_WINS);
}


void BoardTest::testIsWin2() {
  Board b = Board();
  int t = 0;

  for (int i = 0; i < 10; i += 2) {

    for (size_t j = 0; j < BOARD_SIZE; j++)
      if ((j % 2) == t)
        b.move(i, j, 'X');
      else
        b.move(i, j, 'O');
          
    for (size_t j = 0; j < BOARD_SIZE; j++)
      if ((j % 2) == t)
        b.move(i + 1, j, 'X');
      else
        b.move(i + 1, j, 'O');
    
    t = 1 - t;      
  }

  DO_CHECK(b.isWin() == DRAW);
}


void BoardTest::testIsWin3() {
  Board b = Board();
  b.move(9, 6, 'X');
  b.move(9, 0, 'O');
  b.move(9, 1, 'O');
  b.move(9, 2, 'O');
  b.move(9, 3, 'O');
  b.move(9, 4, 'O');
  DO_CHECK(b.isWin() == O_WINS);
}


void BoardTest::testIsWin4() {
  Board b = Board();
  b.move(0, 9, 'O');
  b.move(1, 9, 'O');
  b.move(2, 9, 'O');
  b.move(3, 9, 'O');
  b.move(4, 9, 'O');
  b.move(5, 9, 'X');
  DO_CHECK(b.isWin() == O_WINS);
}


void BoardTest::testIsWin5() {
  Board b = Board();
  b.move(0, 9, 'O');
  b.move(1, 8, 'O');
  b.move(2, 7, 'O');
  b.move(3, 6, 'O');
  b.move(4, 5, 'O');
  DO_CHECK(b.isWin() == O_WINS);
}


void BoardTest::testMove1() {
  Board b = Board();
  b.move(0, 0, 'X');
  DO_CHECK(b.canMove(0, 0) == false);
}


void BoardTest::testMove2() {
  Board b = Board();
  DO_CHECK(b.canMove(1, 1) == true);
  b.move(0, 0, 'O');
}


void BoardTest::testMove3() {
  Board b = Board();
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (i != 5 || j != 5)
        b.move(i, j, 'X');
  DO_CHECK(b.canMove(5, 5) == true);
}


void BoardTest::testCanMove1() {
  Board b = Board();
  DO_CHECK(b.canMove(-1, 5) == false);
  DO_CHECK(b.canMove(5, -1) == false);
}

void BoardTest::testCanMove2() {
  Board b = Board();
  
  DO_CHECK(b.canMove(1, 10) == false);
  DO_CHECK(b.canMove(10, 1) == false);
}

void BoardTest::testCanMove3() {
  Board b = Board();
 
  b.move(5, 5, 'X');
  
  DO_CHECK(b.canMove(5, 5) == false);
  DO_CHECK(b.canMove(5, 4) == true);
}

void BoardTest::testGetCell1() {
  Board b = Board();
  b.move(1, 1, 'X');
  DO_CHECK(b.getCell(1, 1) == 'X');
}

void BoardTest::testGetCell2() {
  Board b = Board();
  b.move(1, 1, 'O');
  DO_CHECK(b.getCell(1, 1) == 'O');
}

void BoardTest::testGetCell3() {
  Board b = Board();
  DO_CHECK(b.getCell(1, 1) == '.');
}


void BoardTest::runAllTests() {
  testIsWin1();
  testIsWin2();
  testIsWin3();
  testIsWin4();
  testIsWin5();

  testMove1();
  testMove2();
  testMove3();

  testCanMove1();
  testCanMove2();
  testCanMove3();

  testGetCell1();
  testGetCell2();
  testGetCell3();	
}


