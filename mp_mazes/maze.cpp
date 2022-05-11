#include "maze.h"
#include <iostream>
using namespace std;
using namespace cs225;

SquareMaze::SquareMaze() {
    width = 0;
    height = 0;
}

void SquareMaze::makeMaze(int width, int height) {
    this->width = width;
    this->height = height;
    squares.resize(width*height, Both_Walls);
    sets.addelements(width*height);

    while(sets.size(0) != width * height) { 
        int rsquare = rand() % (width * height); 
        int rwall = rand() % 2; 
        if(rwall == 0) {
        if((rsquare+1)%width == 0 || sets.find(rsquare) == sets.find(rsquare+1)) continue;
        else {
            setWall(getX(rsquare), getY(rsquare), 0, false); 
            sets.setunion(rsquare, rsquare+1); 
        }
        }
    else { 
        if (rsquare+width >= width*height || sets.find(rsquare) == sets.find(rsquare+width)) continue;
        else {
            setWall(getX(rsquare), getY(rsquare), 1, false); // remove bottom wall
            sets.setunion(rsquare, rsquare+width); // union them into set
        }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (width == 0 || height == 0) return false;

    if (dir == Right) { 
        if (x < width-1 && squares.at(getIndex(x, y)) != Right_Wall && squares.at(getIndex(x, y)) != Both_Walls) return true;
    }
    if (dir == Down) { 
        if (y < height-1 && squares.at(getIndex(x, y)) != Down_Wall && squares.at(getIndex(x, y)) != Both_Walls) return true;
    }
    if (dir == Left) {
      if (x != 0 && squares.at(getIndex(x - 1, y)) != Right_Wall && squares.at(getIndex(x - 1, y)) != Both_Walls) return true;
    }

    if (dir == Up) { 
        if (y != 0 && squares.at(getIndex(x, y - 1)) != Down_Wall && squares.at(getIndex(x, y - 1)) != Both_Walls) return true;
    }

    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    int wall = squares.at(getIndex(x, y));
    if (dir == Right && exists) { 
        if (wall == No_Wall) squares.at(getIndex(x, y)) = Right_Wall;
        else if (wall == Down_Wall) squares.at(getIndex(x, y)) = Both_Walls;
    }
    else if (dir == Down && exists){ 
        if (wall == No_Wall) squares.at(getIndex(x, y)) = Down_Wall;
        else if (wall == Right_Wall) squares.at(getIndex(x, y)) = Both_Walls;
    }
    else if (dir == Right && !exists){ 
        if (wall == Right_Wall) squares.at(getIndex(x, y)) = No_Wall;
        else if (wall == Both_Walls) squares.at(getIndex(x, y)) = Down_Wall;
    }
    else if (dir == Down && !exists){ 
        if (wall == Down_Wall) squares.at(getIndex(x, y)) = No_Wall;
        else if (wall == Both_Walls) squares.at(getIndex(x, y)) = Right_Wall;
    }
}

vector<int> SquareMaze::solveMaze() {
    vector<int> length(width * height, -1); 
    vector<int> path(width * height, -1);
    vector<int> previous(width * height, -1);
    queue<int> q; 
    q.push(0);
    
    while(!q.empty()) {
        int index = q.front();
        int x = getX(index);
        int y = getY(index);
        if (canTravel(x, y, Right) && length[index + 1] < 0) {
            length[index + 1] = length[index] + 1;
            path[index + 1] = 0;
            previous[index + 1] = index;
            q.push(index + 1);
        }
        if (canTravel(x, y, Down) && length[index + width] < 0) {
            length[index + width] = length[index] + 1;
            path[index + width] = 1;
            previous[index + width] = index;
            q.push(index + width);
        }
        if (canTravel(x, y, Left) && length[index - 1] < 0) {
            length[index - 1] = length[index] + 1;
            path[index - 1] = 2;
            previous[index - 1] = index;
            q.push(index - 1);
        }
        if (canTravel(x, y, Up) && length[index - width] < 0) {
            length[index - width] = length[index] + 1;
            path[index - width] = 3;
            previous[index - width] = index;
            q.push(index - width);
        }
        q.pop();
    }
    int longestPathIndex = -1;
    int longestDist = -1;

    for (int i = getIndex(0, height - 1); i < width * height; i++) {
        if (length[i] > longestDist) {
            longestPathIndex = i;
            longestDist = length[i];
        }
    }
    vector<int> result;
    while (longestPathIndex > 0) {
        result.push_back(path[longestPathIndex]);
        longestPathIndex = previous[longestPathIndex];
    }
    reverse(result.begin(), result.end());
    return result;
}
int SquareMaze::getIndex(int x, int y) const { 
    return y * width + x;
}

int SquareMaze::getX(int index) const { 
    return index % width;
}

int SquareMaze::getY(int index) const { 
    return index / width;
}

PNG * SquareMaze::drawMaze() const {
    PNG* result = new PNG(width * 10 + 1, height * 10 + 1);
    for (int i = 0; i < width * 10 + 1; i++) { 
        if (i < 1 || i > 9) {
            HSLAPixel & pixel = result->getPixel(i, 0);
            pixel.l = 0;
        }
    }
    for (int i = 0; i < height * 10 + 1; i++) { 
        HSLAPixel & pixel = result->getPixel(0, i);
        pixel.l = 0;
    }
    for (int x = 0; x < width; x++) { 
        for (int y = 0; y < height; y++) {
            if (squares.at(getIndex(x, y)) == Right_Wall || squares.at(getIndex(x, y)) == Both_Walls) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = result->getPixel((x+1)*10, y*10+k);
                    pixel.l = 0;
                }
            }
            if (squares.at(getIndex(x, y)) == Down_Wall || squares.at(getIndex(x, y)) == Both_Walls) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = result->getPixel(x*10+k, (y+1)*10);
                    pixel.l = 0;
                }
            }
        }
    }
    return result;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* result = drawMaze();
    vector<int> solution = solveMaze();

    int x = 5;
    int y = 5;

    for (size_t i = 0; i < solution.size(); i++) {
        for (int j = 0; j < 10; j++) {
            HSLAPixel & pixel = result->getPixel(x, y);
            pixel.h = 0;
            pixel.s = 1;
            pixel.l = 0.5;
            pixel.a = 1;
            if (solution[i] == Right) x++;
            if (solution[i] == Down) y++;
            if (solution[i] == Left) x--;
            if (solution[i] == Up) y--;
        }
    }
    HSLAPixel & pixel = result->getPixel(x, y);
    pixel.h = 0;
    pixel.s = 1;
    pixel.l = 0.5;
    pixel.a = 1;

    x -= 4;
    y += 5;
    for (int i = 0; i < 9; i++) {
        HSLAPixel & pixel = result->getPixel(x + i, y);
        pixel.l = 1;
    }
    return result;
}
