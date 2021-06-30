#include "Image.h"
#include <cmath>
#include <iostream>

void cs225::Image::lighten() {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.l <= 0.9) {
        pixel.l += 0.1;
      } else {
        pixel.l = 1.0;
      }
    }
  }
}

void cs225::Image::lighten(double amount) {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.l + amount <= 1.0) {
        pixel.l += amount;
      } else {
        pixel.l = 1.0;
      }
    }
  }
}

void cs225::Image::darken() {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.l >= 0.1) {
        pixel.l -= 0.1;
      } else {
        pixel.l = 0.0;
      }
    }
  }
}

void cs225::Image::darken(double amount) {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.l - amount >= 0.0) {
        pixel.l -= amount;
      } else {
        pixel.l = 0;
      }
    }
  }
}

void cs225::Image::saturate() {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.s <= 0.9) {
        pixel.s += 0.1;
      }
    }
  }
}

void cs225::Image::saturate(double amount) {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.s + amount <= 1.0) {
        pixel.s += amount;
      } else {
        pixel.s = 1;
      }
    }
  }
}

void cs225::Image::desaturate() {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.s >= 0.1) {
        pixel.s -= 0.1;
      }
    }
  }
}

void cs225::Image::desaturate(double amount) {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.s - amount >= 0.0) {
        pixel.s -= amount;
      } else {
        pixel.s = 0;
      }
    }
  }
}

void cs225::Image::grayscale() {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void cs225::Image::rotateColor(double degrees) {
  if (degrees > 360 || degrees < -360) {
    return;
  } else {
    double delta = remainder(degrees, 360);
    if (degrees < 0) {
      degrees += 360;
    }
    for (unsigned int x = 0; x < width(); x++) {
      for (unsigned int y = 0; y < height(); y++) {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);
        pixel.h = remainder(pixel.h + degrees, 360.0);
        if (pixel.h < 0) {
          pixel.h += 360;
        }
      }
    }
  }
}

void cs225::Image::illinify() {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.h >= 293 || pixel. h <= 113) {
        pixel.h = 11;
      } else
      pixel.h = 216;
    }
  }
}

void cs225::Image::scale(double factor) {
  PNG *newImage = new PNG(*this);
  double newWidth = newImage->width();
  double newHeight = newImage->height();
  this->resize(width() * factor, height() * factor);
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      cs225::HSLAPixel & newPixel = newImage->getPixel(x / (width() / newWidth), y / (height() / newHeight));
      pixel = newPixel;
    }
  }
  delete newImage;
}

void cs225::Image::scale(unsigned w, unsigned h) {
  PNG *newImage = new PNG(*this);
  unsigned int area = w * h;
  double pred_w = (double)h * ((double)width() / (double)height());
  double pred_h = (double)w * ((double)height() / (double)width());
  if ((pred_h * w) < area) {
    h = pred_h;
  } else if ((pred_w * h) < area) {
    w = pred_w;
  }
  double newWidth = newImage->width();
  double newHeight = newImage->height();
  this->resize(w, h);
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      cs225::HSLAPixel & newPixel = newImage->getPixel(x / (width() / newWidth), y / (height() / newHeight));
      pixel = newPixel;
      }
    }
    delete newImage;
  }
