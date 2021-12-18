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
  matrix.init();
}

byte fx = 0;
byte fy = 0;
byte col = 1;

void loop()
{

    byte pixel = B10000000;
  
  for (byte indexDigit = 0; indexDigit < 8; ++indexDigit)
  {
    for (byte indexSegment = 0; indexSegment < 4; ++indexSegment)
    {
      while (pixel >= 1)
      {
        matrix.setPixelRange(indexDigit, indexSegment, pixel);
        matrix.displayScreen();
        delay(10);
        pixel >>= 1;
      }
      pixel = B10000000;
      matrix.setPixelRange(indexDigit, indexSegment, 0x00);
    }
  }
  /*
  for (byte i = 0; i < 1; ++i)
    {
      byte x = random(matrix.getWidth());
      byte y = random(matrix.getHeight());

      matrix.setPixel(x, y, random(0, 2));
    }
    *//*
    matrix.setPixel(fx % matrix.getWidth(), fy % matrix.getHeight(), 1);
    if (++fx == matrix.getWidth())
    {
      if (++fy == matrix.getHeight())
      {
        col = col > 0 ? 0 : 1;
      }
    }*/
  matrix.displayScreen();
  delay(50);
}
