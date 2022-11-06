#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "headers/Board2D.h"

using namespace std;

class SnakeGame {
  public:
    void print(bool clearBoard = true) {
      if (clearBoard) {
        for (int i = 0; i <= board->getHeight(); i++) {
          cout << "\x1b[A";
        }
      }

      cout << "   ";
      for (int j = 0; j < board->getWidth(); j++)
      {
        cout << j << " ";
      }
      cout << endl;

      for (int i = 0; i < board->getHeight(); i++)
      {
        cout << i << ": ";
        for (int j = 0; j < board->getWidth(); j++)
        {
          cout << printChars[board->at(j, i)] << " ";
        }
        cout << endl;
      }
    };

    SnakeGame(int width, int height) {
      board = new Board2D<BoardData>(width, height, Empty);

      for (int i = 0; i < 5; i++)
      {
        int x = rand() % board->getWidth();
        int y = rand() % board->getHeight();
        board->set(Food, x, y);
      }

      headPosition = { x: 7, y: 0 };
      tailPosition = { x: 4, y: 0 };
      for (int i = tailPosition.x; i < headPosition.x; i++)
      {
        board->set(SnakeBodyRight, i, headPosition.y);
      }
    }

    void tick() {
      move();
      print();
    }

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

    bool turn(BoardData direction) {
      if (board->at(getNextPosition(headPosition, direction)) == getOppositeDirection(direction)) {
        return false;
      }
      board->set(direction, headPosition);
      print();
      return true;
    }

  private:
    Board2D<BoardData> *board;
    map<int, char> printChars = {
      { Empty, ' ' },
      { SnakeBodyUp, '^' },
      { SnakeBodyRight, '>' },
      { SnakeBodyDown, 'v' },
      { SnakeBodyLeft, '<' },
      { SnakeTail, 'O' },
      { Food, 'X' }
    };
    BoardPosition headPosition = { x: 0, y: 0 };
    BoardPosition tailPosition = { x: 0, y: 0 };
    BoardPosition getNextPosition(BoardPosition currentPosition) {
      return getNextPosition(currentPosition, board->at(currentPosition));
    }
    BoardData getOppositeDirection(BoardData direction) {
      if (direction == SnakeBodyRight) {
        return SnakeBodyLeft;
      }
      if (direction == SnakeBodyLeft) {
        return SnakeBodyRight;
      }
      if (direction == SnakeBodyUp) {
        return SnakeBodyDown;
      }
      return SnakeBodyUp;
    }
    BoardPosition getNextPosition(BoardPosition currentPosition, BoardData direction) {
      BoardPosition nextPosition = currentPosition;
      switch (direction)
      {
        case SnakeBodyUp:
          if (currentPosition.y == 0) {
            nextPosition.y = board->getHeight() - 1;
          } else {
            nextPosition.y = currentPosition.y - 1;
          }
          break;
        case SnakeBodyDown:
          if (currentPosition.y == board->getHeight() - 1) {
            nextPosition.y = 0;
          } else {
            nextPosition.y = currentPosition.y + 1;
          }
          break;
        case SnakeBodyLeft:
          if (currentPosition.x == 0) {
            nextPosition.x = board->getWidth() - 1;
          } else {
            nextPosition.x = currentPosition.x - 1;
          }
          break;
        case SnakeBodyRight:
          if (currentPosition.x == board->getWidth() - 1) {
            nextPosition.x = 0;
          } else {
            nextPosition.x = currentPosition.x + 1;
          }
          break;
        default:
          break;
      }
      return nextPosition;
    }
    void move() {
      BoardPosition nextHeadPosition = getNextPosition(headPosition);
      BoardData nextHeadCell = board->at(nextHeadPosition);
      bool foodAhead = nextHeadCell == Food;
      if (!foodAhead) {
        if (nextHeadCell != Empty) {
          throw std::runtime_error("Morreu!");
        }
        BoardPosition nextTailPosition = getNextPosition(tailPosition);
        board->reset(tailPosition);
        tailPosition = nextTailPosition;
      }
      board->set(board->at(headPosition), nextHeadPosition);
      headPosition = nextHeadPosition;
    }
};

int main(int argc, char const *argv[])
{
  int boardWidth = argc < 2 ? 10 : stoi(argv[1]);
  int boardHeight = argc < 3 ? 10 : stoi(argv[2]);
  srand((unsigned) time(NULL));

  SnakeGame *game = new SnakeGame(boardWidth, boardHeight);
  game->print(false);

  SnakeGame::BoardData direcoes[] {
    SnakeGame::SnakeBodyUp,
    SnakeGame::SnakeBodyRight,
    SnakeGame::SnakeBodyDown,
    SnakeGame::SnakeBodyLeft
  };

  int tickTime = 200;
  while (true)
  {
    int directionIndex = rand() % 4;
    if (game->turn(direcoes[directionIndex])) {
      std::this_thread::sleep_for(std::chrono::milliseconds(tickTime));
    }
    int steps = rand() % 5;
    for (int j = 0; j < steps; j++)
    {
      game->tick();
      std::this_thread::sleep_for(std::chrono::milliseconds(tickTime));
    }
  }
  return 0;
}
