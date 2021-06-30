#include <iostream>
#include "dsets.h"
#include "maze.h"
#include <cmath>
#include "cs225/PNG.h"
#include <ctime>


using namespace std;

int main()
{
  // Write your own main here
  cs225::HSLAPixel hot_pink(332, 1, .61, 1);
  srand(time(NULL));
  SquareMaze myMaze;

  int radius = 40;
  int width = 100;
  int height = 150;
  double center_x = width / 2 * 10;
  double center_y = height / 2 * 10;


  myMaze.makeMaze(width, height);
  cs225::PNG * mazeOutput = myMaze.drawMazeWithSolution();
  cs225::PNG * maze_copy = mazeOutput;
  
  for (int x = 0; x < width * 10 + 1; x++) {
    for (int y = 0; y < width * 10 + 1; y++)  {
      double center = sqrt((center_y - y) * (center_y - y) + (center_x - x) * (center_x - x));
      if (center >= radius * 10 - 1) {
        if ((center) >= radius * 10) {
          cs225::HSLAPixel & pixel = mazeOutput->getPixel(x, y);
          pixel = hot_pink;
        }
      }

    }
  }


  for (int x = width / 2; x < width * 10 + 1; x++) {
    for (int y = height / 2; y < width * 10 + 1; y++)  {
      double center = sqrt((height / 10 * 2 - y) * (height / 10 * 2 - y) + (width / 10 * 2 - x) * (width / 10 * 2 - x));
      if (center > radius * 15 - 1) {
        if (center > radius * 20) {
          cs225::HSLAPixel & pix = mazeOutput->getPixel(x, y);
          cs225::HSLAPixel & pixel = maze_copy->getPixel(x, y);
          pix = pixel;
        }
        else {
          cs225::HSLAPixel & pix = mazeOutput->getPixel(x, y);
          pix = hot_pink;
        }
      }
    }
  }




  mazeOutput->writeToFile("creative.png");
  delete mazeOutput;
  delete maze_copy;
  return 0;
}
