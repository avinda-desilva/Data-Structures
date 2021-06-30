/* Your code here! */
#include "maze.h"
#include <cmath>


void SquareMaze::makeMaze(int width, int height) {
  _width = width;
  _height = height;
  _size = _width  * _height;
  _grid.addelements(_size);
  _rightWall = std::vector<bool>(_size, true);
  _downWall = std::vector<bool>(_size, true);

  int wall_count = _size;
  while (wall_count > 1) {
    int x = rand() % _width;
    int y = rand() % _height;
    int wall_dir = rand() % 2;
    if (wall_dir == 0 && x < _width - 1) {
      if (_rightWall[x + y * _width] != false) {
        if(_grid.find(x + y * _width) != _grid.find(x + 1 + y * _width)) {
          _grid.setunion(x + y * _width, x + 1 + y * _width);
          setWall(x, y, wall_dir, false);
          wall_count--;
        }
      }
    } else if (wall_dir == 1 && y < _height - 1) {
      if (_downWall[x + y * _width] != false) {
        if(_grid.find(x + y * _width) != _grid.find(x + (y + 1) * _width)){
          _grid.setunion(x + y * _width, x + (y + 1) * _width);
          setWall(x, y, wall_dir, false);
          wall_count--;
        }
      }
    }
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if (x >= _width || y >= _height) {
    return;
  }
  if (dir == 0) {
    _rightWall[x + y * _width] = exists;
  } else if (dir == 1) {
    _downWall[x + y * _width] = exists;
  }
}

bool SquareMaze::canTravel(int x, int y , int dir) const {
  if (dir == 0) {
    if (x < _width) {
      if (_rightWall[_width * y + x] != true) {
        return true;
      }
    }
  }

  if (dir == 2) {
    if (x > 0) {
      if (_rightWall[_width * y + (x - 1)] != true) {
        return true;
      }
    }
  }

  if (dir == 1) {
    if (y < _height) {
      if (_downWall[_width * y + x] != true) {
        return true;
      }
    }
  }

  if (dir == 3) {
    if (y > 0) {
      if (_downWall[_width * (y - 1) + x] != true) {
        return true;
      }
    }
  }

  return false;
}

std::vector< int > SquareMaze::solveMaze() {
  std::vector<int> delta_idx;
  delta_idx.push_back(1);
  delta_idx.push_back(1);
  delta_idx.push_back(-1);
  delta_idx.push_back(-1);
  _hasVisited.resize(_width, std::vector<bool>(_height, false));
  while (!_position.empty()) {
    _position.pop();
  }
  _position.push(std::pair<int, int>(0, 0));
  _hasVisited[0][0] = true;

  while(!_position.empty()) {
    std::pair<int, int> position = _position.front();
    _position.pop();
    int x = position.first;
    int y = position.second;
    int maze_pos = (y * _width) + x;
    if (y == _height - 1) {
      _lastRow.push_back(maze_pos);
    }
    for(int i = 0; i <= 3; i++) {
      if (canTravel(x, y, i)) {
        if (i % 2 == 0) {
          if (!_hasVisited[x+delta_idx[i]][y] && x < _width) {
            _path.insert(std::pair<int, int> (maze_pos + (delta_idx[i] * 1), maze_pos));
            _hasVisited[x+delta_idx[i]][y] = true;
            _position.push(std::pair<int, int>(x+delta_idx[i], y));
          }
        } else {
          if (!_hasVisited[x][y+delta_idx[i]] && y < _height) {
            _path.insert(std::pair<int, int> (maze_pos + (delta_idx[i] * _width), maze_pos));
            _hasVisited[x][y+delta_idx[i]] = true;
            _position.push(std::pair<int, int>(x, y+delta_idx[i]));
          }
        }
      }
    }
  }
  if (!_dirs.empty()) {
    _dirs.clear();
  }
  int end = _width - 1;
  while(_lastRow[end] == _lastRow[end - 1]) {
    end -= 1;
  }
  int dist_from_start = _lastRow[end];
  while (dist_from_start != 0) {
    int prev = _path[dist_from_start];
    if (dist_from_start - prev == 1) {
      _dirs.push_back(0);
    }
    else if (dist_from_start - prev == _width) {
      _dirs.push_back(1);
    }
    else if (dist_from_start - prev == -1) {
      _dirs.push_back(2);
    }
    else if (dist_from_start - prev == _width * -1) {
      _dirs.push_back(3);
    }
    dist_from_start = prev;
  }
  reverse(_dirs.begin(), _dirs.end());
  return _dirs;
}


cs225::PNG * SquareMaze::drawMaze()	const {
  cs225::PNG* newMaze = new cs225::PNG(_width * 10 + 1 , _height * 10 + 1);
  int newWidth = (_width * 10) + 1;
  int newHeight = (_height * 10) + 1;

  for (int i = 10; i < newWidth; i++) {
    cs225::HSLAPixel & temp = newMaze->getPixel(i , 0);
    temp.l = 0.0;
  }

  for (int i = 0; i < newHeight; i ++) {
    cs225::HSLAPixel & temp = newMaze->getPixel(0 , i);
    temp.l = 0.0;
  }

  for (int rows = 0; rows < _width; rows++) {
    for (int colums = 0; colums < _height; colums++) {
      if (_rightWall[_width * colums + rows] != false) {
        for (int i = 0; i <= 10; i++) {
          int blackenPixelsX = 10 * (rows + 1);
          int blackenPixelsY = 10 * colums;
          cs225::HSLAPixel & temp = newMaze->getPixel(blackenPixelsX , blackenPixelsY + i);
          temp.l = 0.0;
        }
      }
      if (_downWall[_width * colums + rows] == true) {
        for (int i = 0; i <= 10; i++) {
          int blackenPixelsX2 = 10 * rows;
          int blackenPixelsY2 = 10 * (colums + 1);
          cs225::HSLAPixel & temp = newMaze->getPixel(blackenPixelsX2 + i , blackenPixelsY2);
          temp.l = 0.0;
        }
      }
    }
  }
  return newMaze;
}


cs225::PNG * SquareMaze::drawMazeWithSolution() {
  std::vector<std::pair<int, int>> delta_idx;
  delta_idx.push_back(std::pair<int, int>(1, 10));
  delta_idx.push_back(std::pair<int, int>(1, 10));
  delta_idx.push_back(std::pair<int, int>(-1, -10));
  delta_idx.push_back(std::pair<int, int>(-1, -10));
  int xPixel = 5;
          int yPixel = 5;

          cs225::PNG* newMaze = drawMaze();
          std::vector<int> temp = solveMaze();

          for (unsigned i = 0; i < temp.size(); i++) {
            /**
            for (int j = 0; j <= 3; j++) {
                if (j % 2 == 0 && temp[i] == j) {
                for (unsigned x = 0; x <= 10; x++) {
                  cs225::HSLAPixel & tempPixel = newMaze->getPixel(xPixel + (delta_idx[i].first * x), yPixel);
                  tempPixel.l = 0.5;
                  tempPixel.s = 1.0;
                  tempPixel.h = 0.0;
                  tempPixel.a = 1.0;
                }
                xPixel += delta_idx[i].second;
              }
              if (j % 2 == 1 && temp[i] == j) {
                for (unsigned x = 0; x <= 10; x++) {
                  cs225::HSLAPixel & tempPixel = newMaze->getPixel(xPixel , yPixel + (delta_idx[i].first * x));
                  tempPixel.l = 0.5;
                  tempPixel.s = 1.0;
                  tempPixel.h = 0.0;
                  tempPixel.a = 1.0;
                }
                yPixel += delta_idx[i].second;
              }
            }
            */
            if (temp[i] == 0) {
              for (unsigned x = 0; x <= 10; x++) {
                cs225::HSLAPixel & tempPixel = newMaze->getPixel(xPixel + x , yPixel);
                tempPixel.l = 0.5;
                tempPixel.s = 1.0;
                tempPixel.h = 0.0;
                tempPixel.a = 1.0;
              }
              xPixel = xPixel + 10;
            }
            if (temp[i] == 1) {
              for (unsigned x = 0; x <= 10; x++) {
                cs225::HSLAPixel & tempPixel = newMaze->getPixel(xPixel , yPixel + x);
                tempPixel.l = 0.5;
                tempPixel.s = 1.0;
                tempPixel.h = 0.0;
                tempPixel.a = 1.0;
              }
              yPixel = yPixel + 10;
            }
            if (temp[i] == 2) {
              for (unsigned x = 0; x <= 10; x++) {
                cs225::HSLAPixel & tempPixel = newMaze->getPixel(xPixel - x, yPixel);
                tempPixel.l = 0.5;
                tempPixel.s = 1.0;
                tempPixel.h = 0.0;
                tempPixel.a = 1.0;
              }
              xPixel = xPixel - 10;
          }
          if (temp[i] == 3) {
            for (unsigned x = 0; x <= 10; x++) {
              cs225::HSLAPixel & tempPixel = newMaze->getPixel(xPixel , yPixel - x);
              tempPixel.l = 0.5;
              tempPixel.s = 1.0;
              tempPixel.h = 0.0;
              tempPixel.a = 1.0;
            }
            yPixel = yPixel - 10;
          }
        }

        for (unsigned x = 1; x <= 9; x++) {
          cs225::HSLAPixel & tempPixel = newMaze->getPixel(xPixel - 5 + x, yPixel + 5);
          tempPixel.l = 1.0;
          tempPixel.s = 0.0;
          tempPixel.h = 0.0;
          tempPixel.a = 1.0;
        }
        return newMaze;
}
