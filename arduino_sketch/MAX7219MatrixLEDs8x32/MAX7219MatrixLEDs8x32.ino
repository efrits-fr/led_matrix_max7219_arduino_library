/*
 * Lisa Monpierre
 * EFRITS SAS
 *
 * MAX7219 Library
 * Dec. 2021
 */

#include "MAX7219MatrixLEDs8x32.h"

MAX7219MatrixLEDs8x32 matrix;

void setup()
{
  Serial.begin(9600);
  matrix.init();
}

void loop()
{
  matrix.setPixelRange(0, 0, 255);
  for (byte i = 0; i < 3; ++i)
    {
      byte x = random(matrix.getWidth());
      byte y = random(matrix.getHeight());

      matrix.setPixel(x, y, random(1));
    }
  matrix.displayScreen();
  delay(50);
}
