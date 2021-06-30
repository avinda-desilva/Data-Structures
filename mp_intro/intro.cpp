#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <ctime>
#include <vector>
#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG inputImage, outputImage;
  inputImage.readFromFile(inputFile);
  outputImage = cs225::PNG(inputImage);
  for (unsigned int x = 0; x < inputImage.width(); x++) {
    for (unsigned int y = 0; y < inputImage.height(); y++) {
      cs225::HSLAPixel & pixel = outputImage.getPixel(inputImage.width() - x - 1, inputImage.height() - y - 1);
      pixel = inputImage.getPixel(x, y);
    }
  }
  outputImage.writeToFile(outputFile);
  // TODO: Part 2
}

double distance(double x1, double y1, double x2, double y2) {
  double dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
  return dist;
}

//Creates a circle with a radius of 75 pixels and ring of 10 pixels with a random center.
void createCircle(cs225::PNG & image) {
  int hue = rand() % 360;
  int centerX = rand() % image.width();
  int centerY = rand() % image.height();
  int count = 0;
  for (unsigned int x = 0; x < image.width(); x++) {
    count++;
    for (unsigned int y = 0; y < image.height(); y++) {
      cs225::HSLAPixel & pixel = image.getPixel(x, y);
      pixel.s = 1.0;
      if (distance(centerX, centerY, x, y) > 0 && distance(centerX, centerY, x, y) < 200){
        pixel.l = 0.5;
        pixel.s = 1.0;
        pixel.h = remainder(pixel.h + hue, 360);
      }
      else if (distance(centerX, centerY, x, y) > 200 && distance(centerX, centerY, x, y) < 210){
        pixel.h = rand() % 360;
      }
    }
  }
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  std::vector<std::pair<int, int>> center;
  srand(time(NULL));
  cs225::PNG png(width, height);
  //Code to create checkerboard pattern
  for (unsigned int x = 0; x < png.width(); x++) {
    for (unsigned int y = 0; (y) < png.height(); y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      if(x % 16 >= 8) {
        if (y % 16 < 8) {
          pixel.l = 1;
        } else {
          pixel.l = 0;
        }
      } else if(x % 16 < 8) {
        if (y % 16 >= 8) {
          pixel.l = 1;
        } else {
          pixel.l = 0;
        }
      }
    }
  }
  //Creates 25 Circles with random centers.
  for (unsigned int i = 0; i < 20; i++) {
    createCircle(png);
  }
  return png;
}
