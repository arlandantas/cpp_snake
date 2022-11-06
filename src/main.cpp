#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

struct BoardPosition {
  int x;
  int y;
};

template<typename CellType> class Board2D {
  public:
    Board2D (int _height, int _width, CellType _defaultValue) {
      height = _height;
      width = _width;
      board = new CellType*[_height];
      defaultValue = _defaultValue;
      for (int i = 0; i < height; i++)
      {
        board[i] = new CellType[_width];
        for (int j = 0; j < width; j++)
        {
          board[i][j] = defaultValue;
        }
      }
    }
    CellType at(int x, int y) {
      return board[y][x];
    }
    CellType at(BoardPosition position) {
      return at(position.x, position.y);
    }
    void set(CellType value, int x, int y) {
      board[y][x] = value;
    }
    void set(CellType value, BoardPosition position) {
      set(value, position.x, position.y);
    }
    void reset(int x, int y) {
      set(defaultValue, x, y);
    }
    void reset(BoardPosition position) {
      reset(position.x, position.y);
    }
    void setAll(CellType value) {
      for (int i = 0; i < height; i++)
      {
        for (int j = 0; j < width; j++)
        {
          set(value, j, i);
        }
      }
    }
    void resetAll() {
      setAll(defaultValue);
    }
    int getWidth() {
      return width;
    }
    int getHeight() {
      return height;
    }
  private:
    CellType** board;
    CellType defaultValue;
    int width;
    int height;
};

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
      printChars[Empty] = ' ';
      printChars[SnakeBodyUp] = '^';
      printChars[SnakeBodyRight] = '>';
      printChars[SnakeBodyDown] = 'v';
      printChars[SnakeBodyLeft] = '<';
      printChars[SnakeTail] = 'O';
      printChars[Food] = 'X';

      headPosition = { x: 2, y: 0 };
      tailPosition = { x: 0, y: 0 };
      board->set(SnakeBodyRight, headPosition);
      board->set(SnakeBodyRight, headPosition.x - 1, headPosition.y);
      board->set(SnakeBodyRight, tailPosition);
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

    void turn(BoardData direction) {
      board->set(direction, headPosition);
      print();
    }

  private:
    Board2D<BoardData> *board;
    map<int, char> printChars;
    BoardPosition headPosition = { x: 0, y: 0 };
    BoardPosition tailPosition = { x: 0, y: 0 };
    BoardPosition getNextPosition(BoardPosition currentPosition) {
      BoardPosition nextPosition = currentPosition;
      switch (board->at(currentPosition))
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
      }
      return nextPosition;
    }
    void move() {
      BoardPosition nextHeadPosition = getNextPosition(headPosition);
      BoardData nextHeadCell = board->at(nextHeadPosition);
      bool foodAhead = nextHeadCell == Food;
      if (!foodAhead) {
        BoardData currentTailData = board->at(tailPosition);
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
  if (argc != 3) {
    cout << "You must define board width and height!" << endl;
    return 1;
  }

  int boardWidth = stoi(argv[1]);
  int boardHeight = stoi(argv[2]);

  SnakeGame *game = new SnakeGame(boardWidth, boardHeight);
  game->print(false);
  SnakeGame::BoardData direcoes[] {
    SnakeGame::SnakeBodyRight,
    SnakeGame::SnakeBodyDown,
    SnakeGame::SnakeBodyLeft,
    SnakeGame::SnakeBodyUp
  };
  for (int i = 0; i < 4; i++)
  {
    game->turn(direcoes[i]);
    for (int i = 0; i < 5; i++)
    {
      game->tick();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }
  return 0;
}
