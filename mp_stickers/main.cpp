#include "Image.h"
#include "StickerSheet.h"
int main() {
cs225::Image EmpireState, Sun, Illinois, Covid;
EmpireState.readFromFile("EmpireState.png");
Sun.readFromFile("Sun.png");
Illinois.readFromFile("i.png");
Covid.readFromFile("Covid.png");

cs225::StickerSheet output(EmpireState, 3);
Sun.scale(200, 200);
Illinois.scale(150, 150);
Covid.scale(600, 600);
output.addSticker(Sun, 0, 0);
output.addSticker(Illinois, 750, 400);
output.addSticker(Covid, 1300,300);

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
cs225::Image outputFile = output.render();
outputFile.writeToFile("myImage.png");
  return 0;
}
