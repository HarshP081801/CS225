#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>

#include <string>
using cs225::PNG;
using cs225::HSLAPixel;
using namespace std;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
cs225::PNG* original = new PNG();
original ->readFromFile(inputFile);
unsigned height = original->height();
unsigned width = original->width();
cs225::PNG* output = new PNG(width, height);
for (unsigned x = 0; x < width; x++) {
  for (unsigned y = 0; y < height; y++) {
    unsigned newX = (width - 1) - x;
    unsigned newY = (height - 1) - y;
    output->getPixel(x, y) = original->getPixel(newX, newY);
  }
}
output->writeToFile(outputFile);
delete original;
delete output;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
PNG png(width, height);
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
     HSLAPixel& curr = png.getPixel(x, y);
     unsigned radius_Sun = sqrt((x * x) + (y * y));
     unsigned radius_Mercury = sqrt((125 - x) * (125 - x) + (125 - y) * (125 -y));
     unsigned radius_Venus = sqrt((150 - x) * (150 - x) + (150 - y) * (150 -y));
     unsigned radius_Earth = sqrt((200 - x) * (200 - x) + (200 - y) * (200 -y));
     unsigned radius_Mars = sqrt((280 - x) * (280 - x) + (280 - y) * (280 -y));
     unsigned radius_Jupiter = sqrt((360 - x) * (360 - x) + (360 - y) * (360 -y));
     unsigned radius_Saturn = sqrt((450 - x) * (450 - x) + (450 - y) * (450 -y));
     unsigned radius_Uranus = sqrt((550 - x) * (550 - x) + (550 - y) * (550 -y));
     unsigned radius_Neptune = sqrt((650 - x) * (650 - x) + (650 - y) * (650 -y));
     curr.h = random() % 360;
     curr.s = .5;
     curr.l = random() % random();
     curr.a = 1;
      if (radius_Sun < 150) {
        curr.h = random() % 45;
        curr.l = .5;
      }
      if (radius_Mercury < 15) {
        curr.h = 0;
        curr.s = 1;
        curr.l = .25;
      }
      if (radius_Venus < 30) {
        curr.h = random() % 60;
        curr.s = 1;
        curr.l = .25;
      }
      if (radius_Earth < 60) {
        curr.h = random() % 170;
        curr.s = .45;
        curr.l = .45;
      }
      if (radius_Mars < 80) {
        curr.h = random() % 4;
        curr.s = .71;
        curr.l = .37;
      }
      if (radius_Jupiter < 100) {
        curr.h = random() % 25;
        curr.s = .54;
        curr.l = .36;
      }
      if (radius_Saturn < 90) {
        curr.h = random() % 25;
        curr.s = .54;
        curr.l = .6;
      }
      if (radius_Uranus < 80) {
        curr.h = random() % 193;
        curr.s = .54;
        curr.l = .6;
      }
      if (radius_Neptune < 70) {
        curr.h = 220;
        curr.s = random() % 2;
        curr.l = .3;
      }
      
    }
  }
  return png;
}