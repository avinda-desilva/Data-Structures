#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  cs225::Image base; base.readFromFile("pictures/Sunrise.png");
  cs225::Image rocket;    rocket.readFromFile("pictures/Rocket.png");
  cs225::Image astro; astro.readFromFile("pictures/astronaut.png");
  cs225::Image spaceship; spaceship.readFromFile("pictures/Spaceship.png");
  cs225::Image label; label.readFromFile("pictures/More-You_Know.png");
  cs225::Image calvin; calvin.readFromFile("pictures/Calvin-Hobbes.png");

  cs225::StickerSheet sheet(base, 5);
  rocket.scale(2);
  sheet.addSticker(rocket, 300, 300);

  astro.scale(0.5);
  sheet.addSticker(astro, 200, 1300);
  spaceship.scale(0.5);
  sheet.addSticker(spaceship, base.width() / 2 - 110, base.height() / 2 - 250);
  label.scale(3.5);
  sheet.addSticker(label, 1900, 200);
  calvin.scale(base.width() / 2, base.height() / 2);
  sheet.addSticker(calvin, 0 + base.width() / 4, base.height() - calvin.height());
  base = sheet.render();
  base.writeToFile("myImage.png");


  return 0;
}
