#include <iostream>
#include "headers/SnakeGame.h"
#include "headers/Board2D.h"

using namespace std;

SnakeGame::SnakeGame(int width, int height) {
  board = new Board2D<BoardData>(width, height, Empty);

  for (int i = 0; i < (width * height / 10); i++)
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
};
void SnakeGame::print(bool clearBoard = true) {
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
void SnakeGame::tick() {
  move();
  print();
};
bool SnakeGame::turn(BoardData direction) {
  if (board->at(getNextPosition(headPosition, direction)) == getOppositeDirection(direction)) {
    return false;
  }
  board->set(direction, headPosition);
  print();
  return true;
};
BoardPosition SnakeGame::getNextPosition(BoardPosition currentPosition) {
  return getNextPosition(currentPosition, board->at(currentPosition));
};
SnakeGame::BoardData SnakeGame::getOppositeDirection(BoardData direction) {
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
};
BoardPosition SnakeGame::getNextPosition(BoardPosition currentPosition, BoardData direction) {
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
};
void SnakeGame::move() {
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
};
map<int, char> SnakeGame::printChars = {
  { Empty, ' ' },
  { SnakeBodyUp, '^' },
  { SnakeBodyRight, '>' },
  { SnakeBodyDown, 'v' },
  { SnakeBodyLeft, '<' },
  { SnakeTail, 'O' },
  { Food, 'X' }
};
