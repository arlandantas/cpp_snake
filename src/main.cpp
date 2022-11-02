#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct BoardPosition {
  int x;
  int y;
};

class SnakeGame {
  public:
    void print(bool clearBoard = true) {
      if (clearBoard) {
        for (int i = 0; i <= boardSize.y; i++) {
          cout << "\x1b[A";
        }
      }


      cout << "   ";
      for (int j = 0; j < boardSize.x; j++)
      {
        cout << j << " ";
      }
      cout << endl;

      for (int i = 0; i < boardSize.y; i++)
      {
        cout << i << ": ";
        const auto line = board.at(i);
        for (int j = 0; j < boardSize.x; j++)
        {
          cout << printChars[line.at(j)] << " ";
        }
        cout << endl;
      }
    };

    SnakeGame(BoardPosition _boardSize) {
      printChars[Empty] = ' ';
      printChars[SnakeBodyUp] = '^';
      printChars[SnakeBodyRight] = '>';
      printChars[SnakeBodyDown] = 'v';
      printChars[SnakeBodyLeft] = '<';
      printChars[SnakeTail] = 'O';
      printChars[Food] = 'X';

      vector<BoardData> boardLine;
      boardSize = _boardSize;
      for (int j = 0; j <= _boardSize.x; j++)
      {
        boardLine.assign(j, Empty);
      }
      for (int i = 0; i <= _boardSize.y; i++)
      {
        board.assign(i, boardLine);
      }

      headPosition = { x: 2, y: 0 };
      tailPosition = { x: 0, y: 0 };
      board.at(headPosition.y).at(headPosition.x) = SnakeBodyRight;
      board.at(headPosition.y).at(headPosition.x - 1) = SnakeBodyRight;
      board.at(tailPosition.y).at(tailPosition.x) = SnakeBodyRight;
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
    BoardPosition boardSize = { x: 0, y: 0 };
    vector<vector<BoardData>> board;
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
            nextPosition.y = boardSize.y - 1;
          } else {
            nextPosition.y = currentPosition.y - 1;
          }
          break;
        case Down:
          if (currentPosition.y == boardSize.y - 1) {
            nextPosition.y = 0;
          } else {
            nextPosition.y = currentPosition.y + 1;
          }
          break;
        case Left:
          if (currentPosition.x == 0) {
            nextPosition.x = boardSize.x - 1;
          } else {
            nextPosition.x = currentPosition.x - 1;
          }
          break;
        case Right:
          if (currentPosition.x == boardSize.x - 1) {
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
      BoardData* nextHeadCell = &board.at(nextHeadPosition.y).at(nextHeadPosition.x);
      bool foodAhead = *nextHeadCell == Food;
      if (!foodAhead) {
        *nextHeadCell = getBoardFromDirection(headDirection);
        BoardData* currentTailCell = &board.at(tailPosition.y).at(tailPosition.x);
        tailPosition = getNextPosition(tailPosition, getDirectionFromBoard(*currentTailCell));
        *currentTailCell = Empty;
      }
      headPosition = nextHeadPosition;
    }
};

int main(int argc, char const *argv[])
{
  SnakeGame *game = new SnakeGame({ x: 10, y: 10 });
  game->print(false);
  for (int i = 0; i < 5; i++)
  {
    game->tick();
  }
  game->turn(SnakeGame::Down);
  for (int i = 0; i < 5; i++)
  {
    game->tick();
  }
  return 0;
}
