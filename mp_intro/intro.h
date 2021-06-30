#pragma once

#include "cs225/PNG.h"

#include <string>

void rotate(std::string inputFile, std::string outputFile);
cs225::PNG myArt(unsigned int width, unsigned int height);
void createCircle(cs225::PNG & image, int centerX, int centerY);
double distance(double x1, double y1, double x2, double y2);
