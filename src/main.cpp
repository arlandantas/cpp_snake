#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "headers/Board2D.h"
#include "headers/SnakeGame.h"
#include "headers/KeyboardInput.h"

using namespace std;

int main(int argc, char const *argv[])
{
  int boardWidth = argc < 2 ? 10 : stoi(argv[1]);
  int boardHeight = argc < 3 ? 10 : stoi(argv[2]);
  srand((unsigned) time(NULL));

  SnakeGame *game = new SnakeGame(boardWidth, boardHeight);
  game->print(false);
  game->startTicking();
  
  map<int, SnakeGame::BoardData> inputDirections {
    { 119, SnakeGame::SnakeBodyUp },
    { 115, SnakeGame::SnakeBodyDown },
    { 97, SnakeGame::SnakeBodyLeft },
    { 100, SnakeGame::SnakeBodyRight }
  };
  bool keepRunning = true;
  while(keepRunning) {
    if (kbhit()) {
      int inputed = getchar();
      auto inputedDirection = inputDirections.find(inputed);
      if (inputedDirection == inputDirections.end()) {
        game->stopTicking();
        keepRunning = false;
        continue;
      }
      game->turn(inputedDirection->second);
    }
  }

  return 0;
}
