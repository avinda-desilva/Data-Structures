
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"
#include <iostream>

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG png;
  png.readFromFile("Rose.png");
  FloodFilledImage image(png);
  //Call #1
  DFS fill_one(png, Point(100, 50), 0.2);
  MyColorPicker myColor;
  image.addFloodFill(fill_one, myColor);
  //Call #2
  DFS fill_two(png, Point(55, 117), 0.2);
  image.addFloodFill(fill_two, myColor);
  //Call #3
  DFS fill_three(png, Point(119, 153), 0.2);
  image.addFloodFill(fill_three, myColor);
  //Call #4
  DFS fill_four(png, Point(151, 107), 0.2);
  image.addFloodFill(fill_four, myColor);
  //Call #5
  DFS fill_five(png, Point(31, 142), 0.2);
  HSLAPixel green(123, 1, .5, 1);
  HSLAPixel l_blue(181, 1, .5, 1);
  GradientColorPicker leaf_color(green, l_blue, Point(png.width() / 2, png.height() / 2), png.height());
  image.addFloodFill(fill_five, leaf_color);
  //Call #6
  DFS fill_six(png, Point(94, 183), 0.2);
  image.addFloodFill(fill_six, leaf_color);
  //Call #7
  DFS fill_seven(png, Point(163, 149), 0.2);
  image.addFloodFill(fill_seven, leaf_color);
  //Call #8
  BFS bfs(png, Point(0, 0), 0.5);
  HSLAPixel red(0, 1, .5, 1);
  HSLAPixel orange(33, 1, .5, 1);
  GradientColorPicker color(red, orange, Point(0, 0), png.height());
  image.addFloodFill(bfs, color);


  Animation animation = image.animate(500);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
