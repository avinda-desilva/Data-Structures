/* Your code here! */
#pragma once

#include "dsets.h"
#include "cs225/PNG.h"
#include <vector>
#include <stack>
#include <map>
#include <queue>

class SquareMaze {
  public:
    void makeMaze(int width, int height);
    void setWall(int x, int y, int dir, bool exists);
    bool canTravel(int x, int y, int dir) const;
    std::vector< int > solveMaze();
    cs225::PNG * drawMaze()	const;
    cs225::PNG * drawMazeWithSolution();

  private:
    DisjointSets _grid;
    std::vector<bool> _rightWall;
    std::vector<bool> _downWall;
    std::queue<std::pair<int, int>> _position;
    std::vector<int> _dirs;
    std::vector<std::vector<bool>> _hasVisited;
    std::vector<int> _lastRow;
    std::map<int, int> _path;
    int _width;
    int _height;
    int _size;
};
