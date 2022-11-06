#ifndef BOARD2D_H
#define BOARD2D_H

struct BoardPosition {
  int x;
  int y;
};

template<typename CellType> class Board2D {
  public:
    Board2D (int _height, int _width, CellType _defaultValue);
    CellType at(int x, int y);
    CellType at(BoardPosition position);
    void set(CellType value, int x, int y);
    void set(CellType value, BoardPosition position);
    void reset(int x, int y);
    void reset(BoardPosition position);
    void setAll(CellType value);
    void resetAll();
    int getWidth();
    int getHeight();
  private:
    CellType** board;
    CellType defaultValue;
    int width;
    int height;
};

#endif