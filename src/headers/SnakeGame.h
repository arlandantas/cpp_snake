#include <map>
#include "Board2D.h"

using namespace std;

class SnakeGame {
  public:
    SnakeGame(int width, int height);
    void print(bool clearBoard);
    void tick();
    enum BoardData {
      Empty,
      SnakeBodyUp,
      SnakeBodyRight,
      SnakeBodyDown,
      SnakeBodyLeft,
      SnakeTail,
      Food,
      Wall
    };
    bool turn(BoardData direction);

  private:
    Board2D<BoardData> *board;
    static map<int, char> printChars;
    BoardPosition headPosition;
    BoardPosition tailPosition;
    BoardPosition getNextPosition(BoardPosition currentPosition);
    BoardData getOppositeDirection(BoardData direction);
    BoardPosition getNextPosition(BoardPosition currentPosition, BoardData direction);
    void move();
};