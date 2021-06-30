#include "StickerSheet.h"
#include <vector>
#include <utility>

cs225::StickerSheet::StickerSheet	(const Image & picture, unsigned max) {
  _baseImage = new Image(picture);
  _size = max;
  _stickers = new Image*[_size];
  _position.push_back(std::make_pair(0, 0));
  for (int i = 0; i < _size; i++) {
    _stickers[i] = NULL;
    _position.push_back(std::make_pair(0, 0));
  }
}

void cs225::StickerSheet::_copy(const cs225::StickerSheet & other) {
  _baseImage = new Image(*other._baseImage);
  _size = other._size;
  _stickers = new Image*[_size];
  for (int i = 0; i < _size; i++) {
    _position.push_back(other._position[i]);
    if (other._stickers[i] != NULL) {
      _stickers[i] = new Image(*other._stickers[i]);
    } else {
      _stickers[i] = NULL;
    }
  }
}

void cs225::StickerSheet::_delete() {
  _position.clear();
  for (int i = 0; i < _size; i++) {
    if (_stickers[i] != NULL) {
      delete _stickers[i];
    }
  }
  delete[] _stickers;
  delete _baseImage;
  _stickers = NULL;
  _baseImage = NULL;
}


cs225::StickerSheet::~StickerSheet() {
  this->_delete();
}

cs225::StickerSheet::StickerSheet(const StickerSheet& other) {
  this->_copy(other);
}

const cs225::StickerSheet& cs225::StickerSheet::operator=(const cs225::StickerSheet & other) {
  this->_delete();
  this->_copy(other);
  return *this;
}

void cs225::StickerSheet::changeMaxStickers(unsigned max) {
  cs225::StickerSheet *copySheet = new cs225::StickerSheet(*this);
  this->_delete();
  _baseImage = new Image(*copySheet->_baseImage);
  _size = max;
  _stickers = new Image*[_size];
  for(int i = 0; i < _size; i++) {
    if (copySheet->getSticker(i) != NULL) {
      _stickers[i] = new Image(*copySheet->getSticker(i));
    } else {
      _stickers[i] = NULL;
    }
    _position.push_back(copySheet->_position[i]);
  }
  delete copySheet;
}

int cs225::StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  for (int i = 0; i < _size; i++) {
    if (_stickers[i] == NULL) {
      _stickers[i] = new Image(sticker);
      _position[i] = std::make_pair((unsigned int)x, (unsigned int)y);
      return i;
    }
  }
  return -1;
}

bool cs225::StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (_stickers[index] != NULL) {
    _position[index] = std::make_pair((int)x, (int)y);
    return true;
  } else {
    return false;
  }
}

void cs225::StickerSheet::removeSticker(unsigned index) {
  if (_stickers[index] != NULL) {
    delete _stickers[index];
    _stickers[index] = NULL;
    _position[index] = std::make_pair(0, 0);
  }
}

cs225::Image* cs225::StickerSheet::getSticker(unsigned index) {
  if ((int)index >= _size) {
    return NULL;
  } else {
    return _stickers[index];
  }
}

cs225::Image cs225::StickerSheet::render() const{
  for (int i = 0; i < _size; i++) {
    if (_stickers[i] != NULL) {
      unsigned int currWidth = _stickers[i]->width();
      unsigned int currHeight= _stickers[i]->height();
      for (unsigned int x = 0; x < currWidth; x++) {
        for (unsigned int y = 0; y < currHeight; y++) {
          unsigned int translateX = _position[i].first + x;
          unsigned int translateY = _position[i].second + y;
          cs225::HSLAPixel & new_pixel = _stickers[i]->getPixel(x, y);
          if (new_pixel.a > 0 && (translateX < _baseImage->width() && (translateY < _baseImage->height()))) {
            cs225::HSLAPixel & base_pixel = _baseImage->getPixel(translateX, translateY);
            base_pixel = new_pixel;
          }
        }
      }
    } else {

    }
  }
  return *_baseImage;
}
