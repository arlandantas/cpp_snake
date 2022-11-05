#include <iostream>
#include <vector>
#include <map>
#include <string>

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
    void set(CellType value, int x, int y) {
      board[y][x] = value;
    }
    void reset(int x, int y) {
      set(defaultValue, x, y);
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
      board->set(SnakeBodyRight, headPosition.x, headPosition.y);
      board->set(SnakeBodyRight, headPosition.x - 1, headPosition.y);
      board->set(SnakeBodyRight, tailPosition.x, tailPosition.y);
    }

    void tick() {
      move();
      print(false);
    }

    enum HeadDirection { Up, Right, Down, Left };
    void turn(HeadDirection direction) {
      headDirection = direction;
    }

  private:
    enum BoardData { Empty, SnakeBodyUp, SnakeBodyRight, SnakeBodyDown, SnakeBodyLeft, SnakeTail, Food, Wall };
    Board2D<BoardData> *board;
    map<int, char> printChars;
    HeadDirection headDirection = Right;
    BoardPosition headPosition = { x: 0, y: 0 };
    BoardPosition tailPosition = { x: 0, y: 0 };
    BoardPosition getNextPosition(BoardPosition currentPosition, HeadDirection direction) {
      BoardPosition nextPosition = currentPosition;
      switch (direction)
      {
        case Up:
          if (currentPosition.y == 0) {
            nextPosition.y = board->getHeight() - 1;
          } else {
            nextPosition.y = currentPosition.y - 1;
          }
          break;
        case Down:
          if (currentPosition.y == board->getHeight() - 1) {
            nextPosition.y = 0;
          } else {
            nextPosition.y = currentPosition.y + 1;
          }
          break;
        case Left:
          if (currentPosition.x == 0) {
            nextPosition.x = board->getWidth() - 1;
          } else {
            nextPosition.x = currentPosition.x - 1;
          }
          break;
        case Right:
          if (currentPosition.x == board->getWidth() - 1) {
            nextPosition.x = 0;
          } else {
            nextPosition.x = currentPosition.x + 1;
          }
          break;
      }
      return nextPosition;
    }
    BoardData getBoardFromDirection(HeadDirection headDirection) {
      switch (headDirection)
      {
        case Up:
          return SnakeBodyUp;
          break;
        case Right:
          return SnakeBodyRight;
          break;
        case Down:
          return SnakeBodyDown;
          break;
        case Left:
          return SnakeBodyLeft;
          break;
      }
      return SnakeBodyUp;
    }
    HeadDirection getDirectionFromBoard(BoardData boardData) {
      switch (boardData)
      {
        case SnakeBodyUp:
          return Up;
          break;
        case SnakeBodyRight:
          return Right;
          break;
        case SnakeBodyDown:
          return Down;
          break;
        case SnakeBodyLeft:
          return Left;
          break;
      }
      return Up;
    }
    void move() {
      BoardPosition nextHeadPosition = getNextPosition(headPosition, headDirection);
      BoardData nextHeadCell = board->at(nextHeadPosition.x, nextHeadPosition. y);
      bool foodAhead = nextHeadCell == Food;
      if (!foodAhead) {
        BoardData currentTailCell = board->at(tailPosition.x, tailPosition.y);
        board->set(Empty, tailPosition.x, tailPosition.y);
        tailPosition = getNextPosition(tailPosition, getDirectionFromBoard(currentTailCell));
      }
      board->set(getBoardFromDirection(headDirection), nextHeadPosition.x, nextHeadPosition.y);
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
  // for (int i = 0; i < 5; i++)
  // {
  //   game->tick();
  // }
  // game->turn(SnakeGame::Down);
  // for (int i = 0; i < 5; i++)
  // {
  //   game->tick();
  // }
  return 0;
}
