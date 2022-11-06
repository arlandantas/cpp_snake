#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "headers/Board2D.h"
#include "headers/SnakeGame.h"

using namespace std;

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
