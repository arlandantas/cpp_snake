#include "headers/Board2D.h"
#include "headers/SnakeGame.h"

template<typename CellType> Board2D<CellType>::Board2D(int _height, int _width, CellType _defaultValue) {
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
};
template<typename CellType> CellType Board2D<CellType>::at(int x, int y) {
  return board[y][x];
};
template<typename CellType> CellType Board2D<CellType>::at(BoardPosition position) {
  return at(position.x, position.y);
};
template<typename CellType> void Board2D<CellType>::set(CellType value, int x, int y) {
  board[y][x] = value;
}
template<typename CellType> void Board2D<CellType>::set(CellType value, BoardPosition position) {
  set(value, position.x, position.y);
}
template<typename CellType> void Board2D<CellType>::reset(int x, int y) {
  set(defaultValue, x, y);
}
template<typename CellType> void Board2D<CellType>::reset(BoardPosition position) {
  reset(position.x, position.y);
}
template<typename CellType> void Board2D<CellType>::setAll(CellType value) {
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      set(value, j, i);
    }
  }
}
template<typename CellType> void Board2D<CellType>::resetAll() {
  setAll(defaultValue);
}
template<typename CellType> int Board2D<CellType>::getWidth() {
  return width;
}
template<typename CellType> int Board2D<CellType>::getHeight() {
  return height;
}
template class Board2D<SnakeGame::BoardData>;
