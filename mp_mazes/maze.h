#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <stdlib.h>
#include <queue>
#include <assert.h>

enum { Right = 0, Down = 1, Left = 2, Up = 3 };
enum { No_Wall = 0, Right_Wall = 1, Down_Wall = 2, Both_Walls = 3 };

class SquareMaze {

  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    std::vector<int> solveMaze();
    cs225::PNG *drawMaze() const;
    cs225::PNG *drawMazeWithSolution();

  private:
    DisjointSets sets;
    vector<int> squares;
    int width;
    int height;
    int getIndex(int x, int y) const;
    int getX(int index) const;
    int getY(int index) const;
};